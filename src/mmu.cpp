#pragma once
#include "mmu.h"
#include "ppu.h"
//#include "cpu.h"
//#include "ppu.h"
//#include "timer.h"

#include <iostream>

MMU::MMU()
{
	for (int i = 0; i < 0xFFFF; ++i)
	{
		memory[i] = 0;
	}
}

void MMU::LoadROM(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (!file)
	{
		std::cout << "Unable to open file. Exiting...";
		exit(1);
	}

	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[file_size];
	fread(buffer, file_size, 1, file);
	fclose(file);

	for (int i = 0; i < file_size; ++i)
	{
		memory[i] = buffer[i];
	}

	delete[] buffer;
}

uint8_t MMU::ReadByte(uint16_t address)
{

	if (address == 0xFF00)
	{
		//joypad
	}

	if (address == 0xFF04) { return timer.div; }
	if (address == 0xFF05) { return timer.tima; }
	if (address == 0xFF06) { return timer.tma; }
	if (address == 0xFF07) { return timer.tac; }

	return memory[address];
}

uint16_t MMU::ReadShort(uint16_t address)
{
	//little endian
	return ReadByte(address) | (ReadByte(address + 1) << 8);
}

void MMU::WriteByte(uint16_t address, uint8_t value)
{

	//copying sprites to OAM
	//disabling rom
	//timers

	if (address >= 0xFEA0 || address < 0xFE00)
	{
		return;
	}

	else if (address == 0xFF04) { timer.div = 0; }
	else if (address == 0xFF05) { timer.tima = value; }
	else if (address == 0xFF06) { timer.tma = value; }
	else if (address == 0xFF07) { timer.tac = value;}

	// //color palette
	//need to check updating tile/sprite 
	//switchable ROM banks

	memory[address] = value;
}

void MMU::WriteShort(uint16_t address, uint16_t value)
{
	WriteByte(address, value & 0xFF);
	WriteByte(address + 1, value >> 8);
}
