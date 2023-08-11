#pragma once
#include "mmu.h"

MMU::MMU(Cart* cart)
{
	this->ram = std::vector<u8>(0x10000);
	this->cart = cart;
}

//assuming no MBC
u8 MMU::read_byte(u16 addr)
{
	if (addr <= 0x7FFF) { return this->cart->rom[addr]; } 
	if (addr == 0xFF44) { return 0x90; }
	
	return this->ram[addr];
	
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
