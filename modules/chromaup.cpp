#include "chromaup.h"

void chromaup::process() {

	int		widthsub = width/2;
	int*	line = new int [widthsub];
	int		row, col, value;

	while(1) {
		for (row=0;row<height;row=row+2){
			for (col=0; col<widthsub; col++) {
				value = input.read();
				line[col] = value;
				output.write(value);
				output.write(value);
			}
			for (col=0; col<widthsub; col++) {
				line[col] = value;
				output.write(value);
				output.write(value);
			}
		}
	}
}

