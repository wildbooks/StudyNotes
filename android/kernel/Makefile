ifeq ($(KERNELRELEASE),)

TEMP_TOP=/work1/Q_SDM636_M1_dev
KERNEL_CROSS_COMPILE = $(TEMP_TOP)/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
TARGET_KERNEL_MAKE_ENV += HOSTCC=$(TEMP_TOP)/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-gcc
TARGET_KERNEL_MAKE_ENV += HOSTAR=$(TEMP_TOP)/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ar
TARGET_KERNEL_MAKE_ENV += HOSTLD=$(TEMP_TOP)/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ld
TARGET_KERNEL_MAKE_ENV += HOSTCFLAGS="-I/usr/include -I/usr/include/x86_64-linux-gnu -L/usr/lib -L/usr/lib/x86_64-linux-gnu"
TARGET_KERNEL_MAKE_ENV += HOSTLDFLAGS="-L/usr/lib -L/usr/lib/x86_64-linux-gnu"
TARGET_KERNEL_SOURCE=$(TEMP_TOP)/kernel/msm-4.4
#TARGET_KERNEL_SOURCE=/work1/msm-4.4
KERNEL_OUT=$(TEMP_TOP)/out/target/product/sdm660_64/obj/kernel/msm-4.4
KERNEL_MODULES_INSTALL=$(TEMP_TOP)/out/target/product/sdm660_64/dlkm
KERNEL_DEFCONFIG=ql1650-perf_defconfig
CUR_DIR =$(shell pwd)

all:

modules:
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android modules

kernel:
	rm -rf $(KERNEL_OUT)/arch/arm64/boot/dts
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android modules
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android INSTALL_MOD_PATH=$(KERNEL_MODULES_INSTALL) INSTALL_MOD_STRIP=1 modules_install

kernel_headers_install:
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) $(KERNEL_DEFCONFIG)
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE)

config:
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) $(KERNEL_DEFCONFIG)

kernelconfig:
	env KCONFIG_NOTIMESTAMP=true \
		make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) menuconfig
	env KCONFIG_NOTIMESTAMP=true \
		make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) savedefconfig
	cp $(KERNEL_OUT)/defconfig $(TARGET_KERNEL_SOURCE)/arch/arm64/configs/$(KERNEL_DEFCONFIG)

distclean:
	make -j6 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) $(TARGET_KERNEL_MAKE_ENV) ARCH=arm64 CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) distclean

install:
	#adb push *.ko 
else
	# 用于指定到底编译哪个代码—hello.c
	obj-m:=hello.o
endif
