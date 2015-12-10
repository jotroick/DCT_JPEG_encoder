#include "rgb2ycbcr.h"

void rgb2ycbcr::process() {

	int		red, green, blue;
	int		value;

	while (1) {
		red = input_red.read();
		green = input_green.read();
		blue = input_blue.read();
		// calc of y
		value = 0.299*red+0.587*green+0.114*blue;
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_y.write(value);
		// calc of cb
		value = 128-0.168736*red-0.331264*green+0.5*blue;
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_cb.write(value);
		// calc of cr
		value = 128+0.5*red-0.418688*green-0.081312*blue;
		if (value < 0) value = 0;
		if (value > 255) value = 255;
		output_cr.write(value);
	}
}
