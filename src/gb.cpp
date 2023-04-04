#include "GB.h"
#include "CPU.h"
#include "memory.h"
#include <stdint.h> 
#include <fstream>
#include <iostream>
#include <vector>

GB::GB(const char* file_path)
{
	this->cpu = new CPU();
	this->mmu = new MMU();
	this->ppu = new PPU();
	this->file_path = file_path;
}

void GB::StartEmulation()
{
	mmu->LoadROM(file_path);

	while (true)
	{
		uint8_t instruction = mmu->ReadMemory(cpu->PC);
		cpu->ExecuteInstruction(instruction);
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: dot_matrix <ROM>" << std::endl;
		return 1;
	}

	GB* gb = new GB(argv[1]);
	gb->StartEmulation();

	return 0;
}


