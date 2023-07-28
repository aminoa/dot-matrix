#pragma once
#include "interrupt.h"
#include "cpu.h"
#include "consts.h"

Interrupt::Interrupt(MMU* mmu, CPU* cpu)
{
	this->mmu = mmu;
	this->cpu = cpu;
	this->ime = false;
}

void Interrupt::check_interrupts()
{
	// enable and flag set
	if (mmu->read_byte(0xFFFF) & mmu->read_byte(0xFF0F) & 0x0F)
	{
		// VBlank
		if (mmu->read_byte(0xFF0F) & INTERRUPT_VBLANK)
		{
			mmu->write_byte(0xFF0F, mmu->read_byte(0xFF0F) & 0xFE);
			handle_interrupt(0x40);
		}
		
		// LCD STAT
				
	}
}

void Interrupt::handle_interrupt(u8 interrupt)
{
	// disable interrupts
	this->ime = false;

	// push pc to stack
	mmu->write_byte(--cpu->sp, cpu->pc >> 8);
	mmu->write_byte(--cpu->sp, cpu->pc & 0xFF);

	// jump to interrupt
	cpu->pc = interrupt;
}
