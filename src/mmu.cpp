#include "MMU.h"
#include <iostream>

MMU::MMU()
{
	for (int i = 0; i < 0xFFFF; ++i)
	{
		memory[i] = 0;
	}
}

void MMU::LoadROM(const char* path)
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

uint8_t MMU::ReadMemory(uint16_t address)
{
	return address;
}
