/*  ufix_stat.h */
#ifndef _UFIX_STAT
#define _UFIX_STAT

#include <float.h>
#include <stdio.h>
#include <string.h>
// this unsigned structure also collects statistics, and can be connected in a linked list

class ufix_stat:
	public sc_ufix {

public:
	// constructors

	// normal constructor for scalar
    ufix_stat( const sc_fxtype_params& typeinfo_, ufix_stat* next_ = NULL, const char* name_ = "")
	: sc_ufix(typeinfo_) {
		count=0;
		smin= DBL_MAX;
		smax= 0;
		ssum=0;
		ssumsquared=0;
		emin= DBL_MAX;
		emax= 0;
		esum=0;
		esumsquared=0;
		sqnrmin = DBL_MAX;
		next=next_;
		if (strlen(name_) == 0) {
			my_name = NULL;
		} else {
			my_name = new char[strlen(name_)];
			strcpy(my_name,name_);
		}
	}

	// default constructor for vector
    ufix_stat(ufix_stat* next_ = NULL, const char* name_ = "" )
	: sc_ufix() {
		count=0;
		smin= DBL_MAX;
		smax= 0;
		ssum=0;
		ssumsquared=0;
		emin= DBL_MAX;
		emax= 0;
		esum=0;
		esumsquared=0;
		sqnrmin = DBL_MAX;
		next=next_;
		if (strlen(name_) == 0) {
			my_name = NULL;
		} else {
			my_name = new char[strlen(name_)];
			strcpy(my_name,name_);
		}
	}

	// initialize functions
    void initialize_array(int size_, const char* name_ = ""){
    	int i;

    	for (i=0;i<size_-1;i++) {
    		this[i].set_next(&this[i+1]);
    		this[i].set_name(name_);
    	}
    	this[size_-1].set_next(NULL);
    	this[size_-1].set_name(name_);
    }

    // read operations

    double sigmin() {return(smin);}
	double sigmax() {return(smax);}
	double sigmean()
		{
		double result;
		if (count == 0) {result = 0;}
		else {result = ssum/count;}
		return(result);
		}
	double sigdev() {
		double result;
		if (count <= 1) {result = 0;}
		else {result = sqrt((ssumsquared/count) - ((ssum/count)*(ssum/count)));}
		return(result);
		}
	double errormin() {return(emin);}
	double errormax() {return(emax);}
	double errormean() {
		double result;
		if (count == 0) {result = 0;}
		else {result = esum/count;}
		return(result);
		}
	double errordev() {
		double result;
		if (count <= 1) {result = 0;}
		else {result = sqrt((esumsquared/count) - ((esum/count)*(esum/count)));}
		return(result);
		}
	double sqnr() {
		double result;
		if ((errormean()+errordev()) == 0) {result = DBL_MAX;}
		else {
			result = 10 * log10 ((sigmean()*sigmean()+sigdev()* sigdev())/(errormean()* errormean()+errordev()* errordev()));
			}
		return(result);
		}
	double minsqnr() {return(sqnrmin);}
	ufix_stat* next_el() {return (next);}
	char* name() { return (my_name);}

	// write operations
	void set_next(ufix_stat* next_el) {next = next_el;}
	void set_name(const char* name) {
		if (strlen(name) == 0) {
			my_name = NULL;
		} else {
			my_name = new char[strlen(name)];
			strcpy(my_name,name);
		}
	}

    // reporting function
	void report() {
		cout << my_name << ", sigmin: " << smin << ", sigmax: " << smax;
		cout << ", sqnr: " << sqnr() << " dB" << endl;
	}

	void report_array() {
			int count;
			double sigmin, sigmax, sigmean, errormean;
			double sqnr, minsqnr;
			ufix_stat* current;

			current = this;
			cout << current->name();
			sigmin = DBL_MAX;
			sigmax = -DBL_MAX;
			errormean = sigmean = 0;
			count = 0;
			sqnr = DBL_MAX;
			minsqnr = DBL_MAX;
			while(current != NULL) {
				if (current->sigmin() < sigmin) sigmin = current->sigmin();
				if (current->sigmax() > sigmax) sigmax = current->sigmax();
				errormean += current->errormean();
				sigmean += current->sigmean();
				if (current->sqnr() < sqnr) sqnr = current->sqnr();
				if (current->minsqnr() < minsqnr) minsqnr = current->minsqnr();
				count++;
				current = current->next_el();
				}
			cout << ", sigmin: " << sigmin << ", sigmax: " << sigmax;
			cout << ", sqnr: " << sqnr << " dB" << endl;
		}

    // assignment operator

	#define DEFN_ASN_OPS_T(tp) \
	ufix_stat& operator = ( tp a ){ \
		count++; \
		double temp = (double)(a); \
		if (temp < smin) smin = temp; \
		if (temp > smax) smax = temp; \
		ssum += temp; \
		ssumsquared += temp*temp; \
		double temp2 = temp; \
		sc_ufix::operator = ( a ); \
		temp -= this->to_double(); \
		if (temp < emin) emin = temp; \
		if (temp > emax) emax = temp; \
		esum += temp; \
		esumsquared += temp*temp; \
		temp2 = 10*log10((temp2*temp2)/(temp*temp));\
		if (temp2 < sqnrmin) sqnrmin = temp2; \
		return *this; \
	} \
		\
	ufix_stat& operator += ( tp a ){ \
		*this = *this + (double)(a);\
		return *this; \
	} \
		\
	ufix_stat& operator -= ( tp a ){ \
		*this = *this - (double)(a);\
		return *this; \
	} \
		\
	ufix_stat& operator *= ( tp a ){ \
		*this = *this * (double)(a);\
		return *this; \
	} \
		\
	ufix_stat& operator /= ( tp a ){ \
		*this = *this / (double)(a);\
		return *this; \
	}

	#define DEFN_ASN_OPS_SC(tp) \
	ufix_stat& operator = ( tp a ){ \
		count++; \
		double temp = a.to_double(); \
		if (temp < smin) smin = temp; \
		if (temp > smax) smax = temp; \
		ssum += temp; \
		ssumsquared += temp*temp; \
		double temp2 = temp; \
		sc_ufix::operator = ( a ); \
		temp -= this->to_double(); \
		if (temp < emin) emin = temp; \
		if (temp > emax) emax = temp; \
		esum += temp; \
		esumsquared += temp*temp; \
		temp2 = 10*log10((temp2*temp2)/(temp*temp));\
		if (temp2 < sqnrmin) sqnrmin = temp2; \
		return *this; \
	} \
		\
	ufix_stat& operator += ( tp a ){ \
		*this = *this + a.to_double();\
		return *this; \
	} \
		\
	ufix_stat& operator -= ( tp a ){ \
		*this = *this - a.to_double();\
		return *this; \
	} \
		\
	ufix_stat& operator *= ( tp a ){ \
		*this = *this * a.to_double();\
		return *this; \
	} \
		\
	ufix_stat& operator /= ( tp a ){ \
		*this = *this / a.to_double();\
		return *this; \
	}

	#ifndef SC_FX_EXCLUDE_OTHER
	#define DEFN_ASN_OPS_OTHER \
	DEFN_ASN_OPS_T(int64) \
	DEFN_ASN_OPS_T(uint64) \
	DEFN_ASN_OPS_T(const sc_int_base&) \
	DEFN_ASN_OPS_T(const sc_uint_base&) \
	DEFN_ASN_OPS_SC(const sc_signed&) \
	DEFN_ASN_OPS_SC(const sc_unsigned&)
	#else
	#define DEFN_ASN_OPS_OTHER
	#endif

	#define DEFN_ASN_OPS \
	DEFN_ASN_OPS_T(int)  \
	DEFN_ASN_OPS_T(unsigned int)  \
	DEFN_ASN_OPS_T(long) \
	DEFN_ASN_OPS_T(unsigned long) \
	DEFN_ASN_OPS_T(double) \
	DEFN_ASN_OPS_SC(const sc_fxval&) \
	DEFN_ASN_OPS_SC(const sc_fxval_fast&) \
	DEFN_ASN_OPS_SC(const sc_fxnum&) \
	DEFN_ASN_OPS_SC(const sc_fxnum_fast&) \
	DEFN_ASN_OPS_SC(const fix_stat&)  \
	DEFN_ASN_OPS_OTHER

	DEFN_ASN_OPS


	ufix_stat& operator <<= ( int a ){
		*this = *this << a;
		return *this;
	}

	ufix_stat& operator >>= ( int a ){
		*this = *this >> a;
		return *this;
	}

	#undef DEFN_ASN_OPS_T
	#undef DEFN_ASN_OPS_OTHER
	#undef DEFN_ASN_OPS
	#undef DEFN_ASN_OPS_SC


private:

	double		smin, smax; //minimum and maximum signal values
	double		ssum, ssumsquared; //mean and variance signal values
	int			count; // number of samples
	double		emin, emax;	// minimum and maximum error values
	double		esum, esumsquared; // mean and variance error values
	double		sqnrmin; // minimum sqnr
	ufix_stat*	next;
	char*		my_name;
};

#endif
