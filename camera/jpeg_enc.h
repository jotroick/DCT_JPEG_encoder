/*  jpeg_enc.h */
#ifndef _JPEG_ENC
#define _JPEG_ENC

#include        "r2b.h"
#include        "dct.h"
#include        "quantize1.h"
#include        "zz_enc1.h"
#include        "rl_enc1.h"
#include        "bit_packing.h"
#include        "P2FF.h"
#include        "FF2P.h"

SC_MODULE(jpeg_enc) {

    /* in and output */
    my_fifo_in<int>     input;
    my_fifo_in<int>     parameters;
    sc_out<sc_int<8> >  output;
    sc_in<bool>         clk;
    sc_in<bool>         ask;
    sc_out<bool>        ready;
    sc_in<bool>         reset;

    /* internal FIFOs */
    fifo_stat<int>      r2b_out;
    fifo_stat<float>    dct_out;

    /* internal modules */
    r2b r2b_1;
    dct dct_1;
    quantize1 quant_1;
    zz_enc1 zz_enc_1;
    rl_enc1 rl_enc_1;
    bit_packing bit_packing_1;

    FF2PC<float, sc_fixed<23, 13, SC_RND, SC_SAT> > ff2p_dct_quantize;
    sc_signal<sc_fixed<23, 13, SC_RND, SC_SAT> >  float_dct_quantize;
    sc_signal<bool> bool_dct_quantize_ask;
    sc_signal<bool> bool_dct_quantize_ready;

    sc_signal<sc_int<9> >  int_quantize_zz;
    sc_signal<bool> bool_quantize_zz_ask;
    sc_signal<bool> bool_quantize_zz_ready;

    sc_signal<sc_int<9> > int_zz_rl_enc;
    sc_signal<bool> bool_zz_rl_enc_ask;
    sc_signal<bool> bool_zz_rl_enc_ready;

    sc_signal<sc_int<9> > int_rl_enc_bit;
    sc_signal<bool> bool_rl_enc_bit_ask;
    sc_signal<bool> bool_rl_enc_bit_ready;

    jpeg_enc(sc_module_name _name, sc_fixed<32, 2>* _quantization, sc_int<9>* _zig_zag,
            int _maxwidth):
        sc_module(_name),
        r2b_1("r2b_1",_maxwidth),
        dct_1("dct_1"),
        ff2p_dct_quantize("ff2p_dct_quantize_"),
        quant_1("quant_1",_quantization),
        zz_enc_1("zz_enc_1", _zig_zag),
        rl_enc_1("rl_enc_1"),
        bit_packing_1("bit_packing_1"),
        r2b_out("r2b_out",1),
        dct_out("dct_out",1)
        {

            r2b_1.input(input);
            r2b_1.parameters(parameters);
            r2b_1.output(r2b_out);

            dct_1.input(r2b_out);
            dct_1.output(dct_out);

            ff2p_dct_quantize.clk(clk);
            ff2p_dct_quantize.input(dct_out);
            ff2p_dct_quantize.output(float_dct_quantize);
            ff2p_dct_quantize.ask(bool_dct_quantize_ask);
            ff2p_dct_quantize.ready(bool_dct_quantize_ready);

            quant_1.input(float_dct_quantize);
            quant_1.clk(clk);
            quant_1.reset(reset);
            quant_1.ready_i(bool_dct_quantize_ready);
            quant_1.ask_i(bool_dct_quantize_ask);
            quant_1.output(int_quantize_zz);
            quant_1.ready_o(bool_quantize_zz_ready);
            quant_1.ask_o(bool_quantize_zz_ask);

            zz_enc_1.input(int_quantize_zz);
            zz_enc_1.ask_i(bool_quantize_zz_ask);
            zz_enc_1.ready_i(bool_quantize_zz_ready);
            zz_enc_1.ask_o(bool_zz_rl_enc_ask);
            zz_enc_1.ready_o(bool_zz_rl_enc_ready);
            zz_enc_1.clk(clk);
            zz_enc_1.reset(reset);
            zz_enc_1.output(int_zz_rl_enc);

            rl_enc_1.input(int_zz_rl_enc);
            rl_enc_1.clk(clk);
            rl_enc_1.reset(reset);
            rl_enc_1.ask_i(bool_zz_rl_enc_ask);
            rl_enc_1.ready_i(bool_zz_rl_enc_ready);
            rl_enc_1.ask_o(bool_rl_enc_bit_ask);
            rl_enc_1.ready_o(bool_rl_enc_bit_ready);
            rl_enc_1.output(int_rl_enc_bit);

            bit_packing_1.input(int_rl_enc_bit);
            bit_packing_1.ask_i(bool_rl_enc_bit_ask);
            bit_packing_1.ready_i(bool_rl_enc_bit_ready);
            bit_packing_1.ask_o(ask);
            bit_packing_1.ready_o(ready);
            bit_packing_1.clk(clk);
            bit_packing_1.reset(reset);
            bit_packing_1.output(output);
        }

    ~jpeg_enc() {
    }

};

#endif

