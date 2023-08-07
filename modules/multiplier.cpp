#include "systemc.h"
#include "multiplier.h"

template<class T>
void mult<T>::mult_process()
{
	output.write(A.read() * B.read());
}