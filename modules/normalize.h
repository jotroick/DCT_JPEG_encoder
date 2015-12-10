/*  normalize.h */ 
#ifndef _NORMALIZE
#define _NORMALIZE
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(normalize) {
  
  my_fifo_in<int>   input;
  my_fifo_out<float>  output;

  int* quantization;

  SC_HAS_PROCESS(normalize);

  normalize(sc_module_name name, int* _quantization):
		sc_module(name),
		quantization(_quantization) {
			SC_THREAD(process);
		}
  
  void process();
};

#endif
