#include "zz_dec.h"

void zz_dec::process() {

	int		i, j, l;
	int		block[64];

	while(1) {
		i=0 , j=-1;

		for ( l = 0 ; l < 4 ; l++ ) {
			for ( j++ ; i >= 0 ; j++, i-- ) {
				block[i*8+j] = input.read();
			}
			for ( i++ ; j >= 0 ; j--, i++ ) {
				block[i*8+j] = input.read();
			}
		}

		for ( l = 0 ; l < 3 ; l++ ) {
			for ( i-- , j += 2 ; j < 8 ; j++ , i-- ) {
				block[i*8+j] = input.read();
			}
			for ( j-- , i += 2 ; i < 8 ; j-- , i++ ) {
				block[i*8+j] = input.read();
			}
		}

		i-- , j+=2;
		block[i*8+j] = input.read();

		for ( i = 0 ; i < 8 ; ++i ) {
			for ( j = 0 ; j < 8 ; ++j ) {
				output.write(block[i*8+j]);
			}
		}
	}
}
