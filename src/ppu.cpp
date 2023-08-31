#pragma once
#include "ppu.h"
#include "cpu.h"
#include "mmu.h"
#include "consts.h"

#include <map>


PPU::PPU(CPU* cpu, MMU* mmu)
{
	this->cpu = cpu;
	this->mmu = mmu;
	this->cycle = 0x0;

	//// initialize framebuffer
	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_WIDTH; ++j)
		{
			framebuffer[i][j][0] = 0x0;
			framebuffer[i][j][1] = 0x0;
			framebuffer[i][j][2] = 0x0;
		}
	}

	color_map[0] = { 0xFF, 0xFF, 0xFF };
	color_map[1] = { 0xC0, 0xC0, 0xC0 };
	color_map[2] = { 0x60, 0x60, 0x60 };
	color_map[3] = { 0x00, 0x00, 0x00 };
}

void PPU::tick()
{
	this->cycle++;

	u8 lx = this->cycle % 114; // 114 cycles per line
	u8 ly = (this->cycle / 114) % 154; // 154 lines per frame

	mmu->write_byte(Memory::LY, ly);
	u8 stat = mmu->read_byte(Memory::STAT);

	// LYC compare and interrupt

	// Mode 2 - OAM search
	if (lx < 20 && ly < 144)
	{
		stat |= Stat::MODE_OAM;
		if (stat & Stat::OAM_INTERRUPT)
		{
			cpu->mark_interrupt(Interrupt::STAT);
		}
	}

	// Mode 3 - Drawing Pixels
	if (lx == 20 && ly < 144)
	{
		stat |= Stat::MODE_VRAM;
		draw_line(ly);
	}

	// HBlank
	else if (lx == 63 && ly < 144)
	{
		stat |= Stat::MODE_HBLANK;
	}

	else if (lx == 0 && ly == 144)
	{
		stat |= Stat::MODE_VBLANK;
		cpu->mark_interrupt(Interrupt::VBLANK);
	}

	mmu->write_byte(Memory::STAT, stat);
}

void PPU::draw_line(u8 ly)
{
	draw_background(ly);
	//draw_window(ly);
}

void PPU::draw_background(u8 ly)
{
	u16 scx = mmu->read_byte(Memory::SCROLL_X);
	u16 scy = mmu->read_byte(Memory::SCROLL_Y);
	u8 lcdc = mmu->read_byte(Memory::LCDC);
	
	// TODO: implement scrolling
	int bg_map_start_address = (lcdc & LCDC::BG_TILE_MAP_SELECT) ? Memory::TILE_MAP_1 : Memory::TILE_MAP_0;
	int tile_start_address = (lcdc & LCDC::BG_WINDOW_TILE_DATA_SELECT) ? Memory::TILE_DATA_1 : Memory::TILE_DATA_0;

	// reading 20 tiles x 8 bytes = 160 (width)
	for (int i = 0; i < 20; ++i)
	{
		// get tile 
		u8 tile_number = mmu->read_byte(tile_start_address + i); //ex. 2F
		u16 tile_data_address = tile_start_address + tile_number * 0x10; // ex. 82F0

		// 16 bytes of entire tile data, ex. 0F08 FFF8 FF00 FF02 FF00 FF40 FF02 FF00 
		// need to read 2 bytes for the tile data corresponding to the current line
		
		u8 tile_data[16];
		for (int j = 0; j < 16; ++j)
		{
			tile_data[j] = mmu->read_byte(tile_data_address + j);
		}

		u16 y_offset = (ly % 8) * 2; //byte offset ex. 0-1, 2-3, 4-5, 6-7, 8-9, 10-11, 12-13, 14-15

		// reading 8 pixels from the tile
		for (int j = 0; j < 8; ++j)
		{
			// for one tile
			u8 low_byte = tile_data[y_offset]; //ex. 0x0F
			u8 high_byte = tile_data[y_offset + 1]; // ex. 0x08

			// get the pixel color
			u8 color_bit = ((low_byte >> (7 - j)) & 0x1) | (((high_byte >> (7 - j)) & 0x1) << 1);

			framebuffer[ly][i * 8 + j][0] = color_map[color_bit][0];
			framebuffer[ly][i * 8 + j][1] = color_map[color_bit][1];
			framebuffer[ly][i * 8 + j][2] = color_map[color_bit][2];
		}
	}

	for (int x = 0; x < SCREEN_WIDTH; ++x)
	{
		// only want to render the top line into the framebuffer
	}
}
