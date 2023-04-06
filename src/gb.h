#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "cpu.h"
#include "interrupts.h"
#include "mmu.h"
#include "ppu.h"
#include "timer.h"

#include <stdint.h> 

class GB
{
public:
	GB(const char* filename);
	void Run();
	//void Tick();

	CPU* cpu;
	MMU* mmu;
	PPU* ppu;
	Timer* timer;
	Interrupts* interrupts;

	const char* file_path;

};