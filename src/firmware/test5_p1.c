/* Test DMA by copying from SRAM to FB.
 * Note: it appears only GP2 can copy to normal RAM.
 *
 * For troubleshooting, resulting firmware can be disassembled using:
 * mipsel-linux-objdump  -D -b binary -EL -mmips:isa32r2 $1
 */
#include "jzsys.h"
#include "jzasm.h"
#include "jzmedia.h"
#include "jz4760e_2ddma_hw.h"
#include "jz4760_dcsc.h"
#include "test5_p1.h"

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
#define FB (*((unsigned int**)(TCSM1+TEST_TCSM1_FB_ADDR)))

/* DMA task queue in TCSM0 */
#define DMA_TASK_QUEUE ((volatile unsigned int*)(TCSM0+TEST_TCSM0_DMA_TASK_QUEUE))
/* DMA task queue in TCSM1 */
//#define DMA_TASK_QUEUE ((volatile unsigned int*)(TCSM1+TEST_TCSM1_DMA_TASK_QUEUE))

/* Tile buffer in TCSM1 (currently unused) */
#define TILE_BUFFER ((volatile unsigned int*)(TCSM1+TEST_TCSM1_TILE_BUFFER))

#define DEPTH 4

#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#define TILE_SIZE ((TILE_WIDTH)*(TILE_HEIGHT)*(DEPTH))

#define FB_WIDTH 320
#define FB_HEIGHT 240

#define RGBA(r,g,b,a) ((((a)&0xFF)<<24) | (((r)&0xFF)<<16) | (((g)&0xFF)<<8) | ((b)&0xFF))

__p1_main int main() {
    int x,y;
    int dptr = 0;
    S32I2M(xr16, 0x3);

    /* Put something interesting in SRAM
     * Write this once, then queue to copy it to the framebuffer multiple times.
     */
    unsigned int *ptr = (unsigned int*)SRAM;
    for(y=0; y<TILE_HEIGHT; ++y)
    {
        for(x=0; x<TILE_HEIGHT; ++x)
        {
            int dx = (x - TILE_WIDTH/2);
            int dy = (y - TILE_HEIGHT/2);
            int l = 255-((dx*dx+dy*dy)>>4);
            int i = (0x40+((x^y)<<1));
            unsigned int col;
            col = RGBA((l*i*200)>>16, (l*i*200)>>16, (l*i*240)>>16,255);
            *(ptr++) = col;
        }
    }

    /* Make DMA commands to tile it to screen */
    /* See diagram in jz4760e_2ddma_hw.h for description */
    for(y=0; y<(FB_HEIGHT+TILE_HEIGHT-1)/TILE_HEIGHT; ++y) /* XXX writes too much on last tile if non-tile-aligned height */
    {
        for(x=0; x<FB_WIDTH/TILE_WIDTH; ++x) /* XXX wouldn't copy with non-tile aligned width */
        {
            DMA_TASK_QUEUE[dptr++] = (unsigned int)SRAM; /* Transfer source address */
            DMA_TASK_QUEUE[dptr++] = (unsigned int)&FB[y*TILE_HEIGHT*FB_WIDTH + x*TILE_WIDTH]; /* Transfer destination address */
            DMA_TASK_QUEUE[dptr++] = GP_STRD(GP_TYP_WORD, TILE_WIDTH*DEPTH, GP_FRM_NML, FB_WIDTH*DEPTH); /* Strides and type */
            DMA_TASK_QUEUE[dptr++] = GP_UNIT(GP_TAG_LK/*Go to next*/, TILE_WIDTH*DEPTH, TILE_SIZE);
        }
    }
    DMA_TASK_QUEUE[dptr-1] |= GP_TAG_UL << 31; /* terminate at last task */

    set_gp2_dha((unsigned int)DMA_TASK_QUEUE);
    set_gp2_dcs();
    poll_gp2_end();

    /* Raise interrupt */
    *((volatile int *)(AUX_MESG)) = 0xb01dface;
    i_nop;
    i_nop;
    i_nop;
    i_nop;
    i_wait();

    return 0;
}
