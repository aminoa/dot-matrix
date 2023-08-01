#pragma once

#include <cstdint>
#include <iostream>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;

const std::string OPCODE_NAMES[] = {
    "NOP",           "LD BC,$%04X", "LD [BC],A",     "INC BC",      "INC B",         "DEC B",
    "LD B,$%02X",    "RCLA",        "LD [$%04X],SP", "ADD HL,BC",   "LD A,[BC]",     "DEC BC",
    "INC C",         "DEC C",       "LD C,$%02X",    "RRCA",        "STOP",          "LD DE,$%04X",
    "LD [DE],A",     "INC DE",      "INC D",         "DEC D",       "LD D,$%02X",    "RLA",
    "JR %+d",        "ADD HL,DE",   "LD A,[DE]",     "DEC DE",      "INC E",         "DEC E",
    "LD E,$%02X",    "RRA",         "JR NZ,%+d",     "LD HL,$%04X", "LD [HL+],A",    "INC HL",
    "INC H",         "DEC H",       "LD H,$%02X",    "DAA",         "JR Z,%+d",      "ADD HL,HL",
    "LD A,[HL+]",    "DEC HL",      "INC L",         "DEC L",       "LD L,$%02X",    "CPL",
    "JR NC,%+d",     "LD SP,$%04X", "LD [HL-],A",    "INC SP",      "INC [HL]",      "DEC [HL]",
    "LD [HL],$%02X", "SCF",         "JR C,%+d",      "ADD HL,SP",   "LD A,[HL-]",    "DEC SP",
    "INC A",         "DEC A",       "LD A,$%02X",    "CCF",         "LD B,B",        "LD B,C",
    "LD B,D",        "LD B,E",      "LD B,H",        "LD B,L",      "LD B,[HL]",     "LD B,A",
    "LD C,B",        "LD C,C",      "LD C,D",        "LD C,E",      "LD C,H",        "LD C,L",
    "LD C,[HL]",     "LD C,A",      "LD D,B",        "LD D,C",      "LD D,D",        "LD D,E",
    "LD D,H",        "LD D,L",      "LD D,[HL]",     "LD D,A",      "LD E,B",        "LD E,C",
    "LD E,D",        "LD E,E",      "LD E,H",        "LD E,L",      "LD E,[HL]",     "LD E,A",
    "LD H,B",        "LD H,C",      "LD H,D",        "LD H,E",      "LD H,H",        "LD H,L",
    "LD H,[HL]",     "LD H,A",      "LD L,B",        "LD L,C",      "LD L,D",        "LD L,E",
    "LD L,H",        "LD L,L",      "LD L,[HL]",     "LD L,A",      "LD [HL],B",     "LD [HL],C",
    "LD [HL],D",     "LD [HL],E",   "LD [HL],H",     "LD [HL],L",   "HALT",          "LD [HL],A",
    "LD A,B",        "LD A,C",      "LD A,D",        "LD A,E",      "LD A,H",        "LD A,L",
    "LD A,[HL]",     "LD A,A",      "ADD A,B",       "ADD A,C",     "ADD A,D",       "ADD A,E",
    "ADD A,H",       "ADD A,L",     "ADD A,[HL]",    "ADD A,A",     "ADC A,B",       "ADC A,C",
    "ADC A,D",       "ADC A,E",     "ADC A,H",       "ADC A,L",     "ADC A,[HL]",    "ADC A,A",
    "SUB A,B",       "SUB A,C",     "SUB A,D",       "SUB A,E",     "SUB A,H",       "SUB A,L",
    "SUB A,[HL]",    "SUB A,A",     "SBC A,B",       "SBC A,C",     "SBC A,D",       "SBC A,E",
    "SBC A,H",       "SBC A,L",     "SBC A,[HL]",    "SBC A,A",     "AND B",         "AND C",
    "AND D",         "AND E",       "AND H",         "AND L",       "AND [HL]",      "AND A",
    "XOR B",         "XOR C",       "XOR D",         "XOR E",       "XOR H",         "XOR L",
    "XOR [HL]",      "XOR A",       "OR B",          "OR C",        "OR D",          "OR E",
    "OR H",          "OR L",        "OR [HL]",       "OR A",        "CP B",          "CP C",
    "CP D",          "CP E",        "CP H",          "CP L",        "CP [HL]",       "CP A",
    "RET NZ",        "POP BC",      "JP NZ,$%04X",   "JP $%04X",    "CALL NZ,$%04X", "PUSH BC",
    "ADD A,$%02X",   "RST 00",      "RET Z",         "RET",         "JP Z,$%04X",    "ERR CB",
    "CALL Z,$%04X",  "CALL $%04X",  "ADC A,$%02X",   "RST 08",      "RET NC",        "POP DE",
    "JP NC,$%04X",   "ERR D3",      "CALL NC,$%04X", "PUSH DE",     "SUB A,$%02X",   "RST 10",
    "RET C",         "RETI",        "JP C,$%04X",    "ERR DB",      "CALL C,$%04X",  "ERR DD",
    "SBC A,$%02X",   "RST 18",      "LDH [$%02X],A", "POP HL",      "LDH [C],A",     "DBG",
    "ERR E4",        "PUSH HL",     "AND $%02X",     "RST 20",      "ADD SP %+d",    "JP HL",
    "LD [$%04X],A",  "ERR EB",      "ERR EC",        "ERR ED",      "XOR $%02X",     "RST 28",
    "LDH A,[$%02X]", "POP AF",      "LDH A,[C]",     "DI",          "ERR F4",        "PUSH AF",
    "OR $%02X",      "RST 30",      "LD HL,SP%+d",   "LD SP,HL",    "LD A,[$%04X]",  "EI",
    "ERR FC",        "ERR FD",      "CP $%02X",      "RST 38" };

const u8 OP_CYCLES[] = {
    // 1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    1, 3, 2, 2, 1, 1, 2, 1, 5, 2, 2, 2, 1, 1, 2, 1, // 0
    0, 3, 2, 2, 1, 1, 2, 1, 3, 2, 2, 2, 1, 1, 2, 1, // 1
    2, 3, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1, 1, 2, 1, // 2
    2, 3, 2, 2, 3, 3, 3, 1, 2, 2, 2, 2, 1, 1, 2, 1, // 3
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 4
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 5
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 6
    2, 2, 2, 2, 2, 2, 0, 2, 1, 1, 1, 1, 1, 1, 2, 1, // 7
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 8
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // 9
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // A
    1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, // B
    2, 3, 3, 4, 3, 4, 2, 4, 2, 4, 3, 0, 3, 6, 2, 4, // C
    2, 3, 3, 0, 3, 4, 2, 4, 2, 4, 3, 0, 3, 0, 2, 4, // D
    3, 3, 2, 0, 0, 4, 2, 4, 4, 1, 4, 0, 0, 0, 2, 4, // E
    3, 3, 2, 1, 0, 4, 2, 4, 3, 2, 4, 1, 0, 0, 2, 4, // F
};

const u8 OP_CB_CYCLES[] = {
    // 1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 0
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 1
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 2
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 3
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 4
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 5
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 6
    2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 3, 2, // 7
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 8
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // 9
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // A
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // B
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // C
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // D
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // E
    2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, // F
};
//

namespace Interrupt 
{
	const u8 VBLANK = 1 << 0;
	const u8 LCD = 1 << 1;
	const u8 TIMER = 1 << 2;
	const u8 SERIAL = 1 << 3;
	const u8 JOYPAD = 1 << 4;
}

namespace Memory {
    const u16 VBLANK= 0x40;
    const u16 LCD= 0x48;
    const u16 TIMER= 0x50;
    const u16 SERIAL= 0x58;
    const u16 JOYPAD= 0x60;

    const u16 IF = 0xFF0F;
	const u16 IE = 0xFFFF;

    const u16 DIV = 0xFF04;
	const u16 TIMA = 0xFF05;
	const u16 TMA = 0xFF06;
	const u16 TAC = 0xFF07;

    const u16 LCDC = 0xFF40;
    const u16 STAT = 0xFF41;
    const u16 SCY = 0xFF42; // SCROLL_Y
    const u16 SCX = 0xFF43; // SCROLL_X
    const u16 LY = 0xFF44;  // LY aka currently drawn line, 0-153, >144 = vblank
    const u16 LYC = 0xFF45;
    const u16 DMA = 0xFF46;
    const u16 BGP = 0xFF47;
    const u16 OBP0 = 0xFF48;
    const u16 OBP1 = 0xFF49;
    const u16 WY = 0xFF4A;
    const u16 WX = 0xFF4B;

}

// Consts for the clock cycles

// Consts for timers
