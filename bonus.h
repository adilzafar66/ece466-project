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

    void bonus_proc() {
        NN_DIGIT t[2], c;
        NN_HALF_DIGIT aHigh, cLow, cHigh;
        while (true) {
            if (ready.read() == true) {
                t[0] = T0.read();
                t[1] = T1.read();
                c = C.read();
                aHigh = AH.read();
                cHigh = (NN_HALF_DIGIT)HIGH_HALF(c);
                cLow = (NN_HALF_DIGIT)LOW_HALF(c);
                while ((t[1] > cHigh) || ((t[1] == cHigh) && (t[0] >= TO_HIGH_HALF(cLow)))) {
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
    
    SC_CTOR(bonus) { SC_CTHREAD(bonus_proc, clock.pos()); }
};

#endif // BONUS_H