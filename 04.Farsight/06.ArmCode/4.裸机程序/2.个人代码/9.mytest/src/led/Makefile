# CORTEX-A9 PERI DRIVER CODE
# VERSION 2.0
# ATHUOR liujh@farsight.com.cn
# MODIFY DATE 
# 2014.05.28  Makefile

CROSS_COMPILE = arm-linux-
NAME = adc_init
#=============================================================================#
CFLAGS += -g   -O0  -mabi=apcs-gnu -mfpu=neon -mfloat-abi=softfp  -fno-builtin \
			-nostdinc  -I.
CC	= $(CROSS_COMPILE)gcc


#============================================================================#
OBJSss 	:= $(wildcard *.c) $(wildcard *.S)
OBJSs  	:= $(patsubst %.S,%.o,$(OBJSss))
OBJS 	:= $(patsubst %.c,%.o,$(OBJSs))


#============================================================================#
%.o: %.S 
	$(CC) $(CFLAGS) -c -o  $@ $<
#%.o: %.s 
#	$(CC) $(CFLAGS) -c -o  $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o  $@ $<
all:clean  $(OBJS)
	$(LD)  $(OBJS) -T map.lds -o $(NAME).elf
	$(OBJCOPY)  -O binary  $(NAME).elf $(NAME).bin 
	$(OBJDUMP) -D $(NAME).elf > $(NAME).dis 
#============================================================================#
clean:
	rm -rf $(OBJS) 
#============================================================================#
