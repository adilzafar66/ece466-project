#ifndef REGISTER_H
#define REGISTER_H
#include "systemc.h"
#include "digit.h"

template<class T>
SC_MODULE(reg) {
    sc_in_clk clock;
    sc_in<sc_logic> load;
    sc_in<T> input; 
    sc_out<T> output;	

    void reg_process();
    
    SC_CTOR(reg) {
        SC_CTHREAD(reg_process, clock.pos());
    }
};

template<class T>
void reg<T>::reg_process() {
    
    while (1) {
        if (load.read() == SC_LOGIC_1) output.write(input.read());
	        wait();
    }
}

#endif //REGISTER_H