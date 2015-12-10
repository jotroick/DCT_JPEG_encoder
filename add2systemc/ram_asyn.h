#ifndef RAM_ASYN
#define RAM_ASYN
#include "systemc.h"

template <class T, unsigned addlines>
SC_MODULE(ram_asyn) {

  sc_in<bool> 					RnW;
  sc_in<sc_uint<addlines> > 	address;
  sc_in<T> 						datain;
  sc_out<T> 					dataout;

  SC_HAS_PROCESS(ram_asyn);

  ram_asyn(sc_module_name _name,  bool _debug = false) :
    sc_module(_name) {

    debug = _debug;
    unsigned size = 2;
    for (unsigned i=1;i<addlines;i++)size *= 2;

    SC_METHOD(ram_proc);
    sensitive << RnW << address << datain;

    buffer = new T[size];
    for(unsigned i=0;i<size;i++) {buffer[i] = 0;}
    if (debug) {
      cout << "Running constructor of " << name() << endl;
      cout << "Number of locations is " << size << endl;
    }
  }

  ~ram_asyn() {
	delete buffer;
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
    T* 		buffer;
    bool 	debug;

};

#endif

