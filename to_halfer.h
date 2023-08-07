#ifndef TO_HALFER_H
#define TO_HALFER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (to_half)
{
	sc_in<NN_DIGIT> input_to_hh;
	sc_out<NN_DIGIT> output_to_hh;

	void to_high_half_process();

	SC_CTOR (to_half)
	{
		SC_METHOD(to_high_half_process);
		sensitive << input_to_hh;
	}
};

void to_half::to_high_half_process()
{
	output_to_hh.write(TO_HIGH_HALF(input_to_hh.read()));
}


#endif //TO_HALFER_H