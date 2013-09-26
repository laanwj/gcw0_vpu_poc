/* Proof of concept for using the Ingenic jz4770 vpu as second core.
 * DMA to framebuffer test.
 * Write tiles from SRAM to frame buffer.
 * Note: it appears only GP2 can copy to normal RAM.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <time.h>
#include <string.h>

#include "jzasm.h"
#include "jzmedia.h"
#include "jz_vpu.h"
#include "jzm_vpu.h"
#include "t_vputlb.h"

#include "../firmware/test5_p1.h"

const char *jz_vpu_device = "/dev/jz-vpu";
const char *fb_device = "/dev/fb0";

/* Defines, these really should be moved to a header... */
#define VPU__OFFSET   0x13200000 /* Main VPU offset */
#define   VPU__SIZE     0x00100000
#define SCH__OFFSET   0x13200000 /* SCHeduler (ARB1 bus arbiter) */
#define   SCH__SIZE     0x00001000
#define GP0__OFFSET   0x13210000 /* General Purpose DMA engine 0 */
#define   GP0__SIZE     0x00001000
#define GP1__OFFSET   0x13220000 /* General Purpose DMA engine 1 */
#define   GP1__SIZE     0x00001000
#define GP2__OFFSET   0x13230000 /* General Purpose DMA engine 2 */
#define   GP2__SIZE     0x00001000
#define EFE__OFFSET   0x13240000 /* Encoder Front End */
#define   EFE__SIZE     0x00001000
#define MC__OFFSET    0x13250000 /* Motion Compensation and Estimation */
#define   MC__SIZE      0x00001000
#define DBLK0__OFFSET 0x13270000 /* Deblock 0 */
#define   DBLK0__SIZE   0x00001000
#define VMAU__OFFSET  0x13280000 /* Vector Matrix Arithmetic Unit) */
#define   VMAU__SIZE    0x0000F000
#define SDE__OFFSET   0x13290000 /* Stream Decode Engine */
#define   SDE__SIZE     0x00004000
#define AUX__OFFSET   0x132A0000 /* AUXilary CPU core */
#define   AUX__SIZE     0x00004000
#define TCSM0__OFFSET 0x132B0000 /* Tightly Coupled Shared Memory coupled to MAIN CPU */
#define   TCSM0__SIZE   0x00004000
#define TCSM1__OFFSET 0x132C0000 /* Tightly Coupled Shared Memory coupled to AUX CPU */
#define   TCSM1__SIZE   0x0000C000
#define DBLK1__OFFSET 0x132D0000 /* Deblock 1 */
#define   DBLK1__SIZE   0x00001000
#define JPGC__OFFSET  0x132E0000 /* JPEG Codec */
#define   JPGC__SIZE    0x00004000
#define SRAM__OFFSET  0x132F0000 /* Scratch RAM for AUX CPU */
#define   SRAM__SIZE    0x00007000

/* Bit definitions for readability */
#define BIT0            (1 << 0)
#define BIT1            (1 << 1)
#define BIT2            (1 << 2)
#define BIT3            (1 << 3)
#define BIT4            (1 << 4)
#define BIT5            (1 << 5)
#define BIT6            (1 << 6)
#define BIT7            (1 << 7)
#define BIT8            (1 << 8)
#define BIT9            (1 << 9)
#define BIT10           (1 << 10)
#define BIT11           (1 << 11)
#define BIT12 	        (1 << 12)
#define BIT13 	        (1 << 13)
#define BIT14 	        (1 << 14)
#define BIT15 	        (1 << 15)
#define BIT16 	        (1 << 16)
#define BIT17 	        (1 << 17)
#define BIT18 	        (1 << 18)
#define BIT19 	        (1 << 19)
#define BIT20 	        (1 << 20)
#define BIT21 	        (1 << 21)
#define BIT22 	        (1 << 22)
#define BIT23 	        (1 << 23)
#define BIT24 	        (1 << 24)
#define BIT25 	        (1 << 25)
#define BIT26 	        (1 << 26)
#define BIT27 	        (1 << 27)
#define BIT28 	        (1 << 28)
#define BIT29 	        (1 << 29)
#define BIT30 	        (1 << 30)
#define BIT31 	        (1 << 31)

/* AUX register definitions */
#define REG_AUX_CTRL       0x0
#define   AUX_CTRL_SLEEP     BIT31
#define   AUX_CTRL_BTB_INV   BIT8
#define   AUX_CTRL_MIRQ_EN   BIT3
#define   AUX_CTRL_NMI_DIS   BIT2
#define   AUX_CTRL_SW_NMI    BIT1
#define   AUX_CTRL_SW_RST    BIT0
#define REG_AUX_SPINLK     0x4
#define   AUX_SPINLK_LOCK_LSB  0
#define   AUX_SPINLK_LOCK_MASK (3 << AUX_SPINLK_LOCK_LSB)
#define REG_AUX_SPIN1      0x8
#define   AUX_SPIN1_SPIN1_LSB  0
#define   AUX_SPIN1_SPIN1_MASK (3 << AUX_SPIN1_SPIN1_LSB)
#define REG_AUX_SPIN2      0xC
#define   AUX_SPIN2_SPIN2_LSB  0
#define   AUX_SPIN2_SPIN2_MASK (3 << AUX_SPIN2_SPIN2_LSB)
#define REG_AUX_MIRQP      0x10
#define   AUX_MIRQP_MIRQP    BIT0
#define REG_AUX_MSG        0x14
#define   AUX_MSG_MESG_LSB     0
#define   AUX_MSG_MESG_MASK    (0xffffffff << AUX_MSG_MESG_LSB)
#define REG_AUX_CORE_MIRQP 0x18
#define   AUX_CORE_MIRQP_MIRQP BIT0
#define REG_AUX_CORE_MSG   0x20
#define   AUX_CORE_MSG_MESG_LSB     0
#define   AUX_CORE_MSG_MESG_MASK    (0xffffffff << AUX_CORE_MSG_MESG_LSB)

/* GP0-2 register definitions */
#define REG_GPx_DHA        0x0
#define   GPx_DHA_DHA_LSB    2
#define   GPx_DHA_DHA_MASK   0xfffffffc
#define REG_GPx_DCS        0x4
#define   GPx_DCS_BTN_LSB    16
#define   GPx_DCS_BTN_MASK   ((0xffff)<<GPx_DCS_BTN_LSB)
#define   GPx_DCS_NDN_LSB    8
#define   GPx_DCS_NDN_MASK   ((0xff)<<GPx_DCS_NDN_LSB)
#define   GPx_DCS_END        BIT2
#define   GPx_DCS_RST        BIT1
#define   GPx_DCS_SUP        BIT0

struct vpu_conn
{
    /* File descriptor for VPU connectino */
    int fd;
    /* Control registers for AHB1 bus (SCH) */
    void *sch_base;
    /* Control registers for AUX secondary MIPS processor */
    void *aux_base;
    /* 16K of fast memory coupled to MAIN CPU.
     * This is generally used for communicating from AUX to MAIN.
     */
    void *tcsm0_base;
    /* 48K of fast memory coupled to AUX CPU.
     * This is generally used for communicating from MAIN to AUX.
     */
    void *tcsm1_base;
    void *gp0_base;
    void *gp1_base;
    void *gp2_base;
    void *sram_base;
};

/* Macros for easy register access */
#define SCH_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->sch_base + address) = data; } while (0)
#define SCH_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->sch_base + address))
#define AUX_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->aux_base + address) = data; } while (0)
#define AUX_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->aux_base + address))
#define TCSM0_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->tcsm0_base + address) = data; } while (0)
#define TCSM0_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->tcsm0_base + address))
#define TCSM1_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->tcsm1_base + address) = data; } while (0)
#define TCSM1_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->tcsm1_base + address))
#define SRAM_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->sram_base + address) = data; } while (0)
#define SRAM_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->sram_base + address))

#define GP0_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->gp0_base + address) = data; } while (0)
#define GP0_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->gp0_base + address))
#define GP1_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->gp1_base + address) = data; } while (0)
#define GP1_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->gp1_base + address))
#define GP2_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->gp2_base + address) = data; } while (0)
#define GP2_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->gp2_base + address))


/* Get time in microseconds */
static unsigned long gettime(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (t.tv_nsec/1000 + (t.tv_sec * 1000000));
}

int main()
{
    int ret;
    /* Open device: enable partial kernel modes for this process
     * (allows cache instructions and access to TCSM)
     * and turns on power to AUX processor and AHB1 bus.
     */
    int fd = open(jz_vpu_device, O_RDWR);
    if(fd < 0)
    {
        perror("Can't open jz-vpu device");
        exit(1);
    }

    int fb = open(fb_device, O_RDWR);
    if(fb < 0)
    {
        perror("Can't open fbdev device");
        exit(1);
    }
    struct fb_var_screeninfo fb_var;
    struct fb_fix_screeninfo fb_fix;
    if (ioctl(fb, FBIOGET_VSCREENINFO, &fb_var) ||
        ioctl(fb, FBIOGET_FSCREENINFO, &fb_fix)) {
            printf("Error: failed to run ioctl on fbdev device\n");
        close(fb);
        exit(1);
    }


    struct vpu_conn *vpu = calloc(1, sizeof(struct vpu_conn));
    vpu->fd = fd;
    vpu->sch_base = mmap(0, SCH__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, SCH__OFFSET);
    vpu->aux_base = mmap(0, AUX__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, AUX__OFFSET);
#if 1 /* Use always-mapped built-in address */
    vpu->tcsm0_base = (void*)0xF4000000;
#else
    vpu->tcsm0_base = mmap(0, TCSM0__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, TCSM0__OFFSET);
#endif
    vpu->tcsm1_base = mmap(0, TCSM1__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, TCSM1__OFFSET);
    vpu->sram_base = mmap(0, SRAM__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, SRAM__OFFSET);
    vpu->gp0_base = mmap(0, GP0__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, GP0__OFFSET);
    vpu->gp1_base = mmap(0, GP1__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, GP1__OFFSET);
    vpu->gp2_base = mmap(0, GP2__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, GP2__OFFSET);

    if(vpu->aux_base == NULL ||
       vpu->sch_base == NULL ||
       vpu->aux_base == NULL ||
       vpu->tcsm0_base == NULL ||
       vpu->tcsm1_base == NULL)
    {
        printf("Can't map register ranges\n");
        exit(1);
    }

    struct jz_vpu_alloc alloc;
    alloc.size = 128*1024;
    alloc.physical = 0;
    ret = ioctl(fd, JZ_VPU_IOCTL_ALLOC, &alloc);
    if(ret < 0)
    {
        perror("Unable to allocate physical memory buffer\n");
        exit(1);
    }
    printf("Allocated physical memory buffer at %08x\n", (uint32_t)alloc.physical);
    uint32_t *data = mmap(0, alloc.size, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, alloc.physical);

    /* Enable MXU instructions on main processor */
    S32I2M(xr16, 0x3);
    /* Put AUX in reset state, just in case */
    AUX_OUTREG32(vpu, REG_AUX_CTRL, AUX_CTRL_SW_RST);
    /* Reset DMA controllers */
    GP0_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_RST);
    GP1_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_RST);
    GP2_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_RST);
    //GP0_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_END);
    //GP1_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_END);
    //GP2_OUTREG32(vpu, REG_GPx_DCS, GPx_DCS_END);
    /* Disable TLB (for now) */
    SCH_OUTREG32(vpu, REG_SCH_GLBC, 0); //(1<<GLBC_TLBE_SFT));

    /* Clear memories */
    memset(vpu->tcsm0_base, 0, TCSM0__SIZE);
    memset(vpu->tcsm1_base, 0, TCSM1__SIZE);
    memset(vpu->sram_base, 0, SRAM__SIZE);

    /* Load code into TCSM1 */
    printf("Loading code...\n");
    int cfd = open("test5_p1.bin", O_RDONLY);
    if(cfd < 0)
    {
        perror("Unable to load firmware");
        exit(1);
    }
    uint32_t firmware[TCSM1__SIZE/4];
    ssize_t firmware_size;
    if((firmware_size=read(cfd, firmware, TCSM1__SIZE))< 0)
    {
        perror("Unable to read firmware");
        exit(1);
    }
    printf("Firmware size: %i\n", firmware_size);
    for(int x=0; x<firmware_size/4; ++x)
        TCSM1_OUTREG32(vpu, x*4, firmware[x]);

    jz_dcache_wb();

    /* Load parameters */
    TCSM1_OUTREG32(vpu, TEST_TCSM1_USER_ADDR, alloc.physical);
    TCSM1_OUTREG32(vpu, TEST_TCSM1_USER_SIZE, alloc.size);
    TCSM1_OUTREG32(vpu, TEST_TCSM1_FB_ADDR, fb_fix.smem_start);
    /* Reset and turn AUX on, and AUX->MAIN interrupts */
    AUX_OUTREG32(vpu, REG_AUX_CTRL, AUX_CTRL_SW_RST);
    jz_dcache_wb();
    AUX_OUTREG32(vpu, REG_AUX_CTRL, AUX_CTRL_SW_NMI | AUX_CTRL_MIRQ_EN);
    jz_dcache_wb();

    /* Wait for execution to complete */
    printf("Executing code...\n");

#if 1
    uint32_t status=0;
    while((status & GPx_DCS_END) == 0) /* Track DMA progress */
    {
        status = GP2_INREG32(vpu, REG_GPx_DCS);
        printf("Bytes %04x Task %i End=%i\n",
                (status & GPx_DCS_BTN_MASK) >> GPx_DCS_BTN_LSB,
                (status & GPx_DCS_NDN_MASK) >> GPx_DCS_NDN_LSB,
                (status & GPx_DCS_END)!=0);
    }
#endif
    unsigned long time_start = gettime();
    /* Wait up to 1000 seconds for completion */
    ret = ioctl(fd, JZ_VPU_IOCTL_WAIT_COMPLETE, 1000000);
    if(ret < 0)
    {
        perror("Unable to wait for completion\n");
        exit(1);
    }

    unsigned long time_end = gettime();

    uint32_t val = AUX_INREG32(vpu, REG_AUX_MSG);
    printf("Completion token: %08x\n", val);
    double elapsed_time = (time_end - time_start)/1e6;
    printf("Elapsed time: %.2fs\n", elapsed_time);

    /* Turn AUX off */
    AUX_OUTREG32(vpu, REG_AUX_CTRL, AUX_CTRL_SW_RST);

    close(fd);
    close(fb);
    return 0;
}

