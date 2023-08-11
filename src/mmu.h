#pragma once
#include "cart.h"

class MMU
{
public:
	MMU(Cart* cart);
	u8 read_byte(u16 addr);
	void write_byte(u16 addr, u8 val);

	u16 read_short(u16 addr);
	void write_short(u16 addr, u16 val);

	std::vector<u8> ram;


	// Interrupts
	u8 IE;
	u8 IF;

	Cart* cart;
};