#pragma once
#include <stdint.h>
class MMU
{
public:
	MMU();

	void LoadROM(const char* file_path);
	uint8_t ReadByte(uint16_t address);
	uint16_t ReadShort(uint16_t address);
	void WriteByte(uint16_t address, uint8_t value);

	uint8_t memory[0xFFFF];
};

