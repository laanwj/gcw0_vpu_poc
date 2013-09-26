/* Interface for test5_p1 user space */
#ifndef TEST5_P1_H
#define TEST5_P1_H

/* TCSM1 locations of parameters */
#define TEST_TCSM1_USER_ADDR 0x6000
#define TEST_TCSM1_USER_SIZE 0x6004
#define TEST_TCSM1_FB_ADDR 0x6008

/* TCSM1 location of other data */
#define TEST_TCSM0_DMA_TASK_QUEUE 0x0000
#define TEST_TCSM1_DMA_TASK_QUEUE 0x6100
#define TEST_TCSM1_TILE_BUFFER 0x6200

#endif
