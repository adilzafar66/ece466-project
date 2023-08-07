#include "systemc.h"
#include "multiplexer.h"

void mux::mux_process() {
    if (sel.read() == SC_LOGIC_1) 
        output.write(B.read());
    else 
        output.write(A.read());
}