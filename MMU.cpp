#include "MMU.h"

MMU::MMU()
{
	for (int i = 0; i < 0xFFFF; ++i)
	{
		memory[i] = 0;
	}
}

void MMU::write_value(uint16_t PC, uint8_t value)
{
	memory[PC] = value;
}
