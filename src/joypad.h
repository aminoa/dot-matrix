#include <SDL2/SDL.h>
#include "consts.h"
#include "mmu.h"

namespace Buttons
{
	const u8 MODE_BUTTONS = 1 << 5;
	const u8 MODE_DPAD = 1 << 4;
	const u8 DOWN = 1 << 3;
	const u8 START = 1 << 3;
	const u8 UP = 1 << 2;
	const u8 SELECT = 1 << 2;
	const u8 LEFT = 1 << 1;
	const u8 B = 1 << 1;
	const u8 RIGHT = 1 << 0;
	const u8 A = 1 << 0;
}

class Joypad
{
public:
	Joypad(MMU* mmu);
	void update_inputs();

	MMU* mmu;

	const u8* state;

	bool up;
	bool down;
	bool left;
	bool right;
	bool a;
	bool b;
	bool start;
	bool select;
};