#ifndef MULTIPLIER_H
#define MULTIPLIER_H
#include "systemc.h"
#include "digit.h"

template <class T>
SC_MODULE (mult)
{
	sc_in<NN_DIGIT> A;
	sc_in<T> B;
	sc_out<NN_DIGIT> output;

	void mult_process();

	SC_CTOR (mult)
	{
		SC_METHOD(mult_process);
		sensitive << A << B;
	}
};

template<class T>
void mult<T>::mult_process()
{
	output.write(A.read() * B.read());
}

#endif //MULTIPLIER_H