#include "cpu.h"

CPU::CPU(MMU* mmu)
{
	AF = 0x1000;
	BC = 0xFF13;
	DE = 0x00C1;
	HL = 0x8403;

	pc = 0x100;
	sp = 0xFFFE;

	this->mmu = mmu;

}

void CPU::execute(u8 opcode)
{
	//need to check overloading different 1 or 2 bytes for some writes

	std::cout << OPCODE_NAMES[opcode] << std::endl;

	switch (opcode)
	{
	case 0x00: break;
	case 0x01: BC = mmu->read(pc); break;
	case 0x02: mmu->write(BC, A); break; 
	case 0x03: BC++; break;
	case 0x04:
		B++;
		if (B == 0) F.Z = 1;
		F.N = 0;
		F.H = 0;
		break;
	
	default:
		break;
	}

	//increment pc
	pc += 1; //not correct
	//modify clock cycles here
}
