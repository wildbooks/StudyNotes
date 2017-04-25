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
				unsigned int GPA0CON;
				unsigned int GPA0DAT;
				unsigned int GPA0PUD;
				unsigned int GPA0DRV;
				unsigned int GPA0CONPDN;
				unsigned int GPA0PUDPDN;
}gpa0;
#define GPA0 (* (volatile gpa0 *)0x11400000)

/* GPA1 */
typedef struct {
				unsigned int GPA1CON;
				unsigned int GPA1DAT;
				unsigned int GPA1PUD;
				unsigned int GPA1DRV;
				unsigned int GPA1CONPDN;
				unsigned int GPA1PUDPDN;
}gpa1;
#define GPA1 (* (volatile gpa1 *)0x11400020)

/* GPB */
typedef struct {
				unsigned int GPBCON;
				unsigned int GPBDAT;
				unsigned int GPBPUD;
				unsigned int GPBDRV;
				unsigned int GPBCONPDN;
				unsigned int GPBPUDPDN;
}gpb;
#define GPB (* (volatile gpb *)0x11400040)

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





/***********************  timer ******************************************/
#define TINT_CSTAT				__REG(0xEA000044)

typedef struct {
				unsigned int TCFG0;
				unsigned int TCFG1;
				unsigned int TCON;
}timer_type;
#define  TIMER  (* (volatile timer_type *)0xEA000000)
/*
*timer0	
*/
typedef	struct {
				unsigned int TCNTB0;
				unsigned int TCMPB0;
				unsigned int TCNTO0;
}timer0_type;
#define	TIMER0 (* (volatile timer0_type *)0xEA00000C )

/*
*timer1	
*/
typedef struct {

				unsigned int TCNTB1;
				unsigned int TCMPB1;
				unsigned int TCNTO1;
}timer1_type;
#define  TIMER1 (* (volatile timer1_type *)0xEA000018 ) 


/*
*timer2
*/
typedef struct {
				unsigned int TCNTB2;
				unsigned int TCMPB2;
				unsigned int TCNT02;
}timer2_type;
#define TIMER2 (* (volatile timer2_type *)0xEA00024 )

/*
*timer3	
*/
typedef struct {
				unsigned int TCNTB3;
				unsigned int TCMPB3;
				unsigned int TCNTO3;
}timer3_type;
#define TIMER3 (* (volatile timer3_type *)0xEA000030 )

/*
*timer4
*/
typedef struct {
				unsigned int TCNTB4;
				unsigned int TCNTO4;
}timer4_type;
#define TIMER4 (* (volatile timer4_type *)0xEA00003c )

typedef struct {
				unsigned int ADCCON;
				unsigned int ADCTSC;
				unsigned int ADCDLY;
				unsigned int ADCDAT0;				
				unsigned int ADCDAT1;
				unsigned int ADCUPDN;
				unsigned int ADCCLRINT;
				unsigned int ADCMUX;
				unsigned int ADCPNDCLR;
}adc;
#define ADC	(* (volatile adc * )0xF3000000 )


/*
*I2C0 REGISTERS
*/
typedef struct {
				unsigned int I2CCON0 ;
				unsigned int I2CSTAT0 ;
				unsigned int I2CADD0  ;
				unsigned int I2CDS0 ;
				unsigned int I2CLC0 ;
}i2c0;
#define  I2C0 (* (volatile i2c0 *)0xEC100000 )

/*
*I2C1 REGISTERS
*/
typedef struct {
				unsigned int I2CCON1;
				unsigned int I2CSTAT1;
				unsigned int I2CADD1;
				unsigned int I2CDS1;
				unsigned int I2CLC1;
}i2c1;
#define  I2C1 (* (volatile i2c1 *)0xEC200000 )

/*
*SPI0 REGISTERS
*/
typedef struct {
				unsigned int CH_CFG ;
				unsigned int CLK_CFG;
				unsigned int MODE_CFG ;
				unsigned int CS_REG;
				unsigned int SPI_INT_EN ;
				unsigned int SPI_STATUS;
				unsigned int SPI_TX_DATA;
				unsigned int SPI_RX_DATA;
				unsigned int PACKET_CNT_REG ;
				unsigned int PENDING_CLR_REG ;
				unsigned int SWAP_CFG ;
				unsigned int FB_CLK_SEL ;
}spi0;
#define  SPI0 (* (volatile spi0 *)0xEC300000 )

/*
*SPI1 REGISTERS
*/
typedef struct {
				unsigned int CH_CFG ;
				unsigned int CLK_CFG;
				unsigned int MODE_CFG ;
				unsigned int CS_REG;
				unsigned int SPI_INT_EN ;
				unsigned int SPI_STATUS ;
				unsigned int SPI_TX_DATA;
				unsigned int SPI_RX_DATA;
				unsigned int PACKET_CNT_REG ;
				unsigned int PENDING_CLR_REG ;
				unsigned int SWAP_CFG ;
				unsigned int FB_CLK_SEL ;
}spi1;
#define  SPI1 (* (volatile spi1 *)0xEC400000 )

/*
*SPI2 REGISTERS
*/
typedef struct {
				unsigned int CH_CFG     ;
				unsigned int CLK_CFG    ;
				unsigned int MODE_CFG   ;
				unsigned int CS_REG     ;
				unsigned int SPI_INT_EN ;
				unsigned int SPI_STATUS ;
				unsigned int SPI_TX_DATA;
				unsigned int SPI_RX_DATA;
				unsigned int PACKET_CNT_REG ;
				unsigned int PENDING_CLR_REG ;
				unsigned int SWAP_CFG   ;
				unsigned int FB_CLK_SEL ;
}spi2;
#define  SPI2 (* (volatile spi2 *)0xEC500000 )

/*
*NAND FLASH CONTROLLER
*/
typedef struct {
				unsigned int NFCONF  ;
				unsigned int NFCONT  ;
				unsigned int NFCMMD  ;
				unsigned int NFDATA  ;
				unsigned int NFADDR  ;
				unsigned int NFMECCD0;
				unsigned int NFMECCD1;
				unsigned int NFSECCD ;
				unsigned int NFSBLK  ;
				unsigned int NFEBLK  ;
				unsigned int NFSTAT  ;
				unsigned int NFECCERR0 ;
				unsigned int NFECCERR1 ;
				unsigned int NFMECC0 ;
				unsigned int NFMECC1 ;
				unsigned int FSECC   ;
				unsigned int NFMLCBITPT;
				unsigned int NF8ECCERR0;
				unsigned int NF8ECCERR1;
				unsigned int NF8ECCERR2;
				unsigned int NFM8ECC0;
				unsigned int NFM8ECC1;
				unsigned int NFM8ECC2;
				unsigned int NFM8ECC3;
				unsigned int NFMLC8BITPT0 ;
				unsigned int NFMLC8BITPT1 ;
				unsigned int NFACTADJ ;
}nfc;
#define  NFC (* (volatile nfc *)0xE7200000 )

/*
*LCD CONTROLLER
*/
typedef struct {
				unsigned int VIDCON0 ;
				unsigned int VIDCON1 ;
				unsigned int VIDCON2 ;
				unsigned int PRTCON ;
				unsigned int VIDTCON0 ;
				unsigned int VIDTCON1 ;
				unsigned int VIDTCON2 ;
				unsigned int RESERVED0 ;
				unsigned int WINCON0 ;
				unsigned int WINCON1 ;
				unsigned int WINCON2 ;
				unsigned int WINCON3 ;
				unsigned int WINCON4 ;
				unsigned int RESERVED1[3];
				unsigned int VIDOSD0A ;
				unsigned int VIDOSD0B ;
				unsigned int VIDOSD0C ;
				unsigned int RESERVED2  ;
				unsigned int VIDOSD1A  ;
				unsigned int VIDOSD1B ;
				unsigned int VIDOSD1C ;
				unsigned int VIDOSD1D ;
				unsigned int VIDOSD2A ;
				unsigned int VIDOSD2B ;
				unsigned int VIDOSD2C ;
				unsigned int VIDOSD2D ;
				unsigned int VIDOSD3A ;
				unsigned int VIDOSD3B ;
				unsigned int VIDOSD3C ;
				unsigned int RESERVED3 ;
				unsigned int VIDOSD4A ;
				unsigned int VIDOSD4B ;
				unsigned int VIDOSD4C ;
				unsigned int RESERVED4[5] ;
				unsigned int VIDW00ADD0B0;
				unsigned int VIDW00ADD0B1;
				unsigned int VIDW01ADD0B0;
				unsigned int VIDW01ADD0B1;
				unsigned int VIDW02ADD0;
				unsigned int RESERVED5;
				unsigned int VIDW03ADD0;
				unsigned int RESERVED6;
				unsigned int VIDW04ADD0;
				unsigned int RESERVED7[3];
				unsigned int VIDW00ADD1B0;
				unsigned int VIDW00ADD1B1 ;
				unsigned int VIDW01ADD1B0 ;
				unsigned int VIDW01ADD1B1 ;
				unsigned int VIDW02ADD1 ;
				unsigned int RESERVED8;
				unsigned int VIDW03ADD1 ;
				unsigned int RESERVED9;
				unsigned int VIDW04ADD1 ;
				unsigned int RESERVED10[3];
				unsigned int VIDW00ADD2 ;
				unsigned int VIDW01ADD2;
				unsigned int VIDW02ADD2;
				unsigned int VIDW03ADD2;
				unsigned int VIDW04ADD2;
				unsigned int RESERVEDX1;
				unsigned int VP1TCON0;
				unsigned int VP1TCON1;
				unsigned int RESERVED11[4];
				unsigned int VIDINTCON0;
				unsigned int VIDINTCON1;
				unsigned int RESERVED12[2];
				unsigned int W1KEYCON0;
				unsigned int W1KEYCON1;
				unsigned int W2KEYCON0;
				unsigned int W2KEYCON1;
				unsigned int W3KEYCON0;
				unsigned int W3KEYCON1;
				unsigned int W4KEYCON0;
				unsigned int W4KEYCON1;
				unsigned int RESERVED13[4];
				unsigned int DITHMODE;
				unsigned int RESERVED14[3];
				unsigned int WIN0MAP;
				unsigned int WIN1MAP;
				unsigned int WIN2MAP;
				unsigned int WIN3MAP;
				unsigned int WIN4MAP;
				unsigned int RESERVED15[2];
				unsigned int WPALCON_H;
				unsigned int WPALCON_L;
				unsigned int TRIGCON;
				unsigned int ITUIFCON;
				unsigned int RESERVEDX2;
				unsigned int I80IFCONA0;
				unsigned int I80IFCONA1 ;
				unsigned int I80IFCONB0;
				unsigned int I80IFCONB1 ;
				unsigned int RESERVED16[4];
				unsigned int LDI_CMDCON0;
				unsigned int LDI_CMDCON1;
				unsigned int RESERVED17[2];
				unsigned int SIFCCON0;
				unsigned int SIFCCON1;
				unsigned int SIFCCON2;
				unsigned int RESERVED18[5];
				unsigned int VIDW0ALPHA0;
				unsigned int VIDW0ALPHA1;
				unsigned int VIDW1ALPHA0;
				unsigned int VIDW1ALPHA1;
				unsigned int VIDW2ALPHA0;
				unsigned int VIDW2ALPHA1;
				unsigned int VIDW3ALPHA0;
				unsigned int VIDW3ALPHA1;
				unsigned int VIDW4ALPHA0;
				unsigned int VIDW4ALPHA1;
				unsigned int RESERVED19[7];
				unsigned int BLENDEQ1;
				unsigned int BLENDEQ2;
				unsigned int BLENDEQ3;
				unsigned int BLENDEQ4;
				unsigned int RESERVED20[3];
				unsigned int BLENDCON;
				unsigned int RESERVED21[7];
				unsigned int LDI_CMD0;
				unsigned int LDI_CMD1;
				unsigned int LDI_CMD2;
				unsigned int LDI_CMD3;
				unsigned int LDI_CMD4;
				unsigned int LDI_CMD5;
				unsigned int LDI_CMD6;
				unsigned int LDI_CMD7;
				unsigned int LDI_CMD8;
				unsigned int LDI_CMD9;
				unsigned int LDI_CMD10;
				unsigned int LDI_CMD11;
}lcd;
#define  LCD (* (volatile lcd *)0xEE000000 )

/*
*WATCHDOG TIMER
*/
typedef struct {
				unsigned int WTCON  ;
				unsigned int WTDAT  ;
				unsigned int WTCNT  ;
				unsigned int WTCLRINT  ;

}wdt;
#define  WDT (* (volatile wdt *)0xEA200000 )

/*
*Power Management
*/
typedef struct {
				unsigned int PWR_CFG  ;
				unsigned int EINT_WAKEUP_MASK ;
				unsigned int RESERVED0[2];
				unsigned int NORMAL_CFG ;
				unsigned int STOP_CFG ;
				unsigned int SLEEP_CFG ;
				unsigned int STOP_MEM_CFG ;
				unsigned int RESERVED1[56] ;
				unsigned int OSC_FREQ ;
				unsigned int OSC_STABLE ;
				unsigned int PWR_STABLE ;
				unsigned int RESERVED2  ;
				unsigned int INTERNAL_PWR_STABLE ;
				unsigned int CLAMP_STABLE ;
				unsigned int RESERVED3[58]  ;
				unsigned int OTHERS ;
				unsigned int RESERVED4[58] ;
				unsigned int RST_STAT ;
				unsigned int WAKEUP_STAT ;
				unsigned int BLK_PWR_STAT ;
				unsigned int RESERVED5[60] ;
				unsigned int INFORM0 ;
				unsigned int INFORM1 ;
				unsigned int INFORM2 ;
				unsigned int INFORM3 ;
				unsigned int INFORM4;
				unsigned int INFORM5 ;
				unsigned int INFORM6 ;
				unsigned int INFORM7 ;
				unsigned int RESERVED6[38] ;
				unsigned int DCGIDX_MAP0 ;
				unsigned int DCGIDX_MAP1 ;
				unsigned int DCGIDX_MAP2 ;
				unsigned int DCGPERF_MAP0 ;
				unsigned int DCGPERF_MAP1 ;
				unsigned int DVCIDX_MAP ;
				unsigned int FREQ_CPU ;
				unsigned int FREQ_DPM ;
				unsigned int DVSEMCLK_EN ;
				unsigned int RESERVED7[37]  ;
				unsigned int APLL_CON_L8 ;
				unsigned int APLL_CON_L7 ;
				unsigned int APLL_CON_L6;
				unsigned int APLL_CON_L5;
				unsigned int APLL_CON_L4;
				unsigned int APLL_CON_L3;
				unsigned int APLL_CON_L2;
				unsigned int APLL_CON_L1;
				unsigned int IEM_CONTROL;
				unsigned int RESERVED8[37];
				unsigned int CLKDIV_IEM_L8;
				unsigned int CLKDIV_IEM_L7;
				unsigned int CLKDIV_IEM_L6;
				unsigned int CLKDIV_IEM_L5;
				unsigned int CLKDIV_IEM_L4;
				unsigned int CLKDIV_IEM_L3;
				unsigned int CLKDIV_IEM_L2;
				unsigned int CLKDIV_IEM_L1;
				unsigned int RESERVED9;
				unsigned int IEM_HPMCLK_DIV;
}pm ;
#define  PM (* (volatile pm *)0xE0108000 )

/*
* OTG PHY CONTROL REGISTERS
*/
typedef struct {
				unsigned int OPHYPWR;
				unsigned int OPHYCLK;
				unsigned int ORSTCON;
				unsigned int RESERVED0[5];
				unsigned int OPHYTUNE;
}otg_phy;
#define  OTG_PYH (* (volatile otg_phy *)0xED300000 )
/*
* Core Global Registers
*/
typedef struct {
				unsigned int GOTGCTL;
				unsigned int GOTGINT;
				unsigned int GAHBCFG;
				unsigned int GUSBCFG;
				unsigned int GRSTCTL;
				unsigned int GINTSTS;
				unsigned int GINTMSK;
				unsigned int GRXSTSR;
				unsigned int GRXSTSP;
				unsigned int GRXFSIZ;
				unsigned int GNPTXFSIZ;
				unsigned int GNPTXSTS;
				unsigned int RESERVED0[52];
				unsigned int HPTXFSIZ;
				unsigned int DPTXFSIZ1;
				unsigned int DPTXFSIZ2;
				unsigned int DPTXFSIZ3;
				unsigned int DPTXFSIZ4;
				unsigned int DPTXFSIZ5;
				unsigned int DPTXFSIZ6;
				unsigned int DPTXFSIZ7;
				unsigned int DPTXFSIZ8;
				unsigned int DPTXFSIZ9;
				unsigned int DPTXFSIZ10;
				unsigned int DPTXFSIZ11;
				unsigned int DPTXFSIZ12;
				unsigned int DPTXFSIZ13;
				unsigned int DPTXFSIZ14;
				unsigned int DPTXFSIZ15;
}otg_cg;
#define  OTG_CG (* (volatile otg_cg *)0xED200000 )
/*
* OTG Host Global Registers
*/
typedef struct {
				unsigned int HCFG;
				unsigned int HFIR;
				unsigned int HFNUM;
				unsigned int RESERVED0;
				unsigned int HPTXSTS;
				unsigned int HAINT;
				unsigned int HAINTMSK;
				unsigned int RESERVED1[9];
				unsigned int HPRT;
}otg_hg;
#define  OTG_HG (* (volatile otg_hg *)0xED200400 )
/*
* OTG Host Channel-Specific Registers
*/
typedef struct {
				unsigned int HCCHAR0;
				unsigned int HCSPLT0;
				unsigned int HCINT0;
				unsigned int HCINTMSK0;
				unsigned int HCTSIZ0;
				unsigned int HCDMA0;
				unsigned int RESERVED0[2];
				unsigned int HCCHAR1;
				unsigned int HCSPLT1;
				unsigned int HCINT1;
				unsigned int HCINTMSK1;
				unsigned int HCTSIZ1;
				unsigned int HCDMA1;
				unsigned int RESERVED1[2];
				unsigned int HCCHAR2;
				unsigned int HCSPLT2;
				unsigned int HCINT2;
				unsigned int HCINTMSK2;
				unsigned int HCTSIZ2;
				unsigned int HCDMA2;
				unsigned int RESERVED2[2];
				unsigned int HCCHAR3;
				unsigned int HCSPLT3;
				unsigned int HCINT3;
				unsigned int HCINTMSK3;
				unsigned int HCTSIZ3;
				unsigned int HCDMA3;
				unsigned int RESERVED3[2];
				unsigned int HCCHAR4;
				unsigned int HCSPLT4;
				unsigned int HCINT4;
				unsigned int HCINTMSK4;
				unsigned int RESERVED4[4];
			//	unsigned int HCTSIZ4;
			//	unsigned int HCDMA4;
				unsigned int HCCHAR5;
				unsigned int HCSPLT5;
				unsigned int HCINT5;
				unsigned int HCINTMSK5;
				unsigned int HCTSIZ5;
				unsigned int HCDMA5;
				unsigned int RESERVED5[2];
				unsigned int HCCHAR6;
				unsigned int HCSPLT6;
				unsigned int HCINT6;
				unsigned int HCINTMSK6;
				unsigned int HCTSIZ6;
				unsigned int HCDMA6;
				unsigned int RESERVED6[2];
				unsigned int HCCHAR7;
				unsigned int HCSPLT7;
				unsigned int HCINT7;
				unsigned int HCINTMSK7;
				unsigned int HCTSIZ7;
				unsigned int HCDMA7;
				unsigned int RESERVED7[2];
				unsigned int HCCHAR8;
				unsigned int HCSPLT8;
				unsigned int HCINT8;
				unsigned int HCINTMSK8;
				unsigned int HCTSIZ8;
				unsigned int HCDMA8;
				unsigned int RESERVED8[2];
				unsigned int HCCHAR9;
				unsigned int HCSPLT9;
				unsigned int HCINT9;
				unsigned int HCINTMSK9;
				unsigned int HCTSIZ9;
				unsigned int HCDMA9;
				unsigned int RESERVED9[2];
				unsigned int HCCHAR10;
				unsigned int HCSPLT10;
				unsigned int HCINT10;
				unsigned int HCINTMSK10;
				unsigned int HCTSIZ10;
				unsigned int HCDMA10;
				unsigned int RESERVED10[2];
				unsigned int HCCHAR11;
				unsigned int HCSPLT11;
				unsigned int HCINT11;
				unsigned int HCINTMSK11;
				unsigned int HCTSIZ11;
				unsigned int HCDMA11;
				unsigned int RESERVED11[2];
				unsigned int HCCHAR12;
				unsigned int HCSPLT12;
				unsigned int HCINT12;
				unsigned int HCINTMSK12;
				unsigned int HCTSIZ12;
				unsigned int HCDMA12;
				unsigned int RESERVED12[2];
				unsigned int HCCHAR13;
				unsigned int HCSPLT13;
				unsigned int HCINT13;
				unsigned int HCINTMSK13;
				unsigned int HCTSIZ13;
				unsigned int HCDMA13;
				unsigned int RESERVED13[2];
				unsigned int HCCHAR14;
				unsigned int HCSPLT14;
				unsigned int HCINT14;
				unsigned int HCINTMSK14;
				unsigned int HCTSIZ14;
				unsigned int HCDMA14;
				unsigned int RESERVED14[2];
				unsigned int HCCHAR15;
				unsigned int HCSPLT15;
				unsigned int HCINT15;
				unsigned int HCINTMSK15;
				unsigned int HCTSIZ15;
				unsigned int HCDMA15;
}otg_hcs;
#define  OTG_HCS (* (volatile otg_hcs *)0xED200500 )

/*
* Device Global Registers 
*/
typedef struct {
				unsigned int HCFG;
				unsigned int DCTL;
				unsigned int DSTS;
				unsigned int RESERVED0;
				unsigned int DIEPMSK;
				unsigned int DOEPMSK;
				unsigned int DAINT;
				unsigned int DAINTMSK;
				unsigned int DTKNQR1;
				unsigned int DTKNQR2;
				unsigned int DVBUSDIS;
				unsigned int DVBUSPULSE;
				unsigned int DTKNQR3;
				unsigned int DTKNQR4;

}otg_dg;
#define  OTG_DG (* (volatile otg_dg *)0xED200800  )

/*
* Device Logical IN Endpoint-Specific Registers 
*/
typedef struct {
				unsigned int DIEPCTL0;
				unsigned int DIEPINT0;
				unsigned int DIEPTSIZ0;
				unsigned int DIEPDMA0;
				unsigned int DIEPCTL1;
				unsigned int DIEPINT1;
				unsigned int DIEPTSIZ1;
				unsigned int DIEPDMA1;
				unsigned int DIEPCTL2;
				unsigned int DIEPINT2;
				unsigned int DIEPTSIZ2;
				unsigned int DIEPDMA2;
				unsigned int DIEPCTL3;
				unsigned int DIEPINT3;
				unsigned int DIEPTSIZ3;
				unsigned int DIEPDMA3;
				unsigned int DIEPCTL4;
				unsigned int DIEPINT4;
				unsigned int DIEPTSIZ4;
				unsigned int DIEPDMA4;
				unsigned int DIEPCTL5;
				unsigned int DIEPINT5;
				unsigned int DIEPTSIZ5;
				unsigned int DIEPDMA5;
				unsigned int DIEPCTL6;
				unsigned int DIEPINT6;
				unsigned int DIEPTSIZ6;
				unsigned int DIEPDMA6;
				unsigned int DIEPCTL7;
				unsigned int DIEPINT7;
				unsigned int DIEPTSIZ7;
				unsigned int DIEPDMA7;
				unsigned int DIEPCTL8;
				unsigned int DIEPINT8;
				unsigned int DIEPTSIZ8;
				unsigned int DIEPDMA8;
				unsigned int DIEPCTL9;
				unsigned int DIEPINT9;
				unsigned int DIEPTSIZ9;
				unsigned int DIEPDMA9;
				unsigned int DIEPCTL10;
				unsigned int DIEPINT10;
				unsigned int DIEPTSIZ10;
				unsigned int DIEPDMA10;
				unsigned int DIEPCTL11;
				unsigned int DIEPINT11;
				unsigned int DIEPTSIZ11;
				unsigned int DIEPDMA11;
				unsigned int DIEPCTL12;
				unsigned int DIEPINT12;
				unsigned int DIEPTSIZ12;
				unsigned int DIEPDMA12;
				unsigned int DIEPCTL13;
				unsigned int DIEPINT13;
				unsigned int DIEPTSIZ13;
				unsigned int DIEPDMA13;
				unsigned int DIEPCTL14;
				unsigned int DIEPINT14;
				unsigned int DIEPTSIZ14;
				unsigned int DIEPDMA14;
				unsigned int DIEPCTL15;
				unsigned int DIEPINT15;
				unsigned int DIEPTSIZ15;
				unsigned int DIEPDMA15;
}otg_dlin;
#define  OTG_DLIN (* (volatile otg_dlin *)0xED200900  )

/*
* Device Logical OUT Endpoint-Specific Registers 
*/
typedef struct {
				unsigned int DOEPCTL0;
				unsigned int RESERVED0;
				unsigned int DOEPINT0;
				unsigned int RESERVED1;
				unsigned int DOEPTSIZ0;
				unsigned int DOEPDMA0;
				unsigned int RESERVED2[2];
				unsigned int DOEPCTL1;
				unsigned int RESERVED3;
				unsigned int DOEPINT1;
				unsigned int RESERVED4;
				unsigned int DOEPTSIZ1;
				unsigned int DOEPDMA1;
				unsigned int RESERVED5[2];
				unsigned int DOEPCTL2;
				unsigned int RESERVED6;
				unsigned int DOEPINT2;
				unsigned int RESERVED7;
				unsigned int DOEPTSIZ2;
				unsigned int DOEPDMA2;
				unsigned int RESERVED8[2];
				unsigned int DOEPCTL3;
				unsigned int RESERVED9;
				unsigned int DOEPINT3;
				unsigned int RESERVED10;
				unsigned int DOEPTSIZ3;
				unsigned int DOEPDMA3;
				unsigned int RESERVED11[2];
				unsigned int DOEPCTL4;
				unsigned int RESERVED12;
				unsigned int DOEPINT4;
				unsigned int RESERVED13;
				unsigned int DOEPTSIZ4;
				unsigned int DOEPDMA4;
				unsigned int RESERVED14[2];
		
				unsigned int DOEPCTL5;
				unsigned int RESERVED15;
				unsigned int DOEPINT5;
				unsigned int RESERVED16;
				unsigned int DOEPTSIZ5;
				unsigned int DOEPDMA5;
				unsigned int RESERVED17[2];
				unsigned int DOEPCTL6;
				unsigned int RESERVED18;
				unsigned int DOEPINT6;
				unsigned int RESERVED19;
				unsigned int DOEPTSIZ6;
				unsigned int DOEPDMA6;
				unsigned int RESERVED20[2];
				unsigned int DOEPCTL7;
				unsigned int RESERVED21;
				unsigned int DOEPINT7;
				unsigned int RESERVED22;
				unsigned int DOEPTSIZ7;
				unsigned int DOEPDMA7;
				unsigned int RESERVED23[2];
				unsigned int DOEPCTL8;
				unsigned int RESERVED24;
				unsigned int DOEPINT8;
				unsigned int RESERVED25;
				unsigned int DOEPTSIZ8;
				unsigned int DOEPDMA8;
				unsigned int RESERVED26[2];
				unsigned int DOEPCTL9;
				unsigned int RESERVED27;
				unsigned int DOEPINT9;
				unsigned int RESERVED28;
				unsigned int DOEPTSIZ9;
				unsigned int DOEPDMA9;
				unsigned int RESERVED29[2];
				unsigned int DOEPCTL10;
				unsigned int RESERVED30;
				unsigned int DOEPINT10;
				unsigned int RESERVED31;
				unsigned int DOEPTSIZ10;
				unsigned int DOEPDMA10;
				unsigned int RESERVED32[2];
				unsigned int DOEPCTL11;
				unsigned int RESERVED33;
				unsigned int DOEPINT11;
				unsigned int RESERVED34;
				unsigned int DOEPTSIZ11;
				unsigned int DOEPDMA11;
				unsigned int RESERVED35[2];
				unsigned int DOEPCTL12;
				unsigned int RESERVED36;
				unsigned int DOEPINT12;
				unsigned int RESERVED37;
				unsigned int DOEPTSIZ12;
				unsigned int DOEPDMA12;
				unsigned int RESERVED38[2];
				unsigned int DOEPCTL13;
				unsigned int RESERVED39;
				unsigned int DOEPINT13;
				unsigned int RESERVED40;
				unsigned int DOEPTSIZ13;
				unsigned int DOEPDMA13;
				unsigned int RESERVED41[2];
				unsigned int DOEPCTL14;
				unsigned int RESERVED42;
				unsigned int DOEPINT14;
				unsigned int RESERVED43;
				unsigned int DOEPTSIZ14;
				unsigned int DOEPDMA14;
				unsigned int RESERVED44[2];
				unsigned int DOEPCTL15;
				unsigned int RESERVED45;
				unsigned int DOEPINT15;
				unsigned int RESERVED46;
				unsigned int DOEPTSIZ15;
				unsigned int DOEPDMA15;
				unsigned int RESERVED47[2];
}otg_dgout;
#define  OTG_DGOUT (* (volatile otg_dgout *)0xED200B00  )

/*
* USB HOST CONTROLLER 
*/
typedef struct {
				unsigned int UHCREV;
				unsigned int UHCCON;
				unsigned int UHCCONSTAT;
				unsigned int UHCINTSTAT;
				unsigned int UHCINTENB;
				unsigned int UHCINTDISB;
				unsigned int UHCHCCA;
				unsigned int UHCPDCURRED;
				unsigned int UHCHDED;
				unsigned int UHCCONCURRED;
				unsigned int UHCBHDED;
				unsigned int UHCBCURRED;
				unsigned int UHCDHD;
				unsigned int UHCFMI;
				unsigned int UHCFMRM;
				unsigned int UHCFMNUM;
				unsigned int UHCPST;
				unsigned int UHCLSTH;
				unsigned int UHCRHDA;
				unsigned int UHCRHDB;
				unsigned int UHCRHSTAT;
				unsigned int UHCRHPSTAT1;
				unsigned int UHCRHPSTAT2;
				

}host;
#define  HOST (* (volatile host *)0xED400000   )

/*
*  DMA_MEM CONTROLLER 
*/
typedef struct {
				unsigned int DS;
				unsigned int DPC;
				unsigned int Reserved0[6];
				unsigned int INTEN;
				unsigned int ES;
				unsigned int INTSTATUS;
				unsigned int INTCLR;
				unsigned int FSM;
				unsigned int FSC;
				unsigned int FTM;
				unsigned int Reserved1;
				unsigned int FTC0;
				unsigned int FTC1;
				unsigned int FTC2;
				unsigned int FTC3;
				unsigned int FTC4;
				unsigned int FTC5;
				unsigned int FTC6;
				unsigned int FTC7;
}dma_mem;
#define  DMA_MEM (* (volatile dma_mem *)0xE8100000    )

/*
*  DMA_MEM Channel Status Registers.
*/
typedef struct {
				unsigned int CS0;
				unsigned int Reserved0;
				unsigned int CS1;
				unsigned int Reserved1;
				unsigned int CS2;
				unsigned int Reserved2;
				unsigned int CS3;
				unsigned int Reserved3;
				unsigned int CS4;
				unsigned int Reserved4;
				unsigned int CS5;
				unsigned int Reserved5;
				unsigned int CS6;
				unsigned int Reserved6;
				unsigned int CS7;
}dma_mem_cs;
#define  DMA_MEM_CS (* (volatile dma_mem_cs *)0xE8100100    )

/*
*  DMA_MEM Channel Program Counter Registers. 
*/
typedef struct {
				unsigned int CPC0;
				unsigned int Reserved0;
				unsigned int CPC1;
				unsigned int Reserved1;
				unsigned int CPC2;
				unsigned int Reserved2;
				unsigned int CPC3;
				unsigned int Reserved3;
				unsigned int CPC4;
				unsigned int Reserved4;
				unsigned int CPC5;
				unsigned int Reserved5;
				unsigned int CPC6;
				unsigned int Reserved6;
				unsigned int CPC7;
}dma_mem_cpc;
#define  DMA_MEM_CPC (* (volatile dma_mem_cpc *)0xE8100104    )

/*
*  DMA_MEM Source Address Registers
*/
typedef struct {
				unsigned int SA_0;
				unsigned int Reserved0[7];
				unsigned int SA_1;
				unsigned int Reserved1[7];
				unsigned int SA_2;
				unsigned int Reserved2[7];
				unsigned int SA_3;
				unsigned int Reserved3[7];
				unsigned int SA_4;
				unsigned int Reserved4[7];
				unsigned int SA_5;
				unsigned int Reserved5[7];
				unsigned int SA_6;
				unsigned int Reserved6[7];
				unsigned int SA_7;
}dma_mem_sa;
#define  DMA_MEM_SA (* (volatile dma_mem_sa *)0xE8100400    )

/*
*  DMA_MEM Destination Address Registers. 
*/
typedef struct {
				unsigned int DA_0;
				unsigned int Reserved0[7];
				unsigned int DA_1;
				unsigned int Reserved1[7];
				unsigned int DA_2;
				unsigned int Reserved02[7];
				unsigned int DA_3;
				unsigned int Reserved3[7];
				unsigned int DA_4;
				unsigned int Reserved4[7];
				unsigned int DA_5;
				unsigned int Reserved5[7];
				unsigned int DA_6;
				unsigned int Reserved6[7];
				unsigned int DA_7;
}dma_mem_da;
#define  DMA_MEM_DA (* (volatile dma_mem_da *)0xE8100404   )

/*
*  DMA_MEM Channel Control Registers
*/
typedef struct {
				unsigned int CC_0 ;
				unsigned int Reserved0[7];
				unsigned int CC_1;
				unsigned int Reserved1[7];
				unsigned int CC_2;
				unsigned int Reserved2[7];
				unsigned int CC_3;
				unsigned int Reserved3[7];
				unsigned int CC_4;
				unsigned int Reserved4[7];
				unsigned int CC_5;
				unsigned int Reserved5[7];
				unsigned int CC_6;
				unsigned int Reserved6[7];
				unsigned int CC_7;
}dma_mem_cc;
#define  DMA_MEM_CC (* (volatile dma_mem_cc *)0xE8100408   )

/*
*  DMA_MEM Loop Counter 0 Registers. 
*/
typedef struct {
				unsigned int LC0_0 ;
				unsigned int Reserved0[7];
				unsigned int LC0_1;
				unsigned int Reserved1[7];
				unsigned int LC0_2;
				unsigned int Reserved2[7];
				unsigned int LC0_3;
				unsigned int Reserved3[7];
				unsigned int LC0_4;
				unsigned int Reserved4[7];
				unsigned int LC0_5;
				unsigned int Reserved5[7];
				unsigned int LC0_6;
				unsigned int Reserved6[7];
				unsigned int LC0_7;
}dma_mem_lc0;
#define  DMA_MEM_LC0 (* (volatile dma_mem_lc0 *)0xE810040C   )

/*
*  DMA_MEM Loop Counter 1 Registers. 
*/
typedef struct {
				unsigned int LC1_0 ;
				unsigned int Reserved0[7];
				unsigned int LC1_1;
				unsigned int Reserved1[7];
				unsigned int LC1_2;
				unsigned int Reserved2[7];
				unsigned int LC1_3;
				unsigned int Reserved3[7];
				unsigned int LC1_4;
				unsigned int Reserved4[7];
				unsigned int LC1_5;
				unsigned int Reserved5[7];
				unsigned int LC1_6;
				unsigned int Reserved6[7];
				unsigned int LC1_7;
}dma_mem_lc1;
#define  DMA_MEM_LC1 (* (volatile dma_mem_lc1 *)0xE8100410   )

/*
*  DMA_MEM Loop Counter 1 EXT Registers. 
*/
typedef struct {
				unsigned int DBGSTATUS ;
				unsigned int DBGCMD;
				unsigned int DBGINST0;
				unsigned int DBGINST1;
				unsigned int Reserved6[60];
				unsigned int CR0;
				unsigned int CR1;
				unsigned int CR2;
				unsigned int CR3;
				unsigned int CR4;
				unsigned int CRDn;
}dma_mem_lc1_e;
#define  DMA_MEM_LC1_E (* (volatile dma_mem_lc1_e *)0xE8100D00   )

/*
*  DMA_peri0 Register 
*/
typedef struct {
				unsigned int DS ;
				unsigned int DPC;
				unsigned int Reserved1[6];
				unsigned int INTEN;
				unsigned int ES;
				unsigned int INTSTATUS;
				unsigned int INTCLR;
				unsigned int FSM;
				unsigned int FSC;
				unsigned int FTM;
				unsigned int Reserved2;
				unsigned int FTC0;
				unsigned int FTC1;
				unsigned int FTC2;
				unsigned int FTC3;
				unsigned int FTC4;
				unsigned int FTC5;
				unsigned int FTC6;
				unsigned int FTC7;

}dma_peri0;
#define  DMA_PERI0 (* (volatile dma_peri0 *)0xE9000000   )

/*
*  DMA_PERI0 Channel Status Registers.
*/
typedef struct {
				unsigned int CS0 ;
				unsigned int Reserved0;
				unsigned int CS1;
				unsigned int Reserved1;
				unsigned int CS2;
				unsigned int Reserved2;
				unsigned int CS3;
				unsigned int Reserved3;
				unsigned int CS4;
				unsigned int Reserved4;
				unsigned int CS5;
				unsigned int Reserved5;
				unsigned int CS6;
				unsigned int Reserved6;
				unsigned int CS7;
}dma_peri0_cs;
#define  DMA_PERI0_CS (* (volatile dma_peri0_cs *)0xE9000100   )

/*
*  DMA_PERI0 Channel Program Counter Registers
*/
typedef struct {
				unsigned int CPC0 ;
				unsigned int Reserved0;
				unsigned int CPC1;
				unsigned int Reserved1;
				unsigned int CPC2;
				unsigned int Reserved2;
				unsigned int CPC3;
				unsigned int Reserved3;
				unsigned int CPC4;
				unsigned int Reserved4;
				unsigned int CPC5;
				unsigned int Reserved5;
				unsigned int CPC6;
				unsigned int Reserved6;
				unsigned int CPC7;
}dma_peri0_cpc;
#define  DMA_PERI0_CPC (* (volatile dma_peri0_cpc *)0xE9000104   )


/*
*  DMA_PERI0 Source Address Registers. 
*/
typedef struct {
				unsigned int SA_0 ;
				unsigned int Reserved0[7];
				unsigned int SA_1;
				unsigned int Reserved1[7];
				unsigned int SA_2;
				unsigned int Reserved2[7];
				unsigned int SA_3;
				unsigned int Reserved3[7];
				unsigned int SA_4;
				unsigned int Reserved4[7];
				unsigned int SA_5;
				unsigned int Reserved5[7];
				unsigned int SA_6;
				unsigned int Reserved6[7];
				unsigned int SA_7;
}dma_peri0_sa;
#define  DMA_PERI0_SA (* (volatile dma_peri0_sa *)0xE9000400   )

/*
*  DMA_PERI0 Destination Address Registers.
*/
typedef struct {
				unsigned int DA_0 ;
				unsigned int Reserved0[7];
				unsigned int DA_1;
				unsigned int Reserved1[7];
				unsigned int DA_2;
				unsigned int Reserved2[7];
				unsigned int DA_3;
				unsigned int Reserved3[7];
				unsigned int DA_4;
				unsigned int Reserved4[7];
				unsigned int DA_5;
				unsigned int Reserved5[7];
				unsigned int DA_6;
				unsigned int Reserved6[7];
				unsigned int DA_7;
}dma_peri0_da;
#define  DMA_PERI0_DA (* (volatile dma_peri0_da *)0xE9000404   )

/*
*  DMA_PERI0 Channel Control Registers.
*/
typedef struct {
				unsigned int CC_0 ;
				unsigned int Reserved0[7];
				unsigned int CC_1;
				unsigned int Reserved1[7];
				unsigned int CC_2;
				unsigned int Reserved2[7];
				unsigned int CC_3;
				unsigned int Reserved3[7];
				unsigned int CC_4;
				unsigned int Reserved4[7];
				unsigned int CC_5;
				unsigned int Reserved5[7];
				unsigned int CC_6;
				unsigned int Reserved6[7];
				unsigned int CC_7;
}dma_peri0_cc;
#define  DMA_PERI0_CC (* (volatile dma_peri0_cc *)0xE9000408   )

/*
*  DMA_PERI0 Loop Counter 0 Registers. 
*/
typedef struct {
				unsigned int LC0_0 ;
				unsigned int Reserved0[7];
				unsigned int LC0_1;
				unsigned int Reserved1[7];
				unsigned int LC0_2;
				unsigned int Reserved2[7];
				unsigned int LC0_3;
				unsigned int Reserved3[7];
				unsigned int LC0_4;
				unsigned int Reserved4[7];
				unsigned int LC0_5;
				unsigned int Reserved5[7];
				unsigned int LC0_6;
				unsigned int Reserved6[7];
				unsigned int LC0_7;
}dma_peri0_lc0;
#define  DMA_PERI0_LC0 (* (volatile dma_peri0_lc0 *)0xE900040C   )

/*
*  DMA_PERI0 Loop Counter 1 Registers. 
*/
typedef struct {
				unsigned int LC1_0 ;
				unsigned int Reserved0[7];
				unsigned int LC1_1;
				unsigned int Reserved1[7];
				unsigned int LC1_2;
				unsigned int Reserved2[7];
				unsigned int LC1_3;
				unsigned int Reserved3[7];
				unsigned int LC1_4;
				unsigned int Reserved4[7];
				unsigned int LC1_5;
				unsigned int Reserved5[7];
				unsigned int LC1_6;
				unsigned int Reserved6[7];
				unsigned int LC1_7;
}dma_peri0_lc1;
#define  DMA_PERI0_LC1 (* (volatile dma_peri0_lc1 *)0xE9000410    )

/*
*  DMA_PERI0 Loop Counter 1 EXT Registers. 
*/
typedef struct {
				unsigned int DBGSTATUS ;
				unsigned int DBGCMD;
				unsigned int DBGINST0;
				unsigned int DBGINST1;
				unsigned int Reserved0[60];
				unsigned int CR0;
				unsigned int CR1;
				unsigned int CR2;
				unsigned int CR3;
				unsigned int CR4;
				unsigned int CRDn;
}dma_peri0_lc1_e;
#define  DMA_PERI0_LC1_E (* (volatile dma_peri0_lc1_e *)0xE9000D00    )


/*
*  DMA_peri1 Register 
*/
typedef struct {
				unsigned int DS ;
				unsigned int DPC;
				unsigned int Reserved1[6];
				unsigned int INTEN;
				unsigned int ES;
				unsigned int INTSTATUS;
				unsigned int INTCLR;
				unsigned int FSM;
				unsigned int FSC;
				unsigned int FTM;
				unsigned int Reserved2;
				unsigned int FTC0;
				unsigned int FTC1;
				unsigned int FTC2;
				unsigned int FTC3;
				unsigned int FTC4;
				unsigned int FTC5;
				unsigned int FTC6;
				unsigned int FTC7;

}dma_peri1;
#define  DMA_PERI1 (* (volatile dma_peri1 *)0xE9200000   )

/*
*  DMA_PERI1 Channel Status Registers.
*/
typedef struct {
				unsigned int CS0 ;
				unsigned int Reserved0;
				unsigned int CS1;
				unsigned int Reserved1;
				unsigned int CS2;
				unsigned int Reserved2;
				unsigned int CS3;
				unsigned int Reserved3;
				unsigned int CS4;
				unsigned int Reserved4;
				unsigned int CS5;
				unsigned int Reserved5;
				unsigned int CS6;
				unsigned int Reserved6;
				unsigned int CS7;
}dma_peri1_cs;
#define  DMA_PERI1_CS (* (volatile dma_peri1_cs *)0xE9200100   )

/*
*  DMA_PERI1 Channel Program Counter Registers
*/
typedef struct {
				unsigned int CPC0 ;
				unsigned int Reserved0;
				unsigned int CPC1;
				unsigned int Reserved1;
				unsigned int CPC2;
				unsigned int Reserved2;
				unsigned int CPC3;
				unsigned int Reserved3;
				unsigned int CPC4;
				unsigned int Reserved4;
				unsigned int CPC5;
				unsigned int Reserved5;
				unsigned int CPC6;
				unsigned int Reserved6;
				unsigned int CPC7;
}dma_peri1_cpc;
#define  DMA_PERI1_CPC (* (volatile dma_peri1_cpc *)0xE9200104   )


/*
*  DMA_PERI1 Source Address Registers. 
*/
typedef struct {
				unsigned int SA_0 ;
				unsigned int Reserved0[7];
				unsigned int SA_1;
				unsigned int Reserved1[7];
				unsigned int SA_2;
				unsigned int Reserved2[7];
				unsigned int SA_3;
				unsigned int Reserved3[7];
				unsigned int SA_4;
				unsigned int Reserved4[7];
				unsigned int SA_5;
				unsigned int Reserved5[7];
				unsigned int SA_6;
				unsigned int Reserved6[7];
				unsigned int SA_7;
}dma_peri1_sa;
#define  DMA_PERI1_SA (* (volatile dma_peri1_sa *)0xE9200400   )

/*
*  DMA_PERI1 Destination Address Registers.
*/
typedef struct {
				unsigned int DA_0 ;
				unsigned int Reserved0[7];
				unsigned int DA_1;
				unsigned int Reserved1[7];
				unsigned int DA_2;
				unsigned int Reserved2[7];
				unsigned int DA_3;
				unsigned int Reserved3[7];
				unsigned int DA_4;
				unsigned int Reserved4[7];
				unsigned int DA_5;
				unsigned int Reserved5[7];
				unsigned int DA_6;
				unsigned int Reserved6[7];
				unsigned int DA_7;
}dma_peri1_da;
#define  DMA_PERI1_DA (* (volatile dma_peri1_da *)0xE9200404   )

/*
*  DMA_PERI1 Channel Control Registers.
*/
typedef struct {
				unsigned int CC_0 ;
				unsigned int Reserved0[7];
				unsigned int CC_1;
				unsigned int Reserved1[7];
				unsigned int CC_2;
				unsigned int Reserved2[7];
				unsigned int CC_3;
				unsigned int Reserved3[7];
				unsigned int CC_4;
				unsigned int Reserved4[7];
				unsigned int CC_5;
				unsigned int Reserved5[7];
				unsigned int CC_6;
				unsigned int Reserved6[7];
				unsigned int CC_7;
}dma_peri1_cc;
#define  DMA_PERI1_CC (* (volatile dma_peri1_cc *)0xE9200408   )

/*
*  DMA_PERI1 Loop Counter 0 Registers. 
*/
typedef struct {
				unsigned int LC0_0 ;
				unsigned int Reserved0[7];
				unsigned int LC0_1;
				unsigned int Reserved1[7];
				unsigned int LC0_2;
				unsigned int Reserved2[7];
				unsigned int LC0_3;
				unsigned int Reserved3[7];
				unsigned int LC0_4;
				unsigned int Reserved4[7];
				unsigned int LC0_5;
				unsigned int Reserved5[7];
				unsigned int LC0_6;
				unsigned int Reserved6[7];
				unsigned int LC0_7;
}dma_peri1_lc0;
#define  DMA_PERI1_LC0 (* (volatile dma_peri1_lc0 *)0xE920040C   )

/*
*  DMA_PERI1 Loop Counter 1 Registers. 
*/
typedef struct {
				unsigned int LC1_0 ;
				unsigned int Reserved0[7];
				unsigned int LC1_1;
				unsigned int Reserved1[7];
				unsigned int LC1_2;
				unsigned int Reserved2[7];
				unsigned int LC1_3;
				unsigned int Reserved3[7];
				unsigned int LC1_4;
				unsigned int Reserved4[7];
				unsigned int LC1_5;
				unsigned int Reserved5[7];
				unsigned int LC1_6;
				unsigned int Reserved6[7];
				unsigned int LC1_7;
}dma_peri1_lc1;
#define  DMA_PERI1_LC1 (* (volatile dma_peri1_lc1 *)0xE9200410    )

/*
*  DMA_PERI1 Loop Counter 1 EXT Registers. 
*/
typedef struct {
				unsigned int DBGSTATUS ;
				unsigned int DBGCMD;
				unsigned int DBGINST0;
				unsigned int DBGINST1;
				unsigned int Reserved0[60];
				unsigned int CR0;
				unsigned int CR1;
				unsigned int CR2;
				unsigned int CR3;
				unsigned int CR4;
				unsigned int CRDn;
}dma_peri1_lc1_e;
#define  DMA_PERI1_LC1_E (* (volatile dma_peri1_lc1_e *)0xE9200D00    )

/*
*  CAMERA INTERFACE0  
*/
typedef struct {
				unsigned int CISRCFMTn ;
				unsigned int CIWDOFSTn;
				unsigned int CIGCTRLn;
				unsigned int Reserved0[2];
				unsigned int CIWDOFST2n;
				unsigned int CIOYSA1n;
				unsigned int CIOYSA2n;
				unsigned int CIOYSA3n;
				unsigned int CIOYSA4n;
				unsigned int CIOCBSA1n;
				unsigned int CIOCBSA2n;
				unsigned int CIOCBSA3n;
				unsigned int CIOCBSA4n;
				unsigned int CIOCRSA1n;
				unsigned int CIOCRSA2n;
				unsigned int CIOCRSA3n;
				unsigned int CIOCRSA4n;
				unsigned int CITRGFMTn;
				unsigned int CIOCTRLn;
				unsigned int CISCPRERATIOn;
				unsigned int CISCPREDSTn;
				unsigned int CISCCTRLn;
				unsigned int CITAREAn;
				unsigned int Reserved1;
				unsigned int CISTATUSn;
				unsigned int Reserved2[22];
				unsigned int CIIMGCPTn;
				unsigned int CICPTSEQn;
				unsigned int Reserved3[2];
				unsigned int CIIMGEFFn;
				unsigned int CIIYSA0n;
				unsigned int CIICBSA0n;
				unsigned int CIICRSA0n;
				unsigned int Reserved4[6];
				unsigned int CIREAL_ISIZEn;
				unsigned int MSCTRLn;
				unsigned int Reserved5[26];
				unsigned int CIOYOFFn;
				unsigned int CIOCBOFFn;
				unsigned int CIOCROFFn;
				unsigned int CIIYOFFn;
				unsigned int CIICBOFFn;
				unsigned int CIICROFFn;
				unsigned int ORGISIZEn;
				unsigned int ORGOSIZEn;
				unsigned int CIEXTENn;
				unsigned int CIDMAPARAMn;
				unsigned int Reserved6;
				unsigned int CSIIMGFMTn;
}camif0;
#define  CAMIF0 (* (volatile camif0 *)0xEE200000    )

/*
*  CAMERA INTERFACE1  
*/
typedef struct {
				unsigned int CISRCFMTn ;
				unsigned int CIWDOFSTn;
				unsigned int CIGCTRLn;
				unsigned int Reserved0[2];
				unsigned int CIWDOFST2n;
				unsigned int CIOYSA1n;
				unsigned int CIOYSA2n;
				unsigned int CIOYSA3n;
				unsigned int CIOYSA4n;
				unsigned int CIOCBSA1n;
				unsigned int CIOCBSA2n;
				unsigned int CIOCBSA3n;
				unsigned int CIOCBSA4n;
				unsigned int CIOCRSA1n;
				unsigned int CIOCRSA2n;
				unsigned int CIOCRSA3n;
				unsigned int CIOCRSA4n;
				unsigned int CITRGFMTn;
				unsigned int CIOCTRLn;
				unsigned int CISCPRERATIOn;
				unsigned int CISCPREDSTn;
				unsigned int CISCCTRLn;
				unsigned int CITAREAn;
				unsigned int Reserved1;
				unsigned int CISTATUSn;
				unsigned int Reserved2[22];
				unsigned int CIIMGCPTn;
				unsigned int CICPTSEQn;
				unsigned int Reserved3[2];
				unsigned int CIIMGEFFn;
				unsigned int CIIYSA0n;
				unsigned int CIICBSA0n;
				unsigned int CIICRSA0n;
				unsigned int Reserved4[6];
				unsigned int CIREAL_ISIZEn;
				unsigned int MSCTRLn;
				unsigned int Reserved5[26];
				unsigned int CIOYOFFn;
				unsigned int CIOCBOFFn;
				unsigned int CIOCROFFn;
				unsigned int CIIYOFFn;
				unsigned int CIICBOFFn;
				unsigned int CIICROFFn;
				unsigned int ORGISIZEn;
				unsigned int ORGOSIZEn;
				unsigned int CIEXTENn;
				unsigned int CIDMAPARAMn;
				unsigned int Reserved6;
				unsigned int CSIIMGFMTn;
}camif1;
#define  CAMIF1 (* (volatile camif1 *)0xEE300000    )

/*
*  CAMERA INTERFACE2  
*/
typedef struct {
				unsigned int CISRCFMTn ;
				unsigned int CIWDOFSTn;
				unsigned int CIGCTRLn;
				unsigned int Reserved0[2];
				unsigned int CIWDOFST2n;
				unsigned int CIOYSA1n;
				unsigned int CIOYSA2n;
				unsigned int CIOYSA3n;
				unsigned int CIOYSA4n;
				unsigned int CIOCBSA1n;
				unsigned int CIOCBSA2n;
				unsigned int CIOCBSA3n;
				unsigned int CIOCBSA4n;
				unsigned int CIOCRSA1n;
				unsigned int CIOCRSA2n;
				unsigned int CIOCRSA3n;
				unsigned int CIOCRSA4n;
				unsigned int CITRGFMTn;
				unsigned int CIOCTRLn;
				unsigned int CISCPRERATIOn;
				unsigned int CISCPREDSTn;
				unsigned int CISCCTRLn;
				unsigned int CITAREAn;
				unsigned int Reserved1;
				unsigned int CISTATUSn;
				unsigned int Reserved2[22];
				unsigned int CIIMGCPTn;
				unsigned int CICPTSEQn;
				unsigned int Reserved3[2];
				unsigned int CIIMGEFFn;
				unsigned int CIIYSA0n;
				unsigned int CIICBSA0n;
				unsigned int CIICRSA0n;
				unsigned int Reserved4[6];
				unsigned int CIREAL_ISIZEn;
				unsigned int MSCTRLn;
				unsigned int Reserved5[26];
				unsigned int CIOYOFFn;
				unsigned int CIOCBOFFn;
				unsigned int CIOCROFFn;
				unsigned int CIIYOFFn;
				unsigned int CIICBOFFn;
				unsigned int CIICROFFn;
				unsigned int ORGISIZEn;
				unsigned int ORGOSIZEn;
				unsigned int CIEXTENn;
				unsigned int CIDMAPARAMn;
				unsigned int Reserved6;
				unsigned int CSIIMGFMTn;
}camif2;
#define  CAMIF2 (* (volatile camif2 *)0xEE400000     )


/*
*  DRAM CONTROLLER  
*/
typedef struct {
				unsigned int CONCONTROL ;
				unsigned int MEMCONTROL ;
				unsigned int MEMCONFIG0 ;
				unsigned int MEMCONFIG1 ;
				unsigned int DIRECTCMD ;
				unsigned int PRECHCONFIG ;
				unsigned int PHYCONTROL0 ;
				unsigned int PHYCONTROL1 ;
				unsigned int PHYCONTROL2 ;
				unsigned int Reserved0;
				unsigned int PWRDNCONFIG ;
				unsigned int Reserved1;
				unsigned int TIMINGAREF ;
				unsigned int TIMINGROW ;
				unsigned int TIMINGDATA ;
				unsigned int TIMINGPOWER ;
				unsigned int PHYSTATUS0 ;
				unsigned int PHYSTATUS1 ;
				unsigned int CHIP0STATUS ;
				unsigned int CHIP1STATUS ;
				unsigned int AREFSTATUS ;
				unsigned int MRSTATUS ;
				unsigned int PHYTEST0 ;
				unsigned int PHYTEST1 ;
				unsigned int QOSCONTROL0 ;
				unsigned int QOSCONFIG0 ;
				unsigned int QOSCONTROL1 ;
				unsigned int QOSCONFIG1 ;
				unsigned int QOSCONTROL2 ;
				unsigned int QOSCONFIG2 ;
				unsigned int QOSCONTROL3 ;
				unsigned int QOSCONFIG3 ;
				unsigned int QOSCONTROL4 ;
				unsigned int QOSCONFIG4 ;
				unsigned int QOSCONTROL5 ;
				unsigned int QOSCONFIG5 ;
				unsigned int QOSCONTROL6 ;
				unsigned int QOSCONFIG6 ;
				unsigned int QOSCONTROL7 ;
				unsigned int QOSCONFIG7 ;
}dram;
#define  DRAM (* (volatile dram *)0xE6000000      )

/*
*  STATIC MEMORY CONTROLLER 
*/
typedef struct {
				unsigned int SMC_BW   ;
				unsigned int SMC_BC0  ;
				unsigned int SMC_BC1  ;
				unsigned int SMC_BC2  ;
				unsigned int SMC_BC3  ;
				unsigned int SMC_BC4  ;
				unsigned int SMC_BC5  ;
}sram;
#define  SRAM (* (volatile sram *)0xE7000000      )


#endif


