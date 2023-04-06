#pragma once
#include <iostream>
#include "mmu.h"
#include "interrupts.h"

class Timer
{
public:
	Timer(MMU* mmu, Interrupts* interrupts);

	void Check();
	void Increment();

private:
	MMU* mmu;
	Interrupts* interrupts;

	int div = 0;
	int tima = 0;
	int tac = 0;


};

