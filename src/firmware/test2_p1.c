/* Test firmware for AUX (VPU) that renders a simple animation to framebuffer.
 *
 * For troubleshooting, resulting firmware can be disassembled using:
 * mipsel-linux-objdump  -D -b binary -EL -mmips:isa32r2 $1
 */
#include "jzsys.h"
#include "jzasm.h"
#include "jzmedia.h"
#include "jz4760_2ddma_hw.h"
#include "jz4760_dcsc.h"

#define __p1_text __attribute__ ((__section__ (".p1_text")))
#define __p1_main __attribute__ ((__section__ (".p1_main")))
#define __p1_data __attribute__ ((__section__ (".p1_data")))

extern int _gp;

#define TCSM0_BANK0 0x132B0000

#define TCSM1_BANK0 0xF4000000
#define TCSM1_BANK1 0xF4001000
#define TCSM1_BANK2 0xF4002000
#define TCSM1_BANK3 0xF4003000
#define TCSM1_BANK4 0xF4004000
#define TCSM1_BANK5 0xF4005000
#define TCSM1_BANK6 0xF4006000

#define FB (*((unsigned int**)TCSM1_BANK6))

#define RGBA(r,g,b,a) ((((a)&0xFF)<<24) | (((r)&0xFF)<<16) | (((g)&0xFF)<<8) | ((b)&0xFF))
#define CENTERX 160
#define CENTERY 120

__p1_main int main() {
    int x, y, t, xo;
    S32I2M(xr16, 0x3);
    unsigned int *fb = FB;

    while(1)
    {
        xo = 0;
        for(t=1; t<1000; t+=2)
        {
            unsigned int ptr = 0;
            for(y=0; y<240; ++y)
            {
                for(x=0; x<320; ++x)
                    fb[ptr++] = RGBA(((x+xo-CENTERX)*t)>>8,((y-CENTERY)*t)>>8,((x+xo-CENTERX)*t*(y-CENTERY))>>16,0);
            }
        }
        for(xo=1; xo<512; xo++)
        {
            unsigned int ptr = 0;
            for(y=0; y<240; ++y)
            {
                for(x=0; x<320; ++x)
                    fb[ptr++] = RGBA(((x+xo-CENTERX)*t)>>8,((y-CENTERY)*t)>>8,((x+xo-CENTERX)*t*(y-CENTERY))>>16,0);
            }
        }
        for(t=999; t>=1; t-=2)
        {
            unsigned int ptr = 0;
            for(y=0; y<240; ++y)
            {
                for(x=0; x<320; ++x)
                    fb[ptr++] = RGBA(((x+xo-CENTERX)*t)>>8,((y-CENTERY)*t)>>8,((x+xo-CENTERX)*t*(y-CENTERY))>>16,0);
            }
        }
    }

    i_nop;
    i_nop;
    i_nop;
    i_nop;
    i_wait();

    return 0;
}
