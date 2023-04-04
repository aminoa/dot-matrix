#pragma once
#include <stdint.h>
class MMU
{
public:
	MMU();

	void LoadROM(const char* file_path);
	uint8_t ReadMemory(uint16_t address);

	uint8_t memory[0xFFFF];
};

