#include "normalize.h"

void normalize::process() {

	int		i, j;
	int		value;
	float		temp_out;

	while (1) {
		for(i=0;i<8;i++) {
			for (j=0; j<8;j++){
				value = input.read();
				temp_out=value * quantization[i*8+j];
				output.write(temp_out);
			}
		}
	}
}
