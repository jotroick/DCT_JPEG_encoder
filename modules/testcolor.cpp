#include "testcolor.h"

void testcolor::evaluate_pixel(int reference, int data) {
	int differ;

	signal += (reference*reference);
	if (reference==data) { correct++;}
	else {
		wrong++;
		differ = data-reference;
		noise += (differ*differ);
	}
}

void testcolor::process() {

	signal = 0.0;
	noise = 0;
	correct = 0;
	wrong = 0;

    while (1) {
    	evaluate_pixel(reference_red.read(),data_red.read());
    	evaluate_pixel(reference_green.read(),data_green.read());
       	evaluate_pixel(reference_blue.read(),data_blue.read());
	}
}

void testcolor::print_result() {
	double snr;
	double psnr; // assuming 255 as maximum value

//	cout << "correct " << correct <<"; wrong " << wrong << endl;
	cout << "signal " << signal << " noise " << noise << endl; 
	snr = 10 * log10(signal / noise);
	psnr = 10 * log10((255*255*(double)(correct+wrong))/noise);
	cout << "snr: " << snr << " dB, psnr: " << psnr << "dB" << endl; 

}
