#include "cart.h"
#include "cpu.h"
#include "mmu.h"
#include "interrupt.h"

class GB
{
public:
	GB(const char* rom_path);

	void run();

private:
	Cart* cart = nullptr;
	CPU* cpu = nullptr;
	MMU* mmu = nullptr;
	Interrupt* interrupt = nullptr;
	const char* rom_path = nullptr;
};
