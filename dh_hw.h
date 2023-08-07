#ifndef _DH_HW_H_
#define _DH_HW_H_ 1

#include "systemc.h"
#include "digit.h"
#include "bonus.h"
#include "adder.h"
#include "comparator.h"
#include "halfer.h"
#include "to_halfer.h"
#include "multiplexer.h"
#include "multiplier.h"
#include "register.h"
#include "splitter.h"
#include "subtractor.h"

SC_MODULE(dh_hw)
{
    // Inputs from SW (Software) and Outputs to SW
    sc_in_clk clk;
    sc_in<NN_DIGIT> from_sw0, from_sw1, from_sw2;
    sc_in<NN_HALF_DIGIT> from_sw3;
    sc_out<NN_DIGIT> to_sw0, to_sw1;
    sc_out<NN_HALF_DIGIT> to_sw2;

    // Control signals
    sc_in<bool> hw_enable;
    sc_out<bool> hw_done;

    // Interconnection Signals
    sc_signal<bool> bon_ready;
    sc_signal<UINT4> max_nn, dec;
    sc_signal<NN_DIGIT> t0, t1, c;
    sc_signal<NN_DIGIT> t0_out, t1_out;
    sc_signal<NN_DIGIT> c_low, c_high, u, v;
    sc_signal<NN_DIGIT> u_to_hh, u_hh, r_comp, l_comp;
    sc_signal<NN_DIGIT> t1_sub1, t1_sub2, t1_sub3, mux_out;
    sc_signal<sc_logic> comp_out_gt, comp_out_lt, comp_out_eq;
    sc_signal<sc_logic> load0_in, load1_in, load2_in, load3_in;
    sc_signal<sc_logic> load0_out, load1_out, load2_out, load3_out;
    sc_signal<sc_logic> sub0_done, sub1_done, sub2_done, sub3_done, sub4_done;
    sc_signal<NN_HALF_DIGIT> ah, ah_out;

    // Registers and Components
    reg<NN_DIGIT> r0_in, r1_in, r2_in, r0_out, r1_out;      // Registers
    reg<NN_HALF_DIGIT> r3_in, r2_out;                       // Registers
    mult<NN_HALF_DIGIT> mult0, mult1;                       // Multipliers
    sub sub0, sub1, sub2, sub3, sub4;                       // Subtractors                   
    to_half to_half0; half half0;                           // Halfers
    split split0; comp comp0;                               // Splitter & Comparator
    mux mux0; bonus bon;                                    // Multiplexer & Bonus

    void process_hw();

    SC_CTOR(dh_hw) : r0_in("r0_in"), r1_in("r1_in"), r2_in("r2_in"), r3_in("r3_in"),
                     r0_out("r0_out"), r1_out("r1_out"), r2_out("r2_out"), mult0("mult1"), mult1("mult2"), 
                     split0("split"), comp0("comp0"), bon("bon"), half0("half0"), to_half0("to_half0"),
                     sub0("sub0"), sub1("sub1"), sub2("sub2"), sub3("sub3"), sub4("sub4"), mux0("mux1")
    {
        dec.write(0x1);
        max_nn.write(MAX_NN_DIGIT);

        // Connect ports of the registers with other components
        r0_in.clock(clk); r0_in.input(from_sw0); r0_in.load(load0_in); r0_in.output(t0);
        r1_in.clock(clk); r1_in.input(from_sw1); r1_in.load(load1_in); r1_in.output(t1);
        r2_in.clock(clk); r2_in.input(from_sw2); r2_in.load(load2_in); r2_in.output(c);
        r3_in.clock(clk); r3_in.input(from_sw3); r3_in.load(load3_in); r3_in.output(ah);        
        r0_out.clock(clk); r0_out.input(t0_out); r0_out.load(load0_out); r0_out.output(to_sw0);
        r1_out.clock(clk); r1_out.input(t1_out); r1_out.load(load1_out); r1_out.output(to_sw1);
        r2_out.clock(clk); r2_out.input(ah_out); r2_out.load(load2_out); r2_out.output(to_sw2);

        // Connect ports of custom components
        bon.T0(l_comp); bon.T1(t1_sub3); bon.C(c); bon.AH(ah); bon.T0new(t0_out);
        bon.clock(clk); bon.ready(bon_ready); bon.T1new(t1_out); bon.AHnew(ah_out);
        mux0.A(t1); mux0.B(t1_sub1); mux0.sel(comp_out_gt); mux0.output(mux_out);
        split0.input(c); split0.output_high(c_high); split0.output_low(c_low);
        mult0.A(c_low); mult0.B(ah); mult0.output(u);
        mult1.A(c_high); mult1.B(ah); mult1.output(v);
        half0.input_hh(u); half0.output_hh(u_hh);
        to_half0.input_to_hh(u); to_half0.output_to_hh(u_to_hh);
        sub0.A(max_nn); sub0.B(u_to_hh); sub0.output(r_comp); sub0.done(sub0_done);
        sub1.A(t0); sub1.B(u_to_hh); sub1.output(l_comp); sub1.done(sub1_done);
        sub2.A(t1); sub2.B(dec); sub2.output(t1_sub1); sub2.done(sub2_done);
        sub3.A(mux_out); sub3.B(u_hh); sub3.output(t1_sub2); sub3.done(sub3_done);
        sub4.A(t1_sub2); sub4.B(v); sub4.output(t1_sub3); sub4.done(sub4_done);
        comp0.A(l_comp); comp0.B(r_comp); comp0.GT(comp_out_gt);
        comp0.LT(comp_out_lt); comp0.EQ(comp_out_eq);

        // Create a new thread to process the hardware functionality
        SC_THREAD(process_hw);
        sensitive << clk.pos();
    }
};

#endif /* end _DH_HW_H_ */