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
	void WriteShort(uint16_t address, uint16_t value);

	uint8_t memory[0xFFFF];

	bool isHalted = false;

	struct clock {
		int t = 0;
		int t_instr = 0;
	} clock;

	struct timer {
		uint16_t div = 0;
		uint8_t tima = 0;
		uint8_t tma = 0;
		uint8_t tac = 0;
	} timer;

};

