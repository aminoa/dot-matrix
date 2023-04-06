#pragma once
#include "mmu.h"
#include "cpu.h"
#include "interrupts.h"

class Interrupts;

class CPU
{
public:
	CPU(MMU* mmu, Interrupts* interrupts);

	void Jump(bool condition);
	void JumpAdd(bool condition);

	uint8_t Add(uint8_t operand1, uint8_t operand2);
	uint16_t Add(uint16_t operand1, uint16_t operand2);
	uint8_t AddCarry(uint8_t operand1, uint8_t operand2);
	uint8_t Subtract(uint8_t operand1, uint8_t operand2);
	uint8_t SubtractCarry(uint8_t operand1, uint8_t operand2);

	uint8_t And(uint8_t operand1, uint8_t operand2);
	uint8_t Or(uint8_t operand1, uint8_t operand2);
	uint8_t Xor(uint8_t operand1, uint8_t operand2);
	uint8_t Increment(uint8_t operand);
	uint8_t Decrement(uint8_t operand);

	uint8_t RotateLeft(uint8_t operand);
	uint8_t RotateLeftCarry(uint8_t operand);
	uint8_t RotateRight(uint8_t operand);
	uint8_t RotateRightCarry(uint8_t operand);	
	uint8_t ShiftLeft(uint8_t operand);
	uint8_t ShiftRight(uint8_t operand);
	uint8_t ShiftRightLogical(uint8_t operand);
	
	uint8_t Swap(uint8_t operand);
	void Bit(uint8_t bit, uint8_t operand);
	
	void Compare(uint8_t operand1, uint8_t operand2);
	void Return(bool condition);
	void Call(bool condition);


	void ExecuteInstruction(uint8_t opcode);
	void SetInterrupts(Interrupts* interrupts);

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
	Interrupts* interrupts;

	//copied from NoobBoy
	const uint8_t InstructionTicks[256] = {
		4, 12, 8, 8, 4, 4, 8, 4, 20, 8, 8, 8, 4, 4, 8, 4,       // 0x0_
		4, 12, 8, 8, 4, 4, 8, 4,  12, 8, 8, 8, 4, 4, 8, 4,      // 0x1_
		0, 12, 8, 8, 4, 4, 8, 4,  0, 8, 8, 8, 4, 4, 8, 4,       // 0x2_
		0, 12, 8, 8, 12, 12, 12, 4,  0, 8, 8, 8, 4, 4, 8, 4,    // 0x3_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x4_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x5_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x6_
		8, 8, 8, 8, 8, 8, 4, 8,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x7_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x8_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0x9_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0xa_
		4, 4, 4, 4, 4, 4, 8, 4,  4, 4, 4, 4, 4, 4, 8, 4,        // 0xb_
		0, 12, 0, 16, 0, 16, 8, 16,  0, 16, 0, 0, 0, 24, 8, 16, // 0xc_
		0, 12, 0, 0, 0, 16, 8, 16,  0, 16, 0, 0, 0, 0, 8, 16,   // 0xd_
		12, 12, 8, 0, 0, 16, 8, 16,  16, 4, 16, 0, 0, 0, 8, 16, // 0xe_
		12, 12, 8, 4, 0, 16, 8, 16,  12, 8, 16, 4, 0, 0, 8, 16  // 0xf_
	};
};

