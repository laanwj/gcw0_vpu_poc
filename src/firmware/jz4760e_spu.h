#ifndef __JZ4760_SPU_H__
#define __JZ4760_SPU_H__

#ifdef JZC_RTL_SIM
# include "instructions.h"
#else
# include "jzasm.h"
#endif //JZC_RTL_SIM

#define SP_CTRL_DPT(val)       do{i_mtc0_2(val , 22, 0);}while(0)
#define SP_ADDR_DPT(val)       do{i_mtc0_2(val , 22, 1);}while(0)
#define SP_PUSH()              do{i_mtc0_2(0x80, 22, 2);}while(0)
#define SP_CLZ()               do{i_mtc0_2(0x0 , 22, 2);}while(0)
#define SP_DO()                do{i_mtc0_2(0x1 , 22, 2);}while(0)

#endif /*__JZ4760_SPU_H__*/
