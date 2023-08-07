#include "systemc.h"
#include "register.h"

template<class T>
void reg<T>::reg_process() {
    
    while (1) {
        if (reset.read() == SC_LOGIC_1) output.write(0);
        else if (load.read() == SC_LOGIC_1) output.write(input.read());
	    wait();
    }
}