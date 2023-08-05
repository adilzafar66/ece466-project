#include "systemc.h"
#include "halfer.h"

void half::to_high_half_process()
{
	output.write(TO_HIGH_HALF(input.read()));
}

void half::high_half_process()
{
	output.write(HIGH_HALF(input.read()));
}
