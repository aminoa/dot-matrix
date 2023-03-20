#define _CRT_SECURE_NO_DEPRECATE
#include <stdint.h> 
#include "CPU.h"
#include "MMU.h"

class GB
{
public:
	void LoadROM(const char* path);
	void StartEmulation();
	void ExecuteInstruction(uint16_t* opcode);

private:
	CPU cpu;
	MMU mmu;
};