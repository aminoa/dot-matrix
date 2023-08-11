#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>

#include "CPU.h"
#include "MMU.h"

struct Sprite
{
	u8 y;
	u8 x;
	u8 tile;	

	union {
		u8 flags;
		struct {
			u8 unused : 4;
			u8 palette : 1;
			u8 x_flip : 1;
			u8 y_flip : 1;
			u8 priority : 1;
		};
	};
};


class PPU
{
public:
	PPU(CPU* cpu, std::string title, MMU* mmu);

	void display_tile_data();

	CPU* cpu;
	MMU* mmu;

	u8 cycle;

	// RGBA is 64 bits
	std::vector<std::vector<u64>> framebuffer;

	// SDL Components
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* surface;
};