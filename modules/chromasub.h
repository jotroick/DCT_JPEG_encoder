/*  chromasub.h */
#ifndef _CHROMASUB
#define _CHROMASUB
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(chromasub) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;
  int width, height;

  SC_HAS_PROCESS(chromasub);

  chromasub(sc_module_name name, int _width, int _height):
	sc_module(name),
	width(_width),
	height(_height){
		SC_THREAD(process);
	}
  
  void process();
};

#endif
