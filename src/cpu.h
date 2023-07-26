#pragma once
#include "consts.h"
#include "mmu.h"

class CPU
{
public:
	CPU(MMU* mmu);

	void execute(u8 opcode);

	void inc(u8& reg);
	void dec(u8& reg);
	void rlca();
	void rrca();

	void add(u8 val);
	void add(u16 val);
	void adc(u8 val);

	void sub(u8 val);
	void sbc(u8 val);

	void _and(u8 val);
	void _xor(u8 val);
	void _or(u8 val);
	void cp(u8 val);

	//void add(u16 val1, u16 val2);

	void pop(u16& reg);
	void push(u16& reg);

	u16 pc;
	u16 sp;
	MMU* mmu;

	//registers
	union {
		struct {
			struct { u8 : 4; u8 Z : 1; u8 N : 1; u8 H : 1; u8 C : 1; } F;
			u8 A;
		};
		u16 AF;
	};

	union {
		struct { u8 C; u8 B; };
		u16 BC;
	};

	union {
		struct { u8 E; u8 D; };
		u16 DE;
	};

	union {
		struct { u8 H; u8 L; };
		u16 HL;
	};
};