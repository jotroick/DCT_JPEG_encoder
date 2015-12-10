#include "idct_loeffler.h"

void idct_loeffler::idct1D(float values[]) {
	float temp;
	float pi = 2*acos(0.0);
	float C0a = cos((6*pi)/16)*sqrt(2);
	float C0b = sin((6*pi)/16)*sqrt(2);
	float C1a = cos((pi)/16);
	float C1b = sin((pi)/16);
	float C2a = cos((3*pi)/16);
	float C2b = sin((3*pi)/16);
//	float scaling = 1/(2*sqrt(2));

	// reorder & scale
	// values[0] = values[0];
	// values[2] = values[2];
	temp = values[1];
	values[1] =  values[4];
	values[4] = values[7];
	values[7] = temp;
	temp = values[3];
	values[3] = values[6];
	values[6] = values[5];
	values[5] = temp;
	// stage 1
	values[5]= values[5]*sqrt(2.0);
	values[6]= values[6]*sqrt(2.0);
	temp = (values[7]-values[4]);
	values[7] = (values[7]+values[4]);
	values[4] = temp;
	// stage 2
	temp = (values[0]-values[1]);
	values[0] = (values[0]+values[1]);
	values[1] = temp;
	temp = (values[4]-values[6]);
	values[4] = (values[4]+values[6]);
	values[6] = temp;
	temp = (values[7]-values[5]);
	values[7] = (values[7]+values[5]);
	values[5] = temp;
	temp = values[2]*C0a - values[3]*C0b;
	values[3] = values[2]*C0b + values[3]*C0a;
	values[2] = temp;
	// stage 3
	temp = (values[0]-values[3]);
	values[0] = (values[0]+values[3]);
	values[3] = temp;
	temp = (values[1]-values[2]);
	values[1] = (values[1]+values[2]);
	values[2] = temp;
	temp = values[5]*C1a - values[6]*C1b;
	values[6] = values[5]*C1b + values[6]*C1a;
	values[5] = temp;
	temp = values[4]*C2a - values[7]*C2b;
	values[7] = values[4]*C2b + values[7]*C2a;
	values[4] = temp;
	// stage 4
	temp = (values[0]-values[7]);
	values[0] = (values[0]+values[7]);
	values[7] = temp;
	temp = (values[1]-values[6]);
	values[1] = (values[1]+values[6]);
	values[6] = temp;
	temp = (values[2]-values[5]);
	values[2] = (values[2]+values[5]);
	values[5] = temp;
	temp = (values[3]-values[4]);
	values[3] = (values[3]+values[4]);
	values[4] = temp;
}

	void idct_loeffler::process() {

	int		i, j;
//	float	value;
	float	block[64];
	float	temp_block[64];
//	float	dct_coeffs[64];
//	float	pi;
	int		blocki[64];
	int		pix;
	float	values_loeffler[8];

	// calculate pi
//	pi = 2*acos(0.0);

	// initialize dct_coeffs
	/* for ( i = 0 ; i < 8 ; i++ ) {
	    for ( j = 0 ; j < 8 ; j++ ) {
			dct_coeffs[i*8+j] = cos((pi*(2*i+1)*j)/16);
		}
	} */

	while (1) {
	// read input
		for ( i = 0 ; i < 8 ; i++ ) {
		    for ( j = 0 ; j < 8 ; j++ ) {
				block[i*8+j] = input.read();
			}
		}

	// vertical loeffler version
		for (j=0;j<8;j++) {
			for (i=0;i<8;i++) values_loeffler[i]=block[i*8+j]/8;
			idct1D(values_loeffler);
			for (i=0;i<8;i++) temp_block[i*8+j] = values_loeffler[i];
		}


	// horizontal loeffler version
		for (j=0;j<8;j++) {
			for (i=0;i<8;i++) values_loeffler[i]=temp_block[j*8+i];
			idct1D(values_loeffler);
			for (i=0;i<8;i++) {
				pix = (int)(floor((values_loeffler[i]) + 0.5));
				if (pix > 255) pix = 255;
				if (pix <   0) pix =   0;
				blocki[j*8+i] = pix;
			}
		}

/*	// horizontal 1D idct processing
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
		*/

	// output
		for ( i = 0 ; i < 8 ; ++i ) {
			for ( j = 0 ; j < 8 ; ++j ){
				output.write(blocki[i*8+j]);
			}
		}
	}
}

