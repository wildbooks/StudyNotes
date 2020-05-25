[toc]

# u-boot 中autoscr命令使用

> 命令说明：
>
> 在u-boot中可以用autoscr命令运行脚本。
>
> 使用方法：
>
> 首先创建文本,输入要执行的命令，然后用tools/mkimage封装，然后下载到开发板中，在u-boot命令行，用autoscr执行下载的脚本镜像文件即可。

## 1.本文以烧写UBIFS格式的Android文件系统为例说明：

1)编辑如下的脚本nand-ubifs-write.script，也可参见附件

```bash
tftp 0x90800000 uramdisk.img;
nand erase ramdisk;nand write ${fileaddr} ramdisk;
nand erase system;
ubi part system;
ubi create system;
tftp 0x90800000 system.img;
ubi write ${fileaddr} system ${filesize};

nand erase userdata;
ubi part userdata;
ubi create userdata;
tftp 0x90800000 userdata.img;
ubi write ${fileaddr} userdata ${filesize};

nand erase cache;
ubi part cache;
ubi create cache;reset
```

2)用tools/mkimage对脚本进行封装

```bash
mkimage -A ARM -O linux -T script -C none -a 0 -e 0 -n "autoscr  nand-ubifs-write script" -d nand-ubifs-write.script  /tftpboot/nand-ubifs-write.img
```

3)在u-boot中加载并执行脚本

```bash
set servrerip 10.10.66.145      #10.10.66.145为tftp服务器
tftp 0x90800000 nand-ubifs-write.img
autoscr 0x90800000
```

通过以上命令即可更新Android文件系统。

快速自动烧写方式：

可以将要执行的命令设置为环境变量，运行环境变量,即可达到自动烧写的目的。

a.设置环境变量

```bash
setenv nand-ubifs-write 'tftp 0x90800000 nand-ubifs-write.img;autoscr 0x90800000'
saveenv
```

b.执行环境变量，自动烧写系统镜像文件

```
run nand-ubifs-write
```

## 2.使用SD卡启动后烧写全新的镜像文件方法

将要烧写的镜像文件包括：u-boot.bin,uImage,uramdisk.img,system.img,userdata.img

准备工作：

搭建好tftp服务器，将要烧写的镜像文件放置于tftp服务器的/tftpboot/目录中

1)在PC端linux下，编辑脚本nand-all-image-write.script如下，也可参见附件

```bash
tftp 0x90800000 u-boot.bin;
mtdparts default;save;
nand erase uboot;
nand write ${fileaddr} uboot;
tftp uImage;
nand erase kernel;
nand write ${fileaddr} kernel;
tftp uramdisk.img;
nand erase ramdisk;
nand write ${fileaddr} ramdisk;
nand erase system;
ubi part system;
ubi create system;
tftp system.img;
ubi write ${fileaddr} system ${filesize};
nand erase userdata;
ubi part userdata;
ubi create userdata;
tftp userdata.img;
ubi write ${fileaddr} userdata ${filesize};
nand erase cache;
ubi part cache;ubi create cache;reset
```

2)在PC端linux环境下，用tools/mkimage对脚本进行封装

```bash
mkimage -A ARM -O linux -T script -C none -a 0 -e 0 -n "autoscr  nand-all-image-write script" -d nand-all-image-write.script  /tftpboot/nand-all-image-write.img
```

3)通过SD卡启动进入u-boot命令行，执行如下的命令

```bash
set servrerip 10.10.66.145      #10.10.66.145为tftp服务器
tftp 0x90800000 nand-ubifs-write.img
autoscr 0x90800000
```

快速自动烧写方式：

可以将要执行的命令设置为环境变量，运行环境变量,即可达到自动烧写的目的。

a.设置环境变量

```bash
setenv nand-all-image 'tftp 0x90800000 nand-all-image-write.img;autoscr 0x90800000'
saveenv
```

b.执行环境变量，自动烧写系统镜像文件

```bash
run nand-all-image
```

通过以上命令即可更新u-boot,kernel,Android文件系统。

注意：在1)中的脚本长度可能已经超出了uboot中参数的最大限度,我们目前设置为512，所以附件中将重复的下载地址0x90800000给去掉了，

这时u-boot会使用环境变量fileaddr作为默认下载地址，脚本中我们第一次下载u-boot.bin时就可以自动设置改值。

如果直接使用我的脚本，就不用关心这些。