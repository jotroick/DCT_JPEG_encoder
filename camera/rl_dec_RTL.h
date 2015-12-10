/*  rl_dec_RTL.h */
//#ifndef _RL_DEC_RTL
//#define _RL_DEC_RTL

#include <systemc.h>
#include "add2systemc.h"

// RTL model of rl_dec

SC_MODULE(rl_dec_RTL) {

	// ports
	sc_out< sc_int<32> >	output;
	sc_in<bool>				ask_o;
	sc_out<bool>			ready_o;
	sc_in< sc_int<32> >		input;
	sc_in<bool>				ready_i;
	sc_out<bool>			ask_i;
	sc_in<bool>				clk;
	sc_in<bool>				reset;

	// variables
	enum		ctrl_state {RESET, READACDC, WRITEACDC, WAITACDC, READZERO, WRITEZERO, WAITZERO, TERMINATION, WAITTERMINATION};
	sc_signal<ctrl_state>	state;//	ctrl_state	state;
	sc_signal< sc_int<32> >	count;
	sc_signal< sc_int<32> >	value;

	// processes
	void process_RTL();

	SC_CTOR(rl_dec_RTL)  {
		SC_METHOD(process_RTL);
		sensitive << clk.pos();
	}

};

//#endif
