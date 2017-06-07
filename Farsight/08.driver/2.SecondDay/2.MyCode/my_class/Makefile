ifneq ($(KERNELRELEASE),)
obj-m:=hello.o
else
KDIR := /lib/modules/$(shell uname -r)/build/
PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
clean:
	rm -rf *.ko *.o  *.mod.c *.order Module.symvers
endif