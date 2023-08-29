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

enum Modes
{
	OAM = 2,
	VRAM = 3,
	HBlank = 0,
	VBlank = 1
};

namespace LCDC
{
	const u8 ENABLED = 1 << 7;
	const u8 WINDOW_TILE_MAP = 1 << 6;
	const u8 WINDOW_ENABLED = 1 << 5;
	const u8 BG_WINDOW_TILE_DATA = 1 << 4;
	const u8 BG_TILE_MAP = 1 << 3;
	const u8 OBJ_SIZE = 1 << 2;
	const u8 OBJ_ENABLED = 1 << 1;
	const u8 BG_ENABLED = 1 << 0;
}

namespace Stat
{
	const u8 LYC_INTERRUPT = 1 << 6;
	const u8 OAM_INTERRUPT = 1 << 5;
	const u8 VBLANK_INTERRUPT = 1 << 4;
	const u8 HBLANK_INTERRUPT = 1 << 3;
	const u8 LYC_LY_FLAG = 1 << 2;
	const u8 MODE_FLAG = 1 << 1 | 1 << 0;

	const u8 MODE_HBLANK = 0x0;
	const u8 MODE_VBLANK = 0x1;
	const u8 MODE_OAM = 0x2;
	const u8 MODE_VRAM = 0x3;
}

class PPU
{
public:
	PPU(CPU* cpu, MMU* mmu);

	//void display_tile_data();
	void tick();
	//void draw_line(i32 ly);
	void display_tile_data();
	void update_frame();

	CPU* cpu;
	MMU* mmu;

	u32 cycle;
	u32 framebuffer[SCREEN_HEIGHT][SCREEN_WIDTH][4];
};