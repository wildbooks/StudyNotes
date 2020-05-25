# 固件区别
initramfs-kernel.bin   首次安装用ram固件。可以直接加载到ram运行
squashfs-mtd2-kernel.bin 首次安装用内核文件
squashfs-mtd5-rootfs.bin    首次安装用rootfs文件
squashfs-sysupgrade.tar  sysupgrade标准更新文件

# squashfs-sysupgrade.tar
该文件由CONTROL、kernel、root文件组成。
kernel为linux内核。而root为squashfs根文件系统


# linux引导过程
 BootLoader、kernel、initrd、rootfs
https://www.oschina.net/question/129540_116839
