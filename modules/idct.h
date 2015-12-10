/*  idct.h */
#ifndef _IDCT
#define _IDCT
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(idct) {

  my_fifo_in<float>   input;
  my_fifo_out<int>  output;

  SC_CTOR(idct) { SC_THREAD(process);}

  void process();
};

#endif
