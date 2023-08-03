#include "systemc.h"
#include "digit.h"
#include "dh_hw.h"

void dh_hw::process_hw()
{

    NN_DIGIT t[2], c, u, v;
    NN_HALF_DIGIT aHigh, cLow, cHigh;

    for (;;)
    {
        // Wait for hw_enable to be asserted by SW
        while (!hw_enable.read())
            wait();

        // Read inputs (blocking FIFO access)
        t[0] = from_sw0.read();
        t[1] = from_sw1.read();
        c = from_sw2.read();
        aHigh = from_sw3.read();

        // Original code from NN_DigitDivHH():

        /*** Begin: Required part (to do: Datapath + Control) ***/
        cHigh = (NN_HALF_DIGIT)HIGH_HALF(c);
        cLow = (NN_HALF_DIGIT)LOW_HALF(c);

        u = (NN_DIGIT)aHigh * (NN_DIGIT)cLow;
        v = (NN_DIGIT)aHigh * (NN_DIGIT)cHigh;

        if ((t[0] -= TO_HIGH_HALF(u)) > (MAX_NN_DIGIT - TO_HIGH_HALF(u)))
            t[1]--;

        t[1] -= HIGH_HALF(u);
        t[1] -= v;
        /*** End: Required part ***/

        /*** Begin: Bonus part (optional: Extra Datapath + Extra Control) ***/
        while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF(cLow))))
        {
            if ((t[0] -= TO_HIGH_HALF(cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF(cLow))
                t[1]--;
            t[1] -= cHigh;
            aHigh++;
        }
        /*** End: Bonus part ***/

        // Write outputs (blocking FIFO access)
        to_sw0.write(t[0]);
        to_sw1.write(t[1]);
        to_sw2.write(aHigh);

        // Assert hw_done flag to indicate completion
        hw_done.write(true);

        // Wait for hw_enable to be deasserted by SW
        while (hw_enable.read())
            wait();

        // Deassert hw_done flag
        hw_done.write(false);
    }
}
