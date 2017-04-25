CC := arm-linux-gcc
PROJECT_NAME = app-key
ifneq ($(KERNELRELEASE),)
obj-m:=device.o driver.o
else
#KDIR := /lib/modules/$(shell uname -r)/build/
KDIR := /home/wildbook/LinuxCode/Linux/linux-3.14-wildbook-fs4412

PWD:=$(shell pwd)
all:
	make -C $(KDIR)  M=$(PWD)  modules
	#$(CC) -o $(PROJECT_NAME) test.c
	cp -rf *.ko $(PROJECT_NAME) /mnt/rootfs_wildbook_fs4412/root
clean:
	rm -rf .[a-Z]* *.???* *.o
distclean:
	rm -rf .[a-Z]* *.??* *.o $(PROJECT_NAME)
	rm -rf /mnt/rootfs_wildbook_fs4412/root/*

endif
