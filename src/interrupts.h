#pragma once

#include "cpu.h"
#include "mmu.h"

#include <iostream>

class CPU;

enum InterruptFlags { INTERRUPT_VBLANK = (1 << 0), INTERRUPT_LCD = (1 << 1), INTERRUPT_TIMER = (1 << 2), INTERRUPT_SERIAL = (1 << 3), INTERRUPT_JOYPAD = (1 << 4) };

class Interrupts
{
public:
	
	bool IME;
	MMU* mmu;
	CPU* cpu;

	Interrupts(MMU* mmu, CPU* cpu);

	bool Check();
	void TriggerInterrupt(InterruptFlags interrupt, uint8_t jump_pc);
	bool IsInterruptEnabled(uint8_t flag);
	bool IsInterruptFlagSet(uint8_t flag);
	void SetMasterFlag(bool state);
	bool IsMasteredEnabled();
	void SetInterruptFlag(uint8_t flag);
	void UnsetInterruptFlag(uint8_t flag);


};


