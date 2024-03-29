#pragma once
#include "consts.h"

class MMU;

class CPU
{
public:
	CPU(MMU* mmu);

	void execute(u8 opcode);
	void execute_cb(u8 opcode);

	void inc(u8& reg);
	void dec(u8& reg);
	void rlca();
	void rrca();
	void rla();
	void rra();

	// CB prefix
	void rlc(u8& reg);
	void rrc(u8& reg);
	void rl(u8& reg);
	void rr(u8& reg);
	void sla(u8& reg);
	void sra(u8& reg);
	void swap(u8& reg);
	void srl(u8& reg);
	void bit(u8 bit, u8 reg);

	void res(u8 bit, u8& reg);
	void set(u8 bit, u8& reg);

	void add(u8 val);
	void add(u16 val);
	void adc(u8 val);
	void add_signed(u8 val);

	void sub(u8 val);
	void sbc(u8 val);

	void _and(u8 val);
	void _xor(u8 val);
	void _or(u8 val);
	void cp(u8 val);

	// CPU control
	void daa();

	u16 pop();
	void push(u16 val);
	void load_hl(u8 val);

	u16 pc;
	u16 sp;
	MMU* mmu;

	// interrupts
	bool ime; 
	void mark_interrupt(u8 interrupt_bit);
	void check_interrupts();
	void handle_interrupt(u16 interrupt_address, u8 interrupt_bit);

	bool halted;
	bool stopped;

	//registers
	union {
		u16 AF;
		struct {
			u8 F;
			u8 A;
		};
		struct {
			u8 : 4;
			u8 FLAG_C: 1;
			u8 FLAG_H: 1;
			u8 FLAG_N: 1;
			u8 FLAG_Z: 1;
			u8 : 8;
		};
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
		struct { u8 L; u8 H; };
		u16 HL;
	};

};