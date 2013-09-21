#ifndef __JZ4760_DCSC_H__
#define __JZ4760_DCSC_H__

#ifdef _RTL_SIM_
# include "instructions.h"
#else
# include "jzasm.h"
#endif //_RTL_SIM_

//#include "mpeg4_tcsm0.h"

extern volatile unsigned char *aux_base;
#define P1_BASE_VADDR	    (aux_base)
#define AUX_START()               \
  ({						\
    *(volatile unsigned int *)P1_BASE_VADDR=1;	\
    *(volatile unsigned int *)P1_BASE_VADDR=2;	\
  })

#define AUX_RESET()               \
  ({						\
    *(volatile unsigned int *)P1_BASE_VADDR=1;	\
  })

#define CP0_STATUS	    12
#define CP0_CAUSE      13
#define CP0_EPC        14
#define CP0_CONFIG     16
#define CP0_DCSC	    20
#define CP0_TAGLO       28
#define CORE_CS_SLT  	2 
#define CORE_RPC_SLT 	3
#define DCSC_MBOX0_SLT	0
#define DCSC_MBOX1_SLT	1
#define DCSC_SPINLK_SLT	2
#define DCSC_SPIN0_SLT	3
#define DCSC_SPIN1_SLT	4
	

//CORE_CS
#define CS_SWRST0_MSK	1
#define CS_SWRST1_MSK	1
#define CS_IRQ0P_MSK	1
#define CS_IRQ1P_MSK	1
#define CS_IRQ0M_MSK	1
#define CS_IRQ1M_MSK	1
#define CS_GIRQP_MSK	1
#define CS_GIRQ0M_MSK	1
#define CS_GIRQ1M_MSK	1
#define CS_SLEEP0M_MSK	1
#define CS_SLEEP1M_MSK	1
#define CS_SLEEP0_MSK	1
#define CS_SLEEP1_MSK	1

#define CS_SWRST0_SFT	0
#define CS_SWRST1_SFT	1
#define CS_IRQ0P_SFT	4
#define CS_IRQ1P_SFT	5
#define CS_IRQ0M_SFT	8
#define CS_IRQ1M_SFT	9	
#define CS_GIRQP_SFT	16
#define CS_GIRQ0M_SFT	20
#define CS_GIRQ1M_SFT	21
#define CS_SLEEP0M_SFT	26
#define CS_SLEEP1M_SFT	27
#define CS_SLEEP0_SFT	30
#define CS_SLEEP1_SFT	31

//CORE_RPC
#define RPC_UNDEF_MSK	0xffffff
#define RPC_RPC1_MSK	1
#define RPC_RPC0_MSK	1

#define RPC_UNDEF_SFT	0
#define RPC_RPC1_SFT	29
#define RPC_RPC0_SFT	31

//CORE_MBOX0
#define MBOX0_MSK	0xffffffff
#define MBOX0_SFT	0

//CORE_MBOX1
#define MBOX1_MSK	0xffffffff
#define MBOX1_SFT	0

//CORE_SPINLK
#define SPINLK_MSK	0x3
#define SPINLK_SFT	0

//CORE_SPIN0
#define SPIN0_MSK	0x3
#define SPIN0_SFT	0

//CORE_SPIN1
#define SPIN1_MSK	0x3
#define SPIN1_SFT	0

//some key functional values
#define RESET_FROM_TCSM	1
#define P0_SPIN0_VAL	1
#define P1_SPIN1_VAL	2


#define TCSM0_CPUBASE	0xF4000000
#define TCSM1_CPUBASE	0xF4000000
#define TCSM0_PBASE	0x132B0000
#define TCSM0_VBASE_UC	0xB32B0000
#define TCSM0_VBASE_CC	0x932B0000
#define TCSM1_PBASE	0x132C0000
#define TCSM1_VBASE_UC	0xB32C0000
#define TCSM1_VBASE_CC	0x932C0000
#define TCSM_BANK0_OFST	0x0
#define TCSM_BANK1_OFST	0x1000
#define TCSM_BANK2_OFST	0x2000
#define TCSM_BANK3_OFST	0x3000


#define P0_SPINLOCK_SET()					\
  ({								\
    while (i_mfc0_2(CP0_DCSC, DCSC_SPIN0_SLT) != P0_SPIN0_VAL);	\
  })
#define P1_SPINLOCK_SET()					\
  ({								\
    while (i_mfc0_2(CP0_DCSC, DCSC_SPIN1_SLT) != P1_SPIN1_VAL);	\
  })
#define P0_SPINLOCK_CLR()				\
  ({							\
    i_mtc0_2(0, CP0_DCSC, DCSC_SPINLK_SLT);		\
  })
#define P1_SPINLOCK_CLR()				\
  ({							\
    i_mtc0_2(0, CP0_DCSC, DCSC_SPINLK_SLT);		\
  })

#define INIT_SPIN0()					\
  ({							\
    i_mtc0_2(1, CP0_DCSC, DCSC_SPIN0_SLT);		\
  })
#define INIT_SPIN1()					\
  ({							\
    i_mtc0_2(2, CP0_DCSC, DCSC_SPIN1_SLT);		\
  })


#define P1_BOOT_ADDR            0x87F00000

#define P1_BOOT(init)							\
({                                                                      \
i_mtc0_2(0x0, CP0_CAUSE, 0);                                            \
i_mtc0_2(i_mfc0_2(CP0_CONFIG, 0) | 3, CP0_CONFIG, 0);                   \
i_mtc0_2(0x1000ff03, CP0_STATUS, 0); /*CU0=1,UM=0,EXL=1,IE=1,IRQM=0*/   \
i_mtc0_2(0x40, CP0_CONFIG, 7);       /*set partial_k*/                  \
if(init){								\
i_mtc0_2(0x0, CP0_TAGLO, 0);                                            \
p1_cache_init();                                                        \
*((volatile int *)(TCSM0_VUCADDR(TCSM0_P1_TASK_DONE))) = 0x1;		\
i_wait();								\
}else{									\
p1_dcache_flush();                                                      \
i_mtc0_2(P1_BOOT_ADDR, CP0_EPC, 0);                                     \
i_eret();								\
}									\
i_nop;                                                                  \
})    

#define P1_STARTUP()                                                    \
({                                                                      \
int i, get_val, set_val;						\
get_val = i_mfc0_2(CP0_STATUS, CORE_RPC_SLT);                           \
set_val = (RESET_FROM_TCSM & RPC_RPC1_MSK)<<RPC_RPC1_SFT;               \
i_mtc0_2(set_val | get_val, CP0_STATUS, CORE_RPC_SLT);                  \
INIT_SPIN0();                                                           \
INIT_SPIN1();                                                           \
get_val = i_mfc0_2(CP0_STATUS, CORE_CS_SLT);                            \
i_mtc0_2(get_val & ~2, CP0_STATUS, CORE_CS_SLT);                        \
})    

#define P1_RESET()							\
({                                                                      \
  int get_val;								\
  get_val = i_mfc0_2(CP0_STATUS, CORE_CS_SLT);				\
  i_mtc0_2(get_val |  2, CP0_STATUS, CORE_CS_SLT);			\
})    

#if 0
void vp6_p1_boot() {
  P1_BOOT(0);
}

void vp6_p1_boot_init() {
  P1_BOOT(1);
}

void vp6_p1_start() {
  P1_STARTUP();
}

void vp6_p1_reset() {
  P1_RESET();
}
#endif

#endif /* __JZ4760_DCSC_H__ */
