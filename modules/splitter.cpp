#include "systemc.h"
#include "splitter.h"

void split::split_process()
{
	output_high.write(HIGH_HALF(input.read()));
	output_low.write(LOW_HALF(input.read()));
}