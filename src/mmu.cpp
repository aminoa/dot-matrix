#include "mmu.h"

MMU::MMU(Cart* cart)
{
	memory = std::vector<u8>(0xFFFF);
	this->cart = cart;

	// TODO: map cart rom to memory
}

// 8000 - 9FFF - VRAM
// A000 - BFFF - External RAM
//

u8 MMU::read_byte(u16 addr)
{
	//assuming ROM only (no MBC)
	if (0x0000 <= addr <= 0x7FFF) 
	{
		return this->cart->rom[addr];
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
	this->write_byte(addr, val & 0xFF);
	this->write_byte(addr, val >> 8);
}
