#pragma once
#include "ppu.h"
#include "cpu.h"
#include "mmu.h"
#include "consts.h"

struct Colors 
{
	u8 zero[3] = { 0xFF, 0xFF, 0xFF };
	u8 one[3] = { 0xC0, 0xC0, 0xC0 };
	u8 two[3] = { 0x60, 0x60, 0x60 };
	u8 three[3] = { 0x00, 0x00, 0x00 };
};

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
	u16 scy = mmu->read_byte(0xFF42);
	u16 scx = mmu->read_byte(0xFF43);
	
	// TODO: implement scrolling
	
	u16 bg_address = Memory::TILE_MAP_0;
	for (int x = 0; x < SCREEN_WIDTH; ++x)
	{
		// need to read tile address
		u8 tile_index = mmu->read_byte(bg_address);
		u16 tile_address = Memory::TILE_DATA_0 + (tile_index * 0x10);

		// read the tile data
		u8 tile_data[16];
		for (int i = 0; i < 16; ++i)
		{
			tile_data[i] = mmu->read_byte(tile_address + i);
		}

		// write tile data to framebuffer - copilot moment
		for (int i = 0; i < 8; ++i)
		{
			u8 color_index = 0;
			u8 bit1 = (tile_data[i * 2] >> (7 - x)) & 0x1;
			u8 bit2 = (tile_data[i * 2 + 1] >> (7 - x)) & 0x1;
			color_index |= bit1;
			color_index |= bit2 << 1;

			u8 color[3];
			switch (color_index)
			{
			case 0:
				color[0] = 0xFF;
				color[1] = 0xFF;
				color[2] = 0xFF;
				break;
			case 1:
				color[0] = 0xC0;
				color[1] = 0xC0;
				color[2] = 0xC0;
				break;
			case 2:
				color[0] = 0x60;
				color[1] = 0x60;
				color[2] = 0x60;
				break;
			case 3:
				color[0] = 0x00;
				color[1] = 0x00;
				color[2] = 0x00;
				break;
			}

			framebuffer[ly][x][0] = color[0];
			framebuffer[ly][x][1] = color[1];
			framebuffer[ly][x][2] = color[2];
		}
		
	}
}
