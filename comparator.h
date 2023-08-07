#ifndef COMPARATOR_H
#define COMPARATOR_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(comp) {
    
    sc_in<NN_DIGIT> A, B; 
    sc_out<sc_logic> EQ, GT, LT;

    void comp_process() {
        EQ.write(SC_LOGIC_0);
        GT.write(SC_LOGIC_0);
        LT.write(SC_LOGIC_0);
        
        if (A.read() == B.read()) EQ.write(SC_LOGIC_1);
        if (A.read() > B.read()) GT.write(SC_LOGIC_1);
        if (A.read() < B.read()) LT.write(SC_LOGIC_1);
    }
    
    SC_CTOR(comp) {
        SC_METHOD(comp_process);
        sensitive << A << B;
    }
};

#endif //COMPARATOR_H
