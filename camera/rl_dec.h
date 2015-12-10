/*  rl_dec.h */
#ifndef _RL_DEC
#define _RL_DEC
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(rl_dec){

  my_fifo_in<int>   input;
  my_fifo_out<int>  output;

  SC_HAS_PROCESS(rl_dec);

  rl_dec(sc_module_name name):
		sc_module(name) {
			SC_THREAD(process);
		}

  void process();
};

//===================================================================================
SC_MODULE(rl_dec_pr) {

// port
  my_fifo_out<int>  	output;
  sc_in<int>		 	input;
  sc_in<bool>			ready;
  sc_out<bool>			ask;
  sc_in_clk				clk;


  SC_HAS_PROCESS(rl_dec_pr);

  rl_dec_pr(sc_module_name name):
		sc_module(name) {
			SC_THREAD(process);
			sensitive << clk.pos();
		}

  void process();
};
// ====================================================================================


#endif
