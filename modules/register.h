#ifndef REGISTER_H
#define REGISTER_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(reg) {
    sc_in_clk clock;
    sc_in<sc_logic> reset, load;
    sc_in<NN_DIGIT> input; 
    sc_out<NN_DIGIT> output;	

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};

#endif //REGISTER_H