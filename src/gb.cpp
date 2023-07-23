#include "gb.h"
#include <iostream>

GB::GB(const char* rom_path)
{
	this->rom_path = rom_path;
	this->cart = new Cart(rom_path);
}

void GB::run()
{
	std::cout << cart->title << std::endl;
	std::cout << cart->type << std::endl;
}


//void GB::load_rom()
//{
//	cart = new Cart(rom_path);
//}
