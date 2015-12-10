/*  zz_dec.h */ 
#ifndef _ZZ_DEC
#define _ZZ_DEC 
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(zz_dec) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;

  SC_HAS_PROCESS(zz_dec);

  zz_dec(sc_module_name name): 
	sc_module(name) {
		SC_THREAD(process);
	}
  
  void process();
};

#endif
