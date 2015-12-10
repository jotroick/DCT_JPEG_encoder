/*  idct.h */
#ifndef _IDCT_FIX
#define _IDCT_FIX
#define		 SC_INCLUDE_FX
#include <systemc.h>
#include "add2systemc.h"


SC_MODULE(idct_fix) {

  my_fifo_in<float>   input;
  my_fifo_out<int>  output;

  const char*	filename;

  ufix_stat* pi;
  fix_stat* accu;
  fix_stat* pix;
  fix_stat* block;
  fix_stat* dct_coeffs;
  fix_stat* blocki;
  fix_stat* temp_block;

  SC_HAS_PROCESS(idct_fix);

  // constructor

	idct_fix(sc_module_name _name, const char* _filename):
		sc_module(_name),
		filename(_filename) {
			SC_THREAD(process);
		}

	void process();

	// destructor
	~idct_fix();

	// calculate HW cost of IDCT_FIX
	unsigned hardware_cost();

};
#endif
