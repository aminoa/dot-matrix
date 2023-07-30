#pragma once
#include <string>
#include "CPU.h"

#include <SDL2/SDL.h>

class PPU
{
public:
	PPU(CPU* cpu, std::string title);
	
	CPU* cpu;
	SDL_Window* window;

};