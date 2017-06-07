
CC:=gcc
PROJECT_NAME=app

ifneq ($(KERNELRELEASE),)
obj-m:=hello.o
else
KDIR := /lib/modules/$(shell uname -r)/build/
#KDIR := /home/wildbook/Documents/04.华清远见培训笔记/08.driver/linux-3.14-wildbook-fs4412

PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
	$(CC) -o $(PROJECT_NAME) test.c	
clean:
	rm -rf *.ko *.o  *.mod.c *.order Module.symvers $(PROJECT_NAME)
endif
