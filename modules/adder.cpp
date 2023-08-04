#include "systemc.h"
#include "adder.h"

void add::add_process()
{
	ouput.write(A.read() + B.read());
}