#include "zz_enc.h"

void zz_enc::process() {

	int		i, j, k, l;
	int		temp_block[64];                     
	int		block[64];

	while(1) {
		//read in the blocks for 8 lines
	    for ( i = 0 ; i < 8 ; i ++) {
			for ( j = 0 ; j < 8 ; j++ ) {
				temp_block[8 * i + j ]= input.read();
			}
		}

		i = 0 , j = -1 , k = 0;

		for ( l = 0 ; l < 4 ; l++ ) {
			for ( j++ ; i >= 0 ; j++ , i-- ) {
				block[k] = temp_block[i*8+j];
				k++;
			}

			for ( i++ ; j >= 0 ; j-- , i++ ) {
				block[k] = temp_block[i*8+j];
				k++;
			}
		}

		for ( l = 0 ; l < 3 ; l++ ) {
			for ( i-- , j += 2 ; j < 8 ; j++ , i-- ) {
				block[k] = temp_block[i*8+j];
				k++;
			}
			for ( j-- , i += 2 ; i < 8 ; j-- , i++ ) {
				block[k] = temp_block[i*8+j];
				k++;
			}
		}

		i-- , j += 2;
		block[k] = temp_block[i*8+j];

		for ( i = 0 ; i < 64 ; ++i ) {
			output.write (block[i]);
		}
	}
}

