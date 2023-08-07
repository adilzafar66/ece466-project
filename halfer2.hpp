#ifndef HALFER2_H
#define HALFER2_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (half2)
{
    sc_in<NN_DIGIT> input_hh;
    sc_out<NN_DIGIT> output_hh;

	void high_half_process();

	SC_CTOR (half2)
	{
		SC_METHOD(high_half_process);
		sensitive << input_hh;
	}
};

void half2::high_half_process()
{
	output_hh.write(HIGH_HALF(input_hh.read()));
	std::cout << "HIGH HALF: " << HIGH_HALF(input_hh.read()) << std::endl;
}

#endif //HALFER2_H