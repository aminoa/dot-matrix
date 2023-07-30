#pragma once
#include "ppu.h"
#include "cpu.h"
#include <SDL2/SDL.h>

int SCALE = 2;
int SCREEN_WIDTH = 160;
int SCREEN_HEIGHT = 144;

PPU::PPU(CPU* cpu, std::string title)
{
	this->cpu = cpu;

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCALE * SCREEN_WIDTH, SCALE * SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}

	//SDL_surface* screenSurface = SDL_GetWindowSurface(window);
	//if (!window_surface)
	//{
	//	std::cout << "Failed to get the surface from the window\n";
	//	return -1;
	//}

	SDL_UpdateWindowSurface(window);

	SDL_Delay(50000);
}
