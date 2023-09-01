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
	this->cycles = 0x0;

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
	
	mode_set = VideoMode::ACCESS_OAM;
	ly = 0;
}

void PPU::tick(u8 instruction_cycles)
{
	this->cycles += instruction_cycles;
	u8 stat = mmu->read_byte(Memory::STAT);

	// TODO: LYC compare and interrupt
	
	switch (mode_set)
	{
	case VideoMode::ACCESS_OAM: 
		if (cycles >= CLOCKS_PER_SCANLINE_OAM)
		{
			cycles %= CLOCKS_PER_SCANLINE_OAM;
			mode_set = VideoMode::ACCESS_VRAM;

			stat |= Stat::MODE_OAM;
			if (stat & Stat::OAM_INTERRUPT)
			{
				cpu->mark_interrupt(Interrupt::STAT);
			}
		}
		break;
	case VideoMode::ACCESS_VRAM:
		if (cycles >= CLOCKS_PER_SCANLINE_VRAM)
		{
			cycles %= CLOCKS_PER_SCANLINE_VRAM;
			mode_set = VideoMode::HBLANK;

			stat |= Stat::MODE_VRAM;

			//TODO: implement LYC compare
		}
	case VideoMode::HBLANK:
		if (cycles >= CLOCKS_PER_HBLANK)
		{
			draw_line(ly);
			ly += 1;

			cycles %= CLOCKS_PER_HBLANK;

			if (ly == 144)
			{
				mode_set = VideoMode::VBLANK;
			}

			stat |= Stat::MODE_HBLANK;
			if (stat & Stat::HBLANK_INTERRUPT)
			{
				cpu->mark_interrupt(Interrupt::STAT);
			}
		}
		break;
	case VideoMode::VBLANK:
		if (cycles >= CLOCKS_PER_VBLANK)
		{
			cycles %= CLOCKS_PER_VBLANK;
			ly += 1;

			if (ly == 154)
			{
				mode_set = VideoMode::ACCESS_OAM;
				ly = 0;
			}

			stat |= Stat::MODE_VBLANK;
			if (stat & Stat::VBLANK_INTERRUPT)
			{
				cpu->mark_interrupt(Interrupt::VBLANK);
			}
		}
		break;
	}

	mmu->write_byte(Memory::LY, ly);
	mmu->write_byte(Memory::STAT, stat);
}

void PPU::draw_line(u8 ly)
{
	draw_background(ly);
	//draw_window(ly);
}

// https://github.com/jgilchrist/gbemu/blob/master/src/video/video.cc - referenced this
void PPU::draw_background(u8 ly)
{
	u16 scx = mmu->read_byte(Memory::SCROLL_X);
	u16 scy = mmu->read_byte(Memory::SCROLL_Y);
	u8 lcdc = mmu->read_byte(Memory::LCDC);
	
	// TODO: implement scrolling

	int tile_map_address = (lcdc & LCDC::BG_TILE_MAP_SELECT) ? Memory::TILE_MAP_1 : Memory::TILE_MAP_0;
	int tile_start_address = (lcdc & LCDC::BG_WINDOW_TILE_DATA_SELECT) ? Memory::TILE_DATA_1 : Memory::TILE_DATA_0;
	//int tile_start_address = 0x8800; // TEMP: dr. mario 

	for (int x = 0; x < SCREEN_WIDTH; ++x)
	{
		// getting the tile position
		int tile_x = x / 8;
		int tile_y = ly / 8;

		// getting the sub tile pixel positions
		int tile_pixel_x = x % 8;
		int tile_pixel_y = ly % 8;

		int tile_index = tile_y * 0x20 + tile_x;
		u16 tile_id_address = tile_map_address + tile_index;
		u8 tile_id = mmu->read_byte(tile_id_address);

		// TODO: account for different tile offsets
		u16 tile_line_data_start_addr = tile_start_address + (tile_id * 0x10) + (tile_pixel_y * 2);

		u8 low_byte = mmu->read_byte(tile_line_data_start_addr);
		u8 high_byte = mmu->read_byte(tile_line_data_start_addr + 1);

		// need to get the color id from the tile data

		int color_bit = ((low_byte >> (7 - tile_pixel_x)) & 0x1) | (((high_byte >> (7 - tile_pixel_x)) & 0x1) << 1);
		framebuffer[ly][x][0] = color_map[color_bit][0];
		framebuffer[ly][x][1] = color_map[color_bit][1];
		framebuffer[ly][x][2] = color_map[color_bit][2];

		
	}
}

// draws 8 bits of the tile line starting from position x at current line y
void PPU::draw_tile_line(i16 tile_id, u16 x, u16 y)
{
	// TODO: account for 0x8800 tile data
	u16 addr = Memory::TILE_DATA_0 + tile_id * 0x10 + y * 2;
	u8 low_byte = mmu->read_byte(addr);
	u8 high_byte = mmu->read_byte(addr + 1);

	// draw 8 pixels
	for (int i = 0; i < 8; ++i)
	{
		u8 color_bit = (((high_byte >> (7 - i)) & 0x1) << 1) | ((low_byte >> (7 - i)) & 0x1);

		framebuffer[y][x + i][0] = color_map[color_bit][0];
		framebuffer[y][x + i][1] = color_map[color_bit][1];
		framebuffer[y][x + i][2] = color_map[color_bit][2];
	}
}

//void PPU::debug_draw_tile_map()
//{
//	//for (int y = 0; y < 32; ++y)
//	//{
//	//	for (int x = 0; x < 32; ++x)
//	//	{
//	//		u8 tile_id = mmu->read_byte(tile_map_address + y * 32 + x);
//	//		draw_tile_line(tile_id, x * 8, y * 8);
//	//	}
//	//}
//
//	u8 tile_map_addr = 0x8000;
//
//
//
//}