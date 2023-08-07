#ifndef SPLITTER_H
#define SPLITTER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE (split)
{
	sc_in<NN_DIGIT> input;
	sc_out<NN_DIGIT> output_high;
	sc_out<NN_DIGIT> output_low;

	void split_process();

	SC_CTOR (split)
	{
		SC_METHOD(split_process);
		sensitive << input;
	}
};

#endif //SPLITTER_H