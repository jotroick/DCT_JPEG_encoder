/*  chromaup.h */
#ifndef _CHROMAUP
#define _CHROMAUP
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(chromaup) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;
  int width, height;

  SC_HAS_PROCESS(chromaup);

  chromaup(sc_module_name name, int _width, int _height):
	sc_module(name),
	width(_width),
	height(_height){
		SC_THREAD(process);
	}
  
  void process();
};

#endif
