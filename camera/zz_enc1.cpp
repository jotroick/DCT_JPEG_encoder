#include "zz_enc1.h"

void zz_enc1::process() {

    sc_uint<7> i_temp;

    if (reset.read() == true ){
        state.write(RESET);
        ready_o.write(false);
        ask_i.write(false);
    } else {
        switch (state.read()){
            case RESET:
                ask_i.write(true);      //indicate that we want to read in next cycle
                ready_o.write(false);   //indicate that we do not write data in this cycle
                state.write(READZIGZAG);
                i = 0;
                break;

            case READZIGZAG:
                if (i < ((sc_uint<7>)(64))){
                    ask_i.write(true);
                    state.write(WAITREAD);
                }
                else{
                    state.write(WRITEZIGZAG);
                    i = 0;
                }
                break;

            case WAITREAD:
                if (ready_i.read()==true){
                    ready_o.write(false);
                    i_temp = i;
                    block[i_temp] = input.read();
                    ask_i.write(false);
                    i_temp++;
                    i = i_temp;
                    state.write(READZIGZAG);
                }
                break;

            case WRITEZIGZAG:
                if (i < ((sc_uint<7>)(64))){
                    ready_o.write(false);
                    i_temp = i;
                    zz_val = zig_zag[i_temp];
                    state.write(WAITWRITE);
                }
                else{
                    ready_o.write(false);
                    i = 0;
                    ask_i.write(true);
                    state.write(READZIGZAG);
                }
                break;

            case WAITWRITE:
                if(ask_o.read()==true){
                    i_temp = i;
                    output.write((sc_int<9>)block[zz_val.read()]);
                    ask_i.write(false);
                    ready_o.write(true);
                    i_temp++;
                    i = i_temp;
                    state.write(WRITEZIGZAG);
                }
                break;
        }
    }
}

