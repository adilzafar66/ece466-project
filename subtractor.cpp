#include "systemc.h"
#include "subtractor.h"

void sub::sub_process() {
    output.write(A.read() - B.read());
}