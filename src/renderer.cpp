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
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0, &window, &renderer);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetWindowResizable(window, SDL_TRUE);
	SDL_SetWindowTitle(window, title.c_str());
}

void Renderer::render()
{
	// need to throttle emulation here

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	//SDL_SetRenderTarget(renderer, viewport);


	// TEMP: generate random pixels for PPU framebuffer
	//for (int i = 0; i < SCREEN_HEIGHT; ++i)
	//{
	//	for (int j = 0; j < SCREEN_WIDTH; ++j)
	//	{
	//		ppu->framebuffer[i][j][0] = rand() % 255;
	//		ppu->framebuffer[i][j][1] = rand() % 255;
	//		ppu->framebuffer[i][j][2] = rand() % 255;
	//	}
	//}
	//
	for (int i = 0; i < SCREEN_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_WIDTH; ++j)
		{
			int red = ppu->framebuffer[i][j][0], blue = ppu->framebuffer[i][j][1], green = ppu->framebuffer[i][j][2];
			SDL_SetRenderDrawColor(renderer, red, blue, green, 255);
			SDL_RenderDrawPoint(renderer, j, i);
		}
	}
	
	SDL_RenderPresent(renderer);
	//SDL_RenderCopy(renderer, viewport, NULL, NULL);
}
