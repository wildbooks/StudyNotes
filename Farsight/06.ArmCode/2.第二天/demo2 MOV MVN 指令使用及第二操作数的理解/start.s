	area first, code, readonly
	code32
	entry 
start
    ; 指令格式 mov rd, op2
	; 1. 第二操作数可以是立即数， 立即数就是直接存储在指令中的数字，
	;    因为 ARM 的指令编码只有 32 bit, 因此， 立即数受指令集编码限制有使用的规范， 使用规范参考ARM指令集编码
	mov r0, #1 	;#代表是立即数  
	mov r0, #2 	;#代表是立即数  
	mov r0, #3 	;#代表是立即数  
	mov r0, #4 	;#代表是立即数  
	; 查看上面指令的机器码，观察立即数的规律
   
    ; 立即数是由 0-255之间的数据循环右移偶数位生成 	  
    mov r0, #0xff000000  ; 0x000000ff 循环右移 8 bit =》 对应机器码是 0xE3A004FF
	; 合法立即数的判断  #200  0x13800000, 0x13810000
	                          ;0b 0001,0011,1000,0000,0000,0000,0000,0000 
	;0xffffffff 是合法立即数吗？
	mov r0, #0xffffffff ; MVN 指令的作用
	mvn r0, #0x1 ; MVN 指令第二操作数按位取反再传输

	; 2. 第二操作数还可以是寄存器
	mov r0, r1

	; 第二操作数 寄存器移位操作， 5种移位方式， 9种语法
	;逻辑左移
	mov r0, #0x1
	mov r1, r0, lsl #1    ; 移位位数1-31肯定合法
	
	mov r0, #0x2
	mov r1, r0, lsr #1	   ; 逻辑右移

	mov r0, #0xffffffff
	mov r1, r0, asr #1	   ; 算数右移符号位不变， 次高位补符号位

	mov r0, #0x7fffffff
	mov r1, r0, asr #1

   	mov r0, #0x7fffffff
	mov r1, r0, ror #1	; 循环右移

   	mov r0, #0xffffffff
	mov r1, r0, rrx	; 唯一不需要指定循环位数的移位方式

	; 移位值可以是另一个寄存器的值低8bit， 写法如下 
	mov r2, #1
	mov r0, #0x1
	mov r1, r0, lsl r2    ; 移位位数1-31肯定合法
c
	mov r0, #0xffffffff
	mov r1, r0, asr r2	   ; 算数右移符号位不变， 次高位补符号位

	mov r0, #0x7fffffff
	mov r1, r0, asr r2

   	mov r0, #0x7fffffff
	mov r1, r0, ror r2	; 循环右移

	; 加 S后缀才影响 CPSR 更新， CMP CMN TST TEQ 除外
	mov r0, #1
	mov r1, r0, lsr #1
	movs r1, r0, lsr #1

stop 
	b stop  

		 
	end