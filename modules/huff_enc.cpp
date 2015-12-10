#include "huff_enc.h"

char huff_enc::magnitude(short v) {
  char mag = 0;
  if (v < 0)
    v = -v;
  while (v > 0) {
    mag++;
    v >>= 1;
  }
  return mag;
}

void huff_enc::process() {

	  short    		diff, pred=0;
	  unsigned char len;
	  short    		pix, level, temp1, temp2;
	  int      		run, cnt;
	  HUF      		e;

	while (1) {
		pix = input.read(); // DC value
		diff = pix - pred; //difference coding
		pred = pix;

	    if (diff < 0){
	    	temp1 = -diff;
	    	temp2 = (diff-1)&(~(-1<<len));
	    }
	    else {
	    	temp1 = diff;
	    	temp2 = diff;
	    }
 	    len = magnitude(temp1);
	    e   = ldht[len];
	    output.write(e.val);
	    outbits.write(e.nb);
	    output.write(temp2);
	    outbits.write(len);

	    // continue with rest of code
	    run = 0;

	    for (cnt=1; cnt<64; ++cnt) { //63 other pixels
	      pix   = input.read();
	      level = pix;
	      if (level != 0) {
	    	  if (level < 0) {
	    		  len = magnitude(-level);
	    		  while (run & ~0xf) {
	    			  e = laht[0xf0];
	    			  output.write(e.val);
	    			  outbits.write(e.nb);
	    			  run -= 16;
					  }
	    		  e = laht[(run<<4) | len];
	    		  output.write(e.val);
	    		  outbits.write(e.nb);
	    		  output.write((level-1)&(~(-1<<len)));
	    		  outbits.write(len);
	    	  } else {
	    		  len = magnitude(level);
	    		  while (run & ~0xf) {
	    			  e = laht[0xf0];
	    			  output.write(e.val);
	    			  outbits.write(e.nb);
	    			  run -= 16;
					  }
	    		  e = laht[(run<<4) | len];
	    		  output.write(e.val);
	    		  outbits.write(e.nb);
	    		  output.write(level);
	    		  outbits.write(len);
	    	  }
	    	  run = 0;
	      } else {
	    	  run++;
	      }
	    }

	    if (run > 0) { //EOB
	    	e = laht[0];
	    	output.write(e.val);
	    	outbits.write(e.nb);
	    }
	}
}

