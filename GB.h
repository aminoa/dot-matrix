#define _CRT_SECURE_NO_DEPRECATE
#include <stdint.h> 

class GB
{
public:
	void LoadROM(const char* path);
	void StartEmulation();

public:
	uint16_t memory[0xFFFF];

	uint16_t AF;
	uint16_t BC;
	uint16_t DE;
	uint16_t HL;
	uint16_t PC;
	uint16_t SP;
};