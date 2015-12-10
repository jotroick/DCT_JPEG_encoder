/*  testcolor.h */
#ifndef _TESTCOLOR
#define _TESTCOLOR
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(testcolor) {

  my_fifo_in<int> reference_red;
  my_fifo_in<int> reference_green;
  my_fifo_in<int> reference_blue;
  my_fifo_in<int> data_red;
  my_fifo_in<int> data_green;
  my_fifo_in<int> data_blue;
  unsigned	correct,wrong;
  double	signal, noise;

  SC_CTOR(testcolor)  {SC_THREAD(process);}
  ~testcolor()  {print_result();}

  void process();
  void print_result();
  void evaluate_pixel(int, int);
};

#endif
