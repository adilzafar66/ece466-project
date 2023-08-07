#ifndef BONUS_H
#define BONUS_H
#include "systemc.h"
#include "digit.h"

SC_MODULE(bonus)
{
    sc_in<NN_DIGIT> T0, T1, C;
    sc_in<NN_HALF_DIGIT> AH;
    sc_out<NN_DIGIT> T0new, T1new;
    sc_out<NN_HALF_DIGIT> AHnew;
    sc_in<bool> ready;
    sc_in_clk clock;

    void bonus_proc();
    
    SC_CTOR(bonus) { SC_CTHREAD(bonus_proc, clock.pos()); }
};

#endif // BONUS_H