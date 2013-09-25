/* Test initialization of user-allocated physical memory area.
 *
 * For troubleshooting, resulting firmware can be disassembled using:
 * mipsel-linux-objdump  -D -b binary -EL -mmips:isa32r2 $1
 */
#include "jzsys.h"
#include "jzasm.h"
#include "jzmedia.h"
#include "jz4760_2ddma_hw.h"
#include "jz4760_dcsc.h"
#include "test3_p1.h"

#define __p1_text __attribute__ ((__section__ (".p1_text")))
#define __p1_main __attribute__ ((__section__ (".p1_main")))
#define __p1_data __attribute__ ((__section__ (".p1_data")))

extern int _gp;

#define TCSM0 0x132B0000
#define TCSM1 0xF4000000

#define USER_DATA (*((unsigned int**)(TCSM1+TEST_TCSM1_USER_ADDR)))
#define USER_DATA_SIZE (*(unsigned int*)(TCSM1+TEST_TCSM1_USER_SIZE))

__p1_main int main() {
    int x;
    S32I2M(xr16, 0x3);
    for(x=0; x<USER_DATA_SIZE/4; ++x)
    {
        USER_DATA[x] = x * x ^ 0xaaaa5555;
    }

    /* finally, copy completion token and wait */
    *((volatile int *)(TCSM0+TEST_TCSM0_WORK_READY)) = 0x87654321;
    i_nop;
    i_nop;
    i_nop;
    i_nop;
    i_wait();

    return 0;
}
