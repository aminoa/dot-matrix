#pragma once
#include "cart.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "input.h"
#include "renderer.h"

class GB
{
public:
	GB(const char* rom_path);

	void run();

private:
	Cart* cart = nullptr;
	CPU* cpu = nullptr;
	MMU* mmu = nullptr;
	PPU* ppu = nullptr;
	Renderer* renderer = nullptr;
	const char* rom_path = nullptr;
	Input* input = nullptr;

};
