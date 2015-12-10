#ifndef _SNKJPEG
#define _SNKJPEG
#include <systemc.h>
#include "add2systemc.h"
#include <stdio.h>

SC_MODULE(snkjpeg) {
	my_fifo_in<int>   	input;
	my_fifo_in<int>   	inbits;
	my_fifo_in<int>		parameters;

	FILE *jpegfile;

	SC_HAS_PROCESS(snkjpeg);

	snkjpeg(sc_module_name name, const char* _filename):
	sc_module(name) {
		jpegfile = fopen(_filename,"w");
			if (jpegfile==NULL) {
				cout << "Error opening file " << _filename << endl;
			}else {
				SC_THREAD(process);
			}
	}

  ~snkjpeg() {
    fclose(jpegfile);
  }

  void process();
  void ww(int);
  void wb(int);
  void store_bits(int);
};

#endif
