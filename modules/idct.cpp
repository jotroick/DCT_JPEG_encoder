#include "idct.h"

void idct::process() {

	int		i, j, k;
	float	value;
	float	block[64];
	float	temp_block[64];
	float	dct_coeffs[64];
	float	pi;
	int		blocki[64];
	int		pix;

	// calculate pi
	pi = 2*acos(0.0);

	// initialize dct_coeffs
	for ( i = 0 ; i < 8 ; i++ ) {
	    for ( j = 0 ; j < 8 ; j++ ) {
			dct_coeffs[i*8+j] = cos((pi*(2*i+1)*j)/16);
		}
	}

	while (1) {
	// read input
		for ( i = 0 ; i < 8 ; i++ ) {
		    for ( j = 0 ; j < 8 ; j++ ) {
				block[i*8+j] = input.read();
			}
		}

	// vertical 1D idct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ) {
				value = (block[j] * dct_coeffs[i*8])/sqrt(2);
				for ( k = 1 ; k < 8 ; k++ ) {
					value += block[k*8+j] * dct_coeffs[i*8+k];
				}
				temp_block[i*8+j] = value / 2.0;
			}
		}

	// horizontal 1D idct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ) {
				value = (temp_block[j*8] * dct_coeffs[i*8])/sqrt(2);
				for ( k = 1 ; k < 8 ; ++k ) {
					value += temp_block[j*8+k] * dct_coeffs[i*8+k];
				}
				pix = (int)(floor((value / 2.0) + 0.5));
				if (pix > 255) pix = 255;
				if (pix <   0) pix =   0;
				blocki[j*8+i] = pix;
			}
		}

	// output
		for ( i = 0 ; i < 8 ; ++i ) {
			for ( j = 0 ; j < 8 ; ++j ){
				output.write(blocki[i*8+j]);
			}
		}
	}
}

