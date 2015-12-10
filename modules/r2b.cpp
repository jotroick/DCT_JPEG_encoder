#include "r2b.h"

void r2b::process() {

	int		in1;
	int		row, col;
	int		maxwidth8  = (maxwidth +7)/8 * 8;   // round up to multiples of 8
	int *		lines = new int [maxwidth8 * 8];	// we need 8 lines before outputting
	int		count = 0;			// number of lines read in
	int		width, height, width8;		// the actual width and height of the picture

	/* read first the parameters */
	width=parameters.read();
	height=parameters.read();
	width8 = ((width+7)/8)*8;

	while(1) {
		for (row=0; row<8; row++) {
			if (count < height) {
				for (col = 0 ; col < width8 ; col++ ) {
					if (col < width) in1 = input.read();    // repeat last values
					lines [row * width8 + col] = in1;
				}
			}
			else {
				for (col = 0; col < width8; col++ ) {
					lines [row * width8 + col] = lines [(row-1) * width8 + col];
				}
			}
		count++;  // line done
		}
		if (count >= height) count = 0;

		//-- when 8 lines read, output blocks
	    for ( col = 0 ; col < width8 ; col += 8 ) {
			for ( row = 0 ; row < 8 ; row++ ) {
				for ( int k = 0 ; k < 8 ; k++ ) {
					output.write (lines [ col + row * width8 + k ]);
				}
			}
		}
	}
}

