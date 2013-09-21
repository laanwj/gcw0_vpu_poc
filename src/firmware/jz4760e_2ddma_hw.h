#ifndef __H264_P1_2DDMA_H__
#define __H264_P1_2DDMA_H__

#ifdef P1_USE_PADDR
#define DDMA_GP0_V_BASE 0x13210000
#define DDMA_GP1_V_BASE 0x13220000
#define DDMA_GP2_V_BASE 0x13230000
#else
#define DDMA_GP0_V_BASE 0xB3210000
#define DDMA_GP1_V_BASE 0xB3220000
#define DDMA_GP2_V_BASE 0xB3230000
#endif

#define DDMA_GP_DHA_OFST 0x0
#define DDMA_GP_DCS_OFST 0x4
#define DDMA_GP_GAT_OFST 0x8
#define DDMA_GP_ENDF_MASK 0x4

#define DDMA_GP2_DHA_PHY_ADDR 0x13230000
#define DDMA_GP2_DCS_PHY_ADDR 0x13230004

#define set_gp0_dha(dha) \
  ((volatile int*)(DDMA_GP0_V_BASE+DDMA_GP_DHA_OFST))[0]=(dha);

#define set_gp0_dcs() \
  ((volatile int*)(DDMA_GP0_V_BASE+DDMA_GP_DCS_OFST))[0]=1;

#define set_gp0_gat(gate) \
  ( *(volatile int*)(DDMA_GP0_V_BASE+DDMA_GP_GAT_OFST) = (gate) )

#define poll_gp0_end() \
  while(!(((volatile int*)(DDMA_GP0_V_BASE+DDMA_GP_DCS_OFST))[0]&DDMA_GP_ENDF_MASK));

#define set_gp1_dha(dha) \
  ((volatile int*)(DDMA_GP1_V_BASE+DDMA_GP_DHA_OFST))[0]=(dha);

#define set_gp1_dcs() \
  ((volatile int*)(DDMA_GP1_V_BASE+DDMA_GP_DCS_OFST))[0]=1;

#define set_gp1_gat(gate) \
  ( *(volatile int*)(DDMA_GP1_V_BASE+DDMA_GP_GAT_OFST) = (gate) )

#define poll_gp1_end() \
  while(!(((volatile int*)(DDMA_GP1_V_BASE+DDMA_GP_DCS_OFST))[0]&DDMA_GP_ENDF_MASK));

#define set_gp2_dha(dha) \
  ((volatile int*)(DDMA_GP2_V_BASE+DDMA_GP_DHA_OFST))[0]=(dha);

#define set_gp2_dcs() \
  ((volatile int*)(DDMA_GP2_V_BASE+DDMA_GP_DCS_OFST))[0]=1;

#define set_gp2_gat(gate) \
  ( *(volatile int*)(DDMA_GP2_V_BASE+DDMA_GP_GAT_OFST) = (gate) )

#define poll_gp2_end() \
  while(!(((volatile int*)(DDMA_GP2_V_BASE+DDMA_GP_DCS_OFST))[0]&DDMA_GP_ENDF_MASK));

#define DDR_STRIDE_ADDR 0xB3020034
#define SET_DDR_STRD(strd1,strd0) \
  (*(volatile int *)DDR_STRIDE_ADDR = ( ((strd1) & 0xFFF)<<16 | ((strd0) & 0xFFF)<<0 ))


/*2D-DMA Descriptor-Node Structure*/
/*
     | bit31 | bit30......bit16 | bit15......bit0 |
     +--------------------------------------------+
   0 |<--------          TSA       -------------->|
     +--------------------------------------------+
   4 |<--------          TDA       -------------->|
     +--------------------------------------------+
   8 |<-   TYP    ->|<- TST   ->|<-FRM->|<- TDT ->|
     +--------------------------------------------+
  12 |<-TAG->|<-    TRN       ->|<-  NUM        ->|
     +--------------------------------------------+         
  
  Note:
    TSA: source address
    TDA: destination address
    TYP: transfer type: 00-word, 01-byte, 10-halfword, 11-illegal
    TST: source stride
    FRM: DDR optimize page size setting: 00-N/C, 01-1Kbyte, 10-2Kbyte, 11-4Kbyte
         only souce or destination is DDR can open FRM for optimizing.
    TDT: destination stride
    TAG: Current node Link or Not
    TRN: ROW width for DMA(unit: byte)
    NUM: Total for DMA(unit: byte)   
 */
#define GP_TYP_WORD 0x0

#define GP_FRM_NML 0x0
#define GP_FRM_1K  0x1
#define GP_FRM_2K  0x2
#define GP_FRM_4K  0x3

#define DDR_PSIZE_2K
#if defined(DDR_PSIZE_1K)
# define GP_FRM_OPT GP_FRM_1K
#elif defined(DDR_PSIZE_2K)
# define GP_FRM_OPT GP_FRM_2K
#elif defined(DDR_PSIZE_4K)
# define GP_FRM_OPT GP_FRM_4K
#else
# define GP_FRM_OPT GP_FRM_NML
#endif

#define GP_TAG_LK  0x0
#define GP_TAG_UL  0x1

#define GP_STRD(TST,FRM,TDT)     \
( GP_TYP_WORD<<30                \
| (((TST) & 0x3FFF)<<16)         \
| (((FRM) & 0x3)<<14)            \ 
| ((TDT) & 0x3FFF))

#define GP_UNIT(TAG,TRN,NUM)     \
( (((TAG) & 0x1)<<31)            \
| (((TRN) & 0x7FFF)<<16)         \
| ((NUM) & 0xFFFF))


#endif//#ifndef __H264_P1_2DDMA_H__
