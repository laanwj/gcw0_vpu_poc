#ifndef __JZ4760_DCSC_H__
#define __JZ4760_DCSC_H__

#ifdef _RTL_SIM_
# include "instructions.h"
#else
# include "jzasm.h"
#endif //_RTL_SIM_

#define P1_BASE_VADDR	    (0xB32A0000)
extern volatile unsigned char *aux_base;

#define P1_BASE_VADDR	    (aux_base)
#define AUX_START()               \
  ({						\
    *(volatile unsigned int *)P1_BASE_VADDR=1;	\
    *(volatile unsigned int *)P1_BASE_VADDR=(2 | 0x800000);	\
  })

#define AUX_RESET()               \
  ({						\
    *(volatile unsigned int *)P1_BASE_VADDR=1;	\
  })

#endif /* __JZ4760_DCSC_H__ */
