#include "vdp.h"
#include "system.h"
#include "puff.h"

unsigned char helloworldraw[] = {
  0xF3,0x48,0xCD,0xC9 ,0xC9 ,0x57 ,0x70 ,0xF6 ,0xF7 
  ,0x0D ,0x08 ,0x72 ,0x0D ,0x0E ,0x76 ,0x75 ,0x51 
  ,0x28 ,0xCF ,0x2F ,0xCA ,0x49 ,0x51 ,0xE4 ,0x02, 0x00
};

// MUST be large enough for output data - you need to know!
unsigned char outbuf[32];
unsigned int dstlen;
unsigned int srclen;

int main() {
	int x = set_text();
	VDP_SET_REGISTER(VDP_REG_MODE1, x);
	charsetlc();
	putstring("hello world!\n");
	putstring("\nsizeof(int): ");
	hexprint(sizeof(int));
	putstring("\nsizeof(long):");
	hexprint(sizeof(long));
	putstring("\nsizeof(short):");
	hexprint(sizeof(short));
	putstring("\n");
	
	dstlen=32;
	srclen=sizeof(helloworldraw);
	x = puff(outbuf, &dstlen, helloworldraw, &srclen);
	putstring("\npuff() returned: ");
	hexprint(x);
	putstring("\n");
	putstring(outbuf);
	putstring("\n");

	unsigned char n;
	for (;;) {
	  VDP_WAIT_VBLANK_CRU_STATUS(n);
	  writestring(16,0,">");
	  faster_hexprint(n);
	}

	halt();

	return 0;
}


