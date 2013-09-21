#define VP6_P1_USE_PADDR
#define MPEG4_P1_USE_PADDR

#include "jzsys.h"
#include "jzasm.h"
#include "jzmedia.h"
#include "jz4760_2ddma_hw.h"
//#include "jz4760e_dcsc.h"
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

__p1_main int main() {
    int x;
    *((volatile int *)TCSM0_BANK0) = 0x87654321;
    //S32I2M(xr16, 0x3);
    //for(x=0; x<16; ++x)
    //  *((volatile int *)TCSM0_BANK0+4*x) = 0x87654321 + x;
  i_nop;
  i_nop;
  i_nop;
  i_nop;
  i_wait();

  return 0;
}
