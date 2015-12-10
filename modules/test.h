/*  test.h */ 
#ifndef _TEST
#define _TEST 
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(test) {

  my_fifo_in<int> reference;
  my_fifo_in<int> data;
  unsigned	correct, wrong;
  float	signal, noise;

  SC_CTOR(test)  {
	  correct = wrong = 0;
	  signal = noise = 0.0;
	  SC_THREAD(process);}
  ~test()  {print_result();}

  void process();
  void print_result();
  float snr();
  float psnr();
};

#endif
