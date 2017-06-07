
PROJECT_NAME=write
PROJECT_NAME1=read

ifneq ($(KERNELRELEASE),)
obj-m:=hello.o
else
KDIR := /lib/modules/$(shell uname -r)/build/
#KDIR := ~/LinuxCode/Linux/linux-3.14-wildbook-fs4412/

PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
	$(CC) -o $(PROJECT_NAME) write.c	
	$(CC) -o $(PROJECT_NAME1) read.c	
clean:
	rm -rf *.ko *.o  *.mod.c *.order Module.symvers $(PROJECT_NAME)\
		$(PROJECT_NAME1)
endif
