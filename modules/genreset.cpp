#include "genreset.h"

void genreset::process() {

	reset.write(true); //could be removed
	for (unsigned count=0; count<duration; count++) {
		wait();}
	reset.write(false);
	while(true) {
		wait();
	}
}



