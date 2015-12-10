/* genreset.h */
#ifndef _GENRESET
#define _GENRESET
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(genreset) {

	sc_out<bool> reset;
	sc_in<bool> clk;
	unsigned duration;

	SC_HAS_PROCESS(genreset);

	genreset(sc_module_name name, unsigned _duration):
		sc_module(name), duration(_duration){
		SC_CTHREAD(process,clk.pos());
		};

	void process();

	void start_of_simulation () {
		cout << "test start of simulation" << endl;
		reset.write(true); // initial value
		};
	};

#endif
