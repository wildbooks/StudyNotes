/*
 * Lowlevel setup for ORIGEN board based on EXYNOS4210
 * Copyright (C) 2014 farsight
 * Version: 1.1
 * Date:	2014.6.24
 * Describe: MoutAPLL: 1Ghz for arm
 *			 MoutMPLL: 800Mhz
 *			 SclkMpll_USER_T : 800Mhz
 *			 Aclk_100: 100Mhz for PERIL and PERIR
 */


#include "4412_clock.h"

/* add by cym 20130218 */
wait_mux_state:
	ldr r1, [r0, r2]
	cmp r1, r3
	bne wait_mux_state
	mov pc, lr

wait_pll_lock:
	ldr r1, [r0, r2]
	tst r1, #(1<<29)
	beq wait_pll_lock
	mov pc, lr


/*
 * system_clock_init: Initialize core clock and bus clock.
 * void system_clock_init(void)
 */

.global system_clock_init
system_clock_init:
	push {lr}

 @ CMU_CPU MUX / DIV
	ldr r0, =CLOCK_BASE   @0x1003_0000

	ldr r1, =0x01000001
	ldr r2, =CLK_SRC_CPU_OFFSET
	str r1, [r0, r2]

	ldr r2, =CLK_MUX_STAT_CPU_OFFSET
	ldr r3, =0x02110002
	bl wait_mux_state

	ldr r1, =CLK_DIV_DMC0_VAL
	ldr r2, =CLK_DIV_DMC0_OFFSET
	str r1, [r0, r2]
    ldr r1, =CLK_DIV_DMC1_VAL
	ldr r2, =CLK_DIV_DMC1_OFFSET
    str r1, [r0, r2]

@ CMU_TOP MUX / DIV
	ldr r1, =0x0
	ldr r2, =CLK_SRC_TOP0_OFFSET
	str r1, [r0, r2]

	ldr r2, =CLK_MUX_STAT_TOP_OFFSET
	ldr r3, =0x11111111
	bl wait_mux_state

	ldr r1, =0x01000
	ldr r2, =CLK_SRC_TOP1_OFFSET
	str r1, [r0, r2]

	ldr r2, =CLK_MUX_STAT_TOP1_OFFSET
	ldr r3, =0x01112110
	bl wait_mux_state

	ldr r1, =CLK_DIV_TOP_VAL
	ldr r2, =CLK_DIV_TOP_OFFSET
	str r1, [r0, r2]

@ CMU_LEFTBUS MUX / DIV
	ldr r1, =0x10
	ldr r2, =CLK_SRC_LEFTBUS_OFFSET
	str r1, [r0, r2]

	ldr r2, =CLK_MUX_STAT_LEFTBUS_OFFSET
	ldr r3, =0x00000021
	bl wait_mux_state

	ldr r1, =CLK_DIV_LEFRBUS_VAL
	ldr r2, =CLK_DIV_LEFTBUS_OFFSET
	str r1, [r0, r2]

@ CMU_RIGHTBUS MUX / DIV
	ldr r1, =0x10
    ldr r2, =CLK_SRC_RIGHTBUS_OFFSET
    str r1, [r0, r2]

    ldr r2, =CLK_MUX_STAT_RIGHTBUS_OFFSET
    ldr r3, =0x00000021
    bl wait_mux_state

    ldr r1, =CLK_DIV_RIGHTBUS_VAL
    ldr r2, =CLK_DIV_RIGHTBUS_OFFSET
    str r1, [r0, r2]

@ Set PLL locktime
	ldr	r1, =APLL_LOCK_VAL
	ldr	r2, =APLL_LOCK_OFFSET
	str	r1, [r0, r2]

	ldr	r1, =MPLL_LOCK_VAL
	ldr	r2, =MPLL_LOCK_OFFSET
	str	r1, [r0, r2]

	ldr	r1, =EPLL_LOCK_VAL
	ldr	r2, =EPLL_LOCK_OFFSET
	str	r1, [r0, r2]

	ldr	r1, =VPLL_LOCK_VAL
	ldr	r2, =VPLL_LOCK_OFFSET
	str	r1, [r0, r2]

	ldr	r1, =CLK_DIV_CPU0_VAL
	ldr	r2, =CLK_DIV_CPU0_OFFSET
	str	r1, [r0, r2]
	ldr	r1, =CLK_DIV_CPU1_VAL
	ldr	r2, =CLK_DIV_CPU1_OFFSET
	str	r1, [r0, r2]

@ Set APLL
	ldr	r1, =APLL_CON1_VAL
	ldr	r2, =APLL_CON1_OFFSET
	str	r1, [r0, r2]
	ldr	r1, =APLL_CON0_VAL
	ldr	r2, =APLL_CON0_OFFSET
	str	r1, [r0, r2]

@ Set MPLL
     ldr r1, =MPLL_CON1_VAL
     ldr r2, =MPLL_CON1_OFFSET
     str r1, [r0, r2]
     ldr r1, =MPLL_CON0_VAL
     ldr r2, =MPLL_CON0_OFFSET
     str r1, [r0, r2]

@Set UART_src_clock
    ldr r0, =CLOCK_BASE   @0x1003_0000
    ldr r1, =CLK_SRC_PERIL0_VAL     @0x666666
    ldr r2, =CLK_SRC_PERIL0_OFFSET
	str r1, [r0, r2]
	ldr r1, =CLK_DIV_PERIL0_VAL     @0x777777
	ldr r2, =CLK_DIV_PERIL0_OFFSET
	str r1, [r0, r2]

#if 0
.globl uart_asm_init
uart_asm_init:

    /* set GPIO to enable UART */
    @ GPIO setting for UART for UART0/1
    ldr r0, =0x11400000
    ldr r1, =0x22222222
    str     r1, [r0]
    ldr r0, =0x11400020
    ldr r1, =0x222222
    str r1, [r0]

	ldr r0, =ELFIN_UART_CONSOLE_BASE
	ldr r1, =0x111
	str r1, [r0, #UFCON_OFFSET]

	mov	r1, #0x3
	str	r1, [r0, #ULCON_OFFSET]

	ldr	r1, =0x3c5
	str	r1, [r0, #UCON_OFFSET]

	ldr	r1, =UART_UBRDIV_VAL	@0x2B /*  UDIV(43) = ((82,500,000 / 16 / 115200) - 1) */
	str	r1, [r0, #UBRDIV_OFFSET]

	ldr	r1, =UART_UDIVSLOT_VAL	@0xC /* UFRACVAL(12) = ((((82,500,000 / 16 / 115200) - 1) - 43) * 16) */
	str	r1, [r0, #UFRACVAL_OFFSET]

	ldr	r1, =0x4f4f4f4f
	str	r1, [r0, #UTXH_OFFSET]		@'O'
#endif

	pop {pc}
