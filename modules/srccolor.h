/* srccolor.h */
#ifndef _SRCCOLOR
#define _SRCCOLOR
#include <systemc.h>
#include "add2systemc.h"
#include "srcgeneral.h"

class srccolor: public srcgeneral {
	public:

	sc_fifo_out<int> output_red;
	sc_fifo_out<int> output_green;
	sc_fifo_out<int> output_blue;

	SC_HAS_PROCESS(srccolor);

	srccolor(sc_module_name name, const char* _filename, unsigned _maxwidth):
		srcgeneral(name, _filename, _maxwidth) {
			SC_THREAD(process);
		}

  	~srccolor() {
 		}

	void process();
};

#endif
