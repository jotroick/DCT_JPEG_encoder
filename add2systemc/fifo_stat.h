/*  fifo_stat.h */ 
#ifndef _FIFO_STAT
#define _FIFO_STAT 

// this FIFO structure also collects statistics
template <class T> class fifo_stat
//: virtual public sc_fifo <T> {
: public sc_fifo <T> {

public:
	// constructors

    fifo_stat( int _size = 16 )
	: sc_fifo <T> ( _size ) {
		size_copy = _size;
		max_num=0;
		num_writes = 0;
	}

    fifo_stat( const char* _name, int _size = 16 )
	: sc_fifo <T> ( _name, _size )  {
		size_copy = _size;
		max_num=0;
		num_writes =0;
	}

    // destructor

    ~fifo_stat() {
		cout << "name: " << sc_fifo<T>::name () << ", size: "<< size() << ", #writes: " << num_writes ;
		cout << ", max_num: " << max_num+1 << ", min_value: " << min << ", max_value: " << max << endl;
	}

	// return size of FIFO
	int size() {return size_copy;}

	// blocking write

	void write( const T& val_ ) {

		sc_fifo<T>::write(val_);

// inserted code to maintain statistics
		if (sc_fifo<T>::num_available() > max_num) { max_num = sc_fifo<T>::num_available(); };
		if (num_writes == 0) { min = max = val_; }
		else {
			if (val_ < min) {min = val_;};
			if (val_ > max) {max = val_;};
		}
		num_writes++;
// end inserted code
	}

private:

	int	max_num; //number of elements in queue before write
	T	min, max;
	int	num_writes;
	int	size_copy;

};

#endif
