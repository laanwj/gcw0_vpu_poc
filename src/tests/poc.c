/* Proof of concept for using the Ingenic jz4770 vpu as second core */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "jzasm.h"
#include "jz_tcsm.h"
#include "jzm_vpu.h"

const char *tcsm_device = "/dev/tcsm";

#define EFE__OFFSET 0x13240000
#define MC__OFFSET 0x13250000
#define VPU__OFFSET 0x13200000
#define CPM__OFFSET 0x10000000
#define AUX__OFFSET 0x132A0000
#define TCSM0__OFFSET 0x132B0000
#define TCSM1__OFFSET 0x132C0000
#define SRAM__OFFSET 0x132F0000
#define GP0__OFFSET 0x13210000
#define GP1__OFFSET 0x13220000
#define GP2__OFFSET 0x13230000
#define DBLK0__OFFSET 0x13270000
#define DBLK1__OFFSET 0x132D0000
#define SDE__OFFSET 0x13290000
#define JPGC__OFFSET 0x132E0000
#define VMAU__OFFSET 0x13280000

#define EFE__SIZE   0x00001000
#define MC__SIZE   0x00001000
#define VPU__SIZE 0x00001000
#define CPM__SIZE 0x00001000
#define AUX__SIZE 0x00004000
#define TCSM0__SIZE 0x00004000
#define TCSM1__SIZE 0x0000C000
#define SRAM__SIZE 0x00007000
#define GP0__SIZE   0x00001000
#define GP1__SIZE   0x00001000
#define GP2__SIZE   0x00001000
#define DBLK0__SIZE   0x00001000
#define DBLK1__SIZE   0x00001000
#define SDE__SIZE   0x00004000
#define JPGC__SIZE   0x00004000
#define VMAU__SIZE 0x0000F000

#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT9	0x00000200
#define BIT11	0x00000800
#define BIT13	0x00002000
#define BIT15	0x00008000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000

struct vpu_conn
{
    int fd;
    void *vpu_base;
    void *aux_base;
    void *tcsm0_base;
    void *tcsm1_base;
    void *cpm_base;
};

#define VPU_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->vpu_base + address) = data; } while (0)
#define VPU_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->vpu_base + address))
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
#define CPM_OUTREG32(conn, address, data) \
    do { *(volatile uint32_t*)((conn)->cpm_base + address) = data; } while (0)
#define CPM_INREG32(conn, address) \
    (*(volatile uint32_t*)((conn)->cpm_base + address))

#define TEST_TCSM0_WORK_READY 0x0000
int main()
{
    int fd = open(tcsm_device, O_RDWR);
    if(fd < 0)
    {
        perror("Can't open tcsm device");
        exit(1);
    }

    printf("Prepare dir\n");
    if(ioctl(fd, TCSM_TOCTL_PREPARE_DIR) < 0)
    {
        perror("Cannot enable tcsm");
        exit(1);
    }

    printf("After prepare dir\n");

    struct vpu_conn *vpu = calloc(1, sizeof(struct vpu_conn));
    vpu->fd = fd;
    vpu->vpu_base = mmap(0, VPU__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, VPU__OFFSET);
    vpu->aux_base = mmap(0, AUX__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, AUX__OFFSET);
#if 1 /* Use always-mapped address */
    vpu->tcsm0_base = (void*)0xF4000000;
#else
    vpu->tcsm0_base = mmap(0, TCSM0__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, TCSM0__OFFSET);
#endif
    vpu->tcsm1_base = mmap(0, TCSM1__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, TCSM1__OFFSET);
    vpu->cpm_base = mmap(0, CPM__SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, vpu->fd, CPM__OFFSET);

    /* Enable partial kernel mode and turn on aux */

    if(vpu->aux_base == NULL ||
       vpu->vpu_base == NULL ||
       vpu->aux_base == NULL ||
       vpu->cpm_base == NULL ||
       vpu->tcsm0_base == NULL ||
       vpu->tcsm1_base == NULL)
    {
        printf("Can't map register ranges\n");
        exit(1);
    }
    AUX_OUTREG32(vpu, 0, 1);
    //printf("AUX status %08x\n", AUX_INREG32(vpu, 0));
    printf("Loading code...\n");


    /* Load code into TCSM1 */
    int cfd = open("test1_p1.bin", O_RDONLY);
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
    AUX_OUTREG32(vpu, 0, 1);
    for(int x=0; x<firmware_size/4; ++x)
        TCSM1_OUTREG32(vpu, x*4, firmware[x]);

    /* Clear ready token */
    TCSM0_OUTREG32(vpu, TEST_TCSM0_WORK_READY, 0);
    jz_dcache_wb();
    i_sync();

    /* Reset and turn AUX on */
    AUX_OUTREG32(vpu, 0, 1);
    AUX_OUTREG32(vpu, 0, 2);

    printf("Executing code...\n");
    /* Wait for execution to complete */
    while(1)
    {
        p1_dcache_flush();
        uint32_t val = TCSM0_INREG32(vpu, TEST_TCSM0_WORK_READY);
        if(val)
        {
            printf("Result: %08x\n", val);
            break;
        }
    }

    /* Turn AUX off */
    AUX_OUTREG32(vpu, 0, 1);

    /* Print current state of TCSM0 memory */
    printf("TCSM0 ");
    for(int x=0; x<16; ++x)
    {
        uint32_t val = TCSM0_INREG32(vpu, TEST_TCSM0_WORK_READY + x*4);
        printf("%x ", val);
    }
    printf("\n");

    printf("Before flush\n");
    if(ioctl(fd, TCSM_TOCTL_FLUSH_WORK) < 0)
    {
        perror("Cannot enable tcsm");
    }
    printf("After flush\n");

    close(fd);
    return 0;
}

