#include "GB.h"

#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: dot_matrix <ROM>" << std::endl;
		return 1;
	}

	GB* gb = new GB();
	gb->LoadROM(argv[1]);
	gb->StartEmulation();
}
