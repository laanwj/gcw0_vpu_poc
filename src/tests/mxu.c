#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "jzmedia.h"
#include "jz_tcsm.h"
#include "jzm_vpu.h"

int main()
{
    uint32_t test_in[4]  = {0x12345678, 0x87654321, 0x55555555, 0xaaaaaaaa};
    uint32_t test_out[4] = {};
    S32I2M(xr16, 0x7); /* Enable mxu and extensions */
    S32LDD(xr1, test_in, 0x0);
    S32LDD(xr2, test_in, 0x4);
    S32LDD(xr3, test_in, 0x8);
    S32LDD(xr4, test_in, 0xc);
    S32XOR(xr1, xr1, xr2);
    S32XOR(xr2, xr3, xr4);
    S32STD(xr1, test_out, 0x0);
    S32STD(xr2, test_out, 0x4);
    S32STD(xr3, test_out, 0x8);
    S32STD(xr4, test_out, 0xc);

    printf("Test out %08x %08x %08x %08x\n", test_out[0], test_out[1], test_out[2], test_out[3]);
}

