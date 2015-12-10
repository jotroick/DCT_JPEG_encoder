#include "bit_unpacking.h"

void bit_unpacking::process() {
    sc_bv<VAL_WIDTH>    value;
    sc_bv<RL_WIDTH>     rl;
    sc_bv<BUS_WIDTH>    buf;
    int i;
    int buf_idx;

    while(1) {
        buf =  input.read();
        buf_idx = 0;
        do {
            // fill value bits into output bits
            for (i = 0; i < VAL_WIDTH; i++) {
                if (buf_idx < BUS_WIDTH) {
                    value[i] = buf[buf_idx];
                }
                else {
                    if (buf_idx == BUS_WIDTH) {
                        buf = input.read();
                        buf_idx = 0;
                    }
                    value[i] = buf[buf_idx];
                }
                buf_idx++;
            }
            output.write(value.to_int());
            // fill rl bits into output bits
            for (i = 0; i < RL_WIDTH; i++) {
                if (buf_idx < BUS_WIDTH) {
                    rl[i] = buf[buf_idx];
                }
                else {
                    if (buf_idx == BUS_WIDTH) {
                        buf = input.read();
                        buf_idx = 0;
                    }
                    rl[i] = buf[buf_idx];
                }
                buf_idx++;
            }
            output.write(rl.to_int());
        }
        while (rl.to_int() < 63);
    }
}
