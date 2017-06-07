SHELL=C:/windows/system32/cmd.exe

##############################################################
CROSS_COMPILE = arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

CFLAGS = -c -g -O0 -o
############################################################## 

objs = start.o led_main.o

pro_name = asm_c
##############################################################

all:$(objs)
	$(LD) $(objs) -Tmap.lds -o $(pro_name).elf                
#链接
	$(OBJCOPY) -O binary $(pro_name).elf $(pro_name).bin
#二进制提取
	$(OBJDUMP) -D $(pro_name).elf > $(pro_name).dis
#反汇编


%.o : %.s	
	$(CC) $(CFLAGS)  $@ $<
#-c 只编译不链接 -g 调试  -O0优化等级 -O1 -O2 -o 输出
%.o : %.c	
	$(CC) $(CFLAGS)  $@ $<
#$@：目标    $<：第一个依赖      $^: 多个依赖


clean:
	rm -rf *.bin *.elf *.dis $(objs)
	 