# test1		make ARCH=arm
ifeq ("$(ARCH)", "arm")                                                                                                                      
	CROSS_COMPILE := arm
endif                                                                                                                                                     

# test2		make
# 第二个不知怎么测试
ifndef CROSS                                                                                                                                   
	CROSS_COMPILE := gcc
endif  

ifdef CROSS                                                                                                                                     
	CROSS_COMPILE := arm-linux-gcc
endif  

# test3		shell命令的使用
SUBB := $(shell ls -l)   

# test4		=,:=,?=三者区别
# 		?=:条件赋值
# 		 =:Makefile全部展开,后一次展开的值是要赋的值
# 		:=:把当前值付给它

# test5 wildcard,patsubst,notdir
SRC := $(wildcard *.org)
SRC := $(wildcard *.org 10.vim/*.org)
SRCD := $(patsubst %.org, %.o,$(wildcard *.org))	#把xx.org改成xx.o
SRD := $(notdir $(SRC))	#去掉路径信息

# test export unexport 导出/取消导出环境变量

# 编译器中常用变量
#  CC          C compiler command    c编译器
#  CFLAGS      C compiler flags      c编译标识符
#  LDFLAGS     链接标识符 -L<lib dir> 添加非标准库
#  LIBS        库传递给编译器, 例如 -l<library>
#  CPPFLAGS    c预编译标识符,例如-I<include dir>添加非标准库路径
#  CPP         C preprocessor C预编译
#  LIBOBJS
#  OBJDUMP
#  STRIP
CPP = gcc -E 
all:
	@echo $(CROSS_COMPILE)
	@echo $(SRC)
	@echo ==========================
	@echo $(SRCD)
	@echo $(SRD)
