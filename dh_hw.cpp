#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"
#include <iostream>

void dh_hw::process_hw()
{

    // FSM state enum
    enum FSM_State
    {
        WAIT,
        LOAD,
        STAGE,
        OUTPUT,
        FINISH
    };
    FSM_State state = WAIT;

    for (;;)
    {
        switch (state)
        {
        case WAIT:
            hw_done.write(false);
            // Wait for hw_enable to be asserted by SW
            while (!hw_enable.read())
                wait();

            // Transition to LOAD state
            state = LOAD;
            break;
        
        case LOAD:

            sub0_done.write(SC_LOGIC_0);
            sub1_done.write(SC_LOGIC_0);
            sub2_done.write(SC_LOGIC_0);
            sub3_done.write(SC_LOGIC_0);
            sub4_done.write(SC_LOGIC_0);

            load0_in.write(SC_LOGIC_1);
            load1_in.write(SC_LOGIC_1);
            load2_in.write(SC_LOGIC_1);
            load3_in.write(SC_LOGIC_1);

            // Transition to STAGE state
            state = STAGE;
            break;

        case STAGE:
            while (sub0_done.read() != SC_LOGIC_1 &&
                   sub1_done.read() != SC_LOGIC_1 && 
                   sub2_done.read() != SC_LOGIC_1 &&
                   sub3_done.read() != SC_LOGIC_1 &&
                   sub4_done.read() != SC_LOGIC_1)
                wait();      
            bon_ready.write(true);
            wait();
            wait();

            // Transition to OUTPUT state
            state = OUTPUT;
            break;

        case OUTPUT:

            load0_out.write(SC_LOGIC_1);
            load1_out.write(SC_LOGIC_1);
            load2_out.write(SC_LOGIC_1);
            wait();

            // Transition to FINISH state
            state = FINISH;
            break;
        
        case FINISH:
            
            // Assert hw_done flag to indicate completion
            hw_done.write(true);

            // Wait for hw_enable to be deasserted by SW
            while (hw_enable.read())
                wait();

            // Transition back to WAIT state
            state = WAIT;
            break;
        }
        wait();
    }
}
