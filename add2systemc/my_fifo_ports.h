/*
 * my_fifo_ports.h
 *
 *  Created on: 15-nov.-2010
 *      Author: meng
 */

#ifndef MY_FIFO_PORTS
#define MY_FIFO_PORTS

// namespace sc_core {

// ----------------------------------------------------------------------------
//  CLASS : my_fifo_in<T>
//
//  The sc_fifo<T> input port class.
// ----------------------------------------------------------------------------

template <class T>
class my_fifo_in
: public sc_port<sc_fifo_in_if<T>,1,SC_ONE_OR_MORE_BOUND>
{
public:

    // typedefs
    typedef sc_fifo_in_if<T>                		if_type;
    typedef sc_port<if_type,1,SC_ONE_OR_MORE_BOUND> base_type;

public:
    // constructors

    my_fifo_in()
	: base_type()
	{}

    explicit my_fifo_in( const char* name_ )
	: base_type( name_ )
	{}

    // destructor (does nothing)

    virtual ~my_fifo_in()
	{}

    // interface access shortcut methods

    // blocking read

    void read( T& value_ ) { (*this)->read( value_ ); }

    T read() { return (*this)->read(); }

    // non-blocking read

    bool nb_read( T& value_ )
        { return (*this)->nb_read( value_ ); }

    // get the number of available samples

    int num_available() const
        { return (*this)->num_available(); }

    // get the data written event

    const sc_event& data_written_event() const
	{ return (*this)->data_written_event(); }

    // use for static sensitivity to data written event

    sc_event_finder& data_written() const
    {
	return *new sc_event_finder_t<if_type>(
	    *this, &if_type::data_written_event );
    }

    virtual const char* kind() const
        { return "my_fifo_in"; }

};

// ----------------------------------------------------------------------------
//  CLASS : my_fifo_out<T>
//
//  The my_fifo<T> output port class.
// ----------------------------------------------------------------------------

template <class T>
class my_fifo_out
: public sc_port<sc_fifo_out_if<T>,1,SC_ONE_OR_MORE_BOUND>
{
public:

    // typedefs

    typedef sc_fifo_out_if<T>                		if_type;
    typedef sc_port<if_type,1,SC_ONE_OR_MORE_BOUND> base_type;

public:

    // constructors

    my_fifo_out()
	: base_type()
	{}

    explicit my_fifo_out( const char* name_ )
	: base_type( name_ )
	{}

    // destructor (does nothing)

    virtual ~my_fifo_out()
	{}

    // interface access shortcut methods

    // blocking write

    void write( const T& value_ ) {
    	(*this)->write( value_ ); }

    // non-blocking write

    bool nb_write( const T& value_ )
        { return (*this)->nb_write( value_ ); }

    // get the number of free spaces

    int num_free() const
        { return (*this)->num_free(); }

    // get the data read event

    const sc_event& data_read_event() const
	{ return (*this)->data_read_event(); }

    // use for static sensitivity to data read event

    sc_event_finder& data_read() const
    {
	return *new sc_event_finder_t<if_type>(
	    *this, &if_type::data_read_event );
    }

    virtual const char* kind() const
        { return "sc_fifo_out"; }

private:

};
// } // namespace sc_core

#endif /* MY_FIFO_PORTS */
