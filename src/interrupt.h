#pragma once
#include "mmu.h"
#include "cpu.h"

class Interrupt
{
public:
	Interrupt(MMU* mmu, CPU* cpu);
	void check_interrupts();
	void handle_interrupt(u8 interrupt);

	MMU* mmu;
	CPU* cpu;
	bool ime;
};