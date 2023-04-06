#pragma once
#include "mmu.h"
class CPU
{
public:
	CPU(MMU* mmu);
	uint8_t Add(uint8_t operand1, uint8_t operand2);
	void Jump(int flag = 0);
	void ExecuteInstruction(uint8_t opcode);

	uint16_t PC;
	uint16_t SP;

	union {
		struct {
			//uint8_t F;
			struct {
				uint8_t : 4;
				uint8_t Z : 1;
				uint8_t N : 1;
				uint8_t H : 1;
				uint8_t C : 1;
			} F;
			uint8_t A;
		};
		uint16_t AF;
	};

	union {
		struct {
			uint8_t C;
			uint8_t B;
		};
		uint16_t BC;
	};

	union {
		struct {
			uint8_t E;
			uint8_t D;
		};
		uint16_t DE;
	};

	union {
		struct {
			uint8_t H;
			uint8_t L;
		};
		uint16_t HL;
	};
	
	MMU* mmu;
	
};

