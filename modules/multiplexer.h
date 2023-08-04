#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(mux) {
    
    sc_in<sc_logic> sel;
    sc_in<NN_DIGIT> A; 
    sc_in<NN_DIGIT> B;	
    sc_out<NN_DIGIT> output;

    void mux_process();
    
    SC_CTOR(mux) {
        SC_METHOD(mux_process);
        sensitive << sel << A << B;
    }
};

#endif //MULTIPLEXER_H