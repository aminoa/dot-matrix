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

void CPU::execute(u8 opcode)
{
	//need to check overloading different 1 or 2 bytes for some writes
	std::cout << OPCODE_NAMES[opcode] << std::endl;

	//modify clock cycles here

	switch (opcode)
	{
	// 8 bit load instructions
	case 0x02: mmu->write_byte(BC, A); break;
	case 0x06: B = mmu->read_byte(pc++); break;
	case 0x0A: A = mmu->read_byte(BC); break;
	case 0x0E: C = mmu->read_byte(pc++); break;
	case 0x12: mmu->write_byte(DE, A); break;
	case 0x16: D = mmu->read_byte(pc++); break;
	case 0x1A: A = mmu->read_byte(DE); break;
	case 0x1E: E = mmu->read_byte(pc++); break;
	case 0x22: mmu->write_byte(HL, A); HL++; break;
	case 0x26: H = mmu->read_byte(pc++); break;
	case 0x2A: A = mmu->read_byte(HL); HL++; break;
	case 0x2E: L = mmu->read_byte(pc++); break;
	case 0x32: mmu->write_byte(HL, A); HL--; break;
	case 0x36: mmu->write_byte(HL, mmu->read_byte(pc++)); break;
	case 0x3A: A = mmu->read_byte(HL); HL--; break;
	case 0x3E: A = mmu->read_byte(pc++); break;

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

	case 0xE0: mmu->write_byte(0xFF00 + mmu->read_byte(pc++), A); break;
	case 0xE2: mmu->write_byte(0xFF00 + C, A); break;

	case 0xEA: mmu->write_byte(mmu->read_byte(pc++) + mmu->read_byte(pc++), A); break; //not sure if this is right
	case 0xF0: A = mmu->read_byte(0xFF00 + mmu->read_byte(pc++)); break;
	case 0xF2: A = mmu->read_byte(0xFF00 + C); break;
	case 0xFA: A = mmu->read_byte(mmu->read_byte(pc++) + mmu->read_byte(pc++)); break;

	// 16 bit load instructions
	case 0x01: BC = mmu->read_short(pc++); pc++; break;


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
	//case 0x11: DE = mmu->read(pc); pc += 2; break;

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

void CPU::add(u16 val1, u16 val2)
{
	u16 result = val1 + val2;
	F.N = 0;
	//carry from bit 11 to 12
	F.H = ((val1 & 0x0FFF) + (val2 & 0x0FFF)) > 0x0FFF;
	F.C = result > 0xFFFF;
	A = result & 0xFF;
}