#include "gb.h"
#include "cpu.h"
#include "mmu.h"
#include "timer.h"
#include <stdint.h> 
#include <fstream>
#include <iostream>
#include <vector>

GB::GB(const char* file_path)
{
	mmu = new MMU();
	interrupts = new Interrupts(mmu);
	ppu = new PPU();

	cpu = new CPU(mmu, interrupts);
	file_path = file_path;
	timer = new Timer(mmu, interrupts);
}

void GB::Run()
{
	mmu->LoadROM(file_path);
	mmu->clock.t_instr = 0;
	bool interrupted = interrupts.Check();

	while (true)
	{
		if (!interrupted)
		{
			uint8_t instruction = mmu->ReadByte(cpu->PC);
			cpu->PC++;
			cpu->ExecuteInstruction(instruction);
		}
		timer->Increment();
		//ppu->Step();
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
	gb->Run();

	return 0;
}


