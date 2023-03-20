#pragma once
#include <stdint.h>
class MMU
{
public:
	MMU();

	void write_value(uint16_t PC, uint8_t value);

	uint8_t memory[0xFFFF];
};

