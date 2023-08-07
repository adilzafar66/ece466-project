#include "systemc.h"
#include "halfer.h"
#include <iostream>

void half::to_high_half_process()
{
	std::cout << "HIGH HALF: " << TO_HIGH_HALF(input_to_hh.read()) << std::endl;
	output_to_hh.write(TO_HIGH_HALF(input_to_hh.read()));
}

void half::high_half_process()
{
	output_hh.write(HIGH_HALF(input_hh.read()));
}
