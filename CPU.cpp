#include "CPU.h"
#include <iostream>

void CPU::ExecuteInstruction(uint16_t* opcode)
{
	switch (*opcode)
	{
	//8 bit load instructions
	
	case 0x00: // NOP
		break;
	case 0xC3:
		PC = opcode[1] | opcode[2] << 8;
		break;

	default:
		std::cout << "Unimplemented Instruction! " << opcode << std::endl;
		break;
	}
};