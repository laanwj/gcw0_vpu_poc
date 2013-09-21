#ifndef _COM_CONFIG_H_
#define _COM_CONFIG_H_

#define EDGE_WIDTH 32

#define JZ4765_OPT
#define JZ4760_OPT
#define JZ4750_OPT
#define JZ47_OPT
#define JZ4740_IPU
#define JZC_SYS

//#define JZC_CRC_VER
#define JZC_HW_MEDIA
#define JZ_LINUX_OS
#ifdef USE_IPU_THROUGH_MODE
#define USE_FBUF_NUM 6
#endif

//#define JZC_PMON_P0
//#define STA_CCLK
//#define STA_DCC
//#define STA_ICC
//#define STA_UINSN
//#define STA_INSN
//#define STA_UINSN
//#define STA_TLB

#ifdef JZ4740_IPU
/* if use h264 cabac hw on linux, this macro must be open. */
#define JZC_BS_HW_OPT
#endif

#define JZC_ROTA90_OPT
#define JZC_LINE_OPT

#endif
