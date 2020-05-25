[toc]

# bootz

tftp 80800000 zImage

tftp 83000000 imx6ull-14x14-emmc-7-1024x600-c.dt

bootz 80800000 – 83000000

从内存引导zImag镜像

# bootm

# booti

# linux内核引导分类

通过bootloader的内存引导

通过bootloader的网络引导([tftp](https://openwrt.org/docs/guide-user/installation/generic.flashing.tftp)/[ftp](https://openwrt.org/docs/guide-user/installation/generic.flashing.ftp)/[xmodem](https://openwrt.org/docs/guide-user/installation/generic.flashing.xmodem))

通过bootloader的mmc引导

通过bootloader的usb引导

通过bootloader的串口引导