#define		 SC_INCLUDE_FX
#include <systemc.h>
#include "my_fxtype_params.h"

sc_q_mode str2qm(char *string) {
	sc_q_mode	q_mode = SC_RND; //default round
	if (strcmp(string,"SC_RND")==0) q_mode = SC_RND;
	if (strcmp(string,"SC_RND_ZERO")==0) q_mode = SC_RND_ZERO;
	if (strcmp(string,"SC_RND_MIN_INF")==0) q_mode = SC_RND_MIN_INF;
	if (strcmp(string,"SC_RND_INF")==0) q_mode = SC_RND_INF;
	if (strcmp(string,"SC_RND_CONV")==0) q_mode = SC_RND_CONV;
	if (strcmp(string,"SC_TRN")==0) q_mode = SC_TRN;
	if (strcmp(string,"SC_TRN_ZERO")==0) q_mode = SC_TRN_ZERO;
	return(q_mode);
}

sc_o_mode str2om(char *string) {
	sc_o_mode	o_mode = SC_WRAP; //default wrap
	if (strcmp(string,"SC_SAT")==0) o_mode = SC_SAT;
	if (strcmp(string,"SC_SAT_ZERO")==0) o_mode = SC_SAT_ZERO;
	if (strcmp(string,"SC_SAT_SYM")==0) o_mode = SC_SAT_SYM;
	if (strcmp(string,"SC_WRAP")==0) o_mode = SC_WRAP;
	if (strcmp(string,"SC_WRAP_SM")==0) o_mode = SC_WRAP_SM;
	return(o_mode);
}

my_fxtype_params::my_fxtype_params(const char* filename, const char* type_name) {

    char		name[25];
	int			wl, iwl;
	char		qm_string[10], om_string[10];
	sc_q_mode	q_mode;
	sc_o_mode	o_mode;
	int			n_bits;

	ifstream typefile (filename);
	if (!typefile.is_open()) {
		cout << "Error opening file " << filename << endl;
		return;
	}

	bool found = 0;
    while (!typefile.eof() ) {
		typefile >> name >> wl >> iwl >> qm_string >> om_string >> n_bits;
		if (strcmp(name, type_name) == 0) {
			found = 1;
			SC_CHECK_WL_( wl );
		    SC_CHECK_N_BITS_( n_bits );
		    this->wl(wl);
		    this->iwl(iwl);
			q_mode =str2qm(qm_string);
			this->q_mode(q_mode);
			o_mode = str2om(om_string);
			this->o_mode(o_mode);
			this->n_bits(n_bits);
		}
	}
	if (found == 0 ) {
		cout << "Error:: type not found \n";
	}

    typefile.close();
}

