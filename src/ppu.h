#pragma once
#include <string>
#include <SDL2/SDL.h>
#include <vector>

#include "CPU.h"
#include "MMU.h"

//Bit7   BG and Window over OBJ (0=No, 1=BG and Window colors 1-3 over the OBJ)
//Bit6   Y flip(0 = Normal, 1 = Vertically mirrored)
//Bit5   X flip(0 = Normal, 1 = Horizontally mirrored)
//Bit4   Palette number** Non CGB Mode Only** (0 = OBP0, 1 = OBP1)
//Bit3   Tile VRAM - Bank * *CGB Mode Only * *(0 = Bank 0, 1 = Bank 1)
//Bit2 - 0 Palette number * *CGB Mode Only * *(OBP0 - 7)

//// LCD control regs
//namespace LCDC
//{
//	const u8 enable = 1 << 7;
//	const u8 window_tile_map = 1 << 6;
//	const u8 window_enable = 1 << 5;
//	const u8 bg_window_tile_data = 1 << 4;
//	const u8 bg_tile_map = 1 << 3;
//	const u8 sprite_size = 1 << 2;
//	const u8 sprite_enable = 1 << 1;
//	const u8 bg_enable = 1 << 0;
//};
//
//// LCD status regs
//namespace Stat
//{
//	const u8 LYC_interrupt = 1 << 6;
//	const u8 OAM_interrupt = 1 << 5;
//	const u8 VBlank_interrupt = 1 << 4;
//	const u8 HBlank_interrupt = 1 << 3;
//	const u8 LYC_coincidence = 1 << 2;
//	const u8 mode = 0x03;
//
//	const u8 HBlank = 0;
//	const u8 VBlank = 1;
//	const u8 OAM = 2;
//	const u8 VRAM = 3;
//}

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
	
	Sprite sprite_ram[40];
	u8 framebuffer[160][144][3];
	
	void update(u8 cycles);

	void draw_frame();

	CPU* cpu;
	MMU* mmu;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	u8 cycle;

	int cycle;
};