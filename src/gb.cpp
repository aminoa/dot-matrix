#include "gb.h"

GB::GB(const char* file_path)
{
	this->file_path = file_path;

	mmu = new MMU();
	cpu = new CPU(mmu, nullptr);
	interrupts = new Interrupts(mmu, cpu);
	cpu->SetInterrupts(interrupts);

	//ppu = new PPU();
	timer = new Timer(mmu, interrupts);
	//joypad
}

void GB::Run()
{
	mmu->LoadROM(file_path);
	mmu->clock.t_instr = 0;

	while (true)
	{
		bool interrupted = interrupts->Check();
		mmu->clock.t_instr = 0;

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


