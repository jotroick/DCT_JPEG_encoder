/*  bit_unpacking.h */
#ifndef _BIT_UNPACK
#define _BIT_UNPACK
#include <systemc.h>
#include "add2systemc.h"

#define BUS_WIDTH 8
#define RL_WIDTH  7
#define VAL_WIDTH 9

SC_MODULE(bit_unpacking){

    my_fifo_in<sc_int<BUS_WIDTH> >   input;
    my_fifo_out<int>                output;

    SC_HAS_PROCESS(bit_unpacking);

    bit_unpacking(sc_module_name name):
        sc_module(name) {
            SC_THREAD(process);
        }

    void process();
};

#endif
