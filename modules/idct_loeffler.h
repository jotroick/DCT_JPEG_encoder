/*  idct_loeffler.h */
#ifndef _IDCT_LOEFFLER
#define _IDCT_LOEFFLER
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(idct_loeffler) {

  my_fifo_in<float>   input;
  my_fifo_out<int>  output;

  SC_CTOR(idct_loeffler) { SC_THREAD(process);}
  void idct1D(float values[]);

  void process();
};

#endif
