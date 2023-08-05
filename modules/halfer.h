#ifndef HALFER_H
#define HALFER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (half)
{
	sc_in<NN_DIGIT> input;
	sc_out<NN_DIGIT> output;

	void to_high_half_process();
	void high_half_process();

	SC_CTOR (half)
	{
		SC_METHOD(to_high_half_process);
		SC_METHOD(high_half_process);
		sensitive << input;
	}
};

#endif //HALFER_H