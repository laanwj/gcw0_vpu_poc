#ifndef __T_VPU_H__
#define __T_VPU_H__
#include "jzasm.h"

#ifdef P1_USE_PADDR
#define VPU_V_BASE          0x13200000
#else
volatile unsigned char *vpu_base;
#define VPU_V_BASE          vpu_base
#endif
#define VPU_P_BASE          0x13200000
extern volatile unsigned char *cpm_base;

#define		CFGC_HID_CFGC		0x0 //0x132
#define		CFGC_HID_GP0		0x1
#define		CFGC_HID_GP1		0x2
#define		CFGC_HID_GP2		0x3
#define		CFGC_HID_MCE		0x5
#define		CFGC_HID_DBLK		0x7
#define		CFGC_HID_VMAU		0x8
#define		CFGC_HID_SDE		0x9
#define		CFGC_HID_AUX		0xA
#define		CFGC_HID_TCSM0		0xB
#define		CFGC_HID_TCSM1		0xC
#define		CFGC_HID_DBLK2		0xD  

#define VPU_GLBC            0x0
#define GLBC_TLBE_SFT       31
#define GLBC_TLBE_MSK       0x1
#define GLBC_ENGM_SFT       10
#define GLBC_ENGM_MSK       0x3
#define GLBC_EPRI_SFT       8
#define GLBC_EPRI_MSK       0x3
#define GLBC_DPRI_SFT       4
#define GLBC_DPRI_MSK       0x7
#define GLBC_CPRI_SFT       0
#define GLBC_CPRI_MSK       0x7

unsigned int tcsm1_word_bank_backup[6]; 
#define SET_VPU_RESET()\
({int i;\
  unsigned int *tcsm1 = tcsm1_base; \
  for(i=0; i<6; i++) tcsm1_word_bank_backup[i] = tcsm1[i*2048];\
  *(volatile int *)(&cpm_base[0x34]) = 0x00000000;\
  *(volatile int *)(&cpm_base[0x4]) = *(volatile int *)(&cpm_base[0x4]) & ~0x40000000;\
  *(volatile unsigned int *)(&cpm_base[0x24])  = (*(volatile unsigned int *)(&cpm_base[0x24]) | (1<<29));\
  do{}while((*(volatile unsigned int *)(&cpm_base[0x24]) & (1<<28)) == 0);\
  *(volatile unsigned int *)(&cpm_base[0x24]) = ((*(volatile unsigned int *)(&cpm_base[0x24]))|1<<30 ) & (~(1<<29));\
  *(volatile unsigned int *)(&cpm_base[0x24]) = ((*(volatile unsigned int *)(&cpm_base[0x24]))) & (~(1<<30));\
  *(volatile unsigned int *)(&cpm_base[0x24]) = ((*(volatile unsigned int *)(&cpm_base[0x24]))) & (~(1<<30));\
  for(i=0; i<6; i++) tcsm1[i*2048] = tcsm1_word_bank_backup[i];\
})

#define SET_VPU_GLBC(tlbe, engm, epri, dpri, cpri)	 \
  ({ write_reg((VPU_V_BASE + VPU_GLBC) , 	 \
      ((tlbe) & GLBC_TLBE_MSK)<<GLBC_TLBE_SFT |		 \
      ((engm) & GLBC_ENGM_MSK)<<GLBC_ENGM_SFT |		 \
      ((epri) & GLBC_EPRI_MSK)<<GLBC_EPRI_SFT |		 \
      ((dpri) & GLBC_DPRI_MSK)<<GLBC_DPRI_SFT |		 \
      ((cpri) & GLBC_CPRI_MSK)<<GLBC_CPRI_SFT );          \
  })
#define GET_VPU_GLBC()     (read_reg(VPU_V_BASE , VPU_GLBC))

#define VPU_MONC            0x4
#define MONC_DID_SFT        20
#define MONC_DID_MSK        0xF
#define MONC_DITEM_SFT      17
#define MONC_DITEM_MSK      0x7
#define MONC_DEN_SFT        16
#define MONC_DEN_MSK        0x1
#define MONC_CID_SFT        4
#define MONC_CID_MSK        0xF
#define MONC_CITEM_SFT      1
#define MONC_CITEM_MSK      0x7
#define MONC_CEN_SFT        0
#define MONC_CEN_MSK        0x1

#define SET_VPU_MONC(did, ditem, den, cid, citem, cen)	 \
  ({ write_reg((VPU_V_BASE + VPU_MONC) , 	 \
      ((did) & MONC_DID_MSK)<<MONC_DID_SFT |		 \
      ((ditem) & MONC_DITEM_MSK)<<MONC_DITEM_SFT |	 \
      ((den) & MONC_DEN_MSK)<<MONC_DEN_SFT |		 \
      ((cid) & MONC_CID_MSK)<<MONC_CID_SFT |		 \
      ((citem) & MONC_CITEM_MSK)<<MONC_CITEM_SFT |	 \
      ((cen) & MONC_CEN_MSK)<<MONC_CEN_SFT );             \
  })
#define GET_VPU_MONC()     (read_reg(VPU_V_BASE , VPU_MONC))

#define VPU_DCNT            0x8
#define VPU_CCNT            0xC
#define CLR_VPU_DCNT()     ({write_reg((VPU_V_BASE + VPU_DCNT) , 0);})
#define CLR_VPU_CCNT()     ({write_reg((VPU_V_BASE + VPU_CCNT) , 0);})
#define GET_VPU_DCNT()     (read_reg(VPU_V_BASE , VPU_DCNT))
#define GET_VPU_CCNT()     (read_reg(VPU_V_BASE , VPU_CCNT))

#define VPU_DBGC            0x10
#define DBGC_DHIT_SFT       31
#define DBGC_DHIT_MSK       0x1
#define DBGC_DID_SFT        20
#define DBGC_DID_MSK        0xF
#define DBGC_DEVT_SFT       16
#define DBGC_DEVT_MSK       0xF
#define DBGC_CHIT_SFT       15
#define DBGC_CHIT_MSK       0x1
#define DBGC_CID_SFT        4
#define DBGC_CID_MSK        0xF
#define DBGC_CEVT_SFT       0
#define DBGC_CEVT_MSK       0xF

#define SET_VPU_DBGC(dhit, did, devt, chit, cid, cevt)	 \
  ({ write_reg((VPU_V_BASE + VPU_DBGC) , 	 \
      ((dhit) & DBGC_DHIT_MSK)<<DBGC_DHIT_SFT |		 \
      ((did) & DBGC_DID_MSK)<<DBGC_DID_SFT |	         \
      ((devt) & DBGC_DEVT_MSK)<<DBGC_DEVT_SFT |		 \
      ((chit) & DBGC_CHIT_MSK)<<DBGC_CHIT_SFT |		 \
      ((cid) & DBGC_CID_MSK)<<DBGC_CID_SFT |	         \
      ((cevt) & DBGC_CEVT_MSK)<<DBGC_CEVT_SFT );          \
  })
#define GET_VPU_DBGC()     (read_reg(VPU_V_BASE , VPU_DBGC))

#define VPU_DWD             0x14
#define VPU_CWD             0x18
#define VPU_DWA             0x1C
#define VPU_CWA             0x20

#define SET_VPU_DWD(dwd)                                 \
  ({ write_reg((VPU_V_BASE + VPU_DWD) , (dwd));	 \
  })
#define SET_VPU_CWD(cwd)                                 \
  ({ write_reg((VPU_V_BASE + VPU_CWD) , (cwd));	 \
  })
#define SET_VPU_DWA(dwa)                                 \
  ({ write_reg((VPU_V_BASE + VPU_DWA) , (dwa));	 \
  })
#define SET_VPU_CWA(cwa)                                 \
  ({ write_reg((VPU_V_BASE + VPU_CWA) , (cwa));	 \
  })
#define GET_VPU_DWD()       (write_reg((VPU_V_BASE , VPU_DWD))
#define GET_VPU_CWD()       (write_reg((VPU_V_BASE , VPU_CWD))
#define GET_VPU_DWA()       (write_reg((VPU_V_BASE , VPU_DWA))
#define GET_VPU_CWA()       (write_reg((VPU_V_BASE , VPU_CWA))

#define VPU_TETY            0x40
#define PSIZE_4M            0
#define PSIZE_8M            1
#define PSIZE_16M           2
#define PSIZE_32M           3

#define VALID_SFT           0
#define VALID_MSK           0x1
#define PSIZE_SFT           1
#define PSIZE_MSK           0x3
#define PTAG_SFT            12
#define PTAG_MSK            0x3FF
#define VTAG_SFT            22
#define VTAG_MSK            0x3FF

#define SET_VPU_TLB(entry, valid, psize, vtag, ptag)	 \
  ({ write_reg((VPU_V_BASE+VPU_TETY+(entry)*4) ,  \
      ((valid) & VALID_MSK)<<VALID_SFT |		 \
      ((psize) & PSIZE_MSK)<<PSIZE_SFT |		 \
      ((vtag ) & VTAG_MSK )<<VTAG_SFT  |                 \
      ((ptag ) & PTAG_MSK )<<PTAG_SFT  );                 \
  })

#define GET_VPU_TLB(entry) (*(volatile int *)(VPU_V_BASE + VPU_TETY + (entry)*4))

#define VPU_SCHC            0x60
#define SCH4_ACT_SFT        31
#define SCH4_ACT_MSK        0x1
#define SCH4_PE1_SFT        30
#define SCH4_PE1_MSK        0x1
#define SCH4_PCH1_SFT       28
#define SCH4_PCH1_MSK       0x3
#define SCH4_PE0_SFT        26
#define SCH4_PE0_MSK        0x1
#define SCH4_PCH0_SFT       24
#define SCH4_PCH0_MSK       0x3
#define SCH3_ACT_SFT        23
#define SCH3_ACT_MSK        0x1
#define SCH3_PE0_SFT        18
#define SCH3_PE0_MSK        0x1
#define SCH3_PCH0_SFT       16
#define SCH3_PCH0_MSK       0x3
#define SCH2_ACT_SFT        15
#define SCH2_ACT_MSK        0x1
#define SCH2_PE0_SFT        10
#define SCH2_PE0_MSK        0x1
#define SCH2_PCH0_SFT       8
#define SCH2_PCH0_MSK       0x3
#define SCH1_ACT_SFT        7
#define SCH1_ACT_MSK        0x1
#define SCH1_PE0_SFT        2
#define SCH1_PE0_MSK        0x1
#define SCH1_PCH0_SFT       0
#define SCH1_PCH0_MSK       0x3
#define SET_VPU_SCHC(sch4_act, sch4_pe1, sch4_pch1,      \
                     sch4_pe0, sch4_pch0,                \
                     sch3_act, sch3_pe0, sch3_pch0,      \
                     sch2_act, sch2_pe0, sch2_pch0,      \
                     sch1_act, sch1_pe0, sch1_pch0)      \
  ({ write_reg((VPU_V_BASE+VPU_SCHC) ,            \
      ((sch4_act) & SCH4_ACT_MSK)<<SCH4_ACT_SFT |	 \
      ((sch4_pe1) & SCH4_PE1_MSK)<<SCH4_PE1_SFT |	 \
      ((sch4_pch1) & SCH4_PCH1_MSK)<<SCH4_PCH1_SFT |	 \
      ((sch4_pe0) & SCH4_PE0_MSK)<<SCH4_PE0_SFT |	 \
      ((sch4_pch0) & SCH4_PCH0_MSK)<<SCH4_PCH0_SFT |	 \
      ((sch3_act) & SCH3_ACT_MSK)<<SCH3_ACT_SFT |	 \
      ((sch3_pe0) & SCH3_PE0_MSK)<<SCH3_PE0_SFT |	 \
      ((sch3_pch0) & SCH3_PCH0_MSK)<<SCH3_PCH0_SFT |	 \
      ((sch2_act) & SCH2_ACT_MSK)<<SCH2_ACT_SFT |	 \
      ((sch2_pe0) & SCH2_PE0_MSK)<<SCH2_PE0_SFT |	 \
      ((sch2_pch0) & SCH2_PCH0_MSK)<<SCH2_PCH0_SFT |	 \
      ((sch1_act) & SCH1_ACT_MSK)<<SCH1_ACT_SFT |	 \
      ((sch1_pe0) & SCH1_PE0_MSK)<<SCH1_PE0_SFT |	 \
      ((sch1_pch0) & SCH1_PCH0_MSK)<<SCH1_PCH0_SFT );	 \
  })

#define GET_VPU_SCHC() (read_reg(VPU_V_BASE , VPU_SCHC))

#define VPU_SCHCS           0x64
#define SCHCS_CS_MSK        0xF
#define SET_VPU_SCHCS(cs4, cs3, cs2, cs1)                \
  ({ write_reg((VPU_V_BASE+VPU_SCHCS) ,                  \
      ((cs4 ) & SCHCS_CS_MSK )<<24  |                    \
      ((cs3 ) & SCHCS_CS_MSK )<<16  |                    \
      ((cs2 ) & SCHCS_CS_MSK )<<8   |                    \
      ((cs1 ) & SCHCS_CS_MSK )<<0   );                   \
  })
#define GET_VPU_SCHCS()     (read_reg(VPU_V_BASE , VPU_SCHCS))

#define VPU_SCHE0           0x6C
#define VPU_SCHE1           0x70
#define VPU_SCHE2           0x74
#define VPU_SCHE3           0x78
#define VPU_SCHE4           0x7C
#define SCHE_SN_SFT         4
#define SCHE_SN_MSK         0x1
#define SCHE_ID_SFT         0
#define SCHE_ID_MSK         0xF
#define SET_VPU_SCHE0(sche_sn, sche_id)	                 \
  ({ write_reg((VPU_V_BASE+VPU_SCHE0) ,           \
      ((sche_sn ) & SCHE_SN_MSK )<<SCHE_SN_SFT  |        \
      ((sche_id ) & SCHE_ID_MSK )<<SCHE_ID_SFT  );        \
  })
#define SET_VPU_SCHE1(sche_sn, sche_id)	                 \
  ({ write_reg((VPU_V_BASE+VPU_SCHE1) ,           \
      ((sche_sn ) & SCHE_SN_MSK )<<SCHE_SN_SFT  |        \
      ((sche_id ) & SCHE_ID_MSK )<<SCHE_ID_SFT  );        \
  })
#define SET_VPU_SCHE2(sche_sn, sche_id)	                 \
  ({ write_reg((VPU_V_BASE+VPU_SCHE2) ,           \
      ((sche_sn ) & SCHE_SN_MSK )<<SCHE_SN_SFT  |        \
      ((sche_id ) & SCHE_ID_MSK )<<SCHE_ID_SFT  );        \
  })
#define SET_VPU_SCHE3(sche_sn, sche_id)	                 \
  ({ write_reg((VPU_V_BASE+VPU_SCHE3) ,           \
      ((sche_sn ) & SCHE_SN_MSK )<<SCHE_SN_SFT  |        \
      ((sche_id ) & SCHE_ID_MSK )<<SCHE_ID_SFT  );        \
  })
#define SET_VPU_SCHE4(sche_sn, sche_id)	                 \
  ({ write_reg((VPU_V_BASE+VPU_SCHE4) ,           \
      ((sche_sn ) & SCHE_SN_MSK )<<SCHE_SN_SFT  |        \
      ((sche_id ) & SCHE_ID_MSK )<<SCHE_ID_SFT  );        \
  })

#define GET_VPU_SCHE0() (read_reg(VPU_V_BASE , VPU_SCHE0))
#define GET_VPU_SCHE1() (read_reg(VPU_V_BASE , VPU_SCHE1))
#define GET_VPU_SCHE2() (read_reg(VPU_V_BASE , VPU_SCHE2))
#define GET_VPU_SCHE3() (read_reg(VPU_V_BASE , VPU_SCHE3))
#define GET_VPU_SCHE4() (read_reg(VPU_V_BASE , VPU_SCHE4))


#define SCH1_DSA  0x13200070
#define SCH2_DSA  0x13200074
#define SCH3_DSA  0x13200078
#define SCH4_DSA  0x1320007C
#endif /*__T_VPU_H__*/
