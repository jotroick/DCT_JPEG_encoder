#include "rl_dec_RTL.h"

void rl_dec_RTL::process_RTL() {



	sc_int<32> value2; // temporary value

	if (reset.read() == true) {
		state.write(RESET);
		ready_o.write(false);
		ask_i.write(false);
	} else {
		switch (state.read()) {

			case RESET: // reset cycle
				ask_i.write(true);		//indicate that we want to read in next cycle
				ready_o.write(false);		//indicate that we do not write data in this cycle
				state.write(READACDC);
				count.write(0);
				break;

	case READACDC: // read AC/DC value
		ready_o.write(false);
		if(ready_i.read() == true) {
			value.write(input.read()); // read DC value
			ask_i.write(false);		
			state.write(WRITEACDC);
		}
		else {
			ask_i.write(true);
			state.write(READACDC);
		}
		break;

	case WRITEACDC: //write AC/DC value
		if(ask_o.read() == true) {
			output.write(value.read()); // write AC/DC value
			value2 = count.read();
			value2++;
			count.write(value2);
			ask_i.write(false);
			ready_o.write(true); //indicate that we do write data in this cycle
			state.write(WAITACDC);
		}
		else {
			ready_o.write(false);
			ask_i.write(false);		
			state.write(WRITEACDC);
		}
		break;

	case WAITACDC: //wait for succesfull write AC/DC value
		ask_i.write(true);
		ready_o.write(false);
		state.write(READZERO);
		break;

	case READZERO: // read the zero value
		ready_o.write(false);
		if(ready_i.read() == true) {
			if (input.read() < (sc_int<32>)(63)) {
				if (input.read() == (sc_int<32>)(0)) {
					state.write(READACDC); 
					ask_i.write(true);
					}
				else {
					value.write(input.read());
					state.write(WRITEZERO); 
					ask_i.write(false);
				}
			}
			else { 
				state.write(TERMINATION);
				ask_i.write(false);
			}
		}
		break;

	case WRITEZERO: // write zero value
		if(ask_o.read() == true) {
			output.write(0); // write zero
			value2 = count.read();
			value2++;
			count.write(value2);
			value2 = value.read();
			value2--;
			value.write(value2);
			ready_o.write(true);
			ask_i.write(false);
			state.write(WAITZERO);
		}
		break;

	case WAITZERO:
		ready_o.write(false);
		if (value.read() == (sc_int<32>)(0)) {
			state.write(READACDC); 
			ask_i.write(true); 
		}
		else {
			state.write(WRITEZERO);
			ask_i.write(false);
		}
		break;

	case TERMINATION: // write last zero values
		if (count.read() < (sc_int<32>)(64)) {
			if(ask_o.read() == true) {
				output.write(0); // write zero
				value2 = count.read();
				value2++;
				count.write(value2);
				ready_o.write(true);
				ask_i.write(false);
				state.write(WAITTERMINATION);
			}
		}
		else {
			ask_i.write(true);
			ready_o.write(false);
			count.write(0);
			state.write(READACDC);
		}
		break;

	case WAITTERMINATION:
		ready_o.write(false);
		ask_i.write(false);
		state.write(TERMINATION);
		break;

	} // end switch
  }// end if

}

