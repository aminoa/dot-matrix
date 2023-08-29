#pragma once
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"

class Renderer
{
public:
	Renderer(CPU* cpu, MMU* mmu, PPU* ppu, std::string title);
	void render();

	SDL_Window* window;
	SDL_Renderer* renderer;

	CPU* cpu;
	MMU* mmu;
	PPU* ppu;

private:
	//void point_set(int x, int y, int color);

};