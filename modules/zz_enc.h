/*  zz_enc.h */ 
#ifndef _ZZ_ENC
#define _ZZ_ENC  
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(zz_enc) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;

  SC_HAS_PROCESS(zz_enc);

  zz_enc(sc_module_name name): 
	sc_module(name) {
		SC_THREAD(process);
	}
  
  void process();
};

#endif
