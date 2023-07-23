#pragma once

#include "cart.h"
#include <stdio.h>
#include <fstream>
#include "consts.h"

Cart::Cart(const char* rom_path)
{
	std::ifstream instream(rom_path, std::ios::binary);
	auto length = instream.seekg(0, std::ios::end).tellg();
	instream.seekg(0, std::ios_base::beg);

	rom.resize(length);
	instream.read(reinterpret_cast<char*>(rom.data()), length);
	instream.close();

	//reading cartidge header metadata
	title = std::string(reinterpret_cast<char*>(rom.data() + 0x134), 16);
	type = rom[0x147];
	rom_size = rom[0x148];
	ram_size = rom[0x149];
	version = rom[0x14C];
}
