#include "gb.h"
#include <iostream>

GB::GB(const char* rom_path)
{
	this->rom_path = rom_path;
	this->cart = new Cart(rom_path);
	this->mmu = new MMU(cart);
	this->interrupt = new Interrupt(mmu);
	this->cpu = new CPU(mmu, interrupt);
}

void GB::run()
{
	std::cout << "Running " << this->cart->title << std::endl;

	while (true)
	{
		//clock, interrupts
				

		u8 instruction = this->mmu->read_byte(this->cpu->pc);
		cpu->execute(instruction);
		//cpu->pc++;
		//cpu->
	}
}
