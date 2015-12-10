/*  quantize.h */ 
#ifndef _QUANTIZE
#define _QUANTIZE 
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(quantize) {
  
  my_fifo_in<float>   input;
  my_fifo_out<int>  output;

  int* quantization;

  SC_HAS_PROCESS(quantize);

  quantize(sc_module_name name, int* _quantization):
		sc_module(name),
		quantization(_quantization) {
			SC_THREAD(process);
		}
  
  void process();
};

#endif
