#include "cart.h"

class GB
{
public:
	GB(const char* rom_path);

	void run();
		
private:
	Cart* cart = nullptr;
	const char* rom_path = nullptr;
};
