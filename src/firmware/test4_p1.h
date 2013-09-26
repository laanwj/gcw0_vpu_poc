/* Interface for test3_p1 user space */
#ifndef TEST4_P1_H
#define TEST4_P1_H

#define CYCLES1 100
#define CYCLES2 1000000

#if 0
/* TCSM0 */
#define ADDRESS TCSM0
#define BANKS 4
#define BANK_SIZE 0x1000
#endif
#if 0
/* TCSM1 */
#define ADDRESS TCSM1
#define BANKS 6
#define BANK_SIZE 0x2000
#endif
#if 1
/* User memory */
#define ADDRESS USER_DATA
#define BANKS 1
#define BANK_SIZE 0x1000  /* ? */
#endif

/* Kind of test to perform */
//#define READ
#define WRITE

/* TCSM1 locations of parameters */
#define TEST_TCSM1_USER_ADDR 0x6000
#define TEST_TCSM1_USER_SIZE 0x6004

#endif
