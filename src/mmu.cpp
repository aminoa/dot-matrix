#pragma once
#include "mmu.h"

bool TETRIS_PATCH = true;

MMU::MMU(Cart* cart)
{
	this->ram = std::vector<u8>(0x10000);
	this->cart = cart;
}

//assuming no MBC
u8 MMU::read_byte(u16 addr)
{
	//stub LY register to 0x90 - only needed for blargs test roms
	//if (addr == 0xFF44) { return 0x90; }

	// Tetris - disable all input
	// randomly either return 0x17 or 0xFF
	//if (addr == 0xFF00) 
	//{ 
	//	return rand() % 2 ? 0x17 : 0xFF; 
	//}


	if (addr <= 0x7FFF) { return this->cart->rom[addr]; } 
	
	return this->ram[addr];
	
}

void MMU::write_byte(u16 addr, u8 val)
{

	if (TETRIS_PATCH && addr == 0xFF80) { return; } // TODO: remove patch

	this->ram[addr] = val;
}

// little endian
u16 MMU::read_short(u16 addr)
{
	return this->read_byte(addr) | (this->read_byte(addr + 1) << 8);
}

void MMU::write_short(u16 addr, u16 val)
{
	this->write_byte(addr, u8(val & 0xFF));
	this->write_byte(addr + 1, u8((val & 0xFF00) >> 8));
}
