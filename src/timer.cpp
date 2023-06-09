#include "timer.h"

Timer::Timer(MMU* mmu, Interrupts* interrupts) {
	this->mmu = mmu;
	this->interrupts = interrupts;
	div = 0;
	tima = 0;
}

void Timer::Increment() {
    mmu->clock.t += mmu->clock.t_instr;
    mmu->clock.t %= gameboy_ticks;

    div += mmu->clock.t_instr;

    while (div >= 256) {
        div -= 256;
        mmu->timer.div++;
    }

    Check();
}

void Timer::Check() {
    if (mmu->timer.tac & 0x04) {
        tima += mmu->clock.t_instr;

        int threshold = 0;
        switch (mmu->timer.tac & 0x03) {
        case 0:
            threshold = 1024;
            break;
        case 1:
            threshold = 16;
            break;
        case 2:
            threshold = 64;
            break;
        case 3:
            threshold = 256;
            break;
        }
        while (tima >= threshold) {
            tima -= threshold;
            if (mmu->timer.tima == 0xFF) {
                mmu->timer.tima = mmu->ReadByte(0xFF06);
                interrupts->SetInterruptFlag(INTERRUPT_TIMER);
            }
            else {
                mmu->timer.tima++;
            }
        }
    }
}
