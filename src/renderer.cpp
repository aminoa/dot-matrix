#pragma once
#include "renderer.h"
#include "ppu.h"
#include "consts.h"
#include <SDL2/SDL.h>

// Credits to NoobBoy, used lots of implementation details from there

Renderer::Renderer(CPU* cpu, MMU* mmu, PPU* ppu, std::string title)
{
	this->cpu = cpu;
	this->mmu = mmu;
	this->ppu = ppu;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);
	
	surface = SDL_GetWindowSurface(window);

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowResizable(window, SDL_TRUE);
	//SDL_SetWindowSize(window, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	SDL_SetWindowTitle(window, title.c_str());
}

void Renderer::render()
{
	// need to throttle emulation here

	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderClear(renderer);
	//SDL_SetRenderTarget(renderer, viewport);

	u32* pixels = (u32*)surface->pixels;

	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_WIDTH; ++j)
		{
			int red = ppu->framebuffer[i][j][0], blue = ppu->framebuffer[i][j][1], green = ppu->framebuffer[i][j][2];
			pixels[i * SCREEN_WIDTH + j] = SDL_MapRGB(surface->format, red, green, blue);
		}
	}

	SDL_UpdateWindowSurface(window);
}
