#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(comp) {
    
    sc_in<NN_DIGIT> A, B; 
    sc_out<sc_logic> EQ, GT, LT;

    void comp_process();
    
    SC_CTOR(comp) {
        SC_METHOD(comp_process);
        sensitive << A << B;
    }
};

#endif //COMPARATOR_H
