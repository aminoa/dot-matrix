#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;


const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;

using std::vector;

struct Opcode
{
	u8 value;
	std::string mnemonic;
	vector<int> cycles;
	int bytes; 
};

const std::vector<Opcode> OPCODES = 
{
	Opcode(0x00, "NOP", {4}, 1),
	Opcode(0x01, "LD", {12}, 3),
	Opcode(0x02, "LD", {8}, 1),
	Opcode(0x03, "INC", {8}, 1),
	Opcode(0x04, "INC", {4}, 1),
	Opcode(0x05, "DEC", {4}, 1),
	Opcode(0x06, "LD", {8}, 2),
	Opcode(0x07, "RLCA", {4}, 1),
	Opcode(0x08, "LD", {20}, 3),
	Opcode(0x09, "ADD", {8}, 1),
	Opcode(0x0A, "LD", {8}, 1),
	Opcode(0x0B, "DEC", {8}, 1),
	Opcode(0x0C, "INC", {4}, 1),
	Opcode(0x0D, "DEC", {4}, 1),
	Opcode(0x0E, "LD", {8}, 2),
	Opcode(0x0F, "RRCA", {4}, 1),
	Opcode(0x10, "STOP", {4}, 2),
	Opcode(0x11, "LD", {12}, 3),
	Opcode(0x12, "LD", {8}, 1),
	Opcode(0x13, "INC", {8}, 1),
	Opcode(0x14, "INC", {4}, 1),
	Opcode(0x15, "DEC", {4}, 1),
	Opcode(0x16, "LD", {8}, 2),
	Opcode(0x17, "RLA", {4}, 1),
	Opcode(0x18, "JR", {12}, 2),
	Opcode(0x19, "ADD", {8}, 1),
	Opcode(0x1A, "LD", {8}, 1),
	Opcode(0x1B, "DEC", {8}, 1),
	Opcode(0x1C, "INC", {4}, 1),
	Opcode(0x1D, "DEC", {4}, 1),
	Opcode(0x1E, "LD", {8}, 2),
	Opcode(0x1F, "RRA", {4}, 1),
	Opcode(0x20, "JR", {12, 8}, 2),
	Opcode(0x21, "LD", {12}, 3),
	Opcode(0x22, "LD", {8}, 1),
	Opcode(0x23, "INC", {8}, 1),
	Opcode(0x24, "INC", {4}, 1),
	Opcode(0x25, "DEC", {4}, 1),
	Opcode(0x26, "LD", {8}, 2),
	Opcode(0x27, "DAA", {4}, 1),
	Opcode(0x28, "JR", {12, 8}, 2),
	Opcode(0x29, "ADD", {8}, 1),
	Opcode(0x2A, "LD", {8}, 1),
	Opcode(0x2B, "DEC", {8}, 1),
	Opcode(0x2C, "INC", {4}, 1),
	Opcode(0x2D, "DEC", {4}, 1),
	Opcode(0x2E, "LD", {8}, 2),
	Opcode(0x2F, "CPL", {4}, 1),
	Opcode(0x30, "JR", {12, 8}, 2),
	Opcode(0x31, "LD", {12}, 3),
	Opcode(0x32, "LD", {8}, 1),
	Opcode(0x33, "INC", {8}, 1),
	Opcode(0x34, "INC", {12}, 1),
	Opcode(0x35, "DEC", {12}, 1),
	Opcode(0x36, "LD", {12}, 2),
	Opcode(0x37, "SCF", {4}, 1),
	Opcode(0x38, "JR", {12, 8}, 2),
	Opcode(0x39, "ADD", {8}, 1),
	Opcode(0x3A, "LD", {8}, 1),
	Opcode(0x3B, "DEC", {8}, 1),
	Opcode(0x3C, "INC", {4}, 1),
	Opcode(0x3D, "DEC", {4}, 1),
	Opcode(0x3E, "LD", {8}, 2),
	Opcode(0x3F, "CCF", {4}, 1),
	Opcode(0x40, "LD", {4}, 1),
	Opcode(0x41, "LD", {4}, 1),
	Opcode(0x42, "LD", {4}, 1),
	Opcode(0x43, "LD", {4}, 1),
	Opcode(0x44, "LD", {4}, 1),
	Opcode(0x45, "LD", {4}, 1),
	Opcode(0x46, "LD", {8}, 1),
	Opcode(0x47, "LD", {4}, 1),
	Opcode(0x48, "LD", {4}, 1),
	Opcode(0x49, "LD", {4}, 1),
	Opcode(0x4A, "LD", {4}, 1),
	Opcode(0x4B, "LD", {4}, 1),
	Opcode(0x4C, "LD", {4}, 1),
	Opcode(0x4D, "LD", {4}, 1),
	Opcode(0x4E, "LD", {8}, 1),
	Opcode(0x4F, "LD", {4}, 1),
	Opcode(0x50, "LD", {4}, 1),
	Opcode(0x51, "LD", {4}, 1),
	Opcode(0x52, "LD", {4}, 1),
	Opcode(0x53, "LD", {4}, 1),
	Opcode(0x54, "LD", {4}, 1),
	Opcode(0x55, "LD", {4}, 1),
	Opcode(0x56, "LD", {8}, 1),
	Opcode(0x57, "LD", {4}, 1),
	Opcode(0x58, "LD", {4}, 1),
	Opcode(0x59, "LD", {4}, 1),
	Opcode(0x5A, "LD", {4}, 1),
	Opcode(0x5B, "LD", {4}, 1),
	Opcode(0x5C, "LD", {4}, 1),
	Opcode(0x5D, "LD", {4}, 1),
	Opcode(0x5E, "LD", {8}, 1),
	Opcode(0x5F, "LD", {4}, 1),
	Opcode(0x60, "LD", {4}, 1),
	Opcode(0x61, "LD", {4}, 1),
	Opcode(0x62, "LD", {4}, 1),
	Opcode(0x63, "LD", {4}, 1),
	Opcode(0x64, "LD", {4}, 1),
	Opcode(0x65, "LD", {4}, 1),
	Opcode(0x66, "LD", {8}, 1),
	Opcode(0x67, "LD", {4}, 1),
	Opcode(0x68, "LD", {4}, 1),
	Opcode(0x69, "LD", {4}, 1),
	Opcode(0x6A, "LD", {4}, 1),
	Opcode(0x6B, "LD", {4}, 1),
	Opcode(0x6C, "LD", {4}, 1),
	Opcode(0x6D, "LD", {4}, 1),
	Opcode(0x6E, "LD", {8}, 1),
	Opcode(0x6F, "LD", {4}, 1),
	Opcode(0x70, "LD", {8}, 1),
	Opcode(0x71, "LD", {8}, 1),
	Opcode(0x72, "LD", {8}, 1),
	Opcode(0x73, "LD", {8}, 1),
	Opcode(0x74, "LD", {8}, 1),
	Opcode(0x75, "LD", {8}, 1),
	Opcode(0x76, "HALT", {4}, 1),
	Opcode(0x77, "LD", {8}, 1),
	Opcode(0x78, "LD", {4}, 1),
	Opcode(0x79, "LD", {4}, 1),
	Opcode(0x7A, "LD", {4}, 1),
	Opcode(0x7B, "LD", {4}, 1),
	Opcode(0x7C, "LD", {4}, 1),
	Opcode(0x7D, "LD", {4}, 1),
	Opcode(0x7E, "LD", {8}, 1),
	Opcode(0x7F, "LD", {4}, 1),
	Opcode(0x80, "ADD", {4}, 1),
	Opcode(0x81, "ADD", {4}, 1),
	Opcode(0x82, "ADD", {4}, 1),
	Opcode(0x83, "ADD", {4}, 1),
	Opcode(0x84, "ADD", {4}, 1),
	Opcode(0x85, "ADD", {4}, 1),
	Opcode(0x86, "ADD", {8}, 1),
	Opcode(0x87, "ADD", {4}, 1),
	Opcode(0x88, "ADC", {4}, 1),
	Opcode(0x89, "ADC", {4}, 1),
	Opcode(0x8A, "ADC", {4}, 1),
	Opcode(0x8B, "ADC", {4}, 1),
	Opcode(0x8C, "ADC", {4}, 1),
	Opcode(0x8D, "ADC", {4}, 1),
	Opcode(0x8E, "ADC", {8}, 1),
	Opcode(0x8F, "ADC", {4}, 1),
	Opcode(0x90, "SUB", {4}, 1),
	Opcode(0x91, "SUB", {4}, 1),
	Opcode(0x92, "SUB", {4}, 1),
	Opcode(0x93, "SUB", {4}, 1),
	Opcode(0x94, "SUB", {4}, 1),
	Opcode(0x95, "SUB", {4}, 1),
	Opcode(0x96, "SUB", {8}, 1),
	Opcode(0x97, "SUB", {4}, 1),
	Opcode(0x98, "SBC", {4}, 1),
	Opcode(0x99, "SBC", {4}, 1),
	Opcode(0x9A, "SBC", {4}, 1),
	Opcode(0x9B, "SBC", {4}, 1),
	Opcode(0x9C, "SBC", {4}, 1),
	Opcode(0x9D, "SBC", {4}, 1),
	Opcode(0x9E, "SBC", {8}, 1),
	Opcode(0x9F, "SBC", {4}, 1),
	Opcode(0xA0, "AND", {4}, 1),
	Opcode(0xA1, "AND", {4}, 1),
	Opcode(0xA2, "AND", {4}, 1),
	Opcode(0xA3, "AND", {4}, 1),
	Opcode(0xA4, "AND", {4}, 1),
	Opcode(0xA5, "AND", {4}, 1),
	Opcode(0xA6, "AND", {8}, 1),
	Opcode(0xA7, "AND", {4}, 1),
	Opcode(0xA8, "XOR", {4}, 1),
	Opcode(0xA9, "XOR", {4}, 1),
	Opcode(0xAA, "XOR", {4}, 1),
	Opcode(0xAB, "XOR", {4}, 1),
	Opcode(0xAC, "XOR", {4}, 1),
	Opcode(0xAD, "XOR", {4}, 1),
	Opcode(0xAE, "XOR", {8}, 1),
	Opcode(0xAF, "XOR", {4}, 1),
	Opcode(0xB0, "OR", {4}, 1),
	Opcode(0xB1, "OR", {4}, 1),
	Opcode(0xB2, "OR", {4}, 1),
	Opcode(0xB3, "OR", {4}, 1),
	Opcode(0xB4, "OR", {4}, 1),
	Opcode(0xB5, "OR", {4}, 1),
	Opcode(0xB6, "OR", {8}, 1),
	Opcode(0xB7, "OR", {4}, 1),
	Opcode(0xB8, "CP", {4}, 1),
	Opcode(0xB9, "CP", {4}, 1),
	Opcode(0xBA, "CP", {4}, 1),
	Opcode(0xBB, "CP", {4}, 1),
	Opcode(0xBC, "CP", {4}, 1),
	Opcode(0xBD, "CP", {4}, 1),
	Opcode(0xBE, "CP", {8}, 1),
	Opcode(0xBF, "CP", {4}, 1),
	Opcode(0xC0, "RET", {20, 8}, 1),
	Opcode(0xC1, "POP", {12}, 1),
	Opcode(0xC2, "JP", {16, 12}, 3),
	Opcode(0xC3, "JP", {16}, 3),
	Opcode(0xC4, "CALL", {24, 12}, 3),
	Opcode(0xC5, "PUSH", {16}, 1),
	Opcode(0xC6, "ADD", {8}, 2),
	Opcode(0xC7, "RST", {16}, 1),
	Opcode(0xC8, "RET", {20, 8}, 1),
	Opcode(0xC9, "RET", {16}, 1),
	Opcode(0xCA, "JP", {16, 12}, 3),
	Opcode(0xCB, "PREFIX", {4}, 0),
	Opcode(0xCC, "CALL", {24, 12}, 3),
	Opcode(0xCD, "CALL", {24}, 3),
	Opcode(0xCE, "ADC", {8}, 2),
	Opcode(0xCF, "RST", {16}, 1),
	Opcode(0xD0, "RET", {20, 8}, 1),
	Opcode(0xD1, "POP", {12}, 1),
	Opcode(0xD2, "JP", {16, 12}, 3),
	Opcode(0xD3, "ILLEGAL_D3", {4}, 1),
	Opcode(0xD4, "CALL", {24, 12}, 3),
	Opcode(0xD5, "PUSH", {16}, 1),
	Opcode(0xD6, "SUB", {8}, 2),
	Opcode(0xD7, "RST", {16}, 1),
	Opcode(0xD8, "RET", {20, 8}, 1),
	Opcode(0xD9, "RETI", {16}, 1),
	Opcode(0xDA, "JP", {16, 12}, 3),
	Opcode(0xDB, "ILLEGAL_DB", {4}, 1),
	Opcode(0xDC, "CALL", {24, 12}, 3),
	Opcode(0xDD, "ILLEGAL_DD", {4}, 1),
	Opcode(0xDE, "SBC", {8}, 2),
	Opcode(0xDF, "RST", {16}, 1),
	Opcode(0xE0, "LDH", {12}, 2),
	Opcode(0xE1, "POP", {12}, 1),
	Opcode(0xE2, "LD", {8}, 1),
	Opcode(0xE3, "ILLEGAL_E3", {4}, 1),
	Opcode(0xE4, "ILLEGAL_E4", {4}, 1),
	Opcode(0xE5, "PUSH", {16}, 1),
	Opcode(0xE6, "AND", {8}, 2),
	Opcode(0xE7, "RST", {16}, 1),
	Opcode(0xE8, "ADD", {16}, 2),
	Opcode(0xE9, "JP", {4}, 1),
	Opcode(0xEA, "LD", {16}, 3),
	Opcode(0xEB, "ILLEGAL_EB", {4}, 1),
	Opcode(0xEC, "ILLEGAL_EC", {4}, 1),
	Opcode(0xED, "ILLEGAL_ED", {4}, 1),
	Opcode(0xEE, "XOR", {8}, 2),
	Opcode(0xEF, "RST", {16}, 1),
	Opcode(0xF0, "LDH", {12}, 2),
	Opcode(0xF1, "POP", {12}, 1),
	Opcode(0xF2, "LD", {8}, 1),
	Opcode(0xF3, "DI", {4}, 1),
	Opcode(0xF4, "ILLEGAL_F4", {4}, 1),
	Opcode(0xF5, "PUSH", {16}, 1),
	Opcode(0xF6, "OR", {8}, 2),
	Opcode(0xF7, "RST", {16}, 1),
	Opcode(0xF8, "LD", {12}, 2),
	Opcode(0xF9, "LD", {8}, 1),
	Opcode(0xFA, "LD", {16}, 3),
	Opcode(0xFB, "EI", {4}, 1),
	Opcode(0xFC, "ILLEGAL_FC", {4}, 1),
	Opcode(0xFD, "ILLEGAL_FD", {4}, 1),
	Opcode(0xFE, "CP", {8}, 2),
	Opcode(0xFF, "RST", {16}, 1), };

const std::vector<Opcode> CB_OPCODES =
{
	Opcode(0x00, "RLC", { 8 }, 2),
	Opcode(0x01, "RLC", { 8 }, 2),
	Opcode(0x02, "RLC", { 8 }, 2),
	Opcode(0x03, "RLC", { 8 }, 2),
	Opcode(0x04, "RLC", { 8 }, 2),
	Opcode(0x05, "RLC", { 8 }, 2),
	Opcode(0x06, "RLC", { 16 }, 2),
	Opcode(0x07, "RLC", { 8 }, 2),
	Opcode(0x08, "RRC", { 8 }, 2),
	Opcode(0x09, "RRC", { 8 }, 2),
	Opcode(0x0A, "RRC", { 8 }, 2),
	Opcode(0x0B, "RRC", { 8 }, 2),
	Opcode(0x0C, "RRC", { 8 }, 2),
	Opcode(0x0D, "RRC", { 8 }, 2),
	Opcode(0x0E, "RRC", { 16 }, 2),
	Opcode(0x0F, "RRC", { 8 }, 2),
	Opcode(0x10, "RL", { 8 }, 2),
	Opcode(0x11, "RL", { 8 }, 2),
	Opcode(0x12, "RL", { 8 }, 2),
	Opcode(0x13, "RL", { 8 }, 2),
	Opcode(0x14, "RL", { 8 }, 2),
	Opcode(0x15, "RL", { 8 }, 2),
	Opcode(0x16, "RL", { 16 }, 2),
	Opcode(0x17, "RL", { 8 }, 2),
	Opcode(0x18, "RR", { 8 }, 2),
	Opcode(0x19, "RR", { 8 }, 2),
	Opcode(0x1A, "RR", { 8 }, 2),
	Opcode(0x1B, "RR", { 8 }, 2),
	Opcode(0x1C, "RR", { 8 }, 2),
	Opcode(0x1D, "RR", { 8 }, 2),
	Opcode(0x1E, "RR", { 16 }, 2),
	Opcode(0x1F, "RR", { 8 }, 2),
	Opcode(0x20, "SLA", { 8 }, 2),
	Opcode(0x21, "SLA", { 8 }, 2),
	Opcode(0x22, "SLA", { 8 }, 2),
	Opcode(0x23, "SLA", { 8 }, 2),
	Opcode(0x24, "SLA", { 8 }, 2),
	Opcode(0x25, "SLA", { 8 }, 2),
	Opcode(0x26, "SLA", { 16 }, 2),
	Opcode(0x27, "SLA", { 8 }, 2),
	Opcode(0x28, "SRA", { 8 }, 2),
	Opcode(0x29, "SRA", { 8 }, 2),
	Opcode(0x2A, "SRA", { 8 }, 2),
	Opcode(0x2B, "SRA", { 8 }, 2),
	Opcode(0x2C, "SRA", { 8 }, 2),
	Opcode(0x2D, "SRA", { 8 }, 2),
	Opcode(0x2E, "SRA", { 16 }, 2),
	Opcode(0x2F, "SRA", { 8 }, 2),
	Opcode(0x30, "SWAP", { 8 }, 2),
	Opcode(0x31, "SWAP", { 8 }, 2),
	Opcode(0x32, "SWAP", { 8 }, 2),
	Opcode(0x33, "SWAP", { 8 }, 2),
	Opcode(0x34, "SWAP", { 8 }, 2),
	Opcode(0x35, "SWAP", { 8 }, 2),
	Opcode(0x36, "SWAP", { 16 }, 2),
	Opcode(0x37, "SWAP", { 8 }, 2),
	Opcode(0x38, "SRL", { 8 }, 2),
	Opcode(0x39, "SRL", { 8 }, 2),
	Opcode(0x3A, "SRL", { 8 }, 2),
	Opcode(0x3B, "SRL", { 8 }, 2),
	Opcode(0x3C, "SRL", { 8 }, 2),
	Opcode(0x3D, "SRL", { 8 }, 2),
	Opcode(0x3E, "SRL", { 16 }, 2),
	Opcode(0x3F, "SRL", { 8 }, 2),
	Opcode(0x40, "BIT", { 8 }, 2),
	Opcode(0x41, "BIT", { 8 }, 2),
	Opcode(0x42, "BIT", { 8 }, 2),
	Opcode(0x43, "BIT", { 8 }, 2),
	Opcode(0x44, "BIT", { 8 }, 2),
	Opcode(0x45, "BIT", { 8 }, 2),
	Opcode(0x46, "BIT", { 12 }, 2),
	Opcode(0x47, "BIT", { 8 }, 2),
	Opcode(0x48, "BIT", { 8 }, 2),
	Opcode(0x49, "BIT", { 8 }, 2),
	Opcode(0x4A, "BIT", { 8 }, 2),
	Opcode(0x4B, "BIT", { 8 }, 2),
	Opcode(0x4C, "BIT", { 8 }, 2),
	Opcode(0x4D, "BIT", { 8 }, 2),
	Opcode(0x4E, "BIT", { 12 }, 2),
	Opcode(0x4F, "BIT", { 8 }, 2),
	Opcode(0x50, "BIT", { 8 }, 2),
	Opcode(0x51, "BIT", { 8 }, 2),
	Opcode(0x52, "BIT", { 8 }, 2),
	Opcode(0x53, "BIT", { 8 }, 2),
	Opcode(0x54, "BIT", { 8 }, 2),
	Opcode(0x55, "BIT", { 8 }, 2),
	Opcode(0x56, "BIT", { 12 }, 2),
	Opcode(0x57, "BIT", { 8 }, 2),
	Opcode(0x58, "BIT", { 8 }, 2),
	Opcode(0x59, "BIT", { 8 }, 2),
	Opcode(0x5A, "BIT", { 8 }, 2),
	Opcode(0x5B, "BIT", { 8 }, 2),
	Opcode(0x5C, "BIT", { 8 }, 2),
	Opcode(0x5D, "BIT", { 8 }, 2),
	Opcode(0x5E, "BIT", { 12 }, 2),
	Opcode(0x5F, "BIT", { 8 }, 2),
	Opcode(0x60, "BIT", { 8 }, 2),
	Opcode(0x61, "BIT", { 8 }, 2),
	Opcode(0x62, "BIT", { 8 }, 2),
	Opcode(0x63, "BIT", { 8 }, 2),
	Opcode(0x64, "BIT", { 8 }, 2),
	Opcode(0x65, "BIT", { 8 }, 2),
	Opcode(0x66, "BIT", { 12 }, 2),
	Opcode(0x67, "BIT", { 8 }, 2),
	Opcode(0x68, "BIT", { 8 }, 2),
	Opcode(0x69, "BIT", { 8 }, 2),
	Opcode(0x6A, "BIT", { 8 }, 2),
	Opcode(0x6B, "BIT", { 8 }, 2),
	Opcode(0x6C, "BIT", { 8 }, 2),
	Opcode(0x6D, "BIT", { 8 }, 2),
	Opcode(0x6E, "BIT", { 12 }, 2),
	Opcode(0x6F, "BIT", { 8 }, 2),
	Opcode(0x70, "BIT", { 8 }, 2),
	Opcode(0x71, "BIT", { 8 }, 2),
	Opcode(0x72, "BIT", { 8 }, 2),
	Opcode(0x73, "BIT", { 8 }, 2),
	Opcode(0x74, "BIT", { 8 }, 2),
	Opcode(0x75, "BIT", { 8 }, 2),
	Opcode(0x76, "BIT", { 12 }, 2),
	Opcode(0x77, "BIT", { 8 }, 2),
	Opcode(0x78, "BIT", { 8 }, 2),
	Opcode(0x79, "BIT", { 8 }, 2),
	Opcode(0x7A, "BIT", { 8 }, 2),
	Opcode(0x7B, "BIT", { 8 }, 2),
	Opcode(0x7C, "BIT", { 8 }, 2),
	Opcode(0x7D, "BIT", { 8 }, 2),
	Opcode(0x7E, "BIT", { 12 }, 2),
	Opcode(0x7F, "BIT", { 8 }, 2),
	Opcode(0x80, "RES", { 8 }, 2),
	Opcode(0x81, "RES", { 8 }, 2),
	Opcode(0x82, "RES", { 8 }, 2),
	Opcode(0x83, "RES", { 8 }, 2),
	Opcode(0x84, "RES", { 8 }, 2),
	Opcode(0x85, "RES", { 8 }, 2),
	Opcode(0x86, "RES", { 16 }, 2),
	Opcode(0x87, "RES", { 8 }, 2),
	Opcode(0x88, "RES", { 8 }, 2),
	Opcode(0x89, "RES", { 8 }, 2),
	Opcode(0x8A, "RES", { 8 }, 2),
	Opcode(0x8B, "RES", { 8 }, 2),
	Opcode(0x8C, "RES", { 8 }, 2),
	Opcode(0x8D, "RES", { 8 }, 2),
	Opcode(0x8E, "RES", { 16 }, 2),
	Opcode(0x8F, "RES", { 8 }, 2),
	Opcode(0x90, "RES", { 8 }, 2),
	Opcode(0x91, "RES", { 8 }, 2),
	Opcode(0x92, "RES", { 8 }, 2),
	Opcode(0x93, "RES", { 8 }, 2),
	Opcode(0x94, "RES", { 8 }, 2),
	Opcode(0x95, "RES", { 8 }, 2),
	Opcode(0x96, "RES", { 16 }, 2),
	Opcode(0x97, "RES", { 8 }, 2),
	Opcode(0x98, "RES", { 8 }, 2),
	Opcode(0x99, "RES", { 8 }, 2),
	Opcode(0x9A, "RES", { 8 }, 2),
	Opcode(0x9B, "RES", { 8 }, 2),
	Opcode(0x9C, "RES", { 8 }, 2),
	Opcode(0x9D, "RES", { 8 }, 2),
	Opcode(0x9E, "RES", { 16 }, 2),
	Opcode(0x9F, "RES", { 8 }, 2),
	Opcode(0xA0, "RES", { 8 }, 2),
	Opcode(0xA1, "RES", { 8 }, 2),
	Opcode(0xA2, "RES", { 8 }, 2),
	Opcode(0xA3, "RES", { 8 }, 2),
	Opcode(0xA4, "RES", { 8 }, 2),
	Opcode(0xA5, "RES", { 8 }, 2),
	Opcode(0xA6, "RES", { 16 }, 2),
	Opcode(0xA7, "RES", { 8 }, 2),
	Opcode(0xA8, "RES", { 8 }, 2),
	Opcode(0xA9, "RES", { 8 }, 2),
	Opcode(0xAA, "RES", { 8 }, 2),
	Opcode(0xAB, "RES", { 8 }, 2),
	Opcode(0xAC, "RES", { 8 }, 2),
	Opcode(0xAD, "RES", { 8 }, 2),
	Opcode(0xAE, "RES", { 16 }, 2),
	Opcode(0xAF, "RES", { 8 }, 2),
	Opcode(0xB0, "RES", { 8 }, 2),
	Opcode(0xB1, "RES", { 8 }, 2),
	Opcode(0xB2, "RES", { 8 }, 2),
	Opcode(0xB3, "RES", { 8 }, 2),
	Opcode(0xB4, "RES", { 8 }, 2),
	Opcode(0xB5, "RES", { 8 }, 2),
	Opcode(0xB6, "RES", { 16 }, 2),
	Opcode(0xB7, "RES", { 8 }, 2),
	Opcode(0xB8, "RES", { 8 }, 2),
	Opcode(0xB9, "RES", { 8 }, 2),
	Opcode(0xBA, "RES", { 8 }, 2),
	Opcode(0xBB, "RES", { 8 }, 2),
	Opcode(0xBC, "RES", { 8 }, 2),
	Opcode(0xBD, "RES", { 8 }, 2),
	Opcode(0xBE, "RES", { 16 }, 2),
	Opcode(0xBF, "RES", { 8 }, 2),
	Opcode(0xC0, "SET", { 8 }, 2),
	Opcode(0xC1, "SET", { 8 }, 2),
	Opcode(0xC2, "SET", { 8 }, 2),
	Opcode(0xC3, "SET", { 8 }, 2),
	Opcode(0xC4, "SET", { 8 }, 2),
	Opcode(0xC5, "SET", { 8 }, 2),
	Opcode(0xC6, "SET", { 16 }, 2),
	Opcode(0xC7, "SET", { 8 }, 2),
	Opcode(0xC8, "SET", { 8 }, 2),
	Opcode(0xC9, "SET", { 8 }, 2),
	Opcode(0xCA, "SET", { 8 }, 2),
	Opcode(0xCB, "SET", { 8 }, 2),
	Opcode(0xCC, "SET", { 8 }, 2),
	Opcode(0xCD, "SET", { 8 }, 2),
	Opcode(0xCE, "SET", { 16 }, 2),
	Opcode(0xCF, "SET", { 8 }, 2),
	Opcode(0xD0, "SET", { 8 }, 2),
	Opcode(0xD1, "SET", { 8 }, 2),
	Opcode(0xD2, "SET", { 8 }, 2),
	Opcode(0xD3, "SET", { 8 }, 2),
	Opcode(0xD4, "SET", { 8 }, 2),
	Opcode(0xD5, "SET", { 8 }, 2),
	Opcode(0xD6, "SET", { 16 }, 2),
	Opcode(0xD7, "SET", { 8 }, 2),
	Opcode(0xD8, "SET", { 8 }, 2),
	Opcode(0xD9, "SET", { 8 }, 2),
	Opcode(0xDA, "SET", { 8 }, 2),
	Opcode(0xDB, "SET", { 8 }, 2),
	Opcode(0xDC, "SET", { 8 }, 2),
	Opcode(0xDD, "SET", { 8 }, 2),
	Opcode(0xDE, "SET", { 16 }, 2),
	Opcode(0xDF, "SET", { 8 }, 2),
	Opcode(0xE0, "SET", { 8 }, 2),
	Opcode(0xE1, "SET", { 8 }, 2),
	Opcode(0xE2, "SET", { 8 }, 2),
	Opcode(0xE3, "SET", { 8 }, 2),
	Opcode(0xE4, "SET", { 8 }, 2),
	Opcode(0xE5, "SET", { 8 }, 2),
	Opcode(0xE6, "SET", { 16 }, 2),
	Opcode(0xE7, "SET", { 8 }, 2),
	Opcode(0xE8, "SET", { 8 }, 2),
	Opcode(0xE9, "SET", { 8 }, 2),
	Opcode(0xEA, "SET", { 8 }, 2),
	Opcode(0xEB, "SET", { 8 }, 2),
	Opcode(0xEC, "SET", { 8 }, 2),
	Opcode(0xED, "SET", { 8 }, 2),
	Opcode(0xEE, "SET", { 16 }, 2),
	Opcode(0xEF, "SET", { 8 }, 2),
	Opcode(0xF0, "SET", { 8 }, 2),
	Opcode(0xF1, "SET", { 8 }, 2),
	Opcode(0xF2, "SET", { 8 }, 2),
	Opcode(0xF3, "SET", { 8 }, 2),
	Opcode(0xF4, "SET", { 8 }, 2),
	Opcode(0xF5, "SET", { 8 }, 2),
	Opcode(0xF6, "SET", { 16 }, 2),
	Opcode(0xF7, "SET", { 8 }, 2),
	Opcode(0xF8, "SET", { 8 }, 2),
	Opcode(0xF9, "SET", { 8 }, 2),
	Opcode(0xFA, "SET", { 8 }, 2),
	Opcode(0xFB, "SET", { 8 }, 2),
	Opcode(0xFC, "SET", { 8 }, 2),
	Opcode(0xFD, "SET", { 8 }, 2),
	Opcode(0xFE, "SET", { 16 }, 2),
	Opcode(0xFF, "SET", { 8 }, 2),
};

namespace Interrupt 
{
	const u8 VBLANK = 1 << 0;
	const u8 STAT = 1 << 1;
	const u8 TIMER = 1 << 2;
	const u8 SERIAL = 1 << 3;
	const u8 JOYPAD = 1 << 4;
}

namespace Memory {
	//interrupts
    const u16 IF = 0xFF0F;
	const u16 IE = 0xFFFF;

    const u16 VBLANK_INTERRUPT = 0x40;
    const u16 STAT_INTERRUPT = 0x48;
    const u16 TIMER_INTERRUPT = 0x50;
    const u16 SERIAL_INTERRUPT = 0x58;
    const u16 JOYPAD_INTERRUPT = 0x60;

	// Timers
	const u16 DIV = 0xFF04;
	const u16 TIMA = 0xFF05;
	const u16 TMA = 0xFF06;
	const u16 TAC = 0xFF07;

	const u16 JOYPAD_ADDR = 0xFF00;

	const u16 LY = 0xFF44;
	const u16 LYC = 0xFF45;
	const u16 STAT = 0xFF41;
	
}

namespace Timer {
	// TAC
	const u8 TIMER_ENABLE = 1 << 2;
	const u8 INPUT_CLOCK_SELECT = 1 << 1;
}
