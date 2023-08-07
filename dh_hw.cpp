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
        INPUT,
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

            // Transition to INPUT state
            state = INPUT;
            break;

        case INPUT:

            // Transition to INPUT state
            state = LOAD;
            break;
        
        case LOAD:
            load0_in.write(SC_LOGIC_1);
            load1_in.write(SC_LOGIC_1);
            load2_in.write(SC_LOGIC_1);
            load3_in.write(SC_LOGIC_1);

            // Transition to STAGE state
            state = STAGE;
            break;

        case STAGE:

            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            wait();
            std::cout << "MUX out: " << t1_sub2.read() << std::endl;
            

            bon_ready.write(true);

            wait();
            wait();
            wait();
            wait();

            load0_out.write(SC_LOGIC_1);
            load1_out.write(SC_LOGIC_1);
            load2_out.write(SC_LOGIC_1);

            wait();
            wait();

            // Transition to OUTPUT state
            state = OUTPUT;
            break;

        case OUTPUT:

            // NN_DIGIT t0_result = to_sw0.read();
            // NN_DIGIT t1_result = to_sw1.read();
            // NN_HALF_DIGIT ah_result = to_sw2.read();

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
