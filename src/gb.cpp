#pragma once
#include "gb.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "consts.h"

#include <iostream>
#include <fmt/core.h>

GB::GB(const char* rom_path)
{
	this->rom_path = rom_path;
	this->cart = new Cart(rom_path);
	this->mmu = new MMU(cart);
	this->cpu = new CPU(mmu);
	this->ppu = new PPU(cpu, cart->title, mmu);
	this->joypad = new Joypad(mmu);
}

void GB::run()
{
	while (true)
	{
		//A:00 F:11 B:22 C:33 D:44 E:55 H:66 L:77 SP:8888 PC:9999 PCMEM:AA,BB,CC,DD
		std::string cpu_state = fmt::format("A:{:02X} F:{:02X} B:{:02X} C:{:02X} D:{:02X} E:{:02X} H:{:02X} L:{:02X} SP:{:04X} PC:{:04X}", 
			cpu->A, cpu->F, cpu->B, cpu->C, cpu->D, cpu->E, cpu->H, cpu->L, cpu->sp, cpu->pc);
		//std::string pc_mem = fmt::format("PCMEM:{:02X},{:02X},{:02X},{:02X}", 
		//	this->mmu->read_byte(cpu->pc), this->mmu->read_byte(cpu->pc + 1), this->mmu->read_byte(cpu->pc + 2), this->mmu->read_byte(cpu->pc + 3));

		u8 instruction = this->mmu->read_byte(this->cpu->pc);
		std::string nmemonic = (instruction == 0xCB) ? CB_OPCODES[instruction].mnemonic : OPCODES[instruction].mnemonic;
		std::string ly = fmt::format("LY:{:02X}", this->mmu->read_byte(0xFF44));
		//fmt::print("{} {} {}\n",cpu_state, nmemonic, ly);


		cpu->execute(instruction);
		
		//for now don't differentiate between number of cycles - explanation for [0] indexing  
		u8 instruction_cycles = (instruction == 0xCB) ? CB_OPCODES[instruction].cycles[0] : OPCODES[instruction].cycles[0];

		//cpu->check_timer(instruction_cycles);
		cpu->check_interrupts();
		//ppu->update();

		if (cpu->pc == 0x282a)
		{
			ppu->display_tile_data();
		}

		//ppu->tick();
		joypad->update_inputs();
	}
}
