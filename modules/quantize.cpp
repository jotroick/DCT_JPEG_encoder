#include "quantize.h"

void quantize::process() {

	int		i, j;
	float	value;
	int		temp_out;

	while (1) {
		for(i=0;i<8;i++) {
			for (j=0; j<8;j++){
				value = input.read();
				temp_out=(int)(floor(value/quantization[i*8+j]+0.5));
//				cout << temp_out << " ";
				output.write(temp_out);
			}
//			cout << endl;
		}
	}
}

