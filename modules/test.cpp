#include "test.h"

void test::process() {
	unsigned temp;
	unsigned value;
	int differ;

	signal = 0.0;
	noise = 0;
	correct = 0;
	wrong = 0;

    while (1) {
		value = reference.read();
		signal += (value*value);
		temp=data.read();
		if (temp==value) {
			correct++;
		}
		else {
			wrong++;
			differ = temp-value;
			noise += (differ*differ);
		}
	}
}

void test::print_result() {

//	cout << "correct " << correct <<"; wrong " << wrong << endl;
	cout << "signal " << signal << " noise " << noise << endl;
	cout << "snr: " << snr() << " dB, psnr: " << psnr() << "dB" << endl;

}

float test::snr() {
	return (10 * log10(signal / noise));
}

float test::psnr() {
	return (10 * log10((255*255*(float)(correct+wrong))/noise));
}
