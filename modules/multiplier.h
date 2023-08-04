#ifndef MULTIPLIER_H
#define MULTIPLIER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (mult)
{
	sc_in<NN_DIGIT> A;
	sc_in<NN_DIGIT> B;
	sc_out<NN_DIGIT> output;

	void mult_process();

	SC_CTOR (mult)
	{
		SC_METHOD(mult_process);
		sensitive << A << B;
	}
};

#endif //MULTIPLIER_H