#include "dct.h"

void dct::process() {

	int		i, j, k;
	float	value;
	float		block[64];
	float	temp_block[64];
	float	dct_coeffs[64];
	float	pi;

	// calculate pi
	pi = acos(0.0) * 2;

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
		//		cout << "after read " << (i*8+j) << endl;
			}
		}

	// horizontal 1D dct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ) {
				value = 0.0;
				for ( k = 0 ; k < 8 ; k++ ) {
					value += block[i*8+k] * dct_coeffs[k*8+j];
				}
				if ( j == 0 ) {
					temp_block[i*8+j] = value / (2.0 * sqrt(2));
				}
				else {
					temp_block[i*8+j] = value / 2.0;
				}
			}
		}

	// vertical 1D dct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ){
				value = 0.0;
				for ( k = 0 ; k < 8 ; k++ ) {
					value += temp_block[k*8+i] * dct_coeffs[k*8+j];
				}
				if ( j == 0 ) {
					block[j*8+i] = value / (2 * sqrt(2));
				}
				else {
					block[j*8+i] = value / 2.0;
				}
			}
		}


	// output
		for ( i = 0 ; i < 8 ; ++i ) {
			for ( j = 0 ; j < 8 ; ++j ){
				output.write(block[i*8+j]);
//				cout << block[i*8+j] << " ";
			}
//			cout << endl;
		}
	}
}

