#pragma once

#include "interrupts.h"

Interrupts::Interrupts(MMU* mmu, CPU* cpu) 
{ 
    this->mmu = mmu; 
    this->cpu = cpu;
    this->IME = false;
}

void Interrupts::SetMasterFlag(bool state)  { IME = (int(state) << 0); }

bool Interrupts::IsMasteredEnabled() { return this->IME & 1U; }

void Interrupts::SetInterruptFlag(uint8_t flag) 
{
    uint8_t IF_value = mmu->ReadByte(0xFF0F);
    IF_value |= flag;
    return mmu->WriteByte(0xFF0F, IF_value);
}

void Interrupts::UnsetInterruptFlag(uint8_t flag) 
{
    uint8_t IF_value = mmu->ReadByte(0xFF0F);
    IF_value &= ~flag;
    return mmu->WriteByte(0xFF0F, IF_value);
}

bool Interrupts::IsInterruptEnabled(uint8_t flag) { return (mmu->ReadByte(0xFFFF) & flag); }

bool Interrupts::IsInterruptFlagSet(uint8_t flag) { return (mmu->ReadByte(0xFF0F) & flag); }

void Interrupts::TriggerInterrupt(InterruptFlags interrupt, uint8_t jump_pc) 
{
    mmu->WriteShort(cpu->SP, cpu->PC);
    cpu->PC = jump_pc;
    SetMasterFlag(false);
    UnsetInterruptFlag(interrupt);

    mmu->isHalted = false;
    mmu->clock.t_instr = 20;
}

bool Interrupts::Check() {

    if (IME) { return false; }

    // VBLANK
    if (this->IsInterruptEnabled(INTERRUPT_VBLANK) && this->IsInterruptFlagSet(INTERRUPT_VBLANK)) {
        this->TriggerInterrupt(INTERRUPT_VBLANK, 0x40);
        return true;
    }

    // Check if LCD
    if (this->IsInterruptEnabled(INTERRUPT_LCD) && this->IsInterruptFlagSet(INTERRUPT_LCD)) {
        this->TriggerInterrupt(INTERRUPT_LCD, 0x48);
        return true;
    }

    // Check if TIMER
    if (this->IsInterruptEnabled(INTERRUPT_TIMER) && this->IsInterruptFlagSet(INTERRUPT_TIMER)) {
        this->TriggerInterrupt(INTERRUPT_TIMER, 0x50);
        return true;
    }

    // Check if JOYPAD
    if (this->IsInterruptEnabled(INTERRUPT_JOYPAD) && this->IsInterruptFlagSet(INTERRUPT_JOYPAD)) {
        this->TriggerInterrupt(INTERRUPT_JOYPAD, 0x60);
        return true;
    }

    return false;
}