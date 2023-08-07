#ifndef SUBTRACTOR_H
#define SUBTRACTOR_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(sub) {
    
    sc_in<NN_DIGIT> A; 
    sc_in<NN_DIGIT> B;	
    sc_out<NN_DIGIT> output;
    sc_out<sc_logic> done;

    void sub_process() {
        output.write(A.read() - B.read());
        done.write(SC_LOGIC_1);
    }
    
    SC_CTOR(sub) {
        SC_METHOD(sub_process);
        sensitive << A << B;
    }
};

#endif // SUBTRACTOR_H