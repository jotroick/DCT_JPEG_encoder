#ifndef _FF2P
#define _FF2P
#include	<systemc.h>

// this module converts a FF to a protocol communication
template <class T> SC_MODULE(FF2P) {

	sc_fifo_in<T>		input;
	sc_out<T>			output;
	sc_in<bool>			ask;
	sc_out<bool>		ready;
	sc_in<bool>			clk;

	SC_CTOR(FF2P)  {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T			value;
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;

		// reset cycle
		ready.write(false);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				ready.write(false);
				value = input.read();
				state = WRITEOUTPUT;
			} else {
				if (ask.read() == true) {
					output.write(value);
					ready.write(true);
					state = READINPUT;
				} else {
					ready.write(false);
					state = WRITEOUTPUT;
				};
			};
		wait();
		}
		return;
	}

};

// this module converts a FF to a burst protocol communication
template <class T, int burstlength> SC_MODULE(FF2PB) {

	sc_fifo_in<T>		input;
	sc_out<T>			output;
	sc_in<bool>			ask;
	sc_out<bool>		ready;
	sc_in<bool>			clk;

	SC_CTOR(FF2PB) {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T			value[burstlength];
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;
		int i;

		// reset cycle
		ready.write(false);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				ready.write(false);
				for(i=0; i<burstlength; i++) value[i] = input.read();
				state = WRITEOUTPUT;
			} else {
				if (ask.read() == true) {
					output.write(value[0]);
					ready.write(true);
					for(i=1; i<burstlength; i++) {
						wait();
						output.write(value[i]);
					}
					state = READINPUT;
				} else {
					ready.write(false);
					state = WRITEOUTPUT;
				};
			};
		wait();
		}
		return;
	}

};

// this module converts a FF to a protocol communication and casts the type
template <class T1, class T2> SC_MODULE(FF2PC) {

	sc_fifo_in<T1>		input;
	sc_out<T2>			output;
	sc_in<bool>			ask;
	sc_out<bool>		ready;
	sc_in<bool>			clk;

	SC_CTOR(FF2PC)  {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T1		value;
		T2		castvalue;
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;

		// reset cycle
		ready.write(false);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				ready.write(false);
				value = input.read();
				state = WRITEOUTPUT;
			} else {
				if (ask.read() == true) {
					castvalue = (T2)(value);
					output.write(castvalue);
					ready.write(true);
					state = READINPUT;
				} else {
					ready.write(false);
					state = WRITEOUTPUT;
				};
			};
		wait();
		}
		return;
	}

};
#endif
