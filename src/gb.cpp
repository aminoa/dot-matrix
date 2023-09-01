#pragma once
#include "gb.h"
#include "cpu.h"
#include "mmu.h"
#include "ppu.h"
#include "consts.h"
#include "renderer.h"
#include "input.h"

#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <chrono>

GB::GB(const char* rom_path)
{
	this->rom_path = rom_path;
	this->cart = new Cart(rom_path);
	this->mmu = new MMU(cart);
	this->cpu = new CPU(mmu);
	this->ppu = new PPU(cpu, mmu);
	this->input = new Input(mmu);
	this->renderer = new Renderer(cpu, mmu, ppu, cart->title);

	this->cycles = 0;
}

void GB::run()
{
	//std::fstream log_file;
	//log_file.open("../../../tools/gameboy-doctor/log.txt", std::ios::out);
	////log_file.clear();
	//int line_count = 1;

	while (true)
	{

		u8 instruction = this->mmu->read_byte(this->cpu->pc);
		std::string nmemonic = (instruction == 0xCB) ? CB_OPCODES[instruction].mnemonic : OPCODES[instruction].mnemonic;

		//A:00 F:11 B:22 C:33 D:44 E:55 H:66 L:77 SP:8888 PC:9999 PCMEM:AA,BB,CC,DD



		//if (TESTING)
		//{
		//	log_file << state << std::endl;
			//fmt::print("{} {}\n", line_count, state);
		//	line_count++;
		//}

		//doesn't differentiate between number of cycles - explanation for [0] indexing  
		u8 instruction_cycles = (instruction == 0xCB) ? CB_OPCODES[instruction].cycles[0] : OPCODES[instruction].cycles[0];
		cycles += instruction_cycles;

		cpu->execute(instruction);
		cpu->check_interrupts();
		ppu->tick(instruction_cycles);

		if (ppu->ly == 144)
		{
			renderer->render();
		}
		input->update_joypad();

		// Blarg test info
		//if (mmu->read_byte(0xff02) == 0x81)
		//{
		//	std::cout << mmu->read_byte(0xff01);
		//	mmu->write_byte(0xff02, 0x00);
		//}
	}
}
