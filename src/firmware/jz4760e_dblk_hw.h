/*****************************************************************************
 *
 * JZ4760 Deblock Filter Accelerate
 *
 * $Id: jz4760e_dblk_hw.h,v 1.1.1.1 2011/03/09 02:17:26 rliu Exp $
 *
 ****************************************************************************/

#ifndef __JZ4760_DBLK_HW_H__
#define __JZ4760_DBLK_HW_H__

#ifdef JZC_RTL_SIM
# include "instructions.h"
#else
# include "jzasm.h"
#endif //JZC_RTL_SIM


// --------------------------------------------------------------
//      Base Address And Offset
// --------------------------------------------------------------
#ifdef P1_USE_PADDR
#define DBLK_BASE 0x13270000
#else
#define DBLK_BASE 0xB3270000
#endif

#define OFST_00 0x00 //DBLK_CTRL
#define OFST_04 0x04 //DATA_FMT
#define OFST_08 0x08 //H264_QP_UY
#define OFST_0C 0x0C //H264_QP_VU
#define OFST_10 0x10 //NNZ
#define OFST_14	0x14 //MV_ADDR
#define OFST_18	0x18 //DEPTH_OFFSET
#define OFST_1C	0x1C //y_up_in_addr;        
#define OFST_20	0x20 //u_up_in_addr;        
#define OFST_24	0x24 //v_up_in_addr;        
#define OFST_28	0x28 //y_up_out_addr;       
#define OFST_2C	0x2C //u_up_out_addr;       
#define OFST_30	0x30 //v_up_out_addr;       
#define OFST_34	0x34 //y_in_addr;           
#define OFST_38	0x38 //u_in_addr;           
#define OFST_3C	0x3C //v_in_addr;           
#define OFST_40	0x40 //y_out_addr;          
#define OFST_44	0x44 //u_out_addr;          
#define OFST_48	0x48 //v_out_addr;          
#define OFST_4C	0x4C
#define OFST_50	0x50
#define OFST_54	0x54
#define OFST_58	0x58
#define OFST_5C	0x5C
#define OFST_60	0x60
#define OFST_64	0x64 //y_up_in_stride;       
#define OFST_68	0x68 //uv_up_in_stride;      
#define OFST_6C	0x6C //y_up_out_stride;      
#define OFST_70	0x70 //uv_up_out_stride;     
#define OFST_74	0x74 //y_in_stride;          
#define OFST_78	0x78 //uv_in_stride;         
#define OFST_7C	0x7C //y_out_stride;         
#define OFST_80	0x80 //uv_out_stride;        

#define OFST_90	0x90 //BS_EDGE_7_0
#define OFST_94	0x94 //BS_EDGE_15_8
#define OFST_98	0x98 //BS_EDGE_23_16
#define OFST_9C	0x9C //BS_EDGE_31_24
#define OFST_130 0x130 //HW BS_EDGE_7_0
#define OFST_134 0x134 //HW BS_EDGE_15_8
#define OFST_138 0x138 //HW BS_EDGE_23_16
#define OFST_13C 0x13C //HW BS_EDGE_31_24
#define OFST_140 0x140 //BS FSM

#define OFST_AB 0xA0 
#define OFST_TC0 0xE8 

#define OFST_DCS 0x84
#define OFST_DHA 0x88
#define OFST_CSA 0x8C


// --------------------------------------------------------------
//      TABLE
// --------------------------------------------------------------


//static const int alph_table[52] = {
//  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
//  0,   0,   0,   0,   0,   0,   4,   4,   5,   6,
//  7,   8,   9,  10,  12,  13,  15,  17,  20,  22,
//  25,  28,  32,  36,  40,  45,  50,  56,  63,  71,
//  80,  90, 101, 113, 127, 144, 162, 182, 203, 226,
//  255, 255
//};
//
//static const int beta_table[52] = {
//   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//   0,  0,  0,  0,  0,  0,  2,  2,  2,  3,
//   3,  3,  3,  4,  4,  4,  6,  6,  7,  7,
//   8,  8,  9,  9, 10, 10, 11, 11, 12, 12,
//  13, 13, 14, 14, 15, 15, 16, 16, 17, 17,
//  18, 18
//};

//static const int tc0_table[52][3] = {
//  { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 
//  { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 
//  { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
//  { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
//  { 0, 0, 0 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, 
//  { 0, 0, 1 }, { 0, 1, 1 }, { 0, 1, 1 }, { 1, 1, 1 },
//  { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 2 }, 
//  { 1, 1, 2 }, { 1, 1, 2 }, { 1, 1, 2 }, { 1, 2, 3 }, 
//  { 1, 2, 3 }, { 2, 2, 3 }, { 2, 2, 4 }, { 2, 3, 4 },
//  { 2, 3, 4 }, { 3, 3, 5 }, { 3, 4, 6 }, { 3, 4, 6 },
//  { 4, 5, 7 }, { 4, 5, 8 }, { 4, 6, 9 }, { 5, 7,10 }, 
//  { 6, 8,11 }, { 6, 8,13 }, { 7,10,14 }, { 8,11,16 },
//  { 9,12,18 }, {10,13,20 }, {11,15,23 }, {13,17,25 }
//};



// =================================================================
//
//                      Set IO Registers
//
// =================================================================
#define SET_DBLK_REG00( mntn_addr_only, tx_always,              \
                        mntn_mb_out, mb_out_echg, mb_out_wrap,  \
                        mntn_mb_in, mb_in_echg, mb_in_wrap,     \
                        mntn_mb_up_out, mb_up_out_incr,         \
                        mntn_mb_up_in, mb_up_in_incr,           \
                        dblk_ctrl )                             \
    ({write_reg((DBLK_BASE + OFST_00),                          \
                ((mntn_addr_only << 31) |                       \
                 (tx_always << 30)      |                       \
                 (mntn_mb_out << 29)    |                       \
                 (mb_out_echg << 28)    |                       \
                 (mb_out_wrap << 27)    |                       \
                 (mntn_mb_in << 26)     |                       \
                 (mb_in_echg << 25)     |                       \
                 (mb_in_wrap << 24)     |                       \
                 (mntn_mb_up_out << 23) |                       \
                 (mb_up_out_incr << 22) |                       \
                 (mntn_mb_up_in << 21)  |                       \
                 (mb_up_in_incr << 20)  |                       \
                 dblk_ctrl) );})
   



#define SET_DBLK_REG04( mv_smooth, edge_mask, row_end,		\
                        yuv_flag, dma_cfg_bs, mv_reduce,	\
                        intra_left, intra_curr, intra_up,	\
                        hw_bs_h264, video_fmt)              \
    ({write_reg((DBLK_BASE + OFST_04),                      \
                ((mv_smooth << 24) |                        \
                 (edge_mask << 16) |                        \
                 (row_end << 15)   |                        \
                 (yuv_flag << 8)   |                        \
                 (dma_cfg_bs << 7) |                        \
                 (mv_reduce << 6)  |                        \
                 (intra_left << 5) |                        \
                 (intra_curr << 4) |                        \
                 (intra_up << 3)   |                        \
                 (hw_bs_h264 << 2) |                        \
                 video_fmt));})

#define SET_DBLK_REG08( u_qp_up, y_qp_left, y_qp_curr, y_qp_up)	\
  ({write_reg((DBLK_BASE + OFST_08),				\
	      ((u_qp_up << 18) 	 |				\
	       (y_qp_left << 12) |				\
	       (y_qp_curr << 6)  |				\
	       y_qp_up));})

#define SET_DBLK_REG0C( v_qp_left, v_qp_curr, u_qp_up,	\
			u_qp_left, u_qp_curr)		\
  ({write_reg((DBLK_BASE + OFST_0C),			\
	      ((v_qp_left << 24) |			\
	       (v_qp_curr << 18) |			\
	       (v_qp_up << 12)   |			\
	       (u_qp_left << 6)  |			\
	       u_qp_curr));})

#define SET_DBLK_REG10(nnz) ({write_reg((DBLK_BASE + OFST_10),	\
                                        nnz); })

//mv_addr
#define SET_DBLK_REG14(addr) ({write_reg((DBLK_BASE + OFST_14), \
                                        addr); })

#define SET_DBLK_REG18(offset_a, offset_b, b_slice)	\
  ({write_reg((DBLK_BASE + OFST_18),			\
	      (((offset_a & 0xff) << 24) |		\
	       ((offset_b & 0xff) << 16) |		\
	       b_slice));})

#define SET_DBLK_REG1C(addr) ({write_reg((DBLK_BASE + OFST_1C), \
                                        addr); })

#define SET_DBLK_REG90( edge7, edge6, edge5, edge4,	\
			edge3, edge2, edge1, edge0)	\
  ({write_reg((DBLK_BASE + OFST_90),			\
	      ((edge7 << 28) +				\
	       (edge6 << 24) +				\
	       (edge5 << 20) +				\
	       (edge4 << 16) +				\
	       (edge3 << 12) +				\
	       (edge2 << 8) +				\
	       (edge1 << 4) +				\
	       edge0));})

#define SET_DBLK_REG94(edge15, edge14, edge13, edge12,	\
		       edge11, edge10, edge9, edge8)	\
  ({write_reg((DBLK_BASE + OFST_94),			\
	      ((edge15 << 28) +				\
	       (edge14 << 24) +				\
	       (edge13 << 20) +				\
	       (edge12 << 16) +				\
	       (edge11 << 12) +				\
	       (edge10 << 8) +				\
	       (edge9 << 4) +				\
	       edge8));})

#define SET_DBLK_REG98(edge23, edge22, edge21, edge20,	\
		       edge19, edge18, edge17, edge16)	\
  ({write_reg((DBLK_BASE + OFST_98),			\
	      ((edge23 << 28) +				\
	       (edge22 << 24) +				\
	       (edge21 << 20) +				\
	       (edge20 << 16) +				\
	       (edge19 << 12) +				\
	       (edge18 << 8) +				\
	       (edge17 << 4) +				\
	       edge16));})

#define SET_DBLK_REG9C(edge31, edge30, edge29, edge28,	\
		       edge27, edge26, edge25, edge24)	\
  ({write_reg((DBLK_BASE + OFST_9C),			\
	      ((edge31 << 28) +				\
	       (edge30 << 24) +				\
	       (edge29 << 20) +				\
	       (edge28 << 16) +				\
	       (edge27 << 12) +				\
	       (edge26 << 8) +				\
	       (edge25 << 4) +				\
	       edge24));})


#define SET_AB_LUT(offset, ab) \
({write_reg((DBLK_BASE + OFST_AB + offset), ab);})

#define SET_TC0_LUT(offset, tc0) \
({write_reg((DBLK_BASE + OFST_TC0 + offset), tc0);})


#define SET_DBLK_DCS(val)			\
({write_reg((DBLK_BASE + OFST_DCS), val);})

#define SET_DBLK_DHA(val) \
({write_reg((DBLK_BASE + OFST_DHA), val);})

#define SET_DBLK_CSA(val) \
({write_reg((DBLK_BASE + OFST_CSA), val);})

#define RUN_DBLK() \
({ write_reg( (DBLK_BASE +  OFST_00), (read_reg(DBLK_BASE, OFST_00)) | 0x1); \
})


// =================================================================
//
//                      Read IO Registers
//
// =================================================================

#define READ_DBLK_REG00()                       \
    ({ (read_reg(DBLK_BASE, OFST_00));          \
    })
#define READ_DBLK_REG04()                       \
    ({ (read_reg(DBLK_BASE, OFST_04));          \
    })
#define READ_DBLK_REG08()                       \
    ({ (read_reg(DBLK_BASE, OFST_08));          \
    })
#define READ_DBLK_REG0C()                       \
    ({ (read_reg(DBLK_BASE, OFST_0C));          \
    })
#define READ_DBLK_REG10()                       \
    ({ (read_reg(DBLK_BASE, OFST_10));          \
    })
#define READ_DBLK_REG14()                       \
    ({ (read_reg(DBLK_BASE, OFST_14));          \
    })
#define READ_DBLK_REG18()                       \
    ({ (read_reg(DBLK_BASE, OFST_18));          \
    })
#define READ_DBLK_REG1C()                       \
    ({ (read_reg(DBLK_BASE, OFST_1C));          \
    })
#define READ_DBLK_REG90()                       \
    ({ (read_reg(DBLK_BASE, OFST_90));          \
    })
#define READ_DBLK_REG94()                       \
    ({ (read_reg(DBLK_BASE, OFST_94));          \
    })
#define READ_DBLK_REG98()                       \
    ({ (read_reg(DBLK_BASE, OFST_98));          \
    })
#define READ_DBLK_REG9C()                       \
    ({ (read_reg(DBLK_BASE, OFST_9C));          \
    })
#define READ_DBLK_REG130()                       \
    ({ (read_reg(DBLK_BASE, OFST_130));          \
    })
#define READ_DBLK_REG134()                       \
    ({ (read_reg(DBLK_BASE, OFST_134));          \
    })
#define READ_DBLK_REG138()                       \
    ({ (read_reg(DBLK_BASE, OFST_138));          \
    })
#define READ_DBLK_REG13C()                       \
    ({ (read_reg(DBLK_BASE, OFST_13C));          \
    })
#define READ_DBLK_REG140()                       \
    ({ (read_reg(DBLK_BASE, OFST_140));          \
    })
#define READ_AB_LUT(offset)			 \
  ({ (read_reg(DBLK_BASE, OFST_AB + offset));	 \
  })


#define READ_DBLK_DCS()				\
    ({ (read_reg(DBLK_BASE, OFST_DCS));         \
    })
#define READ_DBLK_DHA()				\
    ({ (read_reg(DBLK_BASE, OFST_DHA));         \
    })
#define READ_DBLK_CSA()				\
    ({ (read_reg(DBLK_BASE, OFST_CSA));         \
    })

#define POLLING_DBLK_END_FLAG()			\
  ({ while(!((read_reg(DBLK_BASE, OFST_00)) & 0x4));	\
  })


// =================================================================
//
//                      Patch Register Content
//
// =================================================================

#define DBLK_REG04( mv_smooth, edge_mask, row_end,	\
                    yuv_flag, dma_cfg_bs, mv_reduce,	\
                    intra_left, intra_curr, intra_up,	\
                    hw_bs_h264, video_fmt)              \
    ((mv_smooth << 24) |                                \
     (edge_mask << 16) |                                \
     (row_end << 15)   |                                \
     (yuv_flag << 8)   |                                \
     (dma_cfg_bs << 7) |                                \
     (mv_reduce << 6)  |                                \
     (intra_left << 5) |                                \
     (intra_curr << 4) |                                \
     (intra_up << 3)   |                                \
     (hw_bs_h264 << 2) |                                \
     video_fmt)

#define DBLK_REG08( mv_len, u_qp_up, y_qp_left, y_qp_curr, y_qp_up)	\
  ((mv_len << 24)    |							\
   (u_qp_up << 18)   |							\
   (y_qp_left << 12) |							\
   (y_qp_curr << 6)  |							\
   y_qp_up)

#define DBLK_REG0C( v_qp_left, v_qp_curr, v_qp_up,	\
		    u_qp_left, u_qp_curr)		\
  ((v_qp_left << 24) |					\
   (v_qp_curr << 18) |					\
   (v_qp_up << 12)   |					\
   (u_qp_left << 6)  |					\
   u_qp_curr)

#define DBLK_REG10( mv_mask, nnz)               \
    ((mv_mask << 24) |                          \
     nnz)

#define DBLK_REG18(offset_a, offset_b, b_slice)		\
	      (((offset_a & 0xff) << 24) |		\
	       ((offset_b & 0xff) << 16) |		\
	       b_slice)

#define Y_NUM_STRD(mb_num, strd)		        \
              (((mb_num & 0xff) << 16) |	        \
	       strd)

#define H264_EDGE_BS( edge7, edge6, edge5, edge4,	\
		     edge3, edge2, edge1, edge0)	\
  (((edge7 & 0xf) << 28) |					\
   ((edge6 & 0xf) << 24) |					\
   ((edge5 & 0xf) << 20) |					\
   ((edge4 & 0xf) << 16) |					\
   ((edge3 & 0xf) << 12) |					\
   ((edge2 & 0xf) << 8) |					\
   ((edge1 & 0xf) << 4) |					\
   (edge0 & 0xf))


#endif /*__JZ4760_DBLK_HW_H__*/


