#pragma once
#include "gb.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include <iostream>

GB::GB(const char* rom_path)
{
	this->rom_path = rom_path;
	this->cart = new Cart(rom_path);
	this->mmu = new MMU(cart);
	this->cpu = new CPU(mmu);
	this->ppu = new PPU(cpu, cart->title);
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
