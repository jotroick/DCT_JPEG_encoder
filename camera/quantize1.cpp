#include "quantize1.h"

void quantize1::process() {

    sc_fixed<IN_WITDH_1, IN_WITDH_2, SC_RND, SC_SAT>  value;
    sc_uint<INC_WITDH> i_temp;
    sc_uint<INC_WITDH> j_temp;

    if (reset.read()) {
        i = 0;
        j = 0;
        ask_i.write(false);
        ready_o.write(false);
        state.write(CHECKLOOP);
    }
    else {
        switch (state) {
            case CHECKLOOP:
                if (j >= (sc_uint<INC_WITDH>)8) {
                    j = 0;
                    if (i >= (sc_uint<INC_WITDH>)7) {
                        i = 0;
                    }
                    else {
                        i_temp = i;
                        i = i_temp + 1;
                    }
                }
                ask_i.write(false);
                ready_o.write(false);
                state = WAITREAD_P1;
                break;
            case WAITREAD_P1:
                i_temp = i;
                j_temp = j;
                quant_val = quantization[i_temp * 8 + j_temp];
                ask_i.write(true);
                state = WAITREAD_P2;
                break;
            case WAITREAD_P2:
                if (ready_i.read()) {
                    value = input.read();
                    ask_i.write(false);
                    prod_val = quant_val*value;
                    state = WAITREAD;
                }
                break;
            case WAITREAD:
                temp_out=(sc_int<OUT_WITDH>)(floor(prod_val + 0.5));
                state = WAITWRITE;
                break;
            case WAITWRITE:
                if (ask_o.read()) {
                    output.write(temp_out);
                    ask_i.write(false);
                    ready_o.write(true);
                    j_temp = j;
                    j = j_temp + 1;
                    state = CHECKLOOP;
                }
                break;
            deafult:
                state.write(CHECKLOOP);
                ask_i.write(false);
                ready_o.write(false);
        }
    }
}

