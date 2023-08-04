#include "systemc.h"
#include "multiplier.h"

void mult::mult_process()
{
	output.write(A.read() * B.read());
}