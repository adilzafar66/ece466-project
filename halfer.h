#ifndef HALFER_H
#define HALFER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (half)
{
	sc_in<NN_DIGIT> input_to_hh;
	sc_out<NN_DIGIT> output_to_hh;

	void to_high_half_process();

	SC_CTOR (half)
	{
		SC_METHOD(to_high_half_process);
		sensitive << input_to_hh;
	}
};

#endif //HALFER_H