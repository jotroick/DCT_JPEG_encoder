/*  r2b.h */ 
#ifndef _R2B
#define _R2B  
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(r2b) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;
  my_fifo_in<int>	parameters; /* new parameters */
  int maxwidth;

  SC_HAS_PROCESS(r2b);

  r2b(sc_module_name name, int _maxwidth): 
	sc_module(name),
	maxwidth(_maxwidth){
		SC_THREAD(process);
	}
  
  void process();
};

#endif
