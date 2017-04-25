	area first, code, readonly
	code32
	entry
start
	; mov mvn 
	; 数据处理指令的基本应用
	mov r0, #1
	mov r1, #2

	; 1. add 
	add r2, r0, r1	; r2 = r0 + r1
	add r2, r0, #4
	add r2, r0, r1, lsl #2 ;  r2 = r0　＋　Ｒ１＜＜２；　（Ｒ０　＋　Ｒ１　＊　４）

 	mov r0, #0
	mov r1, #0xffffffff
  	mov r2, #0
	mov r3, #0x1
	; 2. adc  64位加法 r0, r1 =  r0, r1 + r2, r3　　
	adds r1, r1, r3 ; r1 = r1 + r3	 必须加S后缀
	adc r0, r0, r2	; r0 = r0 + r2 + c

	; 3. sub  rd = rn - op2 
	mov r0, #1
	sub r0, r0, #1	; r0 = r0 - 1

	; 4. sbc  64位减法 r0, r1 =  r0, r1 - r2, r3　
    ; cpsr c 对于加法运算 C = 1 则代表有进位， C = 0 无进位
	;		 对于减法运算 C = 1 则代表无借位， C = 0 有借位
 	mov r0, #0
	mov r1, #0x0
  	mov r2, #0
	mov r3, #0x1
	subs r1, r1, r3 
	sbc r0, r0, r2

	; 5. rsb   sub指令  rd = rn - op2 	rsb = op2 - rn
	; eg 求 R1 寄存器的负数
	mov r0, #0
	sub r1, r0, r1
	; rsb 作为SUB指令的补充，RSB 使用 OP2作为被减数，更灵活
	rsb r1, r1, #0 ; r1 = 0 - r1

	; 6... rsc	带借位的逆向减法，效果同 SBC指令

	; 7. and 
	and r0, r0, #0x01       ; 取最低为的值
	and r0, r0, #0xfffffffe ; 将最低位清零

	; 8. orr
	orr r0, r0, #0x01       ; 将最低位设置1 

	; 9. eor  
	 
	; 10. bic 位清除 
	mov r0, #0xffffffff
	bic r0, r0, #0xff ; and r0, r0, #0xffffff00 




stop 
	b stop 
	end