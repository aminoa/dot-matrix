#define _CRT_SECURE_NO_DEPRECATE
#include <stdint.h> 
#include "CPU.h"
#include "PPU.h"
#include "memory.h"
#include "mmu.h"
#include "interrupts.h"

class GB
{
public:
	GB(const char* filename);
	void Run();
	void Tick();

	CPU* cpu;
	MMU* mmu;
	PPU* ppu;
	Timer* timer;
	Interrupts* interrupts;

	const char* file_path;
};