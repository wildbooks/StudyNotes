SHELL=C:/windows/system32/cmd.exe
CROSS_COMPILE = arm-none-eabi-

all:
	$(CROSS_COMPILE)gcc -c -o start.o start.s
	$(CROSS_COMPILE)ld start.o -Ttext  0x40008000 -o test.elf
	$(CROSS_COMPILE)objdump -D test.elf > test.dis
	$(CROSS_COMPILE)objcopy -O binary test.elf test.bin

clean:
	rm -rf *.o *.bin *.elf *.dis
	 