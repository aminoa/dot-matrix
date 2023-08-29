#pragma once
#include "input.h"
#include "mmu.h"
#include "consts.h"

Input::Input(MMU* mmu)
{
	this->mmu = mmu;

	up = false;
	down = false;
	left = false;
	right = false;
	a = false;
	b = false;
	start = false;
	select = false;

	state = SDL_GetKeyboardState(NULL);
}

void Input::update_joypad()
{
	SDL_PumpEvents();
	up = state[SDL_SCANCODE_UP];
	down = state[SDL_SCANCODE_DOWN];
	left = state[SDL_SCANCODE_LEFT];
	right = state[SDL_SCANCODE_RIGHT];
	a = state[SDL_SCANCODE_X];
	b = state[SDL_SCANCODE_Z];
	start = state[SDL_SCANCODE_RETURN];
	select = state[SDL_SCANCODE_BACKSPACE];

	//std::cout << up << down << left << right << a << b << start << select << std::endl;
	//0 is pressed, 1 is released
	u8 button_mode = ~mmu->read_byte(Memory::JOYPAD_ADDR) && 0x30; 
	
	if (button_mode && Buttons::MODE_DPAD)
	{
		if (up) { button_mode |= Buttons::UP; }
		if (down) { button_mode |= Buttons::DOWN; }
		if (left) { button_mode |= Buttons::LEFT; }
		if (right) { button_mode |= Buttons::RIGHT; }
	}
	if (button_mode && Buttons::MODE_BUTTONS)
	{
		if (a) { button_mode |= Buttons::A; }
		if (b) { button_mode |= Buttons::B; }
		if (start) { button_mode |= Buttons::START; }
		if (select) { button_mode |= Buttons::SELECT; }
	}
	
	mmu->write_byte(Memory::JOYPAD_ADDR, ~button_mode & 0x3F);

	// TODO: implement joypad interrupt
}
