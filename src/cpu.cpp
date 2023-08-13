#pragma once

#include "cpu.h"
#include "consts.h"
#include "mmu.h"

CPU::CPU(MMU* mmu)
{
	AF = 0x01B0;
	BC = 0x0013;
	DE = 0x00D8;
	HL = 0x014D;

	pc = 0x100;
	sp = 0xFFFE;

	this->mmu = mmu;
	ime = false;
	stopped = false;
	halted = false;
}

// interrupts handling 
//
void CPU::check_interrupts()
{
	// there's an enable and flag set
	if (ime & mmu->read_byte(Memory::IE) & mmu->read_byte(Memory::IF) & 0x0F)
	{
		ime = false;

		if (mmu->read_byte(Memory::IF) & mmu->read_byte(Memory::IE) & Interrupt::VBLANK)
		{
			handle_interrupt(Memory::VBLANK_HANDLER, Interrupt::VBLANK);
		}
		else if (mmu->read_byte(Memory::IF) & mmu->read_byte(Memory::IE) & Interrupt::LCD)
		{
			handle_interrupt(Memory::LCD_HANDLER, Interrupt::LCD);
		}
		else if (mmu->read_byte(Memory::IF) & mmu->read_byte(Memory::IE) & Interrupt::TIMER)
		{
			handle_interrupt(Memory::TIMER_HANDLER, Interrupt::TIMER);
		}
		else if (mmu->read_byte(Memory::IF) & mmu->read_byte(Memory::IE) & Interrupt::SERIAL)
		{
			handle_interrupt(Memory::SERIAL_HANDLER, Interrupt::SERIAL);
		}
		else if (mmu->read_byte(Memory::IF) & mmu->read_byte(Memory::IE) & Interrupt::JOYPAD)
		{
			handle_interrupt(Memory::JOYPAD_HANDLER, Interrupt::JOYPAD);
		}

		//ime restored after routine
	}
}

void CPU::trigger_interrupt(u8 interrupt)
{
	mmu->write_byte(Memory::IF, mmu->read_byte((Memory::IF) | interrupt));
}

//
void CPU::handle_interrupt(u8 interrupt_address, u8 interrupt_flag)
{
	mmu->write_byte(Memory::IF, mmu->read_byte(Memory::IF) & ~interrupt_flag);
	// disable interrupts
	ime = false;
	push(pc);
	pc = interrupt_address;
}

// instructions pre-increment pc for correct order evaluation
void CPU::execute(u8 opcode)
{
	// only necessary if there's an immediate arg
	u8 arg_u8 = mmu->read_byte(pc + 1);
	u16 arg_u16 = mmu->read_short(pc + 1);
	
	// need to check if CB opcode

	if (opcode == 0xCB)
	{
		pc += CB_OPCODES[arg_u8].bytes;
	}
	else
	{
		pc += OPCODES[opcode].bytes;
	}

	//std::cout << OPCODES[opcode].mnemonic << std::endl;

	u8 temp = 0;
	switch (opcode)
	{
	// 8 bit load instructions
	case 0x02: mmu->write_byte(BC, A); break;
	case 0x06: B = arg_u8; break;
	case 0x0A: A = mmu->read_byte(BC); break;
	case 0x0E: C = arg_u8; break;
	case 0x12: mmu->write_byte(DE, A); break;
	case 0x16: D = arg_u8; break;
	case 0x1A: A = mmu->read_byte(DE); break;
	case 0x1E: E = arg_u8; break;
	case 0x22: mmu->write_byte(HL, A); HL++; break;
	case 0x26: H = arg_u8; break;
	case 0x2A: A = mmu->read_byte(HL); HL++; break;
	case 0x2E: L = arg_u8; break;
	case 0x32: mmu->write_byte(HL, A); HL--; break;
	case 0x36: mmu->write_byte(HL, arg_u8); break;
	case 0x3A: A = mmu->read_byte(HL); HL--; break;
	case 0x3E: A = arg_u8; break;

	case 0x40: B = B; break;
	case 0x41: B = C; break;
	case 0x42: B = D; break;
	case 0x43: B = E; break;
	case 0x44: B = H; break;
	case 0x45: B = L; break;
	case 0x46: B = mmu->read_byte(HL); break;
	case 0x47: B = A; break;
	case 0x48: C = B; break;
	case 0x49: C = C; break;
	case 0x4A: C = D; break;
	case 0x4B: C = E; break;
	case 0x4C: C = H; break;
	case 0x4D: C = L; break;
	case 0x4E: C = mmu->read_byte(HL); break;
	case 0x4F: C = A; break;
	case 0x50: D = B; break;
	case 0x51: D = C; break;
	case 0x52: D = D; break;
	case 0x53: D = E; break;
	case 0x54: D = H; break;
	case 0x55: D = L; break;
	case 0x56: D = mmu->read_byte(HL); break;
	case 0x57: D = A; break;
	case 0x58: E = B; break;
	case 0x59: E = C; break;
	case 0x5A: E = D; break;
	case 0x5B: E = E; break;
	case 0x5C: E = H; break;
	case 0x5D: E = L; break;
	case 0x5E: E = mmu->read_byte(HL); break;
	case 0x5F: E = A; break;
	case 0x60: H = B; break;
	case 0x61: H = C; break;
	case 0x62: H = D; break;
	case 0x63: H = E; break;
	case 0x64: H = H; break;
	case 0x65: H = L; break;
	case 0x66: H = mmu->read_byte(HL); break;
	case 0x67: H = A; break;
	case 0x68: L = B; break;
	case 0x69: L = C; break;
	case 0x6A: L = D; break;
	case 0x6B: L = E; break;
	case 0x6C: L = H; break;
	case 0x6D: L = L; break;
	case 0x6E: L = mmu->read_byte(HL); break;
	case 0x6F: L = A; break;
	case 0x70: mmu->write_byte(HL, B); break;
	case 0x71: mmu->write_byte(HL, C); break;
	case 0x72: mmu->write_byte(HL, D); break;
	case 0x73: mmu->write_byte(HL, E); break;
	case 0x74: mmu->write_byte(HL, H); break;
	case 0x75: mmu->write_byte(HL, L); break;
	case 0x77: mmu->write_byte(HL, A); break;
	case 0x78: A = B; break;
	case 0x79: A = C; break;
	case 0x7A: A = D; break;
	case 0x7B: A = E; break;
	case 0x7C: A = H; break;
	case 0x7D: A = L; break;
	case 0x7E: A = mmu->read_byte(HL); break;
	case 0x7F: A = A; break;

	case 0xE0: mmu->write_byte(0xFF00 + arg_u8, A); break;
	case 0xE2: mmu->write_byte(0xFF00 + C, A); break;

	case 0xEA: mmu->write_byte(arg_u16, A); break; 
	case 0xF0: A = mmu->read_byte(0xFF00 + arg_u8); break;
	case 0xF2: A = mmu->read_byte(0xFF00 + C); break;
	case 0xFA: A = mmu->read_byte(arg_u16); break; 

	// 16 bit load instructions
	case 0x01: BC = arg_u16; break;
	case 0x08: mmu->write_short(arg_u16, sp); break;
	case 0x11: DE = arg_u16; break;
	case 0x21: HL = arg_u16; break;
	case 0x31: sp = arg_u16; break;
	case 0xC1: BC = pop(); break;
	case 0xC5: push(BC); break;
	case 0xD1: DE = pop(); break;
	case 0xD5: push(DE); break;
	case 0xE1: HL = pop(); break;
	case 0xE5: push(HL); break;
	case 0xF1: AF = pop() & 0xFFF0; break;
	case 0xF5: push(AF); break;
	case 0xF8: HL = sp + (i8)arg_u8; break;
	case 0xF9: sp = HL; break;

	// 8 bit arithmetic/logic instructions
	case 0x04: inc(B); break;
	case 0x05: dec(B); break;
	case 0x0C: inc(C); break;
	case 0x0D: dec(C); break;
	case 0x14: inc(D); break;
	case 0x15: dec(D); break;
	case 0x1C: inc(E); break;
	case 0x1D: dec(E); break;
	case 0x24: inc(H); break;
	case 0x25: dec(H); break;
	case 0x2C: inc(L); break;
	case 0x2D: dec(L); break;
	case 0x34: temp = mmu->read_byte(HL); inc(temp); mmu->write_byte(HL, temp); break;
	case 0x35: temp = mmu->read_byte(HL); dec(temp); mmu->write_byte(HL, temp); break;
	case 0x3C: inc(A); break;
	case 0x3D: dec(A); break;
	
	case 0x80: add(B); break;
	case 0x81: add(C); break;
	case 0x82: add(D); break;
	case 0x83: add(E); break;
	case 0x84: add(H); break;
	case 0x85: add(L); break;
	case 0x86: add(mmu->read_byte(HL)); break;
	case 0x87: add(A); break;
	case 0x88: adc(B); break;
	case 0x89: adc(C); break;
	case 0x8A: adc(D); break;
	case 0x8B: adc(E); break;
	case 0x8C: adc(H); break;
	case 0x8D: adc(L); break;
	case 0x8E: adc(mmu->read_byte(HL)); break;
	case 0x8F: adc(A); break;
	case 0x90: sub(B); break;
	case 0x91: sub(C); break;
	case 0x92: sub(D); break;
	case 0x93: sub(E); break;
	case 0x94: sub(H); break;
	case 0x95: sub(L); break;
	case 0x96: sub(mmu->read_byte(HL)); break;
	case 0x97: sub(A); break;
	case 0x98: sbc(B); break;
	case 0x99: sbc(C); break;
	case 0x9A: sbc(D); break;
	case 0x9B: sbc(E); break;
	case 0x9C: sbc(H); break;
	case 0x9D: sbc(L); break;
	case 0x9E: sbc(mmu->read_byte(HL)); break;
	case 0x9F: sbc(A); break;
	case 0xA0: _and(B); break;
	case 0xA1: _and(C); break;
	case 0xA2: _and(D); break;
	case 0xA3: _and(E); break;
	case 0xA4: _and(H); break;
	case 0xA5: _and(L); break;
	case 0xA6: _and(mmu->read_byte(HL)); break;
	case 0xA7: _and(A); break;
	case 0xA8: _xor(B); break;
	case 0xA9: _xor(C); break;
	case 0xAA: _xor(D); break;
	case 0xAB: _xor(E); break;
	case 0xAC: _xor(H); break;
	case 0xAD: _xor(L); break;
	case 0xAE: _xor(mmu->read_byte(HL)); break;
	case 0xAF: _xor(A); break;
	case 0xB0: _or(B); break;
	case 0xB1: _or(C); break;
	case 0xB2: _or(D); break;
	case 0xB3: _or(E); break;
	case 0xB4: _or(H); break;
	case 0xB5: _or(L); break;
	case 0xB6: _or(mmu->read_byte(HL)); break;
	case 0xB7: _or(A); break;
	case 0xB8: cp(B); break;
	case 0xB9: cp(C); break;
	case 0xBA: cp(D); break;
	case 0xBB: cp(E); break;
	case 0xBC: cp(H); break;
	case 0xBD: cp(L); break;
	case 0xBE: cp(mmu->read_byte(HL)); break;
	case 0xBF: cp(A); break;

	case 0xC6: add(arg_u8); break;
	case 0xCE: adc(arg_u8); break;
	case 0xD6: sub(arg_u8); break;
	case 0xDE: sbc(arg_u8); break;
	case 0xE6: _and(arg_u8); break;
	case 0xEE: _xor(arg_u8); break;
	case 0xF6: _or(arg_u8); break;
	case 0xFE: cp(arg_u8); break;

	// 16-bit arithmetic/logic instructions
	case 0x03: BC++; break;
	case 0x09: add(BC); break;
	case 0x0B: BC--; break;
	case 0x13: DE++; break;
	case 0x19: add(DE); break;
	case 0x1B: DE--; break;
	case 0x23: HL++; break;
	case 0x29: add(HL); break;
	case 0x2B: HL--; break;
	case 0x33: sp++; break;
	case 0x39: add(sp); break;
	case 0x3B: sp--; break;
	case 0xE8: sp = -(i8)arg_u8 + sp; break;

	// 8-bit shift, rotate and bit instructions
	case 0x07: rlca(); break;
	case 0x0F: rrca(); break;
	case 0x17: rla(); break;
	case 0x1F: rra(); break;
	case 0xCB:  execute_cb(arg_u8); break;

	// CPU control instructions
	case 0x00: break;
	case 0x10: stopped = true; break;
	case 0x27: daa(); break;
	case 0x2F: A = ~A; FLAG_N = 1; FLAG_H = 1; break;
	case 0x37: FLAG_C = 1; FLAG_H = 0; FLAG_N = 0; break;
	case 0x3F: FLAG_C = !FLAG_C; FLAG_H = 0; FLAG_N = 0; break;
	case 0x76: halted = true;  break;
	case 0xF3: ime = false; break; 
	case 0xFB: ime = true; break; 
	
	case 0x18: pc += (i8) arg_u8; break;
	case 0x20: if (FLAG_Z == 0) pc += (i8) arg_u8; break;
	case 0x28: if (FLAG_Z == 1) pc += (i8) arg_u8; break;
	case 0x30: if (FLAG_C == 0) pc += (i8) arg_u8; break;
	case 0x38: if (FLAG_C == 1) pc += (i8) arg_u8; break;
	case 0xC0: if (FLAG_Z == 0) pc = pop(); break;
	case 0xC2: if (FLAG_Z == 0) pc = arg_u16; break;
	case 0xC3: pc = arg_u16; break;
	case 0xC4: if (FLAG_Z == 0) { push(pc); pc = arg_u16; } break;
	case 0xC7: push(pc); pc = 0x00; break;
	case 0xC8: if (FLAG_Z) pc = pop(); break;
	case 0xC9: pc = pop(); break;
	case 0xCA: if (FLAG_Z) pc = arg_u16; break;
	case 0xCC: if (FLAG_Z) { push(pc); pc = arg_u16; } break;
	case 0xCD: push(pc); pc = arg_u16; break;
	case 0xCF: push(pc); pc = 0x08; break;
	case 0xD0: if (FLAG_C == 0) pc = pop(); break;
	case 0xD2: if (FLAG_C == 0) pc = arg_u16; break;
	case 0xD4: if (FLAG_C == 0) { push(pc); pc = arg_u16; } break;
	case 0xD7: push(pc); pc = 0x10; break;
	case 0xD8: if (FLAG_C) pc = pop(); break;
	case 0xD9: pc = pop(); ime = true; break;

	case 0xDA: if (FLAG_C) pc = arg_u16; break;
	case 0xDC: if (FLAG_C) { push(pc); pc = arg_u16; } break;
	case 0xDF: push(pc); pc = 0x18; break;
	case 0xE7: push(pc); pc = 0x20; break;
	case 0xE9: pc = HL; break;
	case 0xEF: push(pc); pc = 0x28; break;
	case 0xF7: push(pc); pc = 0x30; break;
	case 0xFF: push(pc); pc = 0x38; break;

	default: std::cout << "Unknown Opcode (something went wrong)" << std::endl;
	};
};

void CPU::execute_cb(u8 opcode)
{
	u8 temp;
	switch (opcode)
	{
	case 0x00: rlc(B); break;
	case 0x01: rlc(C); break;
	case 0x02: rlc(D); break;
	case 0x03: rlc(E); break;
	case 0x04: rlc(H); break;
	case 0x05: rlc(L); break;
	case 0x06: temp = mmu->read_byte(HL); rlc(temp); mmu->write_byte(HL, temp); break;
	case 0x07: rlc(A); break;
	case 0x08: rrc(B); break;
	case 0x09: rrc(C); break;
	case 0x0A: rrc(D); break;
	case 0x0B: rrc(E); break;
	case 0x0C: rrc(H); break;
	case 0x0D: rrc(L); break;
	case 0x0E: temp = mmu->read_byte(HL); rrc(temp); mmu->write_byte(HL, temp); break;
	case 0x0F: rrc(A); break;
	case 0x10: rl(B); break;
	case 0x11: rl(C); break;
	case 0x12: rl(D); break;
	case 0x13: rl(E); break;
	case 0x14: rl(H); break;
	case 0x15: rl(L); break;
	case 0x16: temp = mmu->read_byte(HL); rl(temp); mmu->write_byte(HL, temp); break;
	case 0x17: rl(A); break;
	case 0x18: rr(B); break;
	case 0x19: rr(C); break;
	case 0x1A: rr(D); break;
	case 0x1B: rr(E); break;
	case 0x1C: rr(H); break;
	case 0x1D: rr(L); break;
	case 0x1E: temp = mmu->read_byte(HL); rr(temp); mmu->write_byte(HL, temp); break;
	case 0x1F: rr(A); break;

	case 0x20: sla(B); break;
	case 0x21: sla(C); break;
	case 0x22: sla(D); break;
	case 0x23: sla(E); break;
	case 0x24: sla(H); break;
	case 0x25: sla(L); break;
	case 0x26: temp = mmu->read_byte(HL); sla(temp); mmu->write_byte(HL, temp); break;
	case 0x27: sla(A); break;
	case 0x28: sra(B); break;
	case 0x29: sra(C); break;
	case 0x2A: sra(D); break;
	case 0x2B: sra(E); break;
	case 0x2C: sra(H); break;
	case 0x2D: sra(L); break;
	case 0x2E: temp = mmu->read_byte(HL); sra(temp); mmu->write_byte(HL, temp); break;
	case 0x2F: sra(A); break;

	case 0x30: swap(B); break;
	case 0x31: swap(C); break;
	case 0x32: swap(D); break;
	case 0x33: swap(E); break;
	case 0x34: swap(H); break;
	case 0x35: swap(L); break;
	case 0x36: temp = mmu->read_byte(HL); swap(temp); mmu->write_byte(HL, temp); break;
	case 0x37: swap(A); break;
	case 0x38: srl(B); break;
	case 0x39: srl(C); break;
	case 0x3A: srl(D); break;
	case 0x3B: srl(E); break;
	case 0x3C: srl(H); break;
	case 0x3D: srl(L); break;
	case 0x3E: temp = mmu->read_byte(HL); srl(temp); mmu->write_byte(HL, temp); break;

	case 0x3F: srl(A); break;
	case 0x40: bit(0, B); break;
	case 0x41: bit(0, C); break;
	case 0x42: bit(0, D); break;
	case 0x43: bit(0, E); break;
	case 0x44: bit(0, H); break;
	case 0x45: bit(0, L); break;
	case 0x46: temp = mmu->read_byte(HL); bit(0, temp); mmu->write_byte(HL, temp); break;
	case 0x47: bit(0, A); break;
	case 0x48: bit(1, B); break;
	case 0x49: bit(1, C); break;
	case 0x4A: bit(1, D); break;
	case 0x4B: bit(1, E); break;
	case 0x4C: bit(1, H); break;
	case 0x4D: bit(1, L); break;
	case 0x4E: temp = mmu->read_byte(HL); bit(1, temp); mmu->write_byte(HL, temp); break;
	case 0x4F: bit(1, A); break;
	case 0x50: bit(2, B); break;
	case 0x51: bit(2, C); break;
	case 0x52: bit(2, D); break;
	case 0x53: bit(2, E); break;
	case 0x54: bit(2, H); break;
	case 0x55: bit(2, L); break;
	case 0x56: temp = mmu->read_byte(HL); bit(2, temp); mmu->write_byte(HL, temp); break;
	case 0x57: bit(2, A); break;
	case 0x58: bit(3, B); break;
	case 0x59: bit(3, C); break;
	case 0x5A: bit(3, D); break;
	case 0x5B: bit(3, E); break;
	case 0x5C: bit(3, H); break;
	case 0x5D: bit(3, L); break;
	case 0x5E: temp = mmu->read_byte(HL); bit(3, temp); mmu->write_byte(HL, temp); break;
	case 0x5F: bit(3, A); break;
	case 0x60: bit(4, B); break;
	case 0x61: bit(4, C); break;
	case 0x62: bit(4, D); break;
	case 0x63: bit(4, E); break;
	case 0x64: bit(4, H); break;
	case 0x65: bit(4, L); break;
	case 0x66: temp = mmu->read_byte(HL); bit(4, temp); mmu->write_byte(HL, temp); break;
	case 0x67: bit(4, A); break;
	case 0x68: bit(5, B); break;
	case 0x69: bit(5, C); break;
	case 0x6A: bit(5, D); break;
	case 0x6B: bit(5, E); break;
	case 0x6C: bit(5, H); break;
	case 0x6D: bit(5, L); break;
	case 0x6E: temp = mmu->read_byte(HL); bit(5, temp); mmu->write_byte(HL, temp); break;
	case 0x6F: bit(5, A); break;
	case 0x70: bit(6, B); break;
	case 0x71: bit(6, C); break;
	case 0x72: bit(6, D); break;
	case 0x73: bit(6, E); break;
	case 0x74: bit(6, H); break;
	case 0x75: bit(6, L); break;
	case 0x76: temp = mmu->read_byte(HL); bit(6, temp); mmu->write_byte(HL, temp); break;
	case 0x77: bit(6, A); break;
	case 0x78: bit(7, B); break;
	case 0x79: bit(7, C); break;
	case 0x7A: bit(7, D); break;
	case 0x7B: bit(7, E); break;
	case 0x7C: bit(7, H); break;
	case 0x7D: bit(7, L); break;
	case 0x7E: temp = mmu->read_byte(HL); bit(7, temp); mmu->write_byte(HL, temp); break;
	case 0x7F: bit(7, A); break;

	case 0x80: res(0, B); break;
	case 0x81: res(0, C); break;
	case 0x82: res(0, D); break;
	case 0x83: res(0, E); break;
	case 0x84: res(0, H); break;
	case 0x85: res(0, L); break;
	case 0x86: temp = mmu->read_byte(HL); res(0, temp); mmu->write_byte(HL, temp); break;
	case 0x87: res(0, A); break;
	case 0x88: res(1, B); break;
	case 0x89: res(1, C); break;
	case 0x8A: res(1, D); break;
	case 0x8B: res(1, E); break;
	case 0x8C: res(1, H); break;
	case 0x8D: res(1, L); break;
	case 0x8E: temp = mmu->read_byte(HL); res(1, temp); mmu->write_byte(HL, temp); break;
	case 0x8F: res(1, A); break;
	case 0x90: res(2, B); break;
	case 0x91: res(2, C); break;
	case 0x92: res(2, D); break;
	case 0x93: res(2, E); break;
	case 0x94: res(2, H); break;
	case 0x95: res(2, L); break;
	case 0x96: temp = mmu->read_byte(HL); res(2, temp); mmu->write_byte(HL, temp); break;
	case 0x97: res(2, A); break;
	case 0x98: res(3, B); break;
	case 0x99: res(3, C); break;
	case 0x9A: res(3, D); break;
	case 0x9B: res(3, E); break;
	case 0x9C: res(3, H); break;
	case 0x9D: res(3, L); break;
	case 0x9E: temp = mmu->read_byte(HL); res(3, temp); mmu->write_byte(HL, temp); break;
	case 0x9F: res(3, A); break;
	case 0xA0: res(4, B); break;
	case 0xA1: res(4, C); break;
	case 0xA2: res(4, D); break;
	case 0xA3: res(4, E); break;
	case 0xA4: res(4, H); break;
	case 0xA5: res(4, L); break;
	case 0xA6: temp = mmu->read_byte(HL); res(4, temp); mmu->write_byte(HL, temp); break;	
	case 0xA7: res(4, A); break;
	case 0xA8: res(5, B); break;
	case 0xA9: res(5, C); break;
	case 0xAA: res(5, D); break;
	case 0xAB: res(5, E); break;
	case 0xAC: res(5, H); break;
	case 0xAD: res(5, L); break;
	case 0xAE: temp = mmu->read_byte(HL); res(5, temp); mmu->write_byte(HL, temp); break;
	case 0xAF: res(5, A); break;
	case 0xB0: res(6, B); break;
	case 0xB1: res(6, C); break;
	case 0xB2: res(6, D); break;
	case 0xB3: res(6, E); break;
	case 0xB4: res(6, H); break;
	case 0xB5: res(6, L); break;
	case 0xB6: temp = mmu->read_byte(HL); res(6, temp); mmu->write_byte(HL, temp); break;
	case 0xB7: res(6, A); break;
	case 0xB8: res(7, B); break;
	case 0xB9: res(7, C); break;
	case 0xBA: res(7, D); break;
	case 0xBB: res(7, E); break;
	case 0xBC: res(7, H); break;
	case 0xBD: res(7, L); break;
	case 0xBE: temp = mmu->read_byte(HL); res(7, temp); mmu->write_byte(HL, temp); break;
	case 0xBF: res(7, A); break;

	case 0xC0: set(0, B); break;
	case 0xC1: set(0, C); break;
	case 0xC2: set(0, D); break;
	case 0xC3: set(0, E); break;
	case 0xC4: set(0, H); break;
	case 0xC5: set(0, L); break;
	case 0xC6: temp = mmu->read_byte(HL); set(0, temp); mmu->write_byte(HL, temp); break;
	case 0xC7: set(0, A); break;
	case 0xC8: set(1, B); break;
	case 0xC9: set(1, C); break;
	case 0xCA: set(1, D); break;
	case 0xCB: set(1, E); break;
	case 0xCC: set(1, H); break;
	case 0xCD: set(1, L); break;
	case 0xCE: temp = mmu->read_byte(HL); set(1, temp); mmu->write_byte(HL, temp); break;
	case 0xCF: set(1, A); break;
	case 0xD0: set(2, B); break;
	case 0xD1: set(2, C); break;
	case 0xD2: set(2, D); break;
	case 0xD3: set(2, E); break;
	case 0xD4: set(2, H); break;
	case 0xD5: set(2, L); break;
	case 0xD6: temp = mmu->read_byte(HL); set(2, temp); mmu->write_byte(HL, temp); break;
	case 0xD7: set(2, A); break;
	case 0xD8: set(3, B); break;
	case 0xD9: set(3, C); break;
	case 0xDA: set(3, D); break;
	case 0xDB: set(3, E); break;
	case 0xDC: set(3, H); break;
	case 0xDD: set(3, L); break;
	case 0xDE: temp = mmu->read_byte(HL); set(3, temp); mmu->write_byte(HL, temp); break;
	case 0xDF: set(3, A); break;
	case 0xE0: set(4, B); break;
	case 0xE1: set(4, C); break;
	case 0xE2: set(4, D); break;
	case 0xE3: set(4, E); break;
	case 0xE4: set(4, H); break;
	case 0xE5: set(4, L); break;
	case 0xE6: temp = mmu->read_byte(HL); set(4, temp); mmu->write_byte(HL, temp); break;
	case 0xE7: set(4, A); break;
	case 0xE8: set(5, B); break;
	case 0xE9: set(5, C); break;
	case 0xEA: set(5, D); break;
	case 0xEB: set(5, E); break;
	case 0xEC: set(5, H); break;
	case 0xED: set(5, L); break;
	case 0xEE: temp = mmu->read_byte(HL); set(5, temp); mmu->write_byte(HL, temp); break;
	case 0xEF: set(5, A); break;
	case 0xF0: set(6, B); break;
	case 0xF1: set(6, C); break;
	case 0xF2: set(6, D); break;
	case 0xF3: set(6, E); break;
	case 0xF4: set(6, H); break;
	case 0xF5: set(6, L); break;
	case 0xF6: temp = mmu->read_byte(HL); set(6, temp); mmu->write_byte(HL, temp); break;
	case 0xF7: set(6, A); break;
	case 0xF8: set(7, B); break;
	case 0xF9: set(7, C); break;
	case 0xFA: set(7, D); break;
	case 0xFB: set(7, E); break;
	case 0xFC: set(7, H); break;
	case 0xFD: set(7, L); break;
	case 0xFE: temp = mmu->read_byte(HL); set(7, temp); mmu->write_byte(HL, temp); break;
	case 0xFF: set(7, A); break;	
	default: break;
	}
}

void CPU::inc(u8& reg)
{
	reg++;
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = (reg & 0x0F) == 0x00;
}

void CPU::dec(u8& reg)
{
	reg--;
	FLAG_Z = reg == 0;
	FLAG_N = 1;
	FLAG_H = (reg & 0x0F) == 0x0F;
}

void CPU::rlca()
{
	u8 carry = A >> 7;
	A = (A << 1) | carry;
	FLAG_Z = 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = carry;
}

void CPU::rrca()
{
	u8 carry = A & 0x01;
	A = (A >> 1) | (carry << 7);
	FLAG_Z = 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = carry;
}

void CPU::rla()
{
	u8 carry = A >> 7;
	A = (A << 1) | FLAG_C;
	FLAG_Z = 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = carry;
}

void CPU::rra()
{
	u8 carry = A & 0x01;
	A = (A >> 1) | (FLAG_C << 7);
	FLAG_Z = 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = carry;
}

// CB commands
void CPU::rlc(u8& reg)
{
	FLAG_C = reg >> 7;
	reg = (reg << 1) | FLAG_C;
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::rrc(u8& reg)
{
	FLAG_C = reg & 0x01;
	reg = (reg >> 1) | (FLAG_C << 7);
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::rl(u8& reg)
{
	FLAG_C = reg >> 7;
	reg = (reg << 1) | FLAG_C;
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::rr(u8& reg)
{
	u8 temp_carry = FLAG_C;
	FLAG_C = reg & 0x01;

	reg >>= 1;
	if (temp_carry) { reg |= (1 << 7); }

	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::sla(u8& reg)
{
	FLAG_C = reg >> 7;
	reg = reg << 1;
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::sra(u8& reg)
{
	FLAG_C = reg & 0x01;
	reg = (reg >> 1) | (reg & 0x80);
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::swap(u8& reg)
{
	reg = (reg << 4) | (reg >> 4);
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = 0;
}

// adds to A
void CPU::add(u8 val)
{
	FLAG_C = u16(A) + u16(val) > 0xFF;
	u8 result = A + val;
	FLAG_N = 0;
	// carry from bit 3 to 4
	FLAG_H = ((A & 0x0F) + (val & 0x0F)) > 0x0F;
	FLAG_Z = result == 0;
	A = result;
}

// adds to HL
void CPU::add(u16 val)
{
	FLAG_C = u32(HL) + u32(val) > 0xFFFF;
	u16 result = HL + val;
	FLAG_N = 0;
	// carry from bit 11 to 12
	FLAG_H = ((HL & 0x0FFF) + (val & 0x0FFF)) > 0x0FFF;
	HL = result;
}

void CPU::adc(u8 val)
{	
	u8 carry = FLAG_C;
	FLAG_C = u16(A) + u16(val) + u16(carry) > 0xFF;
	u8 result = A + val + carry;
	FLAG_Z = result == 0;
	FLAG_N = 0;
	// carry from bit 3 to 4
	FLAG_H = ((A & 0x0F) + (val & 0x0F) + carry) > 0x0F;
	A = result;
}

void CPU::sub(u8 val)
{
	FLAG_C = A < val;
	u8 result = A - val;
	FLAG_N = 1;
	FLAG_H = ((A & 0x0F) < (val & 0x0F));
	FLAG_Z = result == 0;
	A = result;
}

void CPU::sbc(u8 val)
{
	u8 carry = FLAG_C;
	FLAG_C = A < u16(val) + u16(carry);
	u8 result = A - val - carry;
	FLAG_N = 1;
	FLAG_H = ((A & 0x0F) < (val & 0x0F) - carry);
	A = result;
}

void CPU::srl(u8& reg)
{
	FLAG_C = reg & 0x01;
	reg = reg >> 1;
	FLAG_Z = reg == 0;
	FLAG_N = 0;
	FLAG_H = 0;
}

void CPU::bit(u8 bit, u8 reg)
{
	FLAG_Z = (reg & (1 << bit)) == 0;
	FLAG_N = 0;
	FLAG_H = 1;
}

void CPU::res(u8 bit, u8& reg)
{
	reg &= ~(1 << bit);
}

void CPU::set(u8 bit, u8& reg)
{
	reg |= (1 << bit);
}

void CPU::_and(u8 val)
{
	A = A & val;
	FLAG_Z = A == 0;
	FLAG_N = 0;
	FLAG_H = 1;
	FLAG_C = 0;
}

void CPU::_xor(u8 val)
{
	A = A ^ val;
	FLAG_Z = A == 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = 0;
}

void CPU::_or(u8 val)
{
	A = A | val;
	FLAG_Z = A == 0;
	FLAG_N = 0;
	FLAG_H = 0;
	FLAG_C = 0;
}

void CPU::cp(u8 val)
{
	FLAG_Z = A == val;
	FLAG_C = A < val;
	FLAG_N = 1;
	FLAG_H = ((A & 0x0F) < (val & 0x0F));
}

// Credit: https://github.com/LIJI32/SameBoy/blob/master/Core/sm83_cpu.c
void CPU::daa()
{
	int a = A;

	if (!FLAG_N)
	{
		if (FLAG_H || (a & 0xF) > 9) { a += 0x06; }

		if (FLAG_C || a > 0x9F) { a += 0x60; }
	}
	else
	{
		if (FLAG_H) { a = (a - 6) & 0xFF; }

		if (FLAG_C) { a -= 0x60; }
	}

	F &= ~(FLAG_H | FLAG_Z);

	if ((a & 0x100) == 0x100) { F |= FLAG_C; }

	a &= 0xFF;

	if (a == 0) { F |= FLAG_Z; }

	A = (u8)a;
}

u16 CPU::pop()
{
	auto val = mmu->read_short(sp);
	sp += 2;
	return val;

}

void CPU::push(u16 val)
{
	//this->ram->set(this->SP - 1, ((val & 0xFF00) >> 8) & 0xFF);
	//this->ram->set(this->SP - 2, val & 0xFF);
	//this->SP -= 2;

	mmu->write_short(sp - 2, val);
	sp -= 2;
}

//void CPU::call(bool condition)
//{
//	if (condition)
//	{
//		push(pc); 
//		pc = mmu->read_short(pc + 1); 
//		pc -= 1; 
//	}
//}
