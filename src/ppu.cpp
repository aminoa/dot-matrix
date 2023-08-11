#pragma once
#include "ppu.h"
#include "cpu.h"
#include "mmu.h"
#include "consts.h"
//
#include <SDL2/SDL.h>
//
//
//enum Modes
//{
//	OAM = 2,
//	VRAM = 3,
//	HBlank = 0,
//	VBlank = 1
//};
//
//

PPU::PPU(CPU* cpu, std::string title, MMU* mmu)
{
	this->cpu = cpu;
	this->mmu = mmu;
	this->cycle = 0;

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	
	this->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	SDL_SetWindowSize(window, SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4);

	this->framebuffer = std::vector<std::vector<u64>>(SCREEN_WIDTH, std::vector<u64>(SCREEN_HEIGHT, 0));
}

// test framebuffer by drawing all tiles 
void PPU::display_tile_data()
{
	// 0x8000 - 0x8FFF
	for (int i = 0; i < 8; i++) 
	{
		u16 tile_data = mmu->read_short(0x8000 + i);
	}

}
