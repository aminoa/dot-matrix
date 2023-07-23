#pragma once
#include "cart.h"

class MMU
{
public:
	MMU(Cart* cart);
	u8 read(u16 addr);
	void write(u16 addr, u8 val);

	std::vector<u8> memory;
	Cart* cart;

};