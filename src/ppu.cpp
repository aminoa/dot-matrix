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

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH * scale, SCREEN_HEIGHT * scale, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetScale(renderer, scale, scale);

	//SDL_UpdateTexture(this->hw_buffer, NULL, this->framebuffer->pixels, this->framebuffer->pitch);
	//SDL_RenderCopy(this->hw_renderer, this->hw_buffer, NULL, NULL);
	//SDL_RenderPresent(this->hw_renderer);
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
			cpu->trigger_interrupt(Interrupt::LCD);
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
		cpu->trigger_interrupt(Interrupt::VBLANK);
	}

	mmu->write_byte(Memory::STAT, stat);
}

void PPU::display_tile_data()
{
	
	 //for one tile, read 16 bytes from VRAM
	//std::vector<u8> tile;
	////for (int i = 0; i < 16 * 0xFF; i += 0xFF)
	////{
	////	tile[i] = mmu->read_byte(0x8000 + i);
	////}

	//// decode the 2bpp data 
	//for (int i = 0; i < 16; ++i)
	//{
	//	for (int j = 0; j < 8; ++j)
	//	{
	//		u8 color = 0;
	//		u8 bit1 = (tile[i * 2] >> (7 - j)) & 1;
	//		u8 bit2 = (tile[i * 2 + 1] >> (7 - j)) & 1;
	//		color = bit1 | (bit2 << 1);

	//		//write the pixel to the framebuffer
	//		framebuffer[i][j] = color;

	//	}
	//}

	// draw the framebuffer onto the SDL surface
	//for (int i = 0; i < 16; ++i)
	//{
	//	for (int j = 0; j < 8; ++j)
	//	{
	//		u8 color = framebuffer[i][j];
	//		SDL_Rect rect = { (i % 16) * 8 + j, (i / 16) * 8, 1, 1 };
	//		SDL_FillRect(surface, &rect, color);
	//	}
	//}
}

// this only handles copying the framebuffer to the SDL Surface, still need to update it first
void PPU::update_frame()
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			int color = framebuffer[y][x];
			SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 0xFF);
			SDL_RenderDrawPoint(renderer, x, y);
		}
	}
	
	SDL_RenderPresent(renderer);
}