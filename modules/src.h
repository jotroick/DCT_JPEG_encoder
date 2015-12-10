/* src.h */
#ifndef _SRC
#define _SRC
#include <systemc.h>
#include "add2systemc.h"
#include "srcgeneral.h"

class src: public srcgeneral {
	public:

	my_fifo_out<int> output;

	SC_HAS_PROCESS(src);

	src(sc_module_name name, const char* _filename, unsigned _maxwidth):
		srcgeneral(name, _filename, _maxwidth) {
			SC_THREAD(process);
		}

  	~src() {
  		}

	void process();

};


#endif
