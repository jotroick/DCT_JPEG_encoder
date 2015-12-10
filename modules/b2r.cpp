#include "b2r.h"

void b2r::process() {

	int		row, col;
	int		maxwidth8  = (maxwidth +7)/8 * 8;   // round up to multiples of 8
	int *	lines = new int [maxwidth8 * 8];	// we need 8 lines before outputting
	int		count = 0;							// number of lines read in
	int		width, height, width8;				// the actual width and height of the picture

	/* read first the parameters */
	width=parameters.read();
	height=parameters.read();
	width8 = ((width+7)/8)*8;

	/* perform the block rasterisation */
	while(1) {
		//read in the blocks for 8 lines
	    for ( col = 0 ; col < width8 ; col += 8 ) {
			for ( row = 0 ; row < 8 ; row++ ) {
				for ( int k = 0 ; k < 8 ; k++ ) {
					lines [ col + row * width8 + k ]= input.read();
				}
			}
		}
		for (row=0; row<8; row++) {
			if (count < height) {
				for (col = 0 ; col < width ; col++ ) {
					output.write(lines [row * width8 + col]);
				}
			}
		count++;  // line done
		}
		if (count >= height) count = 0;
	}
}
