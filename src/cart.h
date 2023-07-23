#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include "consts.h"

using std::vector; 
using std::byte;

class Cart
{
public:
	Cart(const char* rom_path);

	vector<byte> rom;

	std::string title;
	u8 type;
	u8 rom_size;
	u8 ram_size;
	u8 version;

};