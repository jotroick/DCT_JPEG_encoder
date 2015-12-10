#include "bit_packing.h"

void bit_packing::process() {
    sc_uint<CNT_WIDTH> i_temp;
    sc_uint<CNT_WIDTH> buf_idx_temp;
    sc_bv<BUS_WIDTH> buf_temp;

    if (reset.read()) {
        i = 0;
        buf_idx = 0;
        ask_i.write(false);
        ready_o.write(false);
        state.write(RESET);
    }
    else {
        switch (state) {
            case RESET:
                ask_i.write(true);
                ready_o.write(false);
                state = WAIT_READ_VAL;
                break;
            case WAIT_READ_VAL:
                if (ready_i.read()) {
                    value = static_cast<sc_bv<VAL_WIDTH> >(input.read());
                    ask_i.write(false);
                    state = READ_VAL;
                }
                break;
            case READ_VAL:
                ask_i.write(true);
                state = WAIT_READ_RL;
                break;
            case WAIT_READ_RL:
                if (ready_i.read()) {
                    rl = static_cast<sc_bv<RL_WIDTH> >(input.read());
                    ask_i.write(false);
                    state = PREPARE_VAL;
                }
                break;
            case PREPARE_VAL:
                ready_o.write(false);
                if ((i.read() < VAL_WIDTH) || (buf_idx.read() >= BUS_WIDTH)) {
                    if (buf_idx.read() < BUS_WIDTH) {
                        buf_temp = buf;
                        buf_temp[buf_idx.read()] = value.read()[i.read()];
                        buf = buf_temp;
                        buf_idx_temp = buf_idx;
                        buf_idx = buf_idx_temp + 1;
                        i_temp = i;
                        i = i_temp + 1;
                    }
                    else {
                        state = WAIT_WRITE_VAL;
                        buf_idx = 0;
                    }
                }
                else {
                    state = PREPARE_RL;
                    i = 0;
                }
                break;
            case WAIT_WRITE_VAL:
                if (ask_o.read()) {
                    buf_temp = buf;
                    output.write(buf_temp);
                    ready_o.write(true);
                    state = PREPARE_VAL;
                }
                break;
            case PREPARE_RL:
                ready_o.write(false);
                if ((i.read() < RL_WIDTH) || (buf_idx.read() >= BUS_WIDTH)) {
                    if (buf_idx.read() < BUS_WIDTH) {
                        buf_temp = buf;
                        buf_temp[buf_idx.read()] = rl.read()[i.read()];
                        buf = buf_temp;
                        buf_idx_temp = buf_idx;
                        buf_idx = buf_idx_temp + 1;
                        i_temp = i;
                        i = i_temp + 1;
                    }
                    else {
                        state = WAIT_WRITE_RL;
                        buf_idx = 0;
                    }
                }
                else {
                    state = WAIT_READ_VAL;
                    ask_i.write(true);
                    ready_o.write(false);
                    i = 0;
                }
                break;
            case WAIT_WRITE_RL:
                if (ask_o.read()) {
                    buf_temp = buf;
                    output.write(buf_temp);
                    ready_o.write(true);
                    state = PREPARE_RL;
                }
                break;
            default:
                ask_i.write(true);
                ready_o.write(false);
        }
    }
}
