#pragma once
#include "cart.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "joypad.h"

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
	const char* rom_path = nullptr;
	Joypad* joypad = nullptr;

};
