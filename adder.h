#ifndef ADDER_H
#define ADDER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (add)
{
	sc_in<NN_DIGIT> A;
	sc_in<NN_DIGIT> B;
	sc_out<NN_DIGIT> ouput;

	void add_process() {
		ouput.write(A.read() + B.read());
	}

	SC_CTOR (add)
	{
		SC_METHOD(add_process);
		sensitive << A << B;
	}
};

#endif //ADDER_H