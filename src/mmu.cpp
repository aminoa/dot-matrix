#pragma once
#include "mmu.h"

MMU::MMU(Cart* cart)
{
	memory = std::vector<u8>(0x10000);
	this->cart = cart;
}

u8 MMU::read_byte(u16 addr)
{
	//assuming ROM only (no MBC)
	
	
	if (0x0000 <= addr && addr <= 0x7FFF)
	{
		return this->cart->rom[addr];
	} else 
	{
		return this->memory[addr];
	}


	if (addr == 0xFF44)
	{
		return 0x90;
	}
}

void MMU::write_byte(u16 addr, u8 val)
{
	//ignore special writes for now
	//if (0x0000 <= addr <= 0x7FFF)
	//{
	//	std::cout << "Unimplemented" << std::endl;
	//	return;
	//}
	//else if (0xA000 <= addr <= 0xBFFF)
	//{
	//	std::cout << "Unimplemented" << std::endl;
	//	return;
	//}

	this->memory[addr] = val;
}

// little endian
u16 MMU::read_short(u16 addr)
{
	return this->read_byte(addr) | (this->read_byte(addr + 1) << 8);
	// 8000 - 9FFF - VRAM
	// A000 - BFFF - External RAM
	// C000 - CFFF - WRAM
	// D000 - DFFF - also WRAM
	// E000 - FDFF - Prohibited Copy or WRAM
	// FE00 - FE9F - OAM
	// FF00 - FF7F- I/O Registers
	// FF80 - FFFE - High RAM
	// FFFF: Interrupt Enable reigster	
}

void MMU::write_short(u16 addr, u16 val)
{
	this->write_byte(addr, u8(val & 0xFF));
	this->write_byte(addr + 1, u8((val & 0xFF00) >> 8));
}
