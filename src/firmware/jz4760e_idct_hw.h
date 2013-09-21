/*****************************************************************************
 *
 * JZ4760 IDCT/INTRA Accelerate
 *
 * $Id: jz4760e_idct_hw.h,v 1.1.1.1 2011/03/09 02:17:26 rliu Exp $
 *
 ****************************************************************************/

#ifndef __JZ4760_IDCT_HW_H__
#define __JZ4760_IDCT_HW_H__

#ifdef _RTL_SIM_
# include "instructions.h"
#else
# include "jzasm.h"
#endif //JZC_RTL_SIM

// IDCT_REG_BASE
#ifdef P1_USE_PADDR
#define IDCT_V_BASE 0x13280000
#else
#define IDCT_V_BASE 0xB3280000
#endif

// chain dsph
#define DSPH_DTC_SFT 0x4
#define DSPH_DTC_MSK 0x7F
#define DSPH_CY_SFT 0x1
#define DSPH_CY_MSK 0x1
#define DSPH_LINK_SFT 0x0
#define DSPH_LINK_MSK 0x1

// chain addr
#define DSPA_OFST_SFT 0x18
#define DSPA_OFST_MSK 0x7F
#define DSPH_MASK_SFT 0x0
#define DSPH_MASK_MSK 0xFFFFFF

#define IDCT_GCSR_REG 0x60
#define REG_GCSR IDCT_GCSR_REG


#define IDCT_END_REG 0x64
#define REG_END IDCT_END_REG

#define IDCT_DHA_REG 0x68
#define REG_DDMA_DHA IDCT_DHA_REG

#define IDCT_STR_REG 0x6C
#define REG_STR IDCT_STR_REG


#define IDCT_BOFT_REG 0x70
#define REG_BOFT IDCT_BOFT_REG

#define IDCT_VTR_REG 0x74
#define REG_VTR IDCT_VTR_REG

#define IDCT_DCS_REG 0x78
#define REG_IDCT_DCS IDCT_DCS_REG

#define IDCT_CSA_REG 0x7C

#define IDCT_INPUT_REG 0xC
#define REG_INPUT_ADDR IDCT_INPUT_REG

#define IDCT_OUTPUT_REG 0x10
#define REG_OUT_ADDR IDCT_OUTPUT_REG

#define IDCT_CBP_REG 0x14
#define REG_CBP IDCT_CBP_REG

#define IDCT_T_CBP_REG 0x18
#define IDCT_LT_SFT 24
#define IDCT_LT_MSK 0xFF
#define IDCT_TCBP_SFT 0
#define IDCT_TCBP_MSK 0xFFFFFF

#define IDCT_PRED8_LT_REG 0x1C


#define IDCT_PRED_TYPE0_REG 0x20
#define IDCT_PRED_TYPE1_REG 0x24
//#define IDCT_PRED_TYPE2_REG 0x28

#define IDCT_TOP0_REG 0x28
#define IDCT_LEFT0_REG 0x2C
#define IDCT_TOP1_REG 0x30
#define IDCT_LEFT1_REG 0x34
#define IDCT_TOP2_REG 0x38
#define IDCT_LEFT2_REG 0x3C
#define IDCT_TOP3_REG 0x40
#define IDCT_LEFT3_REG 0x44
#define IDCT_TOP4_REG 0x48
#define IDCT_TOP5_REG 0x4C

#define VERT_PRED             0
#define HOR_PRED              1
#define DC_PRED               2
#define DIAG_DOWN_LEFT_PRED   3
#define DIAG_DOWN_RIGHT_PRED  4
#define VERT_RIGHT_PRED       5
#define HOR_DOWN_PRED         6
#define VERT_LEFT_PRED        7
#define HOR_UP_PRED           8

#define LEFT_DC_PRED          9
#define TOP_DC_PRED           10
#define DC_128_PRED           11

#define DIAG_DOWN_LEFT_PRED_RV40_NODOWN   12
#define HOR_UP_PRED_RV40_NODOWN           13

#define DC_PRED8x8            0
#define HOR_PRED8x8           1
#define VERT_PRED8x8          2
#define PLANE_PRED8x8         3

#define LEFT_DC_PRED8x8       4
#define TOP_DC_PRED8x8        5
#define DC_128_PRED8x8        6



//DCS
/*
#define DDMA_DCS_DMAE_SFT 0x0
#define DDMA_DCS_DMAE_MSK 0x1
#define DDMA_DCS_IE_SFT 0x1
#define DDMA_DCS_IE_MSK 0x1
#define DDMA_DCS_TT_SFT 0x2
#define DDMA_DCS_TT_MSK 0x1
#define DDMA_DCS_IRQ_SFT 0x3
#define DDMA_DCS_IRQ_MSK 0x1
#define DDMA_DCS_LINK_SFT 0x4
#define DDMA_DCS_LINK_MSK 0x1
*/

// GCSR

#define IDCT_EN_SFT 0x0
#define IDCT_EN_MSK 0x1
#define IDCT_START_SFT 0x1
#define IDCT_START_MSK 0x1
#define IDCT_DESP_SFT 0x2
#define IDCT_DESP_MSK 0x1
#define IDCT_IRQ_EN_SFT 0x3
#define IDCT_IRQ_EN_MSK 0x1
#define IDCT_FRESH_SFT 0x4
#define IDCT_FRESH_MSK 0x1

#define IDCT_ERRO_SFT 0x18
#define IDCT_ERRO_MSK 0x3
#define IDCT_NOGATE_SFT 31
#define IDCT_NOGATE_MSK 1

//END

// DHA
#define DDMA_DHA_SFT 0x0
#define DDMA_DHA_MSK 0xFFFFFFFF


// VTR 

#define IDCT_TYPE_SFT 0x0
#define IDCT_TYPE_MSK 0x3
#define IDCT_VIDEO_SFT 0x10
#define IDCT_VIDEO_MSK 0x3


#define IDCT_DCS_EN_SFT 0x0
#define IDCT_DCS_EN_MSK 0x1
#define IDCT_DCS_RST_SFT 0x1
#define IDCT_DCS_RST_MSK 0x1


#define DDMA_NODE_DTC_SFT 0x10
#define DDMA_NODE_DTC_MSK 0x3F
#define DDMA_NODE_DONE_SFT 0x6
#define DDMA_NODE_DONE_MSK 0x1
#define DDMA_NODE_NDTYPE_SFT 0x4
#define DDMA_NODE_NDTYPE_MSK 0x3
#define DDMA_NODE_HSK_SFT 0x3
#define DDMA_NODE_HSK_MSK 0x1
#define DDMA_NODE_CKG_SFT 0x2
#define DDMA_NODE_CKG_MSK 0x1
#define DDMA_NODE_NDCY_SFT 0x1
#define DDMA_NODE_NDCY_MSK 0x1
#define DDMA_NODE_LINK_SFT 0x0
#define DDMA_NODE_LINK_MSK 0x1
#define DDMA_NODE_CSA_SFT 0x18
#define DDMA_NODE_CSA_MSK 0xFF




#define HAMA 0x0
#define H264 0x1
#define REAL 0x2
#define WMV 0x3

// INPUT_ADDR


// OUT_ADDR


// STRIDE

#define IN_STR_SFT 0x0
#define IN_STR_MSK 0xFF
#define OUT_STR_SFT 0x10
#define OUT_STR_MSK 0xFF

//BOFT

#define INPUT_BOFT_SFT 0x0
#define INPUT_BOFT_MSK 0x1FF
#define OUTPUT_BOFT_SFT 0x10
#define OUTPUT_BOFT_MSK 0x1FF


#define CBP_SFT 0x0
#define CBP_MSK 0xFFFFFF
#define M_TYPE_SFT 0x18
#define M_TYPE_MSK 0x3
#define PREDIC_SFT 28
#define PREDIC_MSK 1

#define IDCT_CBP(pred_en, m_type, cbp)\
(((m_type & M_TYPE_MSK) << M_TYPE_SFT)	\
|((cbp & CBP_MSK) << CBP_SFT)\
|((pred_en & PREDIC_MSK) << PREDIC_SFT))


#define IDCT_TCBP(lt, tcbp)\
(((lt & IDCT_LT_MSK) << IDCT_LT_SFT)	\
|((tcbp & IDCT_TCBP_MSK) << IDCT_TCBP_SFT))


#define nod_head(node_done, csa, link, cy, ckg, hsk, ndtype, dtc)	\
((((link & DDMA_NODE_LINK_MSK) << DDMA_NODE_LINK_SFT )\
| ((cy & DDMA_NODE_NDCY_MSK) << DDMA_NODE_NDCY_SFT )\
| ((ckg & DDMA_NODE_CKG_MSK) << DDMA_NODE_CKG_SFT )\
| ((hsk & DDMA_NODE_HSK_MSK) << DDMA_NODE_HSK_SFT )\
| ((ndtype & DDMA_NODE_NDTYPE_MSK) << DDMA_NODE_NDTYPE_SFT)\
| ((dtc & DDMA_NODE_DTC_MSK) << DDMA_NODE_DTC_SFT)\
| ((csa & DDMA_NODE_CSA_MSK) << DDMA_NODE_CSA_SFT )\
| ((node_done & DDMA_NODE_DONE_MSK ) << DDMA_NODE_DONE_SFT ))\
)

#define run_idct_ddma() \
({write_reg((IDCT_V_BASE + REG_IDCT_DCS), IDCT_DCS_EN_MSK);	\
})

#define set_idct_type_video(video, type) \
({ write_reg( (IDCT_V_BASE + REG_VTR), ((type & IDCT_TYPE_MSK)<<IDCT_TYPE_SFT)| \
((video & IDCT_VIDEO_MSK)<<IDCT_VIDEO_SFT)); \
})

#define set_idct_ddma_dha(dha) \
({ write_reg( (IDCT_V_BASE + REG_DDMA_DHA), ((dha & DDMA_DHA_MSK)<<DDMA_DHA_SFT)); \
})

#define set_idct_ddma_chain_header(addr, link, cy, dtc) \
({ addr = ((link & DSPH_LINK_MSK)<<DSPH_LINK_SFT)| \
((cy & DSPH_CY_MSK)<<DSPH_CY_SFT)| \
((dtc & DSPH_DTC_MSK)<<DSPH_DTC_SFT); \
})

#define set_idct_ddma_chain_nod_addr(addr, ofst, mask) \
({ addr = ofst ;\
})

#define set_idct_ddma_chain_nod_data_ctrl(addr, type, video) \
({ addr =  ((type & IDCT_TYPE_MSK)<<IDCT_TYPE_SFT)| \
((video & IDCT_VIDEO_MSK)<<IDCT_VIDEO_SFT); \
})

#define set_idct_input_addr(input_addr) \
({ write_reg( (IDCT_V_BASE + REG_INPUT_ADDR), input_addr); \
})

#define set_idct_out_addr(out_addr) \
({ write_reg( (IDCT_V_BASE + REG_OUT_ADDR), out_addr); \
})

#define set_idct_stride(input_stride, out_stride)			    \
  ({ write_reg( (IDCT_V_BASE + REG_STR), ((input_stride & IN_STR_MSK))| \
		((out_stride & OUT_STR_MSK)<<OUT_STR_SFT));\
})

#define fresh_idct(flag) \
({ write_reg( (IDCT_V_BASE + REG_GCSR), ((read_reg(IDCT_V_BASE, REG_GCSR)) \
& (~(IDCT_FRESH_MSK<<IDCT_FRESH_SFT))| \
((flag & IDCT_FRESH_MSK) <<IDCT_FRESH_SFT))); \
})

#define irq_enable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), ((read_reg(IDCT_V_BASE, REG_GCSR)) \
&(~(IDCT_IRQ_EN_MSK<<IDCT_FRESH_SFT))) \
| (IDCT_IRQ_EN_MSK<<IDCT_IRQ_EN_SFT)); \
})

#define desp_enable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) \
| (IDCT_DESP_MSK<<IDCT_DESP_SFT)); \
})

#define desp_disable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) \
& (~(IDCT_DESP_MSK<<IDCT_DESP_SFT)));			\
})


#define irq_disable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) \
& (~(IDCT_IRQ_EN_MSK<<IDCT_IRQ_EN_SFT))); \
})

#define run_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) | 0x2); \
})

#define enable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) | 0x1); \
})

#define disable_idct() \
({ write_reg( (IDCT_V_BASE + REG_GCSR), (read_reg(IDCT_V_BASE, REG_GCSR)) & ~0x1); \
})

#define idct_polling_end_flag() \
({ do{}\
while((read_reg(IDCT_V_BASE, REG_END)) == 0);	\
})

#define clean_idct_end_flag() \
({ write_reg( (IDCT_V_BASE + REG_END), 0); \
})

#define set_idct_block_width(src_block_w, out_block_w)\
({write_reg((IDCT_V_BASE + REG_BOFT), ((src_block_w& INPUT_BOFT_MSK)<<INPUT_BOFT_SFT)\
| ((out_block_w & OUTPUT_BOFT_MSK) << OUTPUT_BOFT_SFT));\
})

#define set_idct_cbp(pred, m_type, cbp)					\
({write_reg((IDCT_V_BASE + REG_CBP), IDCT_CBP(pred, m_type, cbp));	\
})
#define disable_idct_clk_gate()\
({ write_reg( (IDCT_V_BASE + REG_GCSR), ((read_reg(IDCT_V_BASE, REG_GCSR)) \
|(IDCT_NOGATE_MSK << IDCT_NOGATE_SFT) )\
); \
})
#define DCT_REG(offset) (*((unsigned int *)(IDCT_V_BASE+offset)))
#define INTRA_4x4_NOD_HEAD 0x4810004D
#define INTRA_8x8_NOD_HEAD 0x4C11004D
#define INTER_NOD_HEAD 0x14030048//ckg=0, addrnode will boot

#endif /*__JZ4760_IDCT_HW_H__*/
