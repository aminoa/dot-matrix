#pragma once
#include "cpu.h"

#include <iostream>
#include <iomanip>

#define UNIMPLEMENTED(instruction) std::cout << "Unimplemented Instruction: " << instruction << std::endl; exit(1);
#define PRINT(instruction) std::cout << "Instruction: " << instruction << std::endl;

CPU::CPU(MMU* mmu, Interrupts* interrupts)
{
	A = 0x10;
	F.Z = 0x00;
	F.N = 0x00;
	F.H = 0x00;
	F.C = 0x00;
	
	B = 0xFF;
	C = 0x13;
	D = 0x00;
	E = 0xC1;
	H = 0x84;
	L = 0x03;

	PC = 0x100;
	SP = 0xFFFE;

	this->mmu = mmu;
	this->interrupts = interrupts;
}

void CPU::Jump(bool condition)
{
	if (condition)
	{
		PC = mmu->ReadShort(PC);
		mmu->clock.t_instr += 16;
	}
	else
	{
		PC += 2;
		mmu->clock.t_instr += 12;
	}
}

void CPU::JumpAdd(bool condition)
{
	if (condition)
	{
		PC += 1 + mmu->ReadByte(PC);
		mmu->clock.t_instr += 12;
	}
	else
	{
		PC++;
		mmu->clock.t_instr += 8;
	}
}

//Arithmetic

uint8_t CPU::Add(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 + operand2;
	F.Z = (result == 0);
	F.N = 0;
	//https://stackoverflow.com/questions/8868396/game-boy-what-constitutes-a-half-carry/8874607#8874607
	F.H = ((operand1 & 0xF) + (operand2 & 0xF)) > 0xF; 
	F.C = result < operand1;
	return result;
}

uint16_t CPU::Add(uint16_t operand1, uint16_t operand2)
{	
	uint16_t result = operand1 + operand2;
	F.N = 0;
	F.C = result < operand1;
	F.H = ((operand1 & 0xFFF) + (operand2 & 0xFFF)) > 0xFFF;
	return result;
}

//TODO: offset

uint8_t CPU::AddCarry(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 + operand2 + F.C;
	F.Z = (result == 0);
	F.N = 0;
	F.H = ((operand1 & 0xF) + (operand2 & 0xF) + F.C) > 0xF;
	F.C = result < operand1;
	return result;
}

uint8_t CPU::Subtract(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 - operand2;
	F.Z = (result == 0);
	F.N = 1;
	F.H = ((operand1 & 0xF) - (operand2 & 0xF)) < 0;
	F.C = result > operand1;
	return result;
}

uint8_t CPU::SubtractCarry(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 - operand2 - F.C;
	F.Z = (result == 0);
	F.N = 1;
	F.H = ((operand1 & 0xF) - (operand2 & 0xF) - F.C) < 0;
	F.C = result > operand1;
	return result;
}

uint8_t CPU::And(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 & operand2;
	F.Z = (result == 0);
	F.N = 0;
	F.H = 1;
	F.C = 0;
	return result;
}

uint8_t CPU::Or(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 | operand2;
	F.Z = (result == 0);
	F.N = F.H = F.C =  0;
	return result;
}

uint8_t CPU::Xor(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 ^ operand2;
	F.Z = (result == 0);
	F.N = F.H = F.C = 0;
	return result;
}

uint8_t CPU::Increment(uint8_t operand) //not totally sure on this
{
	F.Z = (operand == 0xFF);
	F.N = 0;
	F.H = ((operand & 0xF) + 1) > 0xF;
	return operand + 1;
}

uint8_t CPU::Decrement(uint8_t operand)
{
	F.Z = (operand == 0);
	F.N = 1;
	F.H = ((operand & 0xF) - 1) < 0;
	return operand - 1;
}

//Rotate and Shifts

//rotate left, then make lsb carry flag
uint8_t CPU::RotateLeft(uint8_t operand)
{
	uint8_t result = (operand << 1) | F.C;
	F.Z = (result == 0);
	F.N = F.H = 0;
	//previous msb becomes carry flag
	F.C = operand >> 7;
	return result;
}

uint8_t CPU::RotateLeftCarry(uint8_t operand)
{
	//shifts each bit to the left by 1, then takes msb and makes it lsb
	uint8_t result = (operand << 1) | (operand >> 7);
	F.Z = (result == 0);
	F.N = F.H = 0;
	//lowest bit in Carry
	F.C = operand >> 7;
	return result;
}

uint8_t CPU::RotateRight(uint8_t operand)
{
	uint8_t result = (operand >> 1) | (F.C << 7);
	F.Z = (result == 0);
	F.N = F.H = 0;
	F.C = operand & 0x1;
	return result;
}

uint8_t CPU::RotateRightCarry(uint8_t operand)
{
	uint8_t result = (operand >> 1) | (operand << 7);
	F.Z = (result == 0);
	F.N = F.H = 0;
	F.C = operand & 0x1;
	return result;
}

uint8_t CPU::ShiftLeft(uint8_t operand)
{
	uint8_t result = operand << 1;
	F.Z = (result == 0);
	F.N = F.H = 0;
	F.C = operand >> 7;
	return result;
}

uint8_t CPU::ShiftRight(uint8_t operand)
{
	uint8_t result = operand >> 1;
	F.Z = (result == 0);
	F.N = F.H = 0;
	F.C = operand & 0x1;
	return result;
}

uint8_t CPU::ShiftRightLogical(uint8_t operand)
{
	uint8_t result = (operand >> 1);
	F.Z = (result == 0);
	F.N = F.H = 0;
	F.C = operand & 0x1;
	return result;
}

//Bit Operations

//swap lower/upper 4 bits
uint8_t CPU::Swap(uint8_t operand)
{
	uint8_t result = (operand >> 4) | (operand << 4);
	F.Z = (result == 0);
	F.N = F.H = F.C = 0;
	return result;
}

void CPU::Bit(uint8_t bit, uint8_t operand)
{
	F.Z = ((operand >> bit) & 0x1) == 0;
	F.N = 0;
	F.H = 1;
}

void CPU::SetInterrupts(Interrupts* interrupts)
{
	this->interrupts = interrupts;
}

//check this later
void CPU::Compare(uint8_t operand1, uint8_t operand2)
{
	uint8_t result = operand1 - operand2;
	F.Z = (result == 0);
	F.N = 1;
	F.H = ((operand1 & 0xF) - (operand2 & 0xF)) < 0;
	F.C = operand1 < operand2;
}

void CPU::Return(bool condition)
{
	if (condition)
	{
		PC = mmu->ReadShort(SP);
		SP += 2;
		mmu->clock.t_instr += 20;
	}
	else
	{
		mmu->clock.t_instr += 8;
	}
}

void CPU::Call(bool condition)
{
	uint16_t address = mmu->ReadShort(PC);
	PC += 2;

	mmu->clock.t_instr += 12;
	if (condition)
	{
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = address;
		mmu->clock.t_instr += 12;
	}
}

//interrupt checking code

void CPU::ExecuteInstruction(uint8_t opcode)
{
	mmu->clock.t_instr += InstructionTicks[opcode];
	switch (opcode)
	{
	case 0x00: 
		PRINT("NOP")
		break;
	case 0x01:
		PRINT("LD BC, d16");
		BC = mmu->ReadShort(PC);
		PC += 2;
		break;
	case 0x02:
		PRINT("LD (BC), A");
		mmu->WriteByte(BC, A);
		break;
	case 0x03:
		PRINT("INC BC");
		BC++;
		break;
	case 0x04:
		PRINT("INC B");
		Increment(B);
		break;
	case 0x05:
		PRINT("DEC B");
		Decrement(B);
		break;
	case 0x06:
		PRINT("LD B, d8");
		B = mmu->ReadByte(PC++);
		break;
	case 0x07:
		PRINT("RLCA");
		RotateLeftCarry(A);
		break;
	case 0x08:
		PRINT("LD (a16), SP");
		mmu->WriteShort(mmu->ReadShort(PC), SP);
		break;
	case 0x09:
		PRINT("ADD HL, BC");
		Add(HL, BC);
		break;
	case 0x0A:
		PRINT("LD A, (BC)");
		A = mmu->ReadByte(BC);
		break;
	case 0x0B:
		PRINT("DEC BC");
		BC--;
		break;
	case 0x0C:
		PRINT("INC C");
		Increment(C);
		break;
	case 0x0D:
		PRINT("DEC C");
		Decrement(C);
		break;
	case 0x0E:
		PRINT("LD C, d8");
		C = mmu->ReadByte(PC++);
		break;
	case 0x0F:
		PRINT("RRCA");
		RotateRightCarry(A);
		break;
	case 0x10:
		PRINT("STOP");
		break;
	case 0x11:
		PRINT("LD DE, d16");
		DE = mmu->ReadShort(PC);
		PC += 2;
		break;
	case 0x12:
		PRINT("LD (DE), A");
		mmu->WriteByte(DE, A);
		break;
	case 0x13:
		PRINT("INC DE");
		DE++;
		break;
	case 0x14:
		PRINT("INC D");
		Increment(D);
		break;
	case 0x15:
		PRINT("DEC D");
		Decrement(D);
		break;
	case 0x16:
		PRINT("LD D, d8");
		D = mmu->ReadByte(PC++);
		break;
	case 0x17:
		PRINT("RLA");
		RotateLeft(A);
		break;
	case 0x18:
		PRINT("JR r8");
		PC += (int8_t) mmu->ReadByte(PC++);
		break;
	case 0x19:
		PRINT("ADD HL, DE");
		Add(HL, DE);
		break;
	case 0x1A:
		PRINT("LD A, (DE)");
		A = mmu->ReadByte(DE);
		break;
	case 0x1B:
		PRINT("DEC DE");
		DE--;
		break;
	case 0x1C:
		PRINT("INC E");
		Increment(E);
		break;
	case 0x1D:
		PRINT("DEC E");
		Decrement(E);
		break;
	case 0x1E:
		PRINT("LD E, d8");
		E = mmu->ReadByte(PC++);
		break;
	case 0x1F:
		PRINT("RRA");
		RotateRight(A);
		break;
	case 0x20: //scuffed
		PRINT("JR NZ, r8");
		if (F.Z)
		{
			PC++;
			//Cycles++;
		}
		else
		{
			PC += (int8_t) mmu->ReadByte(PC++);
			//Cycles += 2;
		}
		break;
	case 0x21:
		PRINT("LD HL, d16");
		HL = mmu->ReadShort(PC);
		PC += 2;
	case 0x22:
		PRINT("LD (HL+), A");
		mmu->WriteByte(HL++, A);
		break;
	case 0x23:
		PRINT("INC HL");
		HL++;
		break;
	case 0x24:
		PRINT("INC H");
		Increment(H);
		break;
	case 0x25:
		PRINT("DEC H");
		Decrement(H);
		break;
	case 0x26:
		PRINT("LD H, d8");
		H = mmu->ReadByte(PC++);
		break;
	//Decimal Adjust A explanation: https://www.righto.com/2023/01/understanding-x86s-decimal-adjust-after.html
	case 0x27: 
		PRINT("DAA");
		
		if (!F.N)
		{
			if (F.H || (A & 0xF) > 9)
				A += 0x6;
			if (F.C || A > 0x9F)
				A += 0x60;
		}
		else
		{
			if (F.H)
				A = (A - 0x6) & 0xFF;
			if (F.C)
				A -= 0x60;
		}
		break;
	case 0x28:
		PRINT("JR Z, r8");
		JumpAdd(F.Z);
		break;
	case 0x29:
		PRINT("ADD HL, HL");
		Add(HL, HL);
		break;
	case 0x2A:
		PRINT("LD A, (HL+)");
		A = mmu->ReadByte(HL++);
		break;
	case 0x2B:
		PRINT("DEC HL");
		HL--;
		break;
	case 0x2C:
		PRINT("INC L");
		Increment(L);
		break;
	case 0x2D:
		PRINT("DEC L");
		Decrement(L);
		break;
	case 0x2E:
		PRINT("LD L, d8");
		L = mmu->ReadByte(PC++);
		break;
	case 0x2F:
		PRINT("CPL");
		A = ~A;
		F.H = 1;
		F.N = 1;
		break;
	case 0x30:
		PRINT("JR NC, r8");
		JumpAdd(!F.C);
		break;
	case 0x31:
		PRINT("LD SP, d16");
		SP = mmu->ReadShort(PC);
		PC += 2;
		break;
	case 0x32:
		PRINT("LD (HL-), A");
		mmu->WriteByte(HL--, A);
		break;
	case 0x33:
		PRINT("INC SP");
		SP++;
		break;
	case 0x34:
		PRINT("INC (HL)");
		uint8_t temp;
		temp = mmu->ReadByte(HL);
		Increment(temp);
		mmu->WriteByte(HL, temp);
		break;
	case 0x35:
		PRINT("DEC (HL)");
		temp;
		temp = mmu->ReadByte(HL);
		Decrement(temp);
		mmu->WriteByte(HL, temp);
		break;
	case 0x36:
		PRINT("LD (HL), d8");
		mmu->WriteByte(HL, mmu->ReadByte(PC++));
		break;
	case 0x37:
		PRINT("SCF");
		F.C = 1;
		F.N = 0;
		F.H = 0;
		break;
	case 0x38:
		PRINT("JR C, r8");
		JumpAdd(F.C);
		break;
	case 0x39:
		PRINT("ADD HL, SP");
		Add(HL, SP);
		break;
	case 0x3A:
		PRINT("LD A, (HL-)");
		A = mmu->ReadByte(HL--);
		break;
	case 0x3B:
		PRINT("DEC SP");
		SP--;
		break;
	case 0x3C:
		PRINT("INC A");
		Increment(A);
		break;
	case 0x3D:
		PRINT("DEC A");
		Decrement(A);
		break;
	case 0x3E:
		PRINT("LD A, d8");
		A = mmu->ReadByte(PC++);
		break;
	case 0x3F:
		PRINT("CCF");
		F.C = !F.C;
		F.N = 0;
		F.H = 0;
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
		AddCarry(A, B);
		break;
	case 0x89:
		PRINT("ADC A, C");
		AddCarry(A, C);
		break;
	case 0x8A:
		PRINT("ADC A, D");
		AddCarry(A, D);
		break;
	case 0x8B:
		PRINT("ADC A, E");
		AddCarry(A, E);
		break;
	case 0x8C:
		PRINT("ADC A, H");
		AddCarry(A, H);
		break;
	case 0x8D:
		PRINT("ADC A, L");
		AddCarry(A, L);
		break;
	case 0x8E:
		PRINT("ADC A, (HL)");
		AddCarry(A, mmu->ReadByte(HL));
		break;
	case 0x8F:
		PRINT("ADC A, A");
		AddCarry(A, A);
		break;
	case 0x90:
		PRINT("SUB B");
		Subtract(A, B);
		break;
	case 0x91:
		PRINT("SUB C");
		Subtract(A, C);
		break;
	case 0x92:
		PRINT("SUB D");
		Subtract(A, D);
		break;
	case 0x93:
		PRINT("SUB E");
		Subtract(A, E);
		break;
	case 0x94:
		PRINT("SUB H");
		Subtract(A, H);
		break;
	case 0x95:
		PRINT("SUB L");
		Subtract(A, L);
		break;
	case 0x96:
		PRINT("SUB (HL)");
		Subtract(A, mmu->ReadByte(HL));
		break;
	case 0x97:
		PRINT("SUB A");
		Subtract(A, A);
		break;
	case 0x98:
		PRINT("SBC A, B");
		SubtractCarry(A, B);
		break;
	case 0x99:
		PRINT("SBC A, C");
		SubtractCarry(A, C);
		break;
	case 0x9A:
		PRINT("SBC A, D");
		SubtractCarry(A, D);
		break;
	case 0x9B:
		PRINT("SBC A, E");
		SubtractCarry(A, E);
		break;
	case 0x9C:
		PRINT("SBC A, H");
		SubtractCarry(A, H);
		break;
	case 0x9D:
		PRINT("SBC A, L");
		SubtractCarry(A, L);
		break;
	case 0x9E:
		PRINT("SBC A, (HL)");
		SubtractCarry(A, mmu->ReadByte(HL));
		break;
	case 0x9F:
		PRINT("SBC A, A");
		SubtractCarry(A, A);
		break;
	case 0xA0:
		PRINT("AND B");
		And(A, B);
		break;
	case 0xA1:
		PRINT("AND C");
		And(A, C);
		break;
	case 0xA2:
		PRINT("AND D");
		And(A, D);
		break;
	case 0xA3:
		PRINT("AND E");
		And(A, E);
		break;
	case 0xA4:
		PRINT("AND H");
		And(A, H);
		break;
	case 0xA5:
		PRINT("AND L");
		And(A, L);
		break;
	case 0xA6:
		PRINT("AND (HL)");
		And(A, mmu->ReadByte(HL));
		break;
	case 0xA7:
		PRINT("AND A");
		And(A, A);
		break;
	case 0xA8:
		PRINT("XOR B");
		Xor(A, B);
		break;
	case 0xA9:
		PRINT("XOR C");
		Xor(A, C);
		break;
	case 0xAA:
		PRINT("XOR D");
		Xor(A, D);
		break;
	case 0xAB:
		PRINT("XOR E");
		Xor(A, E);
		break;
	case 0xAC:
		PRINT("XOR H");
		Xor(A, H);
		break;
	case 0xAD:
		PRINT("XOR L");
		Xor(A, L);
		break;
	case 0xAE:
		PRINT("XOR (HL)");
		Xor(A, mmu->ReadByte(HL));
		break;
	case 0xAF:
		PRINT("XOR A");
		Xor(A, A);
		break;
	case 0xB0:
		PRINT("OR B");
		Or(A, B);
		break;
	case 0xB1:
		PRINT("OR C");
		Or(A, C);
		break;
	case 0xB2:
		PRINT("OR D");
		Or(A, D);
		break;
	case 0xB3:
		PRINT("OR E");
		Or(A, E);
		break;
	case 0xB4:
		PRINT("OR H");
		Or(A, H);
		break;
	case 0xB5:
		PRINT("OR L");
		Or(A, L);
		break;
	case 0xB6:
		PRINT("OR (HL)");
		Or(A, mmu->ReadByte(HL));
		break;
	case 0xB7:
		PRINT("OR A");
		Or(A, A);
		break;
	case 0xB8:
		PRINT("CP B");
		Compare(A, B);
		break;
	case 0xB9:
		PRINT("CP C");
		Compare(A, C);
		break;
	case 0xBA:
		PRINT("CP D");
		Compare(A, D);
		break;
	case 0xBB:
		PRINT("CP E");
		Compare(A, E);
		break;
	case 0xBC:
		PRINT("CP H");
		Compare(A, H);
		break;
	case 0xBD:
		PRINT("CP L");
		Compare(A, L);
		break;
	case 0xBE:
		PRINT("CP (HL)");
		Compare(A, mmu->ReadByte(HL));
		break;
	case 0xBF:
		PRINT("CP A");
		Compare(A, A);
		break;
	case 0xC0:
		PRINT("RET NZ");
		Return(!F.Z);
		break;
	case 0xC1:
		PRINT("POP BC");
		BC = mmu->ReadShort(SP);
		SP += 2;
		break;
	case 0xC2: 
		PRINT("JP NZ, nn");
		Jump(!F.Z);
		break;
	case 0xC3: 
		PRINT("JP nn");
		PC = mmu->ReadShort(PC);
		break;
	case 0xC4:
		PRINT("CALL NZ, nn");
		Call(!F.Z);
	case 0xC5:
		PRINT("PUSH BC");
		SP -= 2;
		mmu->WriteShort(SP, BC);
		break;
	case 0xC6:
		PRINT("ADD A, n");
		Add(A, mmu->ReadByte(PC++));
		break;
	case 0xC7:
		PRINT("RST 0x00");
		SP -= 2;
		mmu->WriteShort(SP, PC++);
		PC = 0x00;
		break;
	case 0xC8:
		PRINT("RET Z");
		Return(F.Z);
		break;
	case 0xC9:
		PRINT("RET");
		SP -= 2;
		PC = mmu->ReadShort(SP);
		break;
	case 0xCA:
		PRINT("JP Z, 0x%04X", (opcode[2] << 8) | opcode[1]);
		Jump(F.Z);
		break;
	case 0xCB:
		PRINT("I'm not implementing this...");
		exit(1);
		break;
	case 0xCC: 
		PRINT("Call Z, nn");
		Call(F.Z);
		break;
	case 0xCD:
		PRINT("Call nn");
		uint16_t addr;
		addr = mmu->ReadShort(PC);
		PC += 2;
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = addr;
		break;
	case 0xCE:
		PRINT("ADC A, n");
		AddCarry(A, mmu->ReadByte(PC++));
		break;
	case 0xCF:
		PRINT("RST 0x08");
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = 0x08;
		break;
	case 0xD0:
		PRINT("RET NC");
		Return(!F.C);
		break;
	case 0xD1:
		PRINT("POP DE");
		SP -= 2;
		DE = mmu->ReadShort(SP);
		break;
	case 0xD2:
		PRINT("JP NC, nn");
		Jump(!F.C);
		break;
	case 0xD4:
		PRINT("Call NC, nn");
		Call(!F.C);
		break;
	case 0xD5:
		PRINT("PUSH DE");
		SP -= 2;
		mmu->WriteShort(SP, DE);
		break;
	case 0xD6:
		PRINT("SUB n");
		Subtract(A, mmu->ReadByte(PC++));
		break;
	case 0xD7:
		PRINT("RST 0x10")
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = 0x10;
		break;
	case 0xD8:
		PRINT("RET C");
		Return(F.C);
		break;
	case 0xD9:
		PRINT("RETI");
		interrupts->IME = true;
		SP -= 2;
		PC = mmu->ReadShort(SP);
		break;
	case 0xDA:
		PRINT("JP C, nn");
		Jump(F.C);
		break;
	case 0xDC:
		PRINT("CALL C, nn");
		break;
	case 0xDE:
		PRINT("SUB n");
		SubtractCarry(A, mmu->ReadByte(PC++));
		break;
	case 0xDF:
		PRINT("RST 0x18");
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = 0x18;
		break;
	case 0xE0:
		PRINT("LDH (0xFF00 + 0x%02X), A", opcode[1]);
		mmu->WriteByte(0xFF00 + mmu->ReadByte(PC++), A);
		break;
	case 0xE1:
		PRINT("POP HL");
		SP -= 2;
		HL = mmu->ReadShort(SP);
		break;
	case 0xE2:
		PRINT("LD (0xFF00 + C), A");
		mmu->WriteByte(0xFF00 + C, A);
		break;
	case 0xE5:
		PRINT("PUSH HL");
		SP -= 2;
		mmu->WriteShort(SP, HL);
		break;
	case 0xE6:
		PRINT("AND n");
		And(A, mmu->ReadByte(PC++));
		break;
	case 0xE7:
		PRINT("RST 0x20");
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = 0x20;
		break;
	case 0xE8:
		PRINT("ADD SP, n");
		Add(SP, (int8_t) mmu->ReadByte(PC++));
		break;
	case 0xE9: 
		PRINT("JP (HL)");
		PC = HL;
		break;
	case 0xEA:
		PRINT("LD (nn), A");
		mmu->WriteByte(mmu->ReadShort(PC), A);
		PC += 2;
		break;
	case 0xEE:
		PRINT("XOR n");
		Xor(A, mmu->ReadByte(PC++));
		break;
	case 0xEF:
		PRINT("RST 0x28");
		SP -= 2;
		mmu->WriteShort(SP, PC);
		PC = 0x28;
		break;
	case 0xF0:
		PRINT("LD A, ($FF00 + n)");
		A = mmu->ReadByte(0xFF00 + mmu->ReadByte(PC++));
		break;
	case 0xF1:
		PRINT("POP AF");
		SP -= 2;
		AF = mmu->ReadShort(SP);
		//F = 0xF0;
		//F &= 0xF0;
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

	default:
		std::cout << "Unimplemented Opcode: " << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(opcode) << std::endl;
		exit(1);
	}
};

