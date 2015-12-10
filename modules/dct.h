/*  dct.h */ 
#ifndef _DCT
#define _DCT
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(dct) {
  
  my_fifo_in<int>   input;
  my_fifo_out<float>  output;

  SC_CTOR(dct) { SC_THREAD(process);}
  
  void process();
};

#endif
