#include "idct_fix.h"


// ========================= process =====================
void idct_fix::process() {

	int		i,j,k;

	my_fxtype_params t_pi(filename,"t_pi");
	my_fxtype_params t_accu(filename,"t_accu");
	my_fxtype_params t_pix(filename,"t_pix");
	my_fxtype_params t_coeffs(filename,"t_coeffs");
	my_fxtype_params t_block(filename,"t_block");
	my_fxtype_params t_temp_block(filename,"t_temp_block");
	my_fxtype_params t_blocki(filename,"t_blocki");

	pi = new ufix_stat(t_pi, NULL, "pi");
	accu = new fix_stat(t_accu, NULL, "accu");
	pix = new fix_stat(t_pix, accu, "pix");

	sc_fxtype_context c_coeffs(t_coeffs);
	dct_coeffs = new fix_stat[64];
	dct_coeffs->initialize_array(64,"dct_coeffs");

	sc_fxtype_context c_block(t_block);
	block = new fix_stat[64];
	block->initialize_array(64,"block");

	sc_fxtype_context c_blocki(t_blocki);
	blocki = new fix_stat[64];
	blocki->initialize_array(64,"blocki");

	sc_fxtype_context c_temp_block(t_temp_block);
	temp_block = new fix_stat[64];
	temp_block->initialize_array(64,"temp_block");


	// calculate pi
	*pi = 2*acos(0.0);

	// initialize dct_coeffs
	for ( i = 0 ; i < 8 ; i++ ) {
	    for ( j = 0 ; j < 8 ; j++ ) {
			dct_coeffs[i*8+j] = cos((*pi*(2*i+1)*j)/16);
		}
	}

	while (1) {

	// read input
		for ( i = 0 ; i < 8 ; i++ ) {
		    for ( j = 0 ; j < 8 ; j++ ) {
				block[i*8+j] = input.read();
			}
		}

	// vertical 1D idct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ) {
				*accu = (block[j] * dct_coeffs[i*8])/sqrt(2);
				for ( k = 1 ; k < 8 ; k++ ) {
					*accu += block[k*8+j] * dct_coeffs[i*8+k];
				}
				temp_block[i*8+j] = *accu / 2.0;
			}
		}

	// horizontal 1D idct processing
		for ( i = 0 ; i < 8 ; i++ ) {
			for ( j = 0 ; j < 8 ; j++ ) {
				*accu = (temp_block[j*8] * dct_coeffs[i*8])/sqrt(2);
				for ( k = 1 ; k < 8 ; k++ ) {
					*accu += temp_block[j*8+k] * dct_coeffs[i*8+k];
				}
				*pix = floor((*accu / 2.0) + 0.5);
				if (*pix > 255) *pix = 255;
				if (*pix <   0) *pix =   0;
				blocki[j*8+i] = *pix;
			}
		}

	// output
		for ( i = 0 ; i < 8 ; ++i ) {
			for ( j = 0 ; j < 8 ; ++j ){
				output.write(blocki[i*8+j]);
			}
		}
	}

}
// ========================= destructor =====================
idct_fix::~idct_fix() {

	// report data type statistics
	cout << "SIGNAL STATISTICS" << endl;
	pi->report();
	pix->report();
	accu->report();
	dct_coeffs->report_array();
	block->report_array();
	temp_block->report_array();
	blocki->report_array();

	// cost calculation for one 8x8 block
	cout << "COST ESTIMATION" << endl;
//	cost = 8*8*8*block->wl() * dct_coeffs->wl();
//	cost += 8*8*8*temp_block->wl() * dct_coeffs->wl();
//	cost += 2*8*8*7*accu->wl();
//	cout << "cost for 8x8 block equals " << cost << " 1-bit additions" << endl;
	cout << "cost for 8x8 block equals " << hardware_cost() << " 1-bit additions" << endl;

	// delete structures
	delete pi;
	delete pix;
	delete accu;
	delete[] dct_coeffs;
	delete[] block;
	delete[] temp_block;
	delete[] blocki;
}
// ============ HW Calculation function =================
unsigned idct_fix::hardware_cost(){
	unsigned		cost;
	my_fxtype_params t_pi(filename,"t_pi");
	my_fxtype_params t_accu(filename,"t_accu");
	my_fxtype_params t_pix(filename,"t_pix");
	my_fxtype_params t_coeffs(filename,"t_coeffs");
	my_fxtype_params t_block(filename,"t_block");
	my_fxtype_params t_temp_block(filename,"t_temp_block");
	my_fxtype_params t_blocki(filename,"t_blocki");
	cost = 8*8*8*t_block.wl() * t_coeffs.wl();
	cost += 8*8*8*t_temp_block.wl() * t_coeffs.wl();
	cost += 2*8*8*7*t_accu.wl();
	return(cost);
}