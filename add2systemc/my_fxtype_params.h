/*  my_fxtype_params.h */
#ifndef _MY_FXTYPE_PARAMS
#define _MY_FXTYPE_PARAMS
// this fxtype_params structure can also be loaded from a file

class my_fxtype_params: public sc_fxtype_params {

public:
	// constructors

	my_fxtype_params():
	  sc_fxtype_params() {}
    	my_fxtype_params(int wl_, int iwl_):
	  sc_fxtype_params( wl_, iwl_ ) {}
    	my_fxtype_params(sc_q_mode qm_, sc_o_mode om_, int nb_ =0 ):
	  sc_fxtype_params(qm_, om_, nb_ ) {}
    	my_fxtype_params(int wl_, int iwl_ ,sc_q_mode qm_,sc_o_mode om_,int nb_ = 0 ):
	  sc_fxtype_params(wl_,iwl_,qm_, om_, nb_ ) {}
	my_fxtype_params ( const sc_fxtype_params& basetype_ ):
	  sc_fxtype_params( basetype_ ) {}
	my_fxtype_params ( const sc_fxtype_params& basetype_, int wl_, int iwl_):
	  sc_fxtype_params( basetype_, wl_, iwl_) {}
	my_fxtype_params ( const sc_fxtype_params& basetype_,sc_q_mode qm_, sc_o_mode om_, int nb_ = 0 ):
	  sc_fxtype_params( basetype_,qm_, om_, nb_ ) {}
//	my_fxtype_params( sc_without_context ):
//	  sc_fxtype_params( sc_without_context ) {}

	my_fxtype_params(const char* , const char*);

	// destructor


};

#endif
