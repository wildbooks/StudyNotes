/*  
 *Exynos4412 SFR address define
 *http://dev.hqyj.com
 *liujh@farsight.com.cn
 *2014.4.21
*/

#ifndef ___EXYNOS4412_H_
#define ___EXYNOS4412_H_

#define  	__REG(x)					(*(volatile unsigned int *)(x))  


/****************EXINT***************/
#define		EXT_INT1_CON		__REG(0X11400700)
#define		EXT_INT2_CON		__REG(0X11400704)
#define		EXT_INT3_CON		__REG(0X11400708)
#define		EXT_INT4_CON		__REG(0X1140070C)
#define		EXT_INT5_CON		__REG(0X11400710)
#define		EXT_INT6_CON		__REG(0X11400714)
#define		EXT_INT7_CON		__REG(0X11400718)
/*
#define		EXT_INT8_CON		__REG(0X11400700)
#define		EXT_INT9_CON		__REG(0X11400700)
#define		EXT_INT10_CON		__REG(0X11400700)
#define		EXT_INT11_CON		__REG(0X11400700)
#define		EXT_INT12_CON		__REG(0X11400700)
*/
#define		EXT_INT13_CON		__REG(0X11400730)
#define		EXT_INT14_CON		__REG(0X11400734)
#define		EXT_INT15_CON		__REG(0X11400738)
#define		EXT_INT16_CON		__REG(0X1140073C)
/*
#define		EXT_INT17_CON		__REG(0X11400700)
#define		EXT_INT18_CON		__REG(0X11400700)
#define		EXT_INT19_CON		__REG(0X11400700)
#define		EXT_INT20_CON		__REG(0X11400700)
*/
#define		EXT_INT21_CON		__REG(0X11400740)
#define		EXT_INT22_CON		__REG(0X11400744)

#define		EXT_INT1_FLTCON0	__REG(0X11400800)
#define		EXT_INT1_FLTCON1	__REG(0X11400804)
#define		EXT_INT2_FLTCON0	__REG(0X11400808)
#define		EXT_INT2_FLTCON1	__REG(0X1140080C)
#define		EXT_INT3_FLTCON0	__REG(0X11400810)
#define		EXT_INT3_FLTCON1	__REG(0X11400814)
#define		EXT_INT4_FLTCON0	__REG(0X11400818)
#define		EXT_INT4_FLTCON1	__REG(0X1140081C)
#define		EXT_INT5_FLTCON0	__REG(0X11400820)
#define		EXT_INT5_FLTCON1	__REG(0X11400824)
#define		EXT_INT6_FLTCON0	__REG(0X11400828)
#define		EXT_INT6_FLTCON1	__REG(0X1140082C)
#define		EXT_INT7_FLTCON0	__REG(0X11400830)
#define		EXT_INT7_FLTCON1	__REG(0X11400834)


#define		EXT_INT1_MASK		__REG(0X11400900)
#define		EXT_INT2_MASK		__REG(0X11400904)
#define		EXT_INT3_MASK		__REG(0X11400908)
#define		EXT_INT4_MASK		__REG(0X1140090C)
#define		EXT_INT5_MASK		__REG(0X11400910)
#define		EXT_INT6_MASK		__REG(0X11400914)
#define		EXT_INT7_MASK		__REG(0X11400918)


#define		EXT_INT1_PEND		__REG(0X11400A00)
#define		EXT_INT2_PEND		__REG(0X11400A04)
#define		EXT_INT3_PEND		__REG(0X11400A08)
#define		EXT_INT4_PEND		__REG(0X11400A0C)
#define		EXT_INT5_PEND		__REG(0X11400A10)
#define		EXT_INT6_PEND		__REG(0X11400A14)
#define		EXT_INT7_PEND		__REG(0X11400A18)

#define		EXT_INT_SERVICE_XB			__REG(0X11400B08)
#define		EXT_INT_SERVICE_PEND_XB 	__REG(0X11400B0C)
#define		EXT_INT_GRPFIXPRI_XB 		__REG(0X11400B10)

#define		EXT_INT1_FIXPRI		__REG(0X11400B14)
#define		EXT_INT2_FIXPRI		__REG(0X11400B18)
#define		EXT_INT3_FIXPRI		__REG(0X11400B1C)
#define		EXT_INT4_FIXPRI		__REG(0X11400B20)
#define		EXT_INT5_FIXPRI		__REG(0X11400B24)
#define		EXT_INT6_FIXPRI		__REG(0X11400B28)
#define		EXT_INT7_FIXPRI		__REG(0X11400B2C)






#define		EXT_INT40_CON		__REG(0x11000E00)
#define		EXT_INT41_CON		__REG(0x11000E04)
#define		EXT_INT42_CON		__REG(0x11000E08)
#define		EXT_INT43_CON		__REG(0x11000E0C)

#define		EXT_INT40_FLTCON0	__REG(0x11000E80)
#define		EXT_INT40_FLTCON1	__REG(0x11000E84)
#define		EXT_INT41_FLTCON0	__REG(0x11000E88)
#define		EXT_INT41_FLTCON1	__REG(0x11000E8C)
#define		EXT_INT42_FLTCON0	__REG(0x11000E90)
#define		EXT_INT42_FLTCON1	__REG(0x11000E94)
#define		EXT_INT43_FLTCON0	__REG(0x11000E98)
#define		EXT_INT43_FLTCON1	__REG(0x11000E9C)

#define		EXT_INT40_MASK		__REG(0x11000F00)
#define		EXT_INT41_MASK		__REG(0x11000F04)
#define		EXT_INT42_MASK		__REG(0x11000F08)
#define		EXT_INT43_MASK		__REG(0x11000F0C)

#define		EXT_INT40_PEND		__REG(0x11000F40)
#define		EXT_INT41_PEND		__REG(0x11000F44)
#define		EXT_INT42_PEND		__REG(0x11000F48)
#define		EXT_INT43_PEND		__REG(0x11000F4C)





/* ******************************Clock & Power Controller * ********************************/
#define 	CLK_OUT				__REG(0xE0100400)
#define 	CLK_GATE_D2_0		__REG(0xE0100540)
/**********************************RTC independ register*********************************************/
#define		RTCINTP			__REG(0XEA300030)
#define		RTCCON			__REG(0XEA300040)
#define		TICCNT			__REG(0XEA300044)
#define		CURTICCNT		__REG(0XEA300090)
/*********************************    *****************************************************************/
/*************************** HS OTG  Power and Clock Gating Register ********************************************/
#define		PCGCCTL		__REG(0xED200E00)
#define     HCTSIZ4     __REG(0xED200580) 
#define     HCDMA4      __REG(0xED200584) 
  


typedef struct {
				unsigned int RTCALM;
				unsigned int ALMSEC;
				unsigned int ALMMIN;
				unsigned int ALMHOUR;
				unsigned int ALMDATE;
				unsigned int ALMMON;
				unsigned int ALMYEAR;
}rtclam;
#define		RTALM (* (volatile rtclam *)0XEA300050)


typedef	struct {

				unsigned int BCDSEC;
				unsigned int BCDMIN;
				unsigned int BCDHOUR;
				unsigned int BCDDATE;
				unsigned int BCDDAY;
				unsigned int BCDMON;
				unsigned int BCDYEAR;
}rtcbcd;
#define 	RTCBCD (* (volatile rtcbcd *)0xEA300070)

typedef struct {
				unsigned int APLL_MASK;
				unsigned int MPLL_MASK;
				unsigned int EPLL_MASK;
				unsigned int HPLL_MASK;
}pll_mask;	
#define  PLL_MASK (* (volatile pll_mask *)0xE0100000 )

typedef struct {
				unsigned int APLL_CON;
				unsigned int MPLL_CON;
				unsigned int EPLL_CON;
				unsigned int HPLL_CON;
}pll_con;
#define PLL_CON (* (volatile pll_con *)0xE0100100 )

typedef struct {
				unsigned int CLK_SRC0;
				unsigned int CLK_SRC1;
				unsigned int CLK_SRC2;
				unsigned int CLK_SRC3;
}clk_src;
#define CLK_SRC (* (volatile clk_src *)0xE0100200 )

typedef struct {
				unsigned int CLK_DIV0;
				unsigned int CLK_DIV1;
				unsigned int CLK_DIV2;
				unsigned int CLK_DIV3;
				unsigned int CLK_DIV4;
}clk_div;
#define CLK_DIV (* (volatile clk_div *)0xE0100300 )

typedef struct {
				unsigned int CLK_GATE_D0_0;
				unsigned int CLK_GATE_D0_1;
				unsigned int CLK_GATE_D0_2;
}clk_gate_d0;
#define CLK_GATE_D0 (* (volatile clk_gate_d0 *)0xE0100500 )

typedef struct {
				unsigned int CLK_GATE_D1_0;
				unsigned int CLK_GATE_D1_1;
				unsigned int CLK_GATE_D1_2;
				unsigned int CLK_GATE_D1_3;
				unsigned int CLK_GATE_D1_4;
				unsigned int CLK_GATE_D1_5;
}clk_gate_d1;
#define CLK_GATE_D1 (* (volatile clk_gate_d1 *)0xE0100520 )

typedef struct {
				unsigned int CLK_GATE_SCLK_0;
				unsigned int CLK_GATE_SCLK_1;
}clk_gate_sclk;
#define CLK_GATE_SCLK (* (volatile clk_gate_sclk *)0xE0100560 )


/****************************** GPIO **********************************/
/* GPA0 */
typedef struct {
				unsigned int CON;
				unsigned int DAT;
				unsigned int PUD;
				unsigned int DRV;
				unsigned int CONPDN;
				unsigned int PUDPDN;
}gpa0;
#define GPA0 (* (volatile gpa0 *)0x11400000)

/* GPA1 */
typedef struct {
				unsigned int CON;
				unsigned int DAT;
				unsigned int PUD;
				unsigned int DRV;
				unsigned int CONPDN;
				unsigned int PUDPDN;
}gpa1;
#define GPA1 (* (volatile gpa1 *)0x11400020)

/* GPF0 */
typedef struct {
				unsigned int GPF0CON;
				unsigned int GPF0DAT;
				unsigned int GPF0PUD;
				unsigned int GPF0DRV;
				unsigned int GPF0CONPDN;
				unsigned int GPF0PUDPDN;
}gpf0;
#define GPF0 (* (volatile gpf0 *)0x11400180)

/* GPF1 */
typedef struct {
				unsigned int GPF1CON;
				unsigned int GPF1DAT;
				unsigned int GPF1PUD;
				unsigned int GPF1DRV;
				unsigned int GPF1CONPDN;
				unsigned int GPF1PUDPDN;
}gpf1;
#define GPF1 (* (volatile gpf1 *)0x114001A0)

/* GPF2 */
typedef struct {
				unsigned int GPF2CON;
				unsigned int GPF2DAT;
				unsigned int GPF2PUD;
				unsigned int GPF2DRV;
				unsigned int GPF2CONPDN;
				unsigned int GPF2PUDPDN;
}gpf2;
#define GPF2 (* (volatile gpf2 *)0x114001C0)

/* GPF3 */
typedef struct {
				unsigned int GPF3CON;
				unsigned int GPF3DAT;
				unsigned int GPF3PUD;
				unsigned int GPF3DRV;
				unsigned int GPF3CONPDN;
				unsigned int GPF3PUDPDN;
}gpf3;
#define GPF3 (* (volatile gpf3 *)0x114001E0)

/* GPX0 */
typedef struct {
				unsigned int GPX0CON;
				unsigned int GPX0DAT;
				unsigned int GPX0PUD;
				unsigned int GPX0DRV;
}gpx0;
#define GPX0 (* (volatile gpx0 *)0x11000C00)

/* GPX1 */
typedef struct {
				unsigned int GPX1CON;
				unsigned int GPX1DAT;
				unsigned int GPX1PUD;
				unsigned int GPX1DRV;
}gpx1;
#define GPX1 (* (volatile gpx1 *)0x11000C20 )

/* GPX2 */
typedef struct {
				unsigned int GPX2CON;
				unsigned int GPX2DAT;
				unsigned int GPX2PUD;
				unsigned int GPX2DRV;
}gpx2;
#define GPX2 (* (volatile gpx2 *)0x11000C40 )

/* GPX3 */
typedef struct {
				unsigned int GPX3CON;
				unsigned int GPX3DAT;
				unsigned int GPX3PUD;
				unsigned int GPX3DRV;
}gpx3;
#define GPX3 (* (volatile gpx3 *)0x11000C60 )

/*****************************************   GIC  **************************************/

/* CPU0 */
typedef struct {
				unsigned int ICCICR;	//CPU interface control register
				unsigned int ICCPMR;
				unsigned int ICCBPR;
				unsigned int ICCIAR;	//Interrupt acknowledge register
				unsigned int ICCEOIR;
				unsigned int ICCRPR;	//Running priority register
				unsigned int ICCHPIR;
				unsigned int ICCABPR;
				unsigned int INTEG_EN;
				unsigned int INTERRUPT_OUT;
}cpu0;
#define CPU0 (* (volatile cpu0 *)0x10480000 )

#define ICCIIDR	__REG(0x104800FC)

/* CPU1 */
typedef struct {
				unsigned int ICCICR;
				unsigned int ICCPMR;
				unsigned int ICCBPR;
				unsigned int ICCIAR;
				unsigned int ICCEOIR;
				unsigned int ICCRPR;
				unsigned int ICCHPIR;
				unsigned int ICCABPR;
				unsigned int INTEG_EN;
				unsigned int INTERRUPT_OUT;
}cpu1;
#define CPU1 (* (volatile cpu1 *)0x10484000 )

/* CPU2 */
typedef struct {
				unsigned int ICCICR;
				unsigned int ICCPMR;
				unsigned int ICCBPR;
				unsigned int ICCIAR;
				unsigned int ICCEOIR;
				unsigned int ICCRPR;
				unsigned int ICCHPIR;
				unsigned int ICCABPR;
				unsigned int INTEG_EN;
				unsigned int INTERRUPT_OUT;
}cpu2;
#define CPU2 (* (volatile cpu2 *)0x10488000 )

/* CPU3 */
typedef struct {
				unsigned int ICCICR;
				unsigned int ICCPMR;
				unsigned int ICCBPR;
				unsigned int ICCIAR;
				unsigned int ICCEOIR;
				unsigned int ICCRPR;
				unsigned int ICCHPIR;
				unsigned int ICCABPR;
				unsigned int INTEG_EN;
				unsigned int INTERRUPT_OUT;
}cpu3;
#define CPU3 (* (volatile cpu3 *)0x1048C000 )

#define		ICDDCR		__REG(0X10490000)
#define		ICDICTR		__REG(0X10490004)
#define		ICDIIDR		__REG(0X10490008)

/* Interrupt security registers */
typedef struct {
				unsigned int ICDISR0_CPU0;
				unsigned int ICDISR1; // (SPI[31:0])
				unsigned int ICDISR2; // (SPI[63:32])
				unsigned int ICDISR3;
				unsigned int ICDISR4;
}isr;
#define ICDISR (* (volatile isr *)0x10490080 )

/* Interrupt set-enable register */
typedef struct {
				unsigned int ICDISER0_CPU0;
				unsigned int ICDISER1;	// (SPI[31:0])
				unsigned int ICDISER2;	// (SPI[63:32])
				unsigned int ICDISER3;
				unsigned int ICDISER4;
}iser;
#define ICDISER (* (volatile iser *)0x10490100 )

/* Interrupt clear-enable register */
typedef struct {
				unsigned int ICDICER0_CPU0;
				unsigned int ICDICER1;
				unsigned int ICDICER2;
				unsigned int ICDICER3;
				unsigned int ICDICER4;
}icer;
#define ICDICER (* (volatile icer *)0x10490180 )

/* Interrupt pending-set register */
typedef struct {
				unsigned int ICDISPR0_CPU0;
				unsigned int ICDISPR1; // (SPI[31:0])
				unsigned int ICDISPR2; // (SPI[63:32])
				unsigned int ICDISPR3;
				unsigned int ICDISPR4;
}ispr;
#define ICDISPR (* (volatile ispr *)0x10490200 )

/* Interrupt pending-clear register */
typedef struct {
				unsigned int ICDICPR0_CPU0;
				unsigned int ICDICPR1;
				unsigned int ICDICPR2;
				unsigned int ICDICPR3;
				unsigned int ICDICPR4;
}icpr;
#define ICDICPR (* (volatile icpr *)0x10490280 )

/* Active bit register */
typedef struct {
				unsigned int ICDABR0_CPU0;
				unsigned int ICDABR1;	// SPI 0 ~ 31
				unsigned int ICDABR2;	// SPI 32 ~ 63
				unsigned int ICDABR3;
				unsigned int ICDABR4;
}abr;
#define ICDABR (* (volatile abr *)0x10490300 )

/* Priority level register  */
typedef struct {
				unsigned int ICDIPR0_CPU0;
				unsigned int ICDIPR1_CPU0;
				unsigned int ICDIPR2_CPU0;
				unsigned int ICDIPR3_CPU0;
				unsigned int ICDIPR4_CPU0;
				unsigned int ICDIPR5_CPU0;
				unsigned int ICDIPR6_CPU0;
				unsigned int ICDIPR7_CPU0;
				unsigned int ICDIPR8;
				unsigned int ICDIPR9;
				unsigned int ICDIPR10;
				unsigned int ICDIPR11;
				unsigned int ICDIPR12;
				unsigned int ICDIPR13;
				unsigned int ICDIPR14;
				unsigned int ICDIPR15;
				unsigned int ICDIPR16;
				unsigned int ICDIPR17;
				unsigned int ICDIPR18;
				unsigned int ICDIPR19;
				unsigned int ICDIPR20;
				unsigned int ICDIPR21;
				unsigned int ICDIPR22;
				unsigned int ICDIPR23;
				unsigned int ICDIPR24;
				unsigned int ICDIPR25;
				unsigned int ICDIPR26;
				unsigned int ICDIPR27;
				unsigned int ICDIPR28;
				unsigned int ICDIPR29;
				unsigned int ICDIPR30;
				unsigned int ICDIPR31;
				unsigned int ICDIPR32;
				unsigned int ICDIPR33;
				unsigned int ICDIPR34;
				unsigned int ICDIPR35;
				unsigned int ICDIPR36;
				unsigned int ICDIPR37;
				unsigned int ICDIPR38;
				unsigned int ICDIPR39;
}ipr;
#define ICDIPR  (* (volatile ipr *)0x10490400 )

/* Processor targets register  */
typedef struct {
				unsigned int ICDIPTR0_CPU0;
				unsigned int ICDIPTR1_CPU0;
				unsigned int ICDIPTR2_CPU0;
				unsigned int ICDIPTR3_CPU0;
				unsigned int ICDIPTR4_CPU0;
				unsigned int ICDIPTR5_CPU0;
				unsigned int ICDIPTR6_CPU0;
				unsigned int ICDIPTR7_CPU0;
				unsigned int ICDIPTR8;
				unsigned int ICDIPTR9;
				unsigned int ICDIPTR10;
				unsigned int ICDIPTR11;
				unsigned int ICDIPTR12;
				unsigned int ICDIPTR13;
				unsigned int ICDIPTR14;
				unsigned int ICDIPTR15;
				unsigned int ICDIPTR16;
				unsigned int ICDIPTR17;
				unsigned int ICDIPTR18;
				unsigned int ICDIPTR19;
				unsigned int ICDIPTR20;
				unsigned int ICDIPTR21;
				unsigned int ICDIPTR22;
				unsigned int ICDIPTR23;
				unsigned int ICDIPTR24;
				unsigned int ICDIPTR25;
				unsigned int ICDIPTR26;
				unsigned int ICDIPTR27;
				unsigned int ICDIPTR28;
				unsigned int ICDIPTR29;
				unsigned int ICDIPTR30;
				unsigned int ICDIPTR31;
				unsigned int ICDIPTR32;
				unsigned int ICDIPTR33;
				unsigned int ICDIPTR34;
				unsigned int ICDIPTR35;
				unsigned int ICDIPTR36;
				unsigned int ICDIPTR37;
				unsigned int ICDIPTR38;
				unsigned int ICDIPTR39;
}iptr;
#define ICDIPTR  (* (volatile iptr *)0x10490800 )

/* Interrupt configuration register  */
typedef struct {
				unsigned int ICDICFR0_CPU0;
				unsigned int ICDICFR1_CPU0;
				unsigned int ICDICFR2;
				unsigned int ICDICFR3;
				unsigned int ICDICFR4;
				unsigned int ICDICFR5;
				unsigned int ICDICFR6;
				unsigned int ICDICFR7;
				unsigned int ICDICFR8;
				unsigned int ICDICFR9;
}icfr;
#define ICDICFR  (* (volatile icfr *)0X10490C00 )

#define PPI_STATUS_CPU0		__REG(0X10490D00)

/* SPI status register  */
typedef struct {
				unsigned int STATUS0;	//SPI[31:0] status register
				unsigned int STATUS1;	//SPI[63:32] status register
				unsigned int STATUS2;	//SPI[95:64] status register
				unsigned int STATUS3;	//SPI[127:96] status register
}icdspi_status;
#define ICDSPI_STATUS  (* (volatile icdspi_status *)0X10490D04 )

/*  Software generated interrupt register  */
#define ICDSGIR		__REG(0X10490F00)


/* CPU1 interrupt's register  */
typedef struct {
				unsigned int ICDISR0;
				unsigned int ICDISER0;
				unsigned int ICDICER0;
				unsigned int ICDISPR0;
				unsigned int ICDICPR0;
				unsigned int ICDABR0;
				unsigned int ICDIPR0;
				unsigned int ICDIPR1;
				unsigned int ICDIPR2;
				unsigned int ICDIPR3;
				unsigned int ICDIPR4;
				unsigned int ICDIPR5;
				unsigned int ICDIPR6;
				unsigned int ICDIPR7;
				unsigned int ICDIPTR0;
				unsigned int ICDIPTR1;
				unsigned int ICDIPTR2;
				unsigned int ICDIPTR3;
				unsigned int ICDIPTR4;
				unsigned int ICDIPTR5;
				unsigned int ICDIPTR6;
				unsigned int ICDIPTR7;
				unsigned int ICDICFR0;
				unsigned int ICDICFR1;
				unsigned int PPI_STATUS;
}icdcpu1;
#define ICDCPU1  (* (volatile icdcpu1 *)0X10494080 )

/* CPU2 interrupt's register  */
typedef struct {
				unsigned int ICDISR0;
				unsigned int ICDISER0;
				unsigned int ICDICER0;
				unsigned int ICDISPR0;
				unsigned int ICDICPR0;
				unsigned int ICDABR0;
				unsigned int ICDIPR0;
				unsigned int ICDIPR1;
				unsigned int ICDIPR2;
				unsigned int ICDIPR3;
				unsigned int ICDIPR4;
				unsigned int ICDIPR5;
				unsigned int ICDIPR6;
				unsigned int ICDIPR7;
				unsigned int ICDIPTR0;
				unsigned int ICDIPTR1;
				unsigned int ICDIPTR2;
				unsigned int ICDIPTR3;
				unsigned int ICDIPTR4;
				unsigned int ICDIPTR5;
				unsigned int ICDIPTR6;
				unsigned int ICDIPTR7;
				unsigned int ICDICFR0;
				unsigned int ICDICFR1;
				unsigned int PPI_STATUS;
}icdcpu2;
#define ICDCPU2  (* (volatile icdcpu2 *)0X10498080 )

/* CPU3 interrupt's register  */
typedef struct {
				unsigned int ICDISR0;
				unsigned int ICDISER0;
				unsigned int ICDICER0;
				unsigned int ICDISPR0;
				unsigned int ICDICPR0;
				unsigned int ICDABR0;
				unsigned int ICDIPR0;
				unsigned int ICDIPR1;
				unsigned int ICDIPR2;
				unsigned int ICDIPR3;
				unsigned int ICDIPR4;
				unsigned int ICDIPR5;
				unsigned int ICDIPR6;
				unsigned int ICDIPR7;
				unsigned int ICDIPTR0;
				unsigned int ICDIPTR1;
				unsigned int ICDIPTR2;
				unsigned int ICDIPTR3;
				unsigned int ICDIPTR4;
				unsigned int ICDIPTR5;
				unsigned int ICDIPTR6;
				unsigned int ICDIPTR7;
				unsigned int ICDICFR0;
				unsigned int ICDICFR1;
				unsigned int PPI_STATUS;
}icdcpu3;
#define ICDCPU3  (* (volatile icdcpu3 *)0X1049C080 )

#endif



/*****************************************    UART  * *************************************/
/* UART0*/
typedef struct {
				unsigned int ULCON0;
				unsigned int UCON0;
				unsigned int UFCON0;
				unsigned int UMCON0;
				unsigned int UTRSTAT0;
				unsigned int UERSTAT0;
				unsigned int UFSTAT0;
				unsigned int UMSTAT0;
				unsigned int UTXH0;
				unsigned int URXH0;
				unsigned int UBRDIV0;
				unsigned int UFRACVAL0;
				unsigned int UINTP0;
				unsigned int UINTSP0;
				unsigned int UINTM0;
}uart0;
#define UART0 ( * (volatile uart0 *)0x13800000 )

/*
 * UART1
 */
typedef struct {
				unsigned int ULCON1;
				unsigned int UCON1;
				unsigned int UFCON1;
				unsigned int UMCON1;
				unsigned int UTRSTAT1;
				unsigned int UERSTAT1;
				unsigned int UFSTAT1;
				unsigned int UMSTAT1;
				unsigned int UTXH1;
				unsigned int URXH1;
				unsigned int UBRDIV1;
				unsigned int UFRACVAL1;
				unsigned int UINTP1;
				unsigned int UINTSP1;
				unsigned int UINTM1;
}uart1;
#define UART1 ( * (volatile uart1 *)0x13810000 )

/*
 * UART2
 */
typedef struct {
				unsigned int ULCON2;
				unsigned int UCON2;
				unsigned int UFCON2;
				unsigned int UMCON2;
				unsigned int UTRSTAT2;
				unsigned int UERSTAT2;
				unsigned int UFSTAT2;
				unsigned int UMSTAT2;
				unsigned int UTXH2;
				unsigned int URXH2;
				unsigned int UBRDIV2;
				unsigned int UFRACVAL2;
				unsigned int UINTP2;
				unsigned int UINTSP2;
				unsigned int UINTM2;
}uart2;
#define UART2 ( * (volatile uart2 *)0x13820000 )

/*
 * UART3
 */
typedef struct {
				unsigned int ULCON3;
				unsigned int UCON3;
				unsigned int UFCON3;
				unsigned int UMCON3;
				unsigned int UTRSTAT3;
				unsigned int UERSTAT3;
				unsigned int UFSTAT3;
				unsigned int UMSTAT3;
				unsigned int UTXH3;
				unsigned int URXH3;
				unsigned int UBRDIV3;
				unsigned int UFRACVAL3;
				unsigned int UINTP3;
				unsigned int UINTSP3;
				unsigned int UINTM3;
}uart3;
#define UART3 ( * (volatile uart3 *)0x13830000 )

/*
 * UART4
 */
typedef struct {
				unsigned int ULCON4;
				unsigned int UCON4;
				unsigned int UFCON4;
				unsigned int UMCON4;
				unsigned int UTRSTAT4;
				unsigned int UERSTAT4;
				unsigned int UFSTAT4;
				unsigned int UMSTAT4;
				unsigned int UTXH4;
				unsigned int URXH4;
				unsigned int UBRDIV4;
				unsigned int UFRACVAL4;
				unsigned int UINTP4;
				unsigned int UINTSP4;
				unsigned int UINTM4;
}uart4;
#define UART4 ( * (volatile uart4 *)0x13840000 )




