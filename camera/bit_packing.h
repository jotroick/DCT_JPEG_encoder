/*  bit_packing.h */
#ifndef _BIT_PACK
#define _BIT_PACK
#include <systemc.h>
#include "add2systemc.h"

#define BUS_WIDTH 8
#define RL_WIDTH  7
#define VAL_WIDTH 9
#define CNT_WIDTH 4

SC_MODULE(bit_packing){

    sc_in<sc_int<9> >           input;
    sc_in<bool>                 ready_i;
    sc_out<bool>                ready_o;
    sc_in<bool>                 clk;
    sc_out<bool>                ask_i;
    sc_in<bool>                 ask_o;
    sc_in<bool>                 reset;
    sc_out<sc_int<BUS_WIDTH> >  output;

    enum ctrl_state {RESET, WAIT_READ_VAL, READ_VAL, WAIT_READ_RL,
                PREPARE_VAL, WAIT_WRITE_VAL, PREPARE_RL, WAIT_WRITE_RL};
    sc_signal<ctrl_state> state;
    sc_signal<sc_uint<CNT_WIDTH> >  i;
    sc_signal<sc_uint<CNT_WIDTH> >  buf_idx;
    sc_signal<sc_bv<VAL_WIDTH> >    value;
    sc_signal<sc_bv<RL_WIDTH> >     rl;
    sc_signal<sc_bv<BUS_WIDTH> >    buf;

    SC_HAS_PROCESS(bit_packing);

    bit_packing(sc_module_name name):
        sc_module(name) {
            SC_METHOD(process);
            sensitive << clk.pos();
        }

    void process();
};

#endif
