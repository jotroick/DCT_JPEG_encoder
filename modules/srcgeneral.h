/* srcgeneral.h */
#ifndef _SRCGENERAL
#define _SRCGENERAL
#include <systemc.h>
#include "add2systemc.h"

SC_MODULE(srcgeneral) {

	my_fifo_out<int> parameters;

  	unsigned maxwidth;
	ifstream *stimulusfile;

	srcgeneral(sc_module_name name, const char* _filename, unsigned _maxwidth):
		sc_module(name),
		maxwidth(_maxwidth) {
			stimulusfile = new ifstream(_filename);
			if (!stimulusfile->is_open()) {
				cout << "Error opening file " << _filename << endl;
			} else {
				cout << "Successful opened file " << _filename << endl;
			}
		}

  	~srcgeneral() {
    		stimulusfile->close();
  		}

	bool read_value_from_file_without_comments(ifstream *, unsigned *);

};


#endif
