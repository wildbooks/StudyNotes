ifneq ($(KERNELRELEASE),)



obj-m := fw.o



else

KDIR  := /lib/modules/$(shell uname -r)/build



PWD := $(shell pwd)

all:

	make -C  $(KDIR) M=$(PWD)  modules

clean:

	rm -f *.ko *.o *.mod.o *.symvers

endif



 

 

