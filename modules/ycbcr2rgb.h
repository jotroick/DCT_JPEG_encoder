/*  ycbcr2rgb.h */
#ifndef _YCbCr2RGB
#define _YCbCr2RGB
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(ycbcr2rgb) {
  
  my_fifo_in<int>   input_y;
  my_fifo_in<int>   input_cb;
  my_fifo_in<int>   input_cr;
  my_fifo_out<int>  output_red;
  my_fifo_out<int>  output_green;
  my_fifo_out<int>  output_blue;

  SC_HAS_PROCESS(ycbcr2rgb);

  ycbcr2rgb(sc_module_name name):
		sc_module(name){
			SC_THREAD(process);
		}
  
  void process();
};

#endif
