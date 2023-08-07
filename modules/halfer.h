#ifndef HALFER_H
#define HALFER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (half)
{
	sc_in<NN_DIGIT> input_hh;
	sc_in<NN_DIGIT> input_to_hh;
	sc_out<NN_DIGIT> output_hh;
	sc_out<NN_DIGIT> output_to_hh;

	void high_half_process();
	void to_high_half_process();

	SC_CTOR (half)
	{
		SC_METHOD(to_high_half_process);
		SC_METHOD(high_half_process);
		sensitive << input_hh << input_to_hh;
	}
};

#endif //HALFER_H