#ifndef _P2FF
#define _P2FF
#include	<systemc.h>

// this module converts a protocol into a FIFO communication

template <class T> SC_MODULE(P2FF) {

	sc_fifo_out<T>		output;
	sc_in<T>			input;
	sc_in<bool>			ready;
	sc_out<bool>		ask;
	sc_in<bool>			clk;

	SC_CTOR(P2FF)  {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T			value;
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;

		// reset cycle
		ask.write(true);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				if (ready.read() == true) {
					value = input.read();
					ask.write(false);
					state = WRITEOUTPUT;
				} else {
					ask.write(true);
					state = READINPUT;
				};
			} else {
				output.write(value);
				ask.write(true);
				state = READINPUT;
			};
		wait();
		}
		return;
	}

};

// this module converts a burst protocol into a FIFO communication

template <class T, int burstlength> SC_MODULE(P2FFB) {

	sc_fifo_out<T>		output;
	sc_in<T>			input;
	sc_in<bool>			ready;
	sc_out<bool>		ask;
	sc_in<bool>			clk;

	SC_CTOR(P2FFB)  {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T			value[burstlength];
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;

		// reset cycle
		ask.write(true);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				if (ready.read() == true) {
					ask.write(false);
					for(int i=0; i<burstlength; i++){
						value[i] = input.read();
						wait();
					}
					state = WRITEOUTPUT;
				} else {
					ask.write(true);
					state = READINPUT;
				};
			} else {
				for(int i=0; i<burstlength; i++){
					output.write(value[i]);
				}
				ask.write(true);
				state = READINPUT;
			};
		wait();
		}
		return;
	}

};
// this module converts a protocol into a FIFO communication and casts the result

template <class T1, class T2> SC_MODULE(P2FFC) {

	sc_fifo_out<T1>		output;
	sc_in<T2>			input;
	sc_in<bool>			ready;
	sc_out<bool>		ask;
	sc_in_clk			clk;

	SC_CTOR(P2FFC)  {
		SC_THREAD(process);
		sensitive << clk.pos();
		}

	void process() {
		T1			value;
		T2		castvalue;
		enum		ctrl_state {READINPUT, WRITEOUTPUT};
		ctrl_state	state;

		// reset cycle
		ask.write(true);
		state = READINPUT;
		wait();
		while(true) {
			if (state == READINPUT) {
				if (ready.read() == true) {
					castvalue = input.read();
					ask.write(false);
					state = WRITEOUTPUT;
				} else {
					ask.write(true);
					state = READINPUT;
				};
			} else {
				value = (T1)(castvalue);
				output.write(value);
				ask.write(true);
				state = READINPUT;
			};
		wait();
		}
		return;
	}

};

#endif
