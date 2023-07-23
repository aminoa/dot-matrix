#pragma once

#include "main.h"
#include "gb.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Usage: dot_matrix <ROM>" << std::endl;
		return 1;
	}

	GB* gb = new GB(argv[1]);
	gb->run();
	return 0;
}