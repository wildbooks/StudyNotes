CC := arm-linux-gcc
PROJECT_NAME = app-mpu6050
ifneq ($(KERNELRELEASE),)
obj-m:=mpu6050.o
else
#KDIR := /lib/modules/$(shell uname -r)/build/
KDIR := /home/wildbook/LinuxCode/Linux/linux-3.14-wildbook-fs4412

PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
	$(CC) -o $(PROJECT_NAME) test.c
	cp  *.ko $(PROJECT_NAME) /mnt/rootfs_wildbook_fs4412/root
clean:
	rm -rf .[^.]*  *.[^ckh]*
distclean:
	rm -rf .[^.]* *.[^ch]*  $(PROJECT_NAME)
	rm -rf /mnt/rootfs_wildbook_fs4412/root/*

endif
