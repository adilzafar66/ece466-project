#include "systemc.h"
#include "comparator.h"

void comp::comp_process() {
    
    // Default
    EQ.write(SC_LOGIC_0);
    GT.write(SC_LOGIC_0);
    LT.write(SC_LOGIC_0);
    
    if (A.read() == B.read()) EQ.write(SC_LOGIC_1);
    if (A.read() > B.read()) GT.write(SC_LOGIC_1);
    if (A.read() < B.read()) LT.write(SC_LOGIC_1);
    
}