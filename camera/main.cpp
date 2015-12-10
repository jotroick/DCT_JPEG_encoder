// toplevel function
// author: Marc Engels
#define      SC_INCLUDE_FX
#include    <systemc.h>
#include    "fifo_stat.h"
#include    "my_fxtype_params.h"
#include    "fix_stat.h"

#include    "test.h"
#include    "df_fork.h"
#include    "snk.h"
#include    "src.h"

#include    "jpeg_dec.h"
#include    "jpeg_enc.h"

#include    "bit_unpacking.h"
#include    "genreset.h"

#define MAXWIDTH 1024
#define MAXWIDTH8 ((MAXWIDTH +7)/8 * 8)

int sc_main (int argc , char *argv[]) {

    /*
       int quantization[64] = { 8,  6,  6,  7,  6,  5,  8,  7,
       7,  7,  9,  9,  8, 10, 12, 20,
       13, 12, 11, 11, 12, 25, 18, 19,
       15, 20, 29, 26, 31, 30, 29, 26,
       28, 28, 32, 36, 46, 39, 32, 34,
       44, 35, 28, 28, 40, 55, 41, 44,
       48, 49, 52, 52, 52, 31, 39, 57,
       61, 56, 50, 60, 46, 51, 52, 50 };
       */

    sc_fixed<32, 2> quantization_inv[64] = {
        0.062500000, 0.090909091, 0.100000000, 0.062500000,
        0.041666667, 0.025000000, 0.019607843, 0.016393443,
        0.083333333, 0.083333333, 0.071428571, 0.052631579,
        0.038461538, 0.017241379, 0.016666667, 0.018181818,
        0.071428571, 0.076923077, 0.062500000, 0.041666667,
        0.025000000, 0.017543860, 0.014492754, 0.017857143,
        0.071428571, 0.058823529, 0.045454545, 0.034482759,
        0.019607843, 0.011494253, 0.012500000, 0.016129032,
        0.055555556, 0.045454545, 0.027027027, 0.017857143,
        0.014705882, 0.009174312, 0.009708738, 0.012987013,
        0.041666667, 0.028571429, 0.018181818, 0.015625000,
        0.012345679, 0.009615385, 0.008849558, 0.010869565,
        0.020408163, 0.015625000, 0.012820513, 0.011494253,
        0.009708738, 0.008264463, 0.008333333, 0.009900990,
        0.013888889, 0.010869565, 0.010526316, 0.010204082,
        0.008928571, 0.010000000, 0.009708738, 0.010101010};

    int quantization[64] = { 16, 11, 10, 16, 24, 40, 51, 61,
        12, 12, 14, 19, 26, 58, 60, 55,
        14, 13, 16, 24, 40, 57, 69, 56,
        14, 17, 22, 29, 51, 87, 80, 62,
        18, 22, 37, 56, 68,109,103, 77,
        24, 35, 55, 64, 81,104,113, 92,
        49, 64, 78, 87,103,121,120,101,
        72, 92, 95, 98,112,100,103, 99};

    sc_int<9> zig_zag[64] = {0,1,8,16,9,2,3,10 ,
        17,24,32,25,18,11,4,5 ,
        12,19, 26, 33, 40, 48, 41, 34,
        27, 20, 13, 6, 7, 14, 21, 28,
        35, 42, 49, 56, 57, 50, 43, 36,
        29, 22, 15, 23, 30, 37, 44, 51,
        58, 59, 52, 45, 38, 31, 39, 46,
        53, 60, 61, 54, 47, 55, 62, 63};

    // definition of default files
    const char* inputfile       = "datain.pgm";
    const char* outputfile      = "dataout.pgm";
    const char* typefile        = "types.txt";

    //  definition of clock
    sc_clock    clk1("clk1",12, SC_NS);

    //  definition of signals
    sc_signal<bool>     ask_rl_enc_out;
    sc_signal<bool>     ask_bit_unpak_out;
    sc_signal<bool>     ask_bit_pack_out;
    sc_signal<bool>     ready_rl_enc_out;
    sc_signal<bool>     ready_bit_unpack_out;
    sc_signal<bool>     ready_bit_pack_out;
    sc_signal<sc_int<32> >      data_rl_enc_out;
    sc_signal<sc_int<32> >      data_bit_unpack_out;
    sc_signal<sc_int<8> >      data_bit_pack_out;
    sc_signal<bool>     reset;

    //  definition of FIFO queues
    fifo_stat<int>  stimulus("stimulus",1);
    fifo_stat<int>  parameters("parameters",3);
    fifo_stat<int>  stimulus_dup1("stimulus_dup1",1);
    fifo_stat<int>  stimulus_dup2("stimulus_dup2",MAXWIDTH8*8+64+64+64+64+64);
    fifo_stat<int>  parameters_dup1("parameters_dup1",3);
    fifo_stat<int>  parameters_dup2("parameters_dup2",3);
    fifo_stat<int>  parameters_dup3("parameters_dup3",3);
    fifo_stat<int>  jpeg_enc_out("jpeg_enc_out",1);
    fifo_stat<int>  result("result",1);
    fifo_stat<int>  result_dup1("result_dup1",1);
    fifo_stat<int>  result_dup2("result_dup2",1);
    fifo_stat<int>  data_rl_enc_out_ff("data_rl_enc_out_ff",1);
    fifo_stat<sc_int<8> >  data_bit_pack_out_ff("data_bit_pack_out_ff",1);
    fifo_stat<int>  data_bit_unpack_out_ff("data_bit_unpack_out_ff",1);

    // processing of command-line arguments
    bool    detected;
    for(int i=3; i<=argc; i+=2) {
        cout << argv[i-2] << " " << argv[i-1] << endl;
        detected = 0;
        if (strcmp(argv[i-2],"-i")==0) {
            inputfile = argv[i-1];
            detected = 1;
        }
        if (strcmp(argv[i-2],"-o")==0) {
            outputfile = argv[i-1];
            detected = 1;
        }
        if (strcmp(argv[i-2],"-t")==0) {
            typefile = argv[i-1];
            detected = 1;
        }
        if (detected == 0) {
            cout << "option " << argv[i-2] << " not known " << endl;
        }
    }

    //  definition of modules
    // setting up reset: first 5 pulses reset is set
    genreset genreset_1("genreset_1", 5);
    genreset_1.reset(reset);
    genreset_1.clk(clk1);

    src src1("src1", inputfile, MAXWIDTH);
    src1.output(stimulus);
    src1.parameters(parameters);

    df_fork<int,2> fork1("fork1");
    fork1.in(stimulus);
    fork1.out[0](stimulus_dup1);
    fork1.out[1](stimulus_dup2);

    df_fork<int,3> fork_param("fork_param");
    fork_param.in(parameters);
    fork_param.out[0](parameters_dup1);
    fork_param.out[1](parameters_dup2);
    fork_param.out[2](parameters_dup3);

    jpeg_enc jpeg_enc_1("jpeg_enc_1", quantization_inv, zig_zag, MAXWIDTH);
    jpeg_enc_1.input(stimulus_dup1);
    jpeg_enc_1.parameters(parameters_dup1);
    jpeg_enc_1.ask(ask_bit_pack_out);
    jpeg_enc_1.ready(ready_bit_pack_out);
    jpeg_enc_1.output(data_bit_pack_out);
    jpeg_enc_1.clk(clk1);
    jpeg_enc_1.reset(reset);

    P2FF<sc_int<8> > p2ff2("p2ff2");
    p2ff2.clk(clk1);
    p2ff2.input(data_bit_pack_out);
    p2ff2.ask(ask_bit_pack_out);
    p2ff2.ready(ready_bit_pack_out);
    p2ff2.output(data_bit_pack_out_ff);

    bit_unpacking bit_unpacking_1("bit_unpacking_1");
    bit_unpacking_1.input(data_bit_pack_out_ff);
    bit_unpacking_1.output(data_bit_unpack_out_ff);

    FF2PC<int, sc_int<32> > ff2p2("ff2p2");
    ff2p2.clk(clk1);
    ff2p2.input(data_bit_unpack_out_ff);
    ff2p2.ask(ask_bit_unpak_out);
    ff2p2.ready(ready_bit_unpack_out);
    ff2p2.output(data_bit_unpack_out);

    jpeg_dec_pr jpeg_dec_1("jpeg_dec_1", quantization, MAXWIDTH, typefile);
    jpeg_dec_1.ask(ask_bit_unpak_out);
    jpeg_dec_1.ready(ready_bit_unpack_out);
    jpeg_dec_1.input(data_bit_unpack_out);
    jpeg_dec_1.clk(clk1);
    jpeg_dec_1.parameters(parameters_dup2);
    jpeg_dec_1.output(result);
    jpeg_dec_1.reset(reset);

    df_fork<int,2> fork2("fork2");
    fork2.in(result);
    fork2.out[0](result_dup1);
    fork2.out[1](result_dup2);

    snk snk1("snk1", outputfile);
    snk1.input(result_dup1);
    snk1.parameters(parameters_dup3);

    test test1("test1");
    test1.reference(stimulus_dup2);
    test1.data(result_dup2);

    sc_trace_file *tracefile;
    tracefile = sc_create_vcd_trace_file("test");
    sc_trace(tracefile, data_rl_enc_out, "data_rl_enc_out");
    sc_trace(tracefile, data_bit_pack_out, "data_bp_out");

    sc_start(200000000, SC_NS);

    return 0;
}
