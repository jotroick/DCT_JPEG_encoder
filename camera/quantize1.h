/*  quantize1.h */ 
#ifndef _QUANTIZE1
#define _QUANTIZE1 
#define SC_INCLUDE_FX
#define INC_WITDH   4
#define IN_WITDH_1  23
#define IN_WITDH_2  13
#define OUT_WITDH   9
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(quantize1) {

    sc_in<sc_fixed<IN_WITDH_1, IN_WITDH_2, SC_RND, SC_SAT> > input;
    sc_in<bool>                 clk;
    sc_in<bool>                 ready_i;
    sc_out<bool>                ready_o;
    sc_out<bool>                ask_i;
    sc_in<bool>                 ask_o;
    sc_in<bool>                 reset;
    sc_out<sc_int<OUT_WITDH> >  output;

    sc_fixed<32,2>* quantization;
    enum ctrl_state {RESET, WAITREAD_P1, WAITREAD_P2, WAITREAD, READ,
        WAITWRITE, CHECKLOOP, TERMINATION};
    sc_signal<ctrl_state> state;
    sc_signal<sc_uint<INC_WITDH> >  i;
    sc_signal<sc_uint<INC_WITDH> >  j;
    sc_signal<sc_int<OUT_WITDH> >   temp_out;
    sc_signal<sc_fixed<32, 2> >     quant_val;
    sc_signal<sc_fixed<23,13> >     prod_val;

    SC_HAS_PROCESS(quantize1);

    quantize1(sc_module_name name, sc_fixed<32, 2>* _quantization):
        sc_module(name),
        quantization(_quantization) {
            SC_METHOD(process);
            sensitive << clk.pos();
        }

    void process();
};

#endif
