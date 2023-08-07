#include "systemc.h"
#include "halfer.h"

void half::to_high_half_process()
{
	output_to_hh.write(TO_HIGH_HALF(input_to_hh.read()));
}
