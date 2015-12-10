//*  rl_enc.h */
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(rl_enc1) {


    // ports

    sc_out< sc_int<9> >     output;
    sc_in<bool>             ask_o;
    sc_out<bool>            ready_o;
    sc_in< sc_int<9> >      input;
    sc_in<bool>             ready_i;
    sc_out<bool>            ask_i;
    sc_in<bool>             clk;
    sc_in<bool>             reset;

    // variables as signals
    enum    ctrl_state {RESET, READZIGZAG, WRITEDC, WAITFORZEROS, READZEROS,
        COUNTING , WRITECOUNT, WAITTOWRITE, TERMINATION};
    sc_signal<ctrl_state>   state;
    sc_signal< sc_int<9> >  count;
    sc_signal< sc_int<9> >  value;
    sc_signal< sc_uint<7> > i;

    void process();

    SC_CTOR(rl_enc1){
        SC_METHOD(process);
        sensitive << clk.pos();
    }

};

