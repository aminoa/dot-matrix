#include "GB.h"
#include "CPU.h"
#include <iostream>
#include <fstream>
#include <vector>

void GB::LoadROM(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (!file)
	{
		std::cout << "Unable to open file. Exiting...";
		exit(1);
	}

	fseek(file, 0L, SEEK_END);
	int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char* buffer = new unsigned char[file_size];
	fread(buffer, file_size, 1, file);
	fclose(file);

	for (int i = 0; i < file_size; ++i)
	{
		memory[i] = buffer[i];
	}

	delete[] buffer;
}

void GB::StartEmulation()
{
	std::cout << "Starting emulation..." << std::endl;
	CPU* cpu = new CPU();
	
	while (true)
	{
		cpu->ExecuteInstruction(&memory[cpu->PC]);
	}

	
}
