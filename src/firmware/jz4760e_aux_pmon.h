#ifndef __JZ4760_AUX_PMON_H__
#define __JZ4760_AUX_PMON_H__
/* ===================================================================== */
/*  MAIN CPU PMON Macros                                                 */
/* ===================================================================== */
#include "jzasm.h"

#ifdef JZC_PMON_P1

#define AUX_PMON_USELESS_INSN_REG 2
#define AUX_PMON_PIPERDY_REG 3
#define AUX_PMON_CCLK_REG 4

#define PMON_ON(func)\
  ({  i_mtc0_2(0, 20, AUX_PMON_USELESS_INSN_REG);\
    i_mtc0_2(0, 20, AUX_PMON_PIPERDY_REG);	 \
    i_mtc0_2(0, 20, AUX_PMON_CCLK_REG);\
    i_mtc0_2(1, 20, 0);\
  })
#define PMON_OFF(func) \
  i_mtc0_2(0, 20, 0);				\
  func##_pmon_val_useless_insn += i_mfc0_2(20, AUX_PMON_USELESS_INSN_REG);	\
  func##_pmon_val_piperdy += i_mfc0_2(20, AUX_PMON_PIPERDY_REG);	\
  func##_pmon_val_cclk += i_mfc0_2(20, AUX_PMON_CCLK_REG);

#define PMON_CREAT(func)   \
  uint32_t func##_pmon_val_useless_insn = 0; \
  uint32_t func##_pmon_val_piperdy = 0; \
  uint32_t func##_pmon_val_cclk = 0;

#define PMON_CLEAR(func)   \
  func##_pmon_val_useless_insn = 0; \
  func##_pmon_val_piperdy = 0; \
  func##_pmon_val_cclk = 0;

#else //!defined(JZC_PMON_P1)

#define PMON_ON(func)
#define PMON_OFF(func)
#define PMON_CREAT(func)
#define PMON_CLEAR(func)

#endif //defined(JZC_PMON_P1)


#endif /*__JZ4760_PMON_H__*/
