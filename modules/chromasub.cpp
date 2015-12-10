#include "chromasub.h"

void chromasub::process() {

	int		widthsub = width/2;
	int*	line = new int [widthsub];
	int		row, col, value;

	while(1) {
		for (row=0;row<height;row=row+2){
			for (col=0; col<widthsub; col++) {
				line[col] = input.read()+ input.read();
			}
			for (col=0; col<widthsub; col++) {
				value = (line[col] + input.read()+ input.read())/4;
				output.write(value);
			}
		}
	}
}

