/*  b2r.h */ 
#ifndef _B2R
#define _B2R  
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(b2r) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;
  my_fifo_in<int>	parameters; /* new parameters */
  int maxwidth;

  SC_HAS_PROCESS(b2r);

  b2r(sc_module_name name, int _maxwidth): 
	sc_module(name),
	maxwidth(_maxwidth){
		SC_THREAD(process);
	}
  
  void process();
};

#endif
