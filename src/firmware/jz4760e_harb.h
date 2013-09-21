#ifdef _RTL_SIM_
# include "instructions.h"
#else
# include "jzasm.h"
#endif //JZC_RTL_SIM

// IDCT_REG_BASE
#define AHB0_ARB_PADDR 0x13000000
#define AHB1_ARB_PADDR 0x13200000
#define AHB2_ARB_PADDR 0x13400000

#ifdef P1_USE_PADDR
#define AHB0_ARB_VADDR 0x13000000
#define AHB1_ARB_VADDR 0x13200000
#define AHB2_ARB_VADDR 0x13400000
#else
#define AHB0_ARB_VADDR 0xB3000000
#define AHB1_ARB_VADDR 0xB3200000
#define AHB2_ARB_VADDR 0xB3400000
#endif

#define ABME_BTC 0 // bus transaction cycle
#define ABME_BTT 1 // bus transaction TIME
#define ABME_GRL 2 // grant latence
#define ABME_CGRL 3 // critical grant latence
#define ABME_SIBT 4 // single transcation times
#define ABME_FILT 5 // burst 4, 8, 16 transaction times
#define ABME_INCT 6 // increament transaction times
#define ABME_CTCT 7 // critical transaction cycles trigger


#define AHB0_ID_CIM 0
#define AHB0_ID_LCD 1
#define AHB0_ID_IPU 2
#define AHB0_ID_CORE1 3
#define AHB0_ID_DMA 4
#define AHB0_ID_CABAC 5
#define AHB0_ID_CORE0 6
#define AHB0_ID_MDMA0 7
#define AHB0_ID_MDMA1 8
#define AHB0_ID_MDMA2 9
#define AHB0_ID_AHB0_AHB2_BRI 10
#define AHB0_ID_ALL 15


#define AHB1_ID_CORE0 0
#define AHB1_ID_IDCT 1
#define AHB1_ID_MC 2
#define AHB1_ID_ME 3
#define AHB1_ID_DBLK 4
#define AHB1_ID_MDMA2 5
#define AHB1_ID_MDMA1 6
#define AHB1_ID_MDMA0 7
#define AHB1_ID_CABAC 8
#define AHB1_ID_CORE1 9
#define AHB1_ID_ALL 15

#define ARB_ADDR 0

#define ARB_CTRL 0x4
#define ARB_CTRL_CLKE_OFT 0x0
#define ARB_CTRL_CLKE_MSK 0x1
#define ARB_CTRL_EVE0E_OFT 0x1
#define ARB_CTRL_EVE0E_MSK 0x1
#define ARB_CTRL_EVE1E_OFT 0x2
#define ARB_CTRL_EVE1E_MSK 0x1

#define ARB_CTRL_EVE0_OFT 0x8
#define ARB_CTRL_EVE0_MSK 0xF

#define ARB_CTRL_EVE1_OFT 12
#define ARB_CTRL_EVE1_MSK 0xF

#define ARB_CTRL_M0_OFT 16
#define ARB_CTRL_M0_MSK 0xF

#define ARB_CTRL_M1_OFT 20
#define ARB_CTRL_M1_MSK 0xF

#define ARB_CLKL 0x8
#define ARB_EVEN0L 0xC
#define ARB_EVEN1L 0x10

#define ARB_EVENH 0x14
#define ARB_EVENH_EV0_OFT 0x0
#define ARB_EVENH_EV0_MSK 0xFF

#define ARB_EVENH_EV1_OFT 0x8
#define ARB_EVENH_EV1_MSK 0xFF

#define ARB_EVENH_CLK_OFT 0x10
#define ARB_EVENH_CLK_MSK 0xFFFF


#define ARB_WATCHCTRL 0x18

#define ARB_WATCHADDR 0x1C
#define ARB_WATCHMSK 0x20
#define ARB_WATCHDATA 0x24
#define ARB_WATCHDMSK 0x28


#define arb_clk_ctrl(arbid, en)\
({write_reg(( arbid##_ARB_VADDR + ARB_CTRL), (((read_reg(arbid##_ARB_VADDR, ARB_CTRL))\
& (~ARB_CTRL_CLKE_MSK)) | (en & ARB_CTRL_CLKE_MSK)));\
})

#define arb_chn0_even_ctrl(arbid, masterid, evnetid, en)			\
({write_reg((arbid##_ARB_VADDR + ARB_CTRL), (((read_reg(arbid##_ARB_VADDR, ARB_CTRL)) \
& (~((ARB_CTRL_EVE0E_MSK<<ARB_CTRL_EVE0E_OFT) | (ARB_CTRL_EVE0_MSK << ARB_CTRL_EVE0_OFT)  | (ARB_CTRL_M0_MSK << ARB_CTRL_M0_OFT))))\
| (( (en &ARB_CTRL_EVE0E_MSK)<<ARB_CTRL_EVE0E_OFT) | ((masterid & ARB_CTRL_M0_MSK) <<ARB_CTRL_M0_OFT) \
| ((evnetid & ARB_CTRL_EVE0_MSK) <<ARB_CTRL_EVE0_OFT))));\
})

#define arb_chn1_even_ctrl(arbid, masterid, evnetid, en)			\
({write_reg((arbid##_ARB_VADDR + ARB_CTRL), (((read_reg(arbid##_ARB_VADDR, ARB_CTRL)) \
& (~((ARB_CTRL_EVE1E_MSK<<ARB_CTRL_EVE1E_OFT) | (ARB_CTRL_EVE1_MSK << ARB_CTRL_EVE1_OFT)  | (ARB_CTRL_M1_MSK << ARB_CTRL_M1_OFT))))\
| (((en & ARB_CTRL_EVE1E_MSK)<<ARB_CTRL_EVE1E_OFT) | ((masterid & ARB_CTRL_M1_MSK) <<ARB_CTRL_M1_OFT) \
| ((evnetid & ARB_CTRL_EVE1_MSK) <<ARB_CTRL_EVE1_OFT))));		\
})

#define arb_ch0_evenl_wr(arbid, value)\
({write_reg((arbid##_ARB_VADDR + ARB_EVEN0L), value);\
})

#define arb_ch1_evenl_wr(arbid, value)\
({write_reg((arbid##_ARB_VADDR + ARB_EVEN1L), value);\
})

#define arb_ch1_clk_wr(arbid, value)\
({write_reg((arbid##_ARB_VADDR + ARB_CLKL), value);\
})

#define arb_eveclk_h_wr(arbid, value)\
({write_reg((arbid##_ARB_VADDR + ARB_EVENH), value);\
})

#define arb_reg(arbid, offset) (*(volatile unsigned int *)(arbid##_ARB_VADDR + offset ))

#define report_c0_result(arbid)\
({\
  printf ("--chn0-- MID: %d, Mvalue: %d\n", ((read_reg(arbid##_ARB_VADDR, ARB_CTRL)>>ARB_CTRL_M0_OFT)& ARB_CTRL_M0_MSK), read_reg(arbid##_ARB_VADDR, ARB_EVEN0L)); \
})

#define report_c1_result(arbid)\
({\
  printf ("--chn1-- MID: %d, Mvalue: %d\n", ((read_reg(arbid##_ARB_VADDR, ARB_CTRL)>>ARB_CTRL_M1_OFT)& ARB_CTRL_M1_MSK), read_reg(arbid##_ARB_VADDR, ARB_EVEN1L)); \
})

#define report_clk_result(arbid)\
({\
  printf ("CLK: %d\n", read_reg(arbid##_ARB_VADDR, ARB_CLKL)); \
})


/*example 
#ifdef JZC_PMON_SIGN_MON
#define AHB1_CHN0_MID_ AHB1_ID_MDMA2
#define AHB1_CHN1_MID_ AHB1_ID_MDMA2
#define AHB0_CHN0_MID_ AHB0_ID_MDMA2
#define AHB0_CHN1_MID_ AHB0_ID_MDMA2

	arb_ch1_clk_wr(AHB1, 0);// clean clk
	arb_ch0_evenl_wr(AHB1, 0);//clean chn0 coutner
	arb_ch1_evenl_wr(AHB1, 0);    //clean chn1 coutner
	arb_chn0_even_ctrl(AHB1, AHB1_CHN0_MID_, ABME_GRL, 1);// configure chn 0 'AHB1_CHN0_MID_, ABME_GRL'
	arb_chn1_even_ctrl(AHB1, AHB1_CHN1_MID_, ABME_BTC,1);    and run it using '1'
	arb_clk_ctrl(AHB1, 1);

	arb_ch1_clk_wr(AHB0, 0); // clean clk
	arb_ch0_evenl_wr(AHB0, 0); //clean chn0 coutner
	arb_ch1_evenl_wr(AHB0, 0);    //clean chn1 coutner
	arb_chn0_even_ctrl(AHB0, AHB0_CHN0_MID_, ABME_GRL, 1); // configure chn 0 'AHB1_CHN0_MID_, ABME_GRL'
	arb_chn1_even_ctrl(AHB0, AHB0_CHN1_MID_, ABME_BTC,1);    and run it using '1'
	arb_clk_ctrl(AHB0, 1);

//\/ need to monitor
	set_gp2_dcs();
	poll_gp2_end();
///\
	arb_chn0_even_ctrl(AHB0, AHB0_CHN0_MID_, ABME_GRL, 0); // stop using '0'
	arb_chn1_even_ctrl(AHB0, AHB0_CHN1_MID_, ABME_BTC,0);    
	arb_clk_ctrl(AHB0, 0);

	arb_chn0_even_ctrl(AHB1, AHB1_CHN0_MID_, ABME_GRL, 0);
	arb_chn1_even_ctrl(AHB1, AHB1_CHN1_MID_, ABME_BTC,0);    
	arb_clk_ctrl(AHB1, 0);
      }	
      }  

 */
