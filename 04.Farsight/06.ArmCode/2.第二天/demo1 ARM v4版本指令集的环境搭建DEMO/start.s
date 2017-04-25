	area first, code, readonly  ;定义一个代码段 first
	code32
	entry
start 
	mov r0, #1
	mov r1, #2
	add r0, r1, r1
	nop 
	b start

	end