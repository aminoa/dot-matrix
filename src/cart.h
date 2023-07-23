#pragma once
#include <cstdint>
#include <vector>
#include <string>

#include "consts.h"

using std::vector; 

class Cart
{
public:
	Cart(const char* rom_path);

	vector<u8> rom;

	std::string title;
	u8 type;
	u8 rom_size;
	u8 ram_size;
	u8 version;

};