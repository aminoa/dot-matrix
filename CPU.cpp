#include "CPU.h"

#include <iostream>

CPU::CPU() {}

void CPU::ExecuteInstruction()
{
	//opcode is a misnomer here; this only gets the value in memory that the PC points to (so the opcode may be longer than 2 bytes).
	uint16_t* opcode =

	switch (opcode[0])
	{
	//8 bit load instructions
	
	case 0x00: // NOP
		std::cout << "NOP" << std::endl;
		break;

	case 0xC3:
		PC = opcode[1] | opcode[2] << 8;
		break;
	
	case 0xCD:
		SP -= 2;
		memory[SP] = PC;
		PC = opcode[1] | opcode[2] << 8;
		break;

	default:
		std::cout << "Unimplemented Instruction! " << opcode << std::endl;
		break;
	}
};
