/*  rgb2ycbcr.h */
#ifndef _RGB2YCbCr
#define _RGB2YCbCr
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(rgb2ycbcr) {
  
  my_fifo_in<int>   input_red;
  my_fifo_in<int>   input_green;
  my_fifo_in<int>   input_blue;
  my_fifo_out<int>  output_y;
  my_fifo_out<int>  output_cb;
  my_fifo_out<int>  output_cr;

  SC_HAS_PROCESS(rgb2ycbcr);

  rgb2ycbcr(sc_module_name name):
		sc_module(name){
			SC_THREAD(process);
		}
  
  void process();
};

#endif
