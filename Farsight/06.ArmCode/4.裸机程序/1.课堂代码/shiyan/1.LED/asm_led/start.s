/*
 * start.s
 *
 *  Created on: 2014-8-29
 *      Author: Administrator
 */
.section .text    @area code
.arm              @code32
.global  _start   @entry

_start:
@	ldr r0, =0x11000c20  @x1:bit0 :0x11000c40  @x2:bit7:0x11000c20
@	ldr r1, =0x11000c24

	ldr r0, =0x11000c40  @x1:bit0 :0x11000c40  @x2:bit7:0x11000c20
	ldr r1, =0x11000c44

	ldr r2, =0x10000000   @设置io 为output
	str r2, [r0]
	ldr r2,=0x0
	str r2,[r1]



led_loop:
	@点灯
	mov r2, #0x80     @输出高电平
	str r2, [r1]
	mov r4, #0x1000
	bl asm_delay
	@关灯
	mov r2, #0x0
	str r2, [r1]
	mov r4, #0x1000
	bl asm_delay

	b led_loop

asm_delay:
	mov r4, #0x10000000
delay_loop:
	cmp r4, #0
	subgt r4, r4, #1
	bgt delay_loop
	mov pc, lr


	.end         @end
