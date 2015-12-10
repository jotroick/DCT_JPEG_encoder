/*  rl_enc.h */ 
#ifndef _RL_ENC
#define _RL_ENC 
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(rl_enc) {
  
  my_fifo_in<int>   input;
  my_fifo_out<int>  output;

  SC_HAS_PROCESS(rl_enc);

  rl_enc(sc_module_name name):
		sc_module(name) {
			SC_THREAD(process);
		}
  
  void process();
};

#endif
