#include "mmu.h"

MMU::MMU(Cart* cart)
{
	memory = std::vector<u8>(0xFFFF);
	this->cart = cart;
}

u8 MMU::read(u16 addr)
{
	//assuming ROM only (no MBC)
	if (0x0000 <= addr <= 0x7FFF) 
	{
		return this->cart->rom[addr];
	}
}

void MMU::write(u16 addr, u8 val)
{
	//ignore special writes for now
	if (0x0000 <= addr <= 0x7FFF)
	{
		std::cout << "Unimplemented" << std::endl;
		return;
	}
	else if (0xA000 <= addr <= 0xBFFF)
	{
		std::cout << "Unimplemented" << std::endl;
		return;
	}

	this->memory[addr] = val;
}
