#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(sub) {
    
    sc_in<NN_DIGIT> A; 
    sc_in<NN_DIGIT> B;	
    sc_out<NN_DIGIT> output;

    void sub_process() {
        output.write(A.read() - B.read());
    }
    
    SC_CTOR(sub) {
        SC_METHOD(sub_process);
        sensitive << A << B;
    }
};

#endif // SUBTRACTOR_H