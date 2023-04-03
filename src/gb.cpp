#include "GB.h"
#include "CPU.h"
#include "memory.h"
#include <stdint.h> 
#include <fstream>
#include <iostream>
#include <vector>

GB::GB(const char* filename)
{
	cpu = new CPU();
	mmu = new MMU(filename);
	ppu = new PPU();

}

void GB::StartEmulation()
{
	//CPU has a value for the PC, calls on MMU to get value in address, then executes based on the instruction, updates cycles and PC accordingly 
	//this->mmu->loadrom(this->filename);
	//int cycles = 0;

	//while (true)
	//{
	//	uint8_t opcode = this->mmu->memory[this->cpu->pc];
	//	this->cpu->execute(opcode, this->mmu);
	//	cycles += this->cpu->cycles;
	//	if (cycles >= 70224)
	//	{
	//		cycles -= 70224;
	//		this->ppu->update(this->mmu);
	//	}
	//}

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

