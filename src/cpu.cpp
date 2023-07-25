#include "cpu.h"

CPU::CPU(MMU* mmu)
{
	AF = 0x1000;
	BC = 0xFF13;
	DE = 0x00C1;
	HL = 0x8403;

	pc = 0x100;
	sp = 0xFFFE;

	this->mmu = mmu;

}

// instructions pre-increment pc for correct order evaluation
void CPU::execute(u8 opcode)
{
	//need to check overloading different 1 or 2 bytes for some writes
	std::cout << OPCODE_NAMES[opcode] << std::endl;

	//modify clock cycles here

	switch (opcode)
	{
	// 8 bit load instructions
	case 0x02: mmu->write_byte(BC, A); break;
	case 0x06: B = mmu->read_byte(++pc); break;
	case 0x0A: A = mmu->read_byte(BC); break;
	case 0x0E: C = mmu->read_byte(++pc); break;
	case 0x12: mmu->write_byte(DE, A); break;
	case 0x16: D = mmu->read_byte(++pc); break;
	case 0x1A: A = mmu->read_byte(DE); break;
	case 0x1E: E = mmu->read_byte(++pc); break;
	case 0x22: mmu->write_byte(HL, A); HL++; break;
	case 0x26: H = mmu->read_byte(++pc); break;
	case 0x2A: A = mmu->read_byte(HL); HL++; break;
	case 0x2E: L = mmu->read_byte(++pc); break;
	case 0x32: mmu->write_byte(HL, A); HL--; break;
	case 0x36: mmu->write_byte(HL, mmu->read_byte(++pc)); break;
	case 0x3A: A = mmu->read_byte(HL); HL--; break;
	case 0x3E: A = mmu->read_byte(++pc); break;

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

	case 0xE0: mmu->write_byte(0xFF00 + mmu->read_byte(++pc), A); break;
	case 0xE2: mmu->write_byte(0xFF00 + C, A); break;

	case 0xEA: mmu->write_byte(mmu->read_short(++pc), A); pc += 1;  break; 
	case 0xF0: A = mmu->read_byte(0xFF00 + mmu->read_byte(++pc)); break;
	case 0xF2: A = mmu->read_byte(0xFF00 + C); break;
	case 0xFA: A = mmu->read_byte(mmu->read_short(++pc)); pc += 1; break; 

	// 16 bit load instructions
	case 0x01: BC = mmu->read_short(++pc); pc++; break;
	case 0x08: mmu->write_short(mmu->read_short(++pc), sp); pc += 1; break;
	case 0x11: DE = mmu->read_short(++pc); pc++; break;
	case 0x21: HL = mmu->read_short(++pc); pc++; break;
	case 0x31: sp = mmu->read_short(++pc); pc++; break;
	case 0xC1: pop(BC); break;
	case 0xC5: push(BC); break;
	case 0xD1: pop(DE); break;
	case 0xD5: push(DE); break;
	case 0xE1: pop(HL); break;
	case 0xE5: push(HL); break;
	case 0xF1: pop(AF); break;
	case 0xF5: push(AF); break;
	case 0xF8: HL = sp + mmu->read_byte(++pc); break;
	case 0xF9: sp = HL; break;

	// 8 bit arithmetic/logic instructions
	case 0x04: increment(B); break;
	case 0x05: decrement(B); break;
	case 0x0C: increment(C); break;
	case 0x0D: decrement(C); break;
	case 0x14: increment(D); break;
	case 0x15: decrement(D); break;
	case 0x1C: increment(E); break;
	case 0x1D: decrement(E); break;
	case 0x24: increment(H); break;
	case 0x25: decrement(H); break;
	case 0x2C: increment(L); break;
	case 0x2D: decrement(L); break;
	case 0x34: u8 temp = mmu->read_byte(HL); increment(temp); mmu->write_byte(HL, temp); break;
	case 0x35: temp = mmu->read_byte(HL); decrement(temp); mmu->write_byte(HL, temp); break;
	case 0x3C: increment(A); break;
	case 0x3D: decrement(A); break;
	
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

	case 0xC6: add(mmu->read_byte(pc)); pc += 1; break;
	case 0xCE: adc(mmu->read_byte(pc)); pc += 1; break;
	case 0xD6: sub(mmu->read_byte(pc)); pc += 1; break;
	case 0xDE: sbc(mmu->read_byte(pc)); pc += 1; break;
	case 0xE6: _and(mmu->read_byte(pc)); pc += 1; break;
	case 0xEE: _xor(mmu->read_byte(pc)); pc += 1; break;
	case 0xF6: _or(mmu->read_byte(pc)); pc += 1; break;
	case 0xFE: cp(mmu->read_byte(pc)); pc += 1; break;

	
	//case 0x00: break;	
	//case 0x03: BC++; break;
	//case 0x04: increment(B); break;
	//case 0x05: B--; break;
	//case 0x07: rlca(); break;
	//case 0x08: mmu->write(mmu->read(pc), sp); pc += 2; break;
	//case 0x09: add(HL, BC); break;
	//case 0x0B: BC--; break;
	//case 0x0C: increment(C); break;
	//case 0x0D: decrement(C); break;
	//case 0x0F: rrca(); break;

	//case 0x10: break;

	default:
		break;
	}
	
	pc += 1;
}

void CPU::increment(u8& reg)
{
	reg++;
	if (reg == 0) { F.Z = 1; }
	F.N = 0;
	F.H = (reg & 0x0F) == 0x00;
}

void CPU::decrement(u8& reg)
{
	reg--;
	if (reg == 0) { F.Z = 1; }
	F.N = 1;
	F.H = (reg & 0x0F) == 0x0F;
}

void CPU::rlca()
{
	u8 carry = A >> 7;
	A = (A << 1) | carry;
	F.Z = 0;
	F.N = 0;
	F.H = 0;
	F.C = carry;
}

void CPU::rrca()
{
	u8 carry = A & 0x01;
	A = (A >> 1) | (carry << 7);
	F.Z = 0;
	F.N = 0;
	F.H = 0;
	F.C = carry;
}

void CPU::add(u8 val)
{
	F.C = u16(A) + u16(val) > 0xFF;
	u8 result = A + val;
	F.N = 0;
	// carry from bit 3 to 4
	F.H = ((A & 0x0F) + (val & 0x0F)) > 0x0F;
	A = result;
}

void CPU::adc(u8 val)
{	
	u8 carry = F.C;
	F.C = u16(A) + u16(val) + u16(carry) > 0xFF;
	u8 result = A + val + carry;
	F.N = 0;
	// carry from bit 3 to 4
	F.H = ((A & 0x0F) + (val & 0x0F) + carry) > 0x0F;
	A = result;
}

void CPU::sub(u8 val)
{
	F.C = A < val;
	u8 result = A - val;
	F.N = 1;
	F.H = ((A & 0x0F) < (val & 0x0F));
	A = result;
}

void CPU::sbc(u8 val)
{
	u8 carry = F.C;
	F.C = A < u16(val) + u16(carry);
	u8 result = A - val - carry;
	F.N = 1;
	F.H = ((A & 0x0F) < (val & 0x0F) - carry);
	A = result;
}

//void CPU::add(u16 reg)
//{
//	F.C = A + reg > 0xFFFF;
//	u16 result = A + reg;
//	F.N = 0;
//	// carry from bit 11 to 12
//	F.H = ((val1 & 0x0FFF) + (val2 & 0x0FFF)) > 0x0FFF;
//	A = result & 0xFF;
//}

void CPU::_and(u8 val)
{
	A = A & val;
	F.Z = A == 0;
	F.N = 0;
	F.H = 1;
	F.C = 0;
}

void CPU::_xor(u8 val)
{
	A = A ^ val;
	F.Z = A == 0;
	F.N = 0;
	F.H = 0;
	F.C = 0;
}

void CPU::_or(u8 val)
{
	A = A | val;
	F.Z = A == 0;
	F.N = 0;
	F.H = 0;
	F.C = 0;
}

void CPU::cp(u8 val)
{
	F.Z = A == val;
	F.C = A < val;
	F.N = 1;
	F.H = ((A & 0x0F) < (val & 0x0F));
}

void CPU::pop(u16& reg)
{
	reg = mmu->read_short(sp);
	sp += 2;
}

// not sure about this
void CPU::push(u16& reg)
{
	sp -= 2;
	reg = mmu->read_short(sp);
}