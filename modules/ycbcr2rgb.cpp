#include "ycbcr2rgb.h"

void ycbcr2rgb::process() {

	int		y, cb, cr;
	int		value;

	while (1) {
		y = input_y.read();
		cb = input_cb.read();
		cr = input_cr.read();
		// calc of red
		value = y+1.402*(cr-128);
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_red.write(value);
		// calc of green
		value = y-0.34414*(cb-128)-0.71414*(cr-128);
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_green.write(value);
		// calc of blue
		value = y+1.772*(cb-128);
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_blue.write(value);
	}
}
