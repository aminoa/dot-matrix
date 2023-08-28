#pragma once
#include "ppu.h"
#include "cpu.h"
#include "mmu.h"
#include "consts.h"
//
#include <SDL2/SDL.h>

u16 scale = 2;

PPU::PPU(CPU* cpu, std::string title, MMU* mmu)
{
	this->cpu = cpu;
	this->mmu = mmu;
	this->cycle = 0x0;

	SDL_InitSubSystem(SDL_INIT_VIDEO);
}

void PPU::tick()
{
	this->cycle++;

	u8 lx = this->cycle % 114; // 114 cycles per line
	u8 ly = (this->cycle / 114) % 154; // 154 lines per frame
	mmu->write_byte(Memory::LY, ly);
	u8 stat = mmu->read_byte(Memory::STAT);

	// LYC compare and interrupt

	// OAM search
	if (lx < 20 && ly < 144)
	{
		stat |= Stat::MODE_OAM;
		if (stat & Stat::OAM_INTERRUPT)
		{
			//cpu->request_interrupt(Interrupt::LCD_STAT);
			//cpu->trigger_interrupt(Interrupt::LCD);
		}
	}

	// Rendering now
	if (lx == 20 && ly < 144)
	{
		stat |= Stat::MODE_VRAM;
		//if (ly == 0) { SDL_RenderClear(renderer); }
		//draw_line(ly);
	}

	// HBlank
	else if (lx == 63 && ly < 144)
	{
		stat |= Stat::MODE_HBLANK;
	}

	else if (lx == 0 && ly == 144)
	{
		stat |= Stat::MODE_VBLANK;
		//cpu->trigger_interrupt(Interrupt::VBLANK);
	}

	mmu->write_byte(Memory::STAT, stat);
}

void PPU::display_tile_data()
{
}

void PPU::update_frame()
{

}