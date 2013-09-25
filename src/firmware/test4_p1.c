/* Test completion notification interrupt.
 *
 * For troubleshooting, resulting firmware can be disassembled using:
 * mipsel-linux-objdump  -D -b binary -EL -mmips:isa32r2 $1
 */
#include "jzsys.h"
#include "jzasm.h"
#include "jzmedia.h"
#include "jz4760_2ddma_hw.h"
#include "jz4760_dcsc.h"
#include "test4_p1.h"

#define __p1_text __attribute__ ((__section__ (".p1_text")))
#define __p1_main __attribute__ ((__section__ (".p1_main")))
#define __p1_data __attribute__ ((__section__ (".p1_data")))

extern int _gp;

#define TCSM0 0x132B0000 /* 4 banks */
#define TCSM1 0xF4000000 /* 12 banks */
#define SRAM  0x132F0000 /* 7 banks */

#define AUX_MESG 0x132A0014 /* Raise interrupt to MAIN core */

#define USER_DATA (*((unsigned int*)(TCSM1+TEST_TCSM1_USER_ADDR)))
#define USER_DATA_SIZE (*(unsigned int*)(TCSM1+TEST_TCSM1_USER_SIZE))

__p1_main int main() {
    int x,y,b;
    S32I2M(xr16, 0x3);
    const unsigned int addr = TCSM1;
    /* Do dummy writes to TCSM1 for delay */
    for(y=0; y<CYCLES1; ++y)
    {
        for(x=0; x<CYCLES2; ++x)
        {
            /* Write to all banks */
            for(b=0; b<BANKS; ++b)
                *((volatile int *)(addr+0x1000*b)) = x;
        }
    }

    /* Raise interrupt */
    *((volatile int *)(AUX_MESG)) = 0xdeadcafe;
    i_nop;
    i_nop;
    i_nop;
    i_nop;
    i_wait();

    return 0;
}
