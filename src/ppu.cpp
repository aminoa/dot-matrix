#pragma once
#include "ppu.h"
#include "cpu.h"
#include "mmu.h"

#include <SDL2/SDL.h>

int SCREEN_WIDTH = 160;
int SCREEN_HEIGHT = 144;

enum Modes
{
	OAM = 2,
	VRAM = 3,
	HBlank = 0,
	VBlank = 1
};


PPU::PPU(CPU* cpu, std::string title, MMU* mmu)
{
	this->cpu = cpu;
	this->mmu = mmu;
	this->cycle = 0;

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);	

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	SDL_SetWindowSize(window, SCREEN_WIDTH * 4, SCREEN_HEIGHT * 4);
}

void PPU::update(u8 cycles)
{
	cycle += cycles;

	u8 mode = mmu->read_byte(0xFF41) & 0x03;

	switch (mode)
	{
	case Modes::OAM: process_oam(); break;
	case Modes::VRAM: process_vram(); break;
	case Modes::HBlank: process_hblank(); break;
	case Modes::VBlank: process_vblank(); break;
	}
}
