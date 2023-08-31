#pragma once
#include "CPU.h"
#include "MMU.h"

#include <string>
#include <vector>
#include <map>
#include <list>
#include <SDL2/SDL.h>


// https://github.com/jgilchrist/gbemu/blob/master/src/video/video.h

enum class VideoMode
{
	ACCESS_OAM,
	ACCESS_VRAM,
	HBLANK,
	VBLANK
};

const int CLOCKS_PER_HBLANK = 204; // Mode 0
const int CLOCKS_PER_SCANLINE_OAM = 80; // Mode 2 
const int CLOCKS_PER_SCANLINE_VRAM = 172; // Mode 3
const int CLOCKS_PER_SCANLINE = CLOCKS_PER_SCANLINE_OAM + CLOCKS_PER_SCANLINE_VRAM + CLOCKS_PER_HBLANK;
const int CLOCKS_PER_VBLANK = 4560; // Mode 1
const int SCANLINES_PER_FRAME = 144;
const int CLOCKS_PER_FRAME = CLOCKS_PER_SCANLINE * SCANLINES_PER_FRAME + CLOCKS_PER_VBLANK;

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

	void tick(u8 instruction_cycles);
	void draw_line(u8 ly);
	void draw_background(u8 ly);

	void draw_tile_line(u16 tile_short, u8 ly);

	CPU* cpu;
	MMU* mmu;

	u32 cycles;
	u32 framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH][3];

	VideoMode mode_set;

	std::map<int, std::vector<int>> color_map;

	u8 ly;
};