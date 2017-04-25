

APP_NAME=app_led


ifneq ($(KERNELRELEASE),)
obj-m:=led.o
else
#KDIR := /lib/modules/$(shell uname -r)/build/
KDIR := /home/wildbook/Documents/04.华清远见培训笔记/08.driver/linux-3.14-wildbook-fs4412
PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
	arm-linux-gcc test.c -o $(APP_NAME)
	cp *.ko $(APP_NAME)  /mnt/rootfs_wildbook_fs4412/root
clean:
	rm -rf *.ko *.o  *.mod.c *.order Module.symvers $(APP_NAME)
endif
