#pragma once
#include "mmu.h"
class CPU
{
public:
	CPU();
	void ExecuteInstruction();

	uint16_t PC;
	uint16_t SP;

private:
	struct AF {
		uint8_t F;
		uint8_t A;
	};
	
	struct BC {
		uint8_t C;
		uint8_t B;
	};

	struct DE {
		uint8_t E;
		uint8_t D;
	};

	struct HL {
		uint8_t L;
		uint8_t H;
	};

	AF AF;
	BC BC;
	DE DE;
	HL HL;


	MMU* memory;
};

