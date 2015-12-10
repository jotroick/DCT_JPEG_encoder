#ifndef _SNK
#define _SNK
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(snk) {
	my_fifo_in<int>   input;
	my_fifo_in<int>	parameters;

	ofstream *resultfile;

	SC_HAS_PROCESS(snk);

	snk(sc_module_name name, const char* _filename):
	sc_module(name) {
		resultfile = new ofstream(_filename);
			if (!resultfile->is_open()) cout << "Error opening file " << _filename << endl;
		SC_THREAD(process);
	}

  ~snk() {
    resultfile->close();
  }

  void process();
};

#endif
