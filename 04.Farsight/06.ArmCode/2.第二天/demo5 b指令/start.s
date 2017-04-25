	area first, code, readonly
	code32
	entry
start
	; bl 指令, 子函数调用
	bl child_func  ;0xeb 00 00 01  注意BL 的跳转限制，因为指令集的限制，BL跳转范围受限， 看BL的机器码编码规范
	nop
	;while (1);
stop 
	b stop 


; 子函数
child_func 
	mov r0, #1	; <===  pc
	; bl child_func1
	;子函数返回
	mov pc, lr

	end
