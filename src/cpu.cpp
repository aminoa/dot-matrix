#include "CPU.h"
#include <iostream>

#define UNIMPLEMENTED(instruction) std::cout << "Unimplemented Instruction: " << instruction << std::endl; exit(1);
#define PRINT(instruction) std::cout << "Instruction: " << instruction << std::endl;

CPU::CPU(MMU* mmu)
{
	A = 0x10;
	F = 0x00;
	B = 0xFF;
	C = 0x13;
	D = 0x00;
	E = 0xC1;
	H = 0x84;
	L = 0x03;

	PC = 0x100;
	SP = 0xFFFE;

	this->mmu = mmu;
}

void CPU::Jump(int flag = 0)
{
	PC = mmu->ReadShort(PC);
	AF = mmu->ReadShort(PC);;
}

uint8_t CPU::Add(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 + operand2;

	F.Z = (result == 0);
	F.N = 0;
	F.H = ((operand1 & 0xF) + (operand2 & 0xF)) > 0xF;
	F.C = (result < operand1);
	return result;
}


void CPU::ExecuteInstruction(uint8_t opcode)
{
	switch (opcode)
	{
	case 0x00: //NOP
		break;
	case 0x01:
		UNIMPLEMENTED("LD BC, d16");
		break;
	case 0x02:
		UNIMPLEMENTED("LD (BC), A");
		break;
	case 0x03:
		UNIMPLEMENTED("INC BC");
		break;
	case 0x04:
		UNIMPLEMENTED("INC B");
		break;
	case 0x05:
		UNIMPLEMENTED("DEC B");
		break;
	case 0x06:
		UNIMPLEMENTED("LD B, d8");
		break;
	case 0x07:
		UNIMPLEMENTED("RLCA");
		break;
	case 0x08:
		UNIMPLEMENTED("LD (a16), SP");
		break;
	case 0x09:
		UNIMPLEMENTED("ADD HL, BC");
		break;
	case 0x0A:
		UNIMPLEMENTED("LD A, (BC)");
		break;
	case 0x0B:
		UNIMPLEMENTED("DEC BC");
		break;
	case 0x0C:
		UNIMPLEMENTED("INC C");
		break;
	case 0x0D:
		UNIMPLEMENTED("DEC C");
		break;
	case 0x0E:
		UNIMPLEMENTED("LD C, d8");
		break;
	case 0x0F:
		UNIMPLEMENTED("RRCA");
		break;
	case 0x10:
		UNIMPLEMENTED("STOP");
		break;
	case 0x11:
		UNIMPLEMENTED("LD DE, d16");
		break;
	case 0x12:
		UNIMPLEMENTED("LD (DE), A");
		break;
	case 0x13:
		UNIMPLEMENTED("INC DE");
		break;
	case 0x14:
		UNIMPLEMENTED("INC D");
		break;
	case 0x15:
		UNIMPLEMENTED("DEC D");
		break;
	case 0x16:
		UNIMPLEMENTED("LD D, d8");
		break;
	case 0x17:
		UNIMPLEMENTED("RLA");
		break;
	case 0x18:
		UNIMPLEMENTED("JR r8");
		break;
	case 0x19:
		UNIMPLEMENTED("ADD HL, DE");
		break;
	case 0x1A:
		UNIMPLEMENTED("LD A, (DE)");
		break;
	case 0x1B:
		UNIMPLEMENTED("DEC DE");
		break;
	case 0x1C:
		UNIMPLEMENTED("INC E");
		break;
	case 0x1D:
		UNIMPLEMENTED("DEC E");
		break;
	case 0x1E:
		UNIMPLEMENTED("LD E, d8");
		break;
	case 0x1F:
		UNIMPLEMENTED("RRA");
		break;
	case 0x20:
		UNIMPLEMENTED("JR NZ, r8");
		break;
	case 0x21:
		UNIMPLEMENTED("LD HL, d16");
		break;
	case 0x22:
		UNIMPLEMENTED("LD (HL+), A");
		break;
	case 0x23:
		UNIMPLEMENTED("INC HL");
		break;
	case 0x24:
		UNIMPLEMENTED("INC H");
		break;
	case 0x25:
		UNIMPLEMENTED("DEC H");
		break;
	case 0x26:
		UNIMPLEMENTED("LD H, d8");
		break;
	case 0x27:
		UNIMPLEMENTED("DAA");
		break;
	case 0x28:
		UNIMPLEMENTED("JR Z, r8");
		break;
	case 0x29:
		UNIMPLEMENTED("ADD HL, HL");
		break;
	case 0x2A:
		UNIMPLEMENTED("LD A, (HL+)");
		break;
	case 0x2B:
		UNIMPLEMENTED("DEC HL");
		break;
	case 0x2C:
		UNIMPLEMENTED("INC L");
		break;
	case 0x2D:
		UNIMPLEMENTED("DEC L");
		break;
	case 0x2E:
		UNIMPLEMENTED("LD L, d8");
		break;
	case 0x2F:
		UNIMPLEMENTED("CPL");
		break;
	case 0x30:
		UNIMPLEMENTED("JR NC, r8");
		break;
	case 0x31:
		UNIMPLEMENTED("LD SP, d16");
		break;
	case 0x32:
		UNIMPLEMENTED("LD (HL-), A");
		break;
	case 0x33:
		UNIMPLEMENTED("INC SP");
		break;
	case 0x34:
		UNIMPLEMENTED("INC (HL)");
		break;
	case 0x35:
		UNIMPLEMENTED("DEC (HL)");
		break;
	case 0x36:
		UNIMPLEMENTED("LD (HL), d8");
		break;
	case 0x37:
		UNIMPLEMENTED("SCF");
		break;
	case 0x38:
		UNIMPLEMENTED("JR C, r8");
		break;
	case 0x39:
		UNIMPLEMENTED("ADD HL, SP");
		break;
	case 0x3A:
		UNIMPLEMENTED("LD A, (HL-)");
		break;
	case 0x3B:
		UNIMPLEMENTED("DEC SP");
		break;
	case 0x3C:
		UNIMPLEMENTED("INC A");
		break;
	case 0x3D:
		UNIMPLEMENTED("DEC A");
		break;
	case 0x3E:
		UNIMPLEMENTED("LD A, d8");
		break;
	case 0x3F:
		UNIMPLEMENTED("CCF");
		break;
	case 0x40:
		PRINT("LD B, B");
		break;
	case 0x41:
		PRINT("LD B, C")
		B = C;
		break;
	case 0x42:
		PRINT("LD B, D");
		B = D;
		break;
	case 0x43:
		PRINT("LD B, E");
		B = E;
		break;
	case 0x44:
		PRINT("LD B, H");
		B = H;
		break;
	case 0x45:
		PRINT("LD B, L");
		B = L;
		break;
	case 0x46:
		PRINT("LD B, (HL)");
		B = mmu->ReadByte(HL);
		break;
	case 0x47:
		PRINT("LD B, A");
		B = A;
		break;
	case 0x48:
		PRINT("LD C, B");
		C = B;
		break;
	case 0x49:
		PRINT("LD C, C");
		break;
	case 0x4A:
		PRINT("LD C, D");
		C = D;
		break;
	case 0x4B:
		PRINT("LD C, E");
		C = E;
		break;
	case 0x4C:
		PRINT("LD C, H");
		C = H;
		break;
	case 0x4D:
		PRINT("LD C, L");
		C = L;
		break;
	case 0x4E:
		PRINT("LD C, (HL)");
		C = mmu->ReadByte(HL);
		break;
	case 0x4F:
		PRINT("LD C, A");
		C = A;
		break;
	case 0x50:
		PRINT("LD D, B");
		D = B;
		break;
	case 0x51:
		PRINT("LD D, C");
		D = C;
		break;
	case 0x52:
		PRINT("LD D, D");
		break;
	case 0x53:
		PRINT("LD D, E");
		D = E;
	case 0x54:
		PRINT("LD D, H");
		D = H;
		break;
	case 0x55:
		PRINT("LD D, L");
		D = L;
		break;
	case 0x56:
		PRINT("LD D, (HL)");
		D = mmu->ReadByte(HL);
		break;
	case 0x57:
		PRINT("LD D, A");
		D = A;
		break;
	case 0x58:
		PRINT("LD E, B");
		E = B;
		break;
	case 0x59:
		PRINT("LD E, C");
		E = C;
		break;
	case 0x5A:
		PRINT("LD E, D");
		E = D;
		break;
	case 0x5B:
		PRINT("LD E, E");
		break;
	case 0x5C:
		PRINT("LD E, H");
		E = H;
		break;
	case 0x5D:
		PRINT("LD E, L");
		E = L;
		break;
	case 0x5E:
		PRINT("LD E, (HL)");
		E = mmu->ReadByte(HL);
		break;
	case 0x5F:
		PRINT("LD E, A");
		E = A;
		break;
	case 0x60:
		PRINT("LD H, B");
		H = B;
		break;
	case 0x61:
		PRINT("LD H, C");
		H = C;
		break;
	case 0x62:
		PRINT("LD H, D");
		H = D;
		break;
	case 0x63:
		PRINT("LD H, E");
		H = E;
		break;
	case 0x64:
		PRINT("LD H, H");
		break;
	case 0x65:
		PRINT("LD H, L");
		H = L;
		break;
	case 0x66:
		PRINT("LD H, (HL)");
		H = mmu->ReadByte(HL);
		break;
	case 0x67:
		PRINT("LD H, A");
		H = A;
		break;
	case 0x68:
		PRINT("LD L, B");
		L = B;
		break;
	case 0x69:
		PRINT("LD L, C");
		L = C;
		break;
	case 0x6A:
		PRINT("LD L, D");
		L = D;
		break;
	case 0x6B:
		PRINT("LD L, E");
		L = E;
		break;
	case 0x6C:
		PRINT("LD L, H");
		L = H;
		break;
	case 0x6D:
		PRINT("LD L, L");
		break;
	case 0x6E:
		PRINT("LD L, (HL)");
		L = mmu->ReadByte(HL);
		break;
	case 0x6F:
		PRINT("LD L, A");
		L = A;
		break;
	case 0x70:
		PRINT("LD (HL), B");
		mmu->WriteByte(HL, B);
		break;
	case 0x71:
		PRINT("LD (HL), C");
		mmu->WriteByte(HL, C);
		break;
	case 0x72:
		PRINT("LD (HL), D");
		mmu->WriteByte(HL, D);
		break;
	case 0x73:
		PRINT("LD (HL), E");
		mmu->WriteByte(HL, E);
		break;
	case 0x74:
		PRINT("LD (HL), H");
		mmu->WriteByte(HL, H);
		break;
	case 0x75:
		PRINT("LD (HL), L");
		mmu->WriteByte(HL, L);
		break;
	case 0x76: //what the fuck
		UNIMPLEMENTED("HALT");
	case 0x77:
		PRINT("LD (HL), A");
		mmu->WriteByte(HL, A);
		break;
	case 0x78:
		PRINT("LD A, B");
		A = B;
		break;
	case 0x79:
		PRINT("LD A, C");
		A = C;
		break;
	case 0x7A:
		PRINT("LD A, D");
		A = D;
		break;
	case 0x7B:
		PRINT("LD A, E");
		A = E;
		break;
	case 0x7C:
		PRINT("LD A, H");
		A = H;
		break;
	case 0x7D:
		PRINT("LD A, L");
		A = L;
		break;
	case 0x7E:
		PRINT("LD A, (HL)");
		A = mmu->ReadByte(HL);
		break;
	case 0x7F:
		PRINT("LD A, A");
		break;
	case 0x80:
		PRINT("ADD A, B");
		A += B;
		break;
	case 0x81:
		PRINT("ADD A, C");
		A += C;
		break;
	case 0x82:
		PRINT("ADD A, D");
		A += D;
		break;
	case 0x83:
		PRINT("ADD A, E");
		A += E;
		break;
	case 0x84:
		PRINT("ADD A, H");
		A += H;
		break;
	case 0x85:
		PRINT("ADD A, L");
		A += L;
		break;
	case 0x86:
		PRINT("ADD A, (HL)");
		A += mmu->ReadByte(HL);
		break;
	case 0x87:
		PRINT("ADD A, A");
		A += A;
		break;
	case 0x88:
		PRINT("ADC A, B");

		break;
	case 0x89:
		UNIMPLEMENTED("ADC A, C");
		break;
	case 0x8A:
		UNIMPLEMENTED("ADC A, D");
		break;
	case 0x8B:
		UNIMPLEMENTED("ADC A, E");
		break;
	case 0x8C:
		UNIMPLEMENTED("ADC A, H");
		break;
	case 0x8D:
		UNIMPLEMENTED("ADC A, L");
		break;
	case 0x8E:
		UNIMPLEMENTED("ADC A, (HL)");
		break;
	case 0x8F:
		UNIMPLEMENTED("ADC A, A");
		break;
	case 0x90:
		UNIMPLEMENTED("SUB B");
		break;
	case 0x91:
		UNIMPLEMENTED("SUB C");
		break;
	case 0x92:
		UNIMPLEMENTED("SUB D");
		break;
	case 0x93:
		UNIMPLEMENTED("SUB E");
		break;
	case 0x94:
		UNIMPLEMENTED("SUB H");
		break;
	case 0x95:
		UNIMPLEMENTED("SUB L");
		break;
	case 0x96:
		UNIMPLEMENTED("SUB (HL)");
		break;
	case 0x97:
		UNIMPLEMENTED("SUB A");
		break;
	case 0x98:
		UNIMPLEMENTED("SBC A, B");
		break;
	case 0x99:
		UNIMPLEMENTED("SBC A, C");
		break;
	case 0x9A:
		UNIMPLEMENTED("SBC A, D");
		break;
	case 0x9B:
		UNIMPLEMENTED("SBC A, E");
		break;
	case 0x9C:
		UNIMPLEMENTED("SBC A, H");
		break;
	case 0x9D:
		UNIMPLEMENTED("SBC A, L");
		break;
	case 0x9E:
		UNIMPLEMENTED("SBC A, (HL)");
		break;
	case 0x9F:
		UNIMPLEMENTED("SBC A, A");
		break;
	case 0xA0:
		UNIMPLEMENTED("AND B");
		break;
	case 0xA1:
		UNIMPLEMENTED("AND C");
		break;
	case 0xA2:
		UNIMPLEMENTED("AND D");
		break;
	case 0xA3:
		UNIMPLEMENTED("AND E");
		break;
	case 0xA4:
		UNIMPLEMENTED("AND H");
		break;
	case 0xA5:
		UNIMPLEMENTED("AND L");
		break;
	case 0xA6:
		UNIMPLEMENTED("AND (HL)");
		break;
	case 0xA7:
		UNIMPLEMENTED("AND A");
		break;
	case 0xA8:
		UNIMPLEMENTED("XOR B");
		break;
	case 0xA9:
		UNIMPLEMENTED("XOR C");
		break;
	case 0xAA:
		UNIMPLEMENTED("XOR D");
		break;
	case 0xAB:
		UNIMPLEMENTED("XOR E");
		break;
	case 0xAC:
		UNIMPLEMENTED("XOR H");
		break;
	case 0xAD:
		UNIMPLEMENTED("XOR L");
		break;
	case 0xAE:
		UNIMPLEMENTED("XOR (HL)");
		break;
	case 0xAF:
		UNIMPLEMENTED("XOR A");
		break;
	case 0xB0:
		UNIMPLEMENTED("OR B");
		break;
	case 0xB1:
		UNIMPLEMENTED("OR C");
		break;
	case 0xB2:
		UNIMPLEMENTED("OR D");
		break;
	case 0xB3:
		UNIMPLEMENTED("OR E");
		break;
	case 0xB4:
		UNIMPLEMENTED("OR H");
		break;
	case 0xB5:
		UNIMPLEMENTED("OR L");
		break;
	case 0xB6:
		UNIMPLEMENTED("OR (HL)");
		break;
	case 0xB7:
		UNIMPLEMENTED("OR A");
		break;
	case 0xB8:
		UNIMPLEMENTED("CP B");
		break;
	case 0xB9:
		UNIMPLEMENTED("CP C");
		break;
	case 0xBA:
		UNIMPLEMENTED("CP D");
		break;
	case 0xBB:
		UNIMPLEMENTED("CP E");
		break;
	case 0xBC:
		UNIMPLEMENTED("CP H");
		break;
	case 0xBD:
		UNIMPLEMENTED("CP L");
		break;
	case 0xBE:
		UNIMPLEMENTED("CP (HL)");
		break;
	case 0xBF:
		UNIMPLEMENTED("CP A");
		break;
	case 0xC0:
		UNIMPLEMENTED("RET NZ");
		break;
	case 0xC1:
		UNIMPLEMENTED("POP BC");
		break;
	case 0xC2: 
		PRINT("JP NZ, nn");
		//Jump_Flag();
	case 0xC3: 
		PRINT("JP nn");
		PC = mmu->ReadShort(PC);
		break;
	case 0xC4:
		UNIMPLEMENTED("CALL NZ, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xC5:
		UNIMPLEMENTED("PUSH BC");
		break;
	case 0xC6:
		UNIMPLEMENTED("ADD A, 0x%02X", opcode[1]);
		break;
	case 0xC7:
		UNIMPLEMENTED("RST 0x00");
		break;
	case 0xC8:
		UNIMPLEMENTED("RET Z");
		break;
	case 0xC9:
		UNIMPLEMENTED("RET");
		break;
	case 0xCA:
		UNIMPLEMENTED("JP Z, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCB:
		UNIMPLEMENTED("CB PREFIX");
		break;
	case 0xCC: //want to check these three
		UNIMPLEMENTED("CALL Z, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCD:
		UNIMPLEMENTED("CALL 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCE:
		UNIMPLEMENTED("ADC A, 0x%02X", opcode[1]);
		break;
	case 0xCF:
		UNIMPLEMENTED("RST 0x08");
		break;
	case 0xD0:
		UNIMPLEMENTED("RET NC");
		break;
	case 0xD1:
		UNIMPLEMENTED("POP DE");
		break;
	case 0xD2:
		UNIMPLEMENTED("JP NC, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xD4:
		UNIMPLEMENTED("CALL NC, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xD5:
		UNIMPLEMENTED("PUSH DE");
		break;
	case 0xD6:
		UNIMPLEMENTED("SUB 0x%02X", opcode[1]);
		break;
	case 0xD7:
		UNIMPLEMENTED("RST 0x10");
		break;
	case 0xD8:
		UNIMPLEMENTED("RET C");
		break;
	case 0xD9:
		UNIMPLEMENTED("RETI");
		break;
	case 0xDA:
		UNIMPLEMENTED("JP C, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xDC:
		UNIMPLEMENTED("CALL C, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xDE:
		UNIMPLEMENTED("SBC A, 0x%02X", opcode[1]);
		break;
	case 0xDF:
		UNIMPLEMENTED("RST 0x18");
		break;
	case 0xE0:
		UNIMPLEMENTED("LDH (0xFF00 + 0x%02X), A", opcode[1]);
		break;
	case 0xE1:
		UNIMPLEMENTED("POP HL");
		break;
	case 0xE2:
		UNIMPLEMENTED("LD (0xFF00 + C), A");
		break;
	case 0xE5:
		UNIMPLEMENTED("PUSH HL");
		break;
	case 0xE6:
		UNIMPLEMENTED("AND 0x%02X", opcode[1]);
		break;
	case 0xE7:
		UNIMPLEMENTED("RST 0x20");
		break;
	case 0xE8:
		UNIMPLEMENTED("ADD SP, 0x%02X", opcode[1]);
		break;
	case 0xE9:
		UNIMPLEMENTED("JP (HL)");
		break;
	case 0xEA:
		UNIMPLEMENTED("LD (0x%04X), A", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xEE:
		UNIMPLEMENTED("XOR 0x%02X", opcode[1]);
		break;
	case 0xEF:
		UNIMPLEMENTED("RST 0x28");
		break;
	case 0xF0:
		UNIMPLEMENTED("LDH A, (0xFF00 + 0x%02X)", opcode[1]);
		break;
	case 0xF1:
		UNIMPLEMENTED("POP AF");
		break;
	case 0xF2:
		UNIMPLEMENTED("LD A, (0xFF00 + C)");
		break;
	case 0xF3:
		UNIMPLEMENTED("DI");
		break;
	case 0xF5:
		UNIMPLEMENTED("PUSH AF");
		break;
	case 0xF6:
		UNIMPLEMENTED("OR 0x%02X", opcode[1]);
		break;
	case 0xF7:
		UNIMPLEMENTED("RST 0x30");
		break;
	case 0xF8:
		UNIMPLEMENTED("LD HL, SP + 0x%02X", opcode[1]);
		break;
	case 0xF9:
		UNIMPLEMENTED("LD SP, HL");
		break;
	case 0xFA: //doubel check
		UNIMPLEMENTED("LD A, (0x%04X)", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xFB:
		UNIMPLEMENTED("EI");
		break;
	case 0xFE:
		UNIMPLEMENTED("CP 0x%02X", opcode[1]);
		break;
	case 0xFF:
		UNIMPLEMENTED("RST 0x38");
		break;
	}
};

