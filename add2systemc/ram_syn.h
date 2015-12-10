#ifndef RAM_SYN
#define RAM_SYN
#include "systemc.h"

template <class T, unsigned addlines>
SC_MODULE(ram_syn) {

  sc_in<bool> clock;
  sc_in<bool> RnW;   // ReadNotWrite
  sc_in<sc_uint<addlines> > address;
  sc_in<T> 						datain;
  sc_out<T> 					dataout;

  SC_HAS_PROCESS(ram_syn);

  ram_syn(sc_module_name _name,  bool _debug = false) :
    sc_module(_name),  debug(_debug)
  {
	SC_METHOD(ram_proc);
    sensitive << clock.pos();

    unsigned size = 2;
    for (unsigned i=1;i<addlines;i++)size *= 2;

    buffer = new T[size];

    if (debug) {
      cout << "Running constructor of " << name() << endl;
      cout << "Number of locations is " << size << endl;
    }
  }

  void ram_proc() {
    if (RnW.read() == true) {
    	dataout.write(buffer[address.read()]);
    	if (debug) cout << "READ DATA:: address: " << address.read() << " , data: " << buffer[address.read()] << endl;
    }
    else {
        buffer[address.read()] = datain.read();
        if (debug) cout << "WRITE DATA:: address: " << address.read() << " , data: " << buffer[address.read()] << endl;
    }
  }

  private:
    T * buffer;
    const bool debug;

};

#endif

