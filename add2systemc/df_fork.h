/*  df_fork.h */ 
#ifndef _DF_FORK
#define _DF_FORK 

// this module forks a dataflow stream
/* template <class T > SC_MODULE(fork) {

	sc_fifo_in<T> in;
	sc_fifo_out<T> out1, out2;

	SC_CTOR(fork)  {SC_THREAD(process);}

	void process() {
		T value;

		while (1) {
			value = in.read();
			out1.write(value);
			out2.write(value);
		}

		return;
	}

};
*/
template <class T, int M=2> SC_MODULE(df_fork) {

	sc_fifo_in<T> in;
	sc_fifo_out<T> out[M];

	SC_CTOR(df_fork)  {SC_THREAD(process);}

	void process() {
		T value;

		while (1) {
			value = in.read();
			for (int i=0;i<M;i++){
				out[i].write(value);
			}
		}

		return;
	}

};

#endif
