#include "CPU.h"
#include <iostream>

//need to make a good macro here

#define INSTRUCTION_PRINT(instruction) std::cout << instruction << std::endl;

CPU::CPU()
{
	PC = 0x100;
	SP = 0xFFFE;

	AF.A = 0x1;
	AF.F = 0x0;
	BC.B = 0xFF;
	BC.C = 0x13;
	DE.D = 0x0;
	DE.E = 0xC1;
	HL.H = 0x84;
	HL.L = 0x03;
}

void CPU::ExecuteInstruction(uint8_t opcode)
{

	switch (opcode)
	{
	case 0x00:
		INSTRUCTION_PRINT("NOP");
		break;
	case 0x01:
		INSTRUCTION_PRINT("LD BC, d16");
		break;
	case 0x02:
		INSTRUCTION_PRINT("LD (BC), A");
		break;
	case 0x03:
		INSTRUCTION_PRINT("INC BC");
		break;
	case 0x04:
		INSTRUCTION_PRINT("INC B");
		break;
	case 0x05:
		INSTRUCTION_PRINT("DEC B");
		break;
	case 0x06:
		INSTRUCTION_PRINT("LD B, d8");
		break;
	case 0x07:
		INSTRUCTION_PRINT("RLCA");
		break;
	case 0x08:
		INSTRUCTION_PRINT("LD (a16), SP");
		break;
	case 0x09:
		INSTRUCTION_PRINT("ADD HL, BC");
		break;
	case 0x0A:
		INSTRUCTION_PRINT("LD A, (BC)");
		break;
	case 0x0B:
		INSTRUCTION_PRINT("DEC BC");
		break;
	case 0x0C:
		INSTRUCTION_PRINT("INC C");
		break;
	case 0x0D:
		INSTRUCTION_PRINT("DEC C");
		break;
	case 0x0E:
		INSTRUCTION_PRINT("LD C, d8");
		break;
	case 0x0F:
		INSTRUCTION_PRINT("RRCA");
		break;
	case 0x10:
		INSTRUCTION_PRINT("STOP");
		break;
	case 0x11:
		INSTRUCTION_PRINT("LD DE, d16");
		break;
	case 0x12:
		INSTRUCTION_PRINT("LD (DE), A");
		break;
	case 0x13:
		INSTRUCTION_PRINT("INC DE");
		break;
	case 0x14:
		INSTRUCTION_PRINT("INC D");
		break;
	case 0x15:
		INSTRUCTION_PRINT("DEC D");
		break;
	case 0x16:
		INSTRUCTION_PRINT("LD D, d8");
		break;
	case 0x17:
		INSTRUCTION_PRINT("RLA");
		break;
	case 0x18:
		INSTRUCTION_PRINT("JR r8");
		break;
	case 0x19:
		INSTRUCTION_PRINT("ADD HL, DE");
		break;
	case 0x1A:
		INSTRUCTION_PRINT("LD A, (DE)");
		break;
	case 0x1B:
		INSTRUCTION_PRINT("DEC DE");
		break;
	case 0x1C:
		INSTRUCTION_PRINT("INC E");
		break;
	case 0x1D:
		INSTRUCTION_PRINT("DEC E");
		break;
	case 0x1E:
		INSTRUCTION_PRINT("LD E, d8");
		break;
	case 0x1F:
		INSTRUCTION_PRINT("RRA");
		break;
	case 0x20:
		INSTRUCTION_PRINT("JR NZ, r8");
		break;
	case 0x21:
		INSTRUCTION_PRINT("LD HL, d16");
		break;
	case 0x22:
		INSTRUCTION_PRINT("LD (HL+), A");
		break;
	case 0x23:
		INSTRUCTION_PRINT("INC HL");
		break;
	case 0x24:
		INSTRUCTION_PRINT("INC H");
		break;
	case 0x25:
		INSTRUCTION_PRINT("DEC H");
		break;
	case 0x26:
		INSTRUCTION_PRINT("LD H, d8");
		break;
	case 0x27:
		INSTRUCTION_PRINT("DAA");
		break;
	case 0x28:
		INSTRUCTION_PRINT("JR Z, r8");
		break;
	case 0x29:
		INSTRUCTION_PRINT("ADD HL, HL");
		break;
	case 0x2A:
		INSTRUCTION_PRINT("LD A, (HL+)");
		break;
	case 0x2B:
		INSTRUCTION_PRINT("DEC HL");
		break;
	case 0x2C:
		INSTRUCTION_PRINT("INC L");
		break;
	case 0x2D:
		INSTRUCTION_PRINT("DEC L");
		break;
	case 0x2E:
		INSTRUCTION_PRINT("LD L, d8");
		break;
	case 0x2F:
		INSTRUCTION_PRINT("CPL");
		break;
	case 0x30:
		INSTRUCTION_PRINT("JR NC, r8");
		break;
	case 0x31:
		INSTRUCTION_PRINT("LD SP, d16");
		break;
	case 0x32:
		INSTRUCTION_PRINT("LD (HL-), A");
		break;
	case 0x33:
		INSTRUCTION_PRINT("INC SP");
		break;
	case 0x34:
		INSTRUCTION_PRINT("INC (HL)");
		break;
	case 0x35:
		INSTRUCTION_PRINT("DEC (HL)");
		break;
	case 0x36:
		INSTRUCTION_PRINT("LD (HL), d8");
		break;
	case 0x37:
		INSTRUCTION_PRINT("SCF");
		break;
	case 0x38:
		INSTRUCTION_PRINT("JR C, r8");
		break;
	case 0x39:
		INSTRUCTION_PRINT("ADD HL, SP");
		break;
	case 0x3A:
		INSTRUCTION_PRINT("LD A, (HL-)");
		break;
	case 0x3B:
		INSTRUCTION_PRINT("DEC SP");
		break;
	case 0x3C:
		INSTRUCTION_PRINT("INC A");
		break;
	case 0x3D:
		INSTRUCTION_PRINT("DEC A");
		break;
	case 0x3E:
		INSTRUCTION_PRINT("LD A, d8");
		break;
	case 0x3F:
		INSTRUCTION_PRINT("CCF");
		break;
	case 0x40:
		INSTRUCTION_PRINT("LD B, B");
		break;
	case 0x41:
		INSTRUCTION_PRINT("LD B, C");
		break;
	case 0x42:
		INSTRUCTION_PRINT("LD B, D");
		break;
	case 0x43:
		INSTRUCTION_PRINT("LD B, E");
		break;
	case 0x44:
		INSTRUCTION_PRINT("LD B, H");
		break;
	case 0x45:
		INSTRUCTION_PRINT("LD B, L");
		break;
	case 0x46:
		INSTRUCTION_PRINT("LD B, (HL)");
		break;
	case 0x47:
		INSTRUCTION_PRINT("LD B, A");
		break;
	case 0x48:
		INSTRUCTION_PRINT("LD C, B");
		break;
	case 0x49:
		INSTRUCTION_PRINT("LD C, C");
		break;
	case 0x4A:
		INSTRUCTION_PRINT("LD C, D");
		break;
	case 0x4B:
		INSTRUCTION_PRINT("LD C, E");
		break;
	case 0x4C:
		INSTRUCTION_PRINT("LD C, H");
		break;
	case 0x4D:
		INSTRUCTION_PRINT("LD C, L");
		break;
	case 0x4E:
		INSTRUCTION_PRINT("LD C, (HL)");
		break;
	case 0x4F:
		INSTRUCTION_PRINT("LD C, A");
		break;
	case 0x50:
		INSTRUCTION_PRINT("LD D, B");
		break;
	case 0x51:
		INSTRUCTION_PRINT("LD D, C");
		break;
	case 0x52:
		INSTRUCTION_PRINT("LD D, D");
		break;
	case 0x53:
		INSTRUCTION_PRINT("LD D, E");
		break;
	case 0x54:
		INSTRUCTION_PRINT("LD D, H");
		break;
	case 0x55:
		INSTRUCTION_PRINT("LD D, L");
		break;
	case 0x56:
		INSTRUCTION_PRINT("LD D, (HL)");
		break;
	case 0x57:
		INSTRUCTION_PRINT("LD D, A");
		break;
	case 0x58:
		INSTRUCTION_PRINT("LD E, B");
		break;
	case 0x59:
		INSTRUCTION_PRINT("LD E, C");
		break;
	case 0x5A:
		INSTRUCTION_PRINT("LD E, D");
		break;
	case 0x5B:
		INSTRUCTION_PRINT("LD E, E");
		break;
	case 0x5C:
		INSTRUCTION_PRINT("LD E, H");
		break;
	case 0x5D:
		INSTRUCTION_PRINT("LD E, L");
		break;
	case 0x5E:
		INSTRUCTION_PRINT("LD E, (HL)");
		break;
	case 0x5F:
		INSTRUCTION_PRINT("LD E, A");
		break;
	case 0x60:
		INSTRUCTION_PRINT("LD H, B");
		break;
	case 0x61:
		INSTRUCTION_PRINT("LD H, C");
		break;
	case 0x62:
		INSTRUCTION_PRINT("LD H, D");
		break;
	case 0x63:
		INSTRUCTION_PRINT("LD H, E");
		break;
	case 0x64:
		INSTRUCTION_PRINT("LD H, H");
		break;
	case 0x65:
		INSTRUCTION_PRINT("LD H, L");
		break;
	case 0x66:
		INSTRUCTION_PRINT("LD H, (HL)");
		break;
	case 0x67:
		INSTRUCTION_PRINT("LD H, A");
		break;
	case 0x68:
		INSTRUCTION_PRINT("LD L, B");
		break;
	case 0x69:
		INSTRUCTION_PRINT("LD L, C");
		break;
	case 0x6A:
		INSTRUCTION_PRINT("LD L, D");
		break;
	case 0x6B:
		INSTRUCTION_PRINT("LD L, E");
		break;
	case 0x6C:
		INSTRUCTION_PRINT("LD L, H");
		break;
	case 0x6D:
		INSTRUCTION_PRINT("LD L, L");
		break;
	case 0x6E:
		INSTRUCTION_PRINT("LD L, (HL)");
		break;
	case 0x6F:
		INSTRUCTION_PRINT("LD L, A");
		break;
	case 0x70:
		INSTRUCTION_PRINT("LD (HL), B");
		break;
	case 0x71:
		INSTRUCTION_PRINT("LD (HL), C");
		break;
	case 0x72:
		INSTRUCTION_PRINT("LD (HL), D");
		break;
	case 0x73:
		INSTRUCTION_PRINT("LD (HL), E");
		break;
	case 0x74:
		INSTRUCTION_PRINT("LD (HL), H");
		break;
	case 0x75:
		INSTRUCTION_PRINT("LD (HL), L");
		break;
	case 0x76:
		INSTRUCTION_PRINT("HALT");
		break;
	case 0x77:
		INSTRUCTION_PRINT("LD (HL), A");
		break;
	case 0x78:
		INSTRUCTION_PRINT("LD A, B");
		break;
	case 0x79:
		INSTRUCTION_PRINT("LD A, C");
		break;
	case 0x7A:
		INSTRUCTION_PRINT("LD A, D");
		break;
	case 0x7B:
		INSTRUCTION_PRINT("LD A, E");
		break;
	case 0x7C:
		INSTRUCTION_PRINT("LD A, H");
		break;
	case 0x7D:
		INSTRUCTION_PRINT("LD A, L");
		break;
	case 0x7E:
		INSTRUCTION_PRINT("LD A, (HL)");
		break;
	case 0x7F:
		INSTRUCTION_PRINT("LD A, A");
		break;
	case 0x80:
		INSTRUCTION_PRINT("ADD A, B");
		break;
	case 0x81:
		INSTRUCTION_PRINT("ADD A, C");
		break;
	case 0x82:
		INSTRUCTION_PRINT("ADD A, D");
		break;
	case 0x83:
		INSTRUCTION_PRINT("ADD A, E");
		break;
	case 0x84:
		INSTRUCTION_PRINT("ADD A, H");
		break;
	case 0x85:
		INSTRUCTION_PRINT("ADD A, L");
		break;
	case 0x86:
		INSTRUCTION_PRINT("ADD A, (HL)");
		break;
	case 0x87:
		INSTRUCTION_PRINT("ADD A, A");
		break;
	case 0x88:
		INSTRUCTION_PRINT("ADC A, B");
		break;
	case 0x89:
		INSTRUCTION_PRINT("ADC A, C");
		break;
	case 0x8A:
		INSTRUCTION_PRINT("ADC A, D");
		break;
	case 0x8B:
		INSTRUCTION_PRINT("ADC A, E");
		break;
	case 0x8C:
		INSTRUCTION_PRINT("ADC A, H");
		break;
	case 0x8D:
		INSTRUCTION_PRINT("ADC A, L");
		break;
	case 0x8E:
		INSTRUCTION_PRINT("ADC A, (HL)");
		break;
	case 0x8F:
		INSTRUCTION_PRINT("ADC A, A");
		break;
	case 0x90:
		INSTRUCTION_PRINT("SUB B");
		break;
	case 0x91:
		INSTRUCTION_PRINT("SUB C");
		break;
	case 0x92:
		INSTRUCTION_PRINT("SUB D");
		break;
	case 0x93:
		INSTRUCTION_PRINT("SUB E");
		break;
	case 0x94:
		INSTRUCTION_PRINT("SUB H");
		break;
	case 0x95:
		INSTRUCTION_PRINT("SUB L");
		break;
	case 0x96:
		INSTRUCTION_PRINT("SUB (HL)");
		break;
	case 0x97:
		INSTRUCTION_PRINT("SUB A");
		break;
	case 0x98:
		INSTRUCTION_PRINT("SBC A, B");
		break;
	case 0x99:
		INSTRUCTION_PRINT("SBC A, C");
		break;
	case 0x9A:
		INSTRUCTION_PRINT("SBC A, D");
		break;
	case 0x9B:
		INSTRUCTION_PRINT("SBC A, E");
		break;
	case 0x9C:
		INSTRUCTION_PRINT("SBC A, H");
		break;
	case 0x9D:
		INSTRUCTION_PRINT("SBC A, L");
		break;
	case 0x9E:
		INSTRUCTION_PRINT("SBC A, (HL)");
		break;
	case 0x9F:
		INSTRUCTION_PRINT("SBC A, A");
		break;
	case 0xA0:
		INSTRUCTION_PRINT("AND B");
		break;
	case 0xA1:
		INSTRUCTION_PRINT("AND C");
		break;
	case 0xA2:
		INSTRUCTION_PRINT("AND D");
		break;
	case 0xA3:
		INSTRUCTION_PRINT("AND E");
		break;
	case 0xA4:
		INSTRUCTION_PRINT("AND H");
		break;
	case 0xA5:
		INSTRUCTION_PRINT("AND L");
		break;
	case 0xA6:
		INSTRUCTION_PRINT("AND (HL)");
		break;
	case 0xA7:
		INSTRUCTION_PRINT("AND A");
		break;
	case 0xA8:
		INSTRUCTION_PRINT("XOR B");
		break;
	case 0xA9:
		INSTRUCTION_PRINT("XOR C");
		break;
	case 0xAA:
		INSTRUCTION_PRINT("XOR D");
		break;
	case 0xAB:
		INSTRUCTION_PRINT("XOR E");
		break;
	case 0xAC:
		INSTRUCTION_PRINT("XOR H");
		break;
	case 0xAD:
		INSTRUCTION_PRINT("XOR L");
		break;
	case 0xAE:
		INSTRUCTION_PRINT("XOR (HL)");
		break;
	case 0xAF:
		INSTRUCTION_PRINT("XOR A");
		break;
	case 0xB0:
		INSTRUCTION_PRINT("OR B");
		break;
	case 0xB1:
		INSTRUCTION_PRINT("OR C");
		break;
	case 0xB2:
		INSTRUCTION_PRINT("OR D");
		break;
	case 0xB3:
		INSTRUCTION_PRINT("OR E");
		break;
	case 0xB4:
		INSTRUCTION_PRINT("OR H");
		break;
	case 0xB5:
		INSTRUCTION_PRINT("OR L");
		break;
	case 0xB6:
		INSTRUCTION_PRINT("OR (HL)");
		break;
	case 0xB7:
		INSTRUCTION_PRINT("OR A");
		break;
	case 0xB8:
		INSTRUCTION_PRINT("CP B");
		break;
	case 0xB9:
		INSTRUCTION_PRINT("CP C");
		break;
	case 0xBA:
		INSTRUCTION_PRINT("CP D");
		break;
	case 0xBB:
		INSTRUCTION_PRINT("CP E");
		break;
	case 0xBC:
		INSTRUCTION_PRINT("CP H");
		break;
	case 0xBD:
		INSTRUCTION_PRINT("CP L");
		break;
	case 0xBE:
		INSTRUCTION_PRINT("CP (HL)");
		break;
	case 0xBF:
		INSTRUCTION_PRINT("CP A");
		break;
	case 0xC0:
		INSTRUCTION_PRINT("RET NZ");
		break;
	case 0xC1:
		INSTRUCTION_PRINT("POP BC");
		break;
	case 0xC2: //double check the next two
		INSTRUCTION_PRINT("JP NZ, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xC3:
		INSTRUCTION_PRINT("JP 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xC4:
		INSTRUCTION_PRINT("CALL NZ, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xC5:
		INSTRUCTION_PRINT("PUSH BC");
		break;
	case 0xC6:
		INSTRUCTION_PRINT("ADD A, 0x%02X", opcode[1]);
		break;
	case 0xC7:
		INSTRUCTION_PRINT("RST 0x00");
		break;
	case 0xC8:
		INSTRUCTION_PRINT("RET Z");
		break;
	case 0xC9:
		INSTRUCTION_PRINT("RET");
		break;
	case 0xCA:
		INSTRUCTION_PRINT("JP Z, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCB:
		INSTRUCTION_PRINT("CB PREFIX");
		break;
	case 0xCC:
		INSTRUCTION_PRINT("CALL Z, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCD:
		INSTRUCTION_PRINT("CALL 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xCE:
		INSTRUCTION_PRINT("ADC A, 0x%02X", opcode[1]);
		break;
	case 0xCF:
		INSTRUCTION_PRINT("RST 0x08");
		break;
	case 0xD0:
		INSTRUCTION_PRINT("RET NC");
		break;
	case 0xD1:
		INSTRUCTION_PRINT("POP DE");
		break;
	case 0xD2:
		INSTRUCTION_PRINT("JP NC, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xD4:
		INSTRUCTION_PRINT("CALL NC, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xD5:
		INSTRUCTION_PRINT("PUSH DE");
		break;
	case 0xD6:
		INSTRUCTION_PRINT("SUB 0x%02X", opcode[1]);
		break;
	case 0xD7:
		INSTRUCTION_PRINT("RST 0x10");
		break;
	case 0xD8:
		INSTRUCTION_PRINT("RET C");
		break;
	case 0xD9:
		INSTRUCTION_PRINT("RETI");
		break;
	case 0xDA:
		INSTRUCTION_PRINT("JP C, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xDC:
		INSTRUCTION_PRINT("CALL C, 0x%04X", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xDE:
		INSTRUCTION_PRINT("SBC A, 0x%02X", opcode[1]);
		break;
	case 0xDF:
		INSTRUCTION_PRINT("RST 0x18");
		break;
	case 0xE0:
		INSTRUCTION_PRINT("LDH (0xFF00 + 0x%02X), A", opcode[1]);
		break;
	case 0xE1:
		INSTRUCTION_PRINT("POP HL");
		break;
	case 0xE2:
		INSTRUCTION_PRINT("LD (0xFF00 + C), A");
		break;
	case 0xE5:
		INSTRUCTION_PRINT("PUSH HL");
		break;
	case 0xE6:
		INSTRUCTION_PRINT("AND 0x%02X", opcode[1]);
		break;
	case 0xE7:
		INSTRUCTION_PRINT("RST 0x20");
		break;
	case 0xE8:
		INSTRUCTION_PRINT("ADD SP, 0x%02X", opcode[1]);
		break;
	case 0xE9:
		INSTRUCTION_PRINT("JP (HL)");
		break;
	case 0xEA:
		INSTRUCTION_PRINT("LD (0x%04X), A", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xEE:
		INSTRUCTION_PRINT("XOR 0x%02X", opcode[1]);
		break;
	case 0xEF:
		INSTRUCTION_PRINT("RST 0x28");
		break;
	case 0xF0:
		INSTRUCTION_PRINT("LDH A, (0xFF00 + 0x%02X)", opcode[1]);
		break;
	case 0xF1:
		INSTRUCTION_PRINT("POP AF");
		break;
	case 0xF2:
		INSTRUCTION_PRINT("LD A, (0xFF00 + C)");
		break;
	case 0xF3:
		INSTRUCTION_PRINT("DI");
		break;
	case 0xF5:
		INSTRUCTION_PRINT("PUSH AF");
		break;
	case 0xF6:
		INSTRUCTION_PRINT("OR 0x%02X", opcode[1]);
		break;
	case 0xF7:
		INSTRUCTION_PRINT("RST 0x30");
		break;
	case 0xF8:
		INSTRUCTION_PRINT("LD HL, SP + 0x%02X", opcode[1]);
		break;
	case 0xF9:
		INSTRUCTION_PRINT("LD SP, HL");
		break;
	case 0xFA:
		INSTRUCTION_PRINT("LD A, (0x%04X)", (opcode[2] << 8) | opcode[1]);
		break;
	case 0xFB:
		INSTRUCTION_PRINT("EI");
		break;
	case 0xFE:
		INSTRUCTION_PRINT("CP 0x%02X", opcode[1]);
		break;
	case 0xFF:
		INSTRUCTION_PRINT("RST 0x38");
		break;
	}
};
