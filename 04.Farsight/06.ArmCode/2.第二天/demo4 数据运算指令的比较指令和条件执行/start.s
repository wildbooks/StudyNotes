	area first, code, readonly
	code32
	entry
start
	 ; 一般做分支运算的时候常用减法
	 ; if （r0 == r1) 
	 ;    mov r2, #2
	 mov r0, #1
	 mov r1, #2
	 ;subs r0, r0, r1	;在条件 分支操作中， 我们常常需要判断两个值大小 是否相等， 但又不想保存计算结果
	 ; 在这种情况下用 比较指令
	 ; cmp 指令 计算效果等同于 SUBS，但不保存结果
	 cmp r0, r1
	 moveq r2, #2

	 ; if （r0 > r1) 
	 ;    mov r2, #2
   	 mov r0, #1
	 mov r1, #2
	 subs r0, r0, r1
	 movgt r2, #2

  	 ; if （r0 < r1) 
	 ;    mov r2, #2
   	 mov r0, #1
	 mov r1, #2
	 subs r0, r0, r1
	 movlt r2, #2

stop 
	b stop 
	end