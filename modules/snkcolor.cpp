#include "snkcolor.h"

void snkcolor::process() {
	unsigned temp;
	unsigned count;
	unsigned width;
	unsigned height;

    	if (!resultfile->is_open()) return;

	// write PGM identifier
    	*resultfile << "P3" << endl;
	// write width & height
	width = parameters.read();
	*resultfile << width << " ";
	height = parameters.read();
	*resultfile << height << endl;
	// write max gray value
	*resultfile << parameters.read() << endl;
	count = 0;
    	for (unsigned i=0; i< (width*height); i++) {
		temp=input_red.read();
		*resultfile << temp << " ";
		temp=input_green.read();
		*resultfile << temp << " ";
		temp=input_blue.read();
		*resultfile << temp << " ";
		count++;
		if (count == 6) {
			*resultfile << endl;
			count = 0;
		}
	}
	sc_stop();
}

