#ifndef _JPEG_DEC
#define _JPEG_DEC

/*  jpeg_dec.h */
#include    "b2r.h"
#include    "systemc.h"
#include    "idct_fix.h"
#include    "normalize.h"
#include    "zz_dec.h"
#include    "rl_dec.h"
#include    "rl_dec_RTL.h"


SC_MODULE(jpeg_dec) {

    /* in and output */
    sc_fifo_in<int>    input;
    sc_fifo_in<int>   parameters;
    sc_fifo_out<int>  output;

    /* internal FIFOs */
    fifo_stat<int>*       rl_dec_out;
    fifo_stat<int>*       zz_dec_out;
    fifo_stat<float>*     norm_out;
    fifo_stat<int>*       idct_out;

    /* internal modules */
    rl_dec* rl_dec_1;
    zz_dec* zz_dec_1;
    normalize* norm_1;
    idct_fix* idct_1;
    b2r* b2r_1;

    /* internal variables */
    int* quantization;
    int maxwidth;
    const char*   filename;

    // constructor
    jpeg_dec(sc_module_name name, int* _quantization, int _maxwidth, const char* _filename):
        sc_module(name),
        quantization(_quantization),
        maxwidth(_maxwidth),
        filename(_filename) {

            rl_dec_out = new fifo_stat<int>("rl_dec_out",1);
            zz_dec_out = new fifo_stat<int>("zz_dec_out",1);
            norm_out = new fifo_stat<float>("norm_out",1);
            idct_out = new fifo_stat<int>("idct_out",1);

            rl_dec_1 = new rl_dec("rl_dec_1");
            rl_dec_1->input(input);
            rl_dec_1->output(*rl_dec_out);

            zz_dec_1 = new zz_dec("zz_dec_1");
            zz_dec_1->input(*rl_dec_out);
            zz_dec_1->output(*zz_dec_out);

            norm_1 = new normalize("norm_1", quantization);
            norm_1->input(*zz_dec_out);
            norm_1->output(*norm_out);

            idct_1 = new idct_fix("idct_1", filename);
            idct_1->input(*norm_out);
            idct_1->output(*idct_out);

            b2r_1 = new b2r("b2r_1",maxwidth);
            b2r_1->input(*idct_out);
            b2r_1->parameters(parameters);
            b2r_1->output(output);

        }

    // destructor
    ~jpeg_dec() {
        delete b2r_1;
        delete idct_1;
        delete norm_1;
        delete zz_dec_1;
        delete rl_dec_1;
        delete rl_dec_out;
        delete zz_dec_out;
        delete norm_out;
        delete idct_out;
    }

};

//===============================================================

SC_MODULE(jpeg_dec_pr) {

    /* in and output */
    sc_fifo_in<int>   parameters;
    sc_fifo_out<int>  output;
    sc_in<sc_int<32> >         input;
    sc_in<bool>           ready;
    sc_out<bool>      ask;
    sc_in_clk         clk;
    sc_in<bool>   reset;

    /* internal FIFOs */
    fifo_stat<int>*       rl_dec_out;
    fifo_stat<int>*       zz_dec_out;
    fifo_stat<float>*     norm_out;
    fifo_stat<int>*       idct_out;
    sc_signal<sc_int<32> >* rl_out;
    sc_signal<bool>*          rl_ask;
    sc_signal<bool>*      rl_ready;



    /* internal modules */
    rl_dec_pr* rl_dec_1;
    zz_dec* zz_dec_1;
    normalize* norm_1;
    idct_fix* idct_1;
    b2r* b2r_1;
    rl_dec_RTL* rl_dec_RTL1;
    P2FFC<int, sc_int<32> >* P2FF1;

    /* internal variables */
    int* quantization;
    int maxwidth;
    const char*   filename;


    // constructor
    jpeg_dec_pr(sc_module_name name, int* _quantization, int _maxwidth, const char* _filename):
        sc_module(name),
        quantization(_quantization),
        maxwidth(_maxwidth),
        filename(_filename) {


            rl_dec_out = new fifo_stat<int>("rl_dec_out",1);
            zz_dec_out = new fifo_stat<int>("zz_dec_out",1);
            norm_out = new fifo_stat<float>("norm_out",1);
            idct_out = new fifo_stat<int>("idct_out",1);
            rl_out = new sc_signal<sc_int<32> >("rl_out");
            rl_ask = new sc_signal<bool> ("rl_ask");
            rl_ready = new sc_signal<bool> ("rl_ready");
            //
            //  rl_dec_1 = new rl_dec_pr("rl_dec_1");
            //  rl_dec_1->input(input);
            //  rl_dec_1->output(*rl_dec_out);
            //  rl_dec_1->ask(ask);
            //  rl_dec_1->ready(ready);
            //  rl_dec_1->clk(clk);

            //
            rl_dec_RTL1 = new rl_dec_RTL("rl_dec_RTL1");
            rl_dec_RTL1 -> output(*rl_out);
            rl_dec_RTL1 -> ask_o(*rl_ask);
            rl_dec_RTL1 -> ready_o(*rl_ready);
            rl_dec_RTL1 -> input(input);
            rl_dec_RTL1 -> ready_i(ready);
            rl_dec_RTL1 -> ask_i(ask);
            rl_dec_RTL1 -> clk(clk);
            rl_dec_RTL1 -> reset(reset);


            P2FF1 = new P2FFC<int, sc_int<32> >("P2FF1");
            P2FF1 -> output(*rl_dec_out);
            P2FF1 -> input(*rl_out);
            P2FF1 -> ready(*rl_ready);
            P2FF1 -> ask(*rl_ask);
            P2FF1 -> clk(clk);


            zz_dec_1 = new zz_dec("zz_dec_1");
            zz_dec_1->input(*rl_dec_out);
            zz_dec_1->output(*zz_dec_out);

            norm_1 = new normalize("norm_1", quantization);
            norm_1->input(*zz_dec_out);
            norm_1->output(*norm_out);

            idct_1 = new idct_fix("idct_1", filename);
            idct_1->input(*norm_out);
            idct_1->output(*idct_out);

            b2r_1 = new b2r("b2r_1",maxwidth);
            b2r_1->input(*idct_out);
            b2r_1->parameters(parameters);
            b2r_1->output(output);

        }

    // destructor
    ~jpeg_dec_pr() {
        delete b2r_1;
        delete idct_1;
        delete norm_1;
        delete zz_dec_1;
        delete rl_dec_1;
        delete rl_dec_out;
        delete zz_dec_out;
        delete norm_out;
        delete idct_out;
    }

};

#endif

