#pragma once
#include "CPU.h"
#include "MMU.h"

#include <string>
#include <vector>
#include <map>
#include <list>
#include <SDL2/SDL.h>

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
	PPU(CPU* cpu, MMU* mmu);

	void tick();
	void draw_line(u8 ly);
	void draw_background(u8 ly);

	CPU* cpu;
	MMU* mmu;

	u32 cycle;
	u32 framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH][3];

	std::map<int, std::vector<int>> color_map;
};