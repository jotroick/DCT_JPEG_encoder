#ifndef _SNKCOLOR
#define _SNKCOLOR
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(snkcolor) {

  my_fifo_in<int>   	input_red;
  my_fifo_in<int>   	input_green;
  my_fifo_in<int>   	input_blue;
  my_fifo_in<int>	parameters;

  ofstream *resultfile;

  SC_HAS_PROCESS(snkcolor);

  snkcolor(sc_module_name name, const char* _filename):
	sc_module(name) {
	    resultfile = new ofstream(_filename);
    	    if (!resultfile->is_open()) cout << "Error opening file " << _filename << endl;
	    SC_THREAD(process);
	}

  ~snkcolor() {
    resultfile->close();
  }

  void process();
};

#endif
