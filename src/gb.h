#pragma once
#include "cart.h"
#include "cpu.h"
#include "mmu.h"

class GB
{
public:
	GB(const char* rom_path);

	void run();

private:
	Cart* cart = nullptr;
	CPU* cpu = nullptr;
	MMU* mmu = nullptr;
	const char* rom_path = nullptr;
};
