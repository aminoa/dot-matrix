#define _CRT_SECURE_NO_DEPRECATE
#include <stdint.h> 
#include "CPU.h"
#include "PPU.h"
#include "memory.h"
#include "mmu.h"

class GB
{
public:
	GB(const char* filename);
	void StartEmulation();

	CPU* cpu;
	MMU* mmu;
	PPU* ppu;

	const char* file_path;
};