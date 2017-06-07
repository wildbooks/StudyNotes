EXTRA_CFLAGS := -g
obj-m += my_debugfs.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ SUBDIRS=$(shell pwd) modules 
clean:
	rm *.[^c]*
