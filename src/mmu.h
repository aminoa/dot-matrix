#pragma once
#include <stdint.h>
class MMU
{
public:
	MMU(const char* file_path);

	void LoadROM(const char* file_path);
	void write_value(uint16_t PC, uint8_t value);

	uint8_t memory[0xFFFF];
};

