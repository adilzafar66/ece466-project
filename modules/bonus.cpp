#include "systemc.h"
#include "bonus.h"

void bonus::bonus_proc()
{
    NN_DIGIT t[2], c;
    NN_HALF_DIGIT aHigh, cLow, cHigh;
    while (true)
    {
        if (ready.read() == true)
        {   // "Required Part" finished? (need valid t[0], t[1])
            t[0] = T0.read();
            t[1] = T1.read();
            c = C.read();
            aHigh = AH.read();
            cHigh = (NN_HALF_DIGIT)HIGH_HALF(c);
            cLow = (NN_HALF_DIGIT)LOW_HALF(c);
            while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF(cLow))))
            {
                if ((t[0] -= TO_HIGH_HALF(cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF(cLow))
                    t[1]--;
                t[1] -= cHigh;
                aHigh++;
            }
            T0new.write(t[0]);
            T1new.write(t[1]);
            AHnew.write(aHigh);
        }
        wait();
    }
}