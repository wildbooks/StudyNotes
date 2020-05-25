# linux系统中如何打开察看img文件内容
    1. 可以把img的文件理解成一个磁盘，一个以文件的二进制形式存在的磁盘。
    2. 磁盘里面肯定有一些分区。
    因此可直接mount进行挂载磁盘里面的分区。使用mount挂载分区前，需要用到fdisk工具获取img磁盘文件的分区的开始地址。

# 利用fdisk工具获取img磁盘文件的分区开始地址
```
$ fdisk noogie.img

Command (m for help): p

Disk noogie.img: 79 MB, 79691776 bytes
128 heads, 32 sectors/track, 38 cylinders, total 155648 sectors
Units = sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disk identifier: 0x00000000

     Device Boot      Start         End      Blocks   Id  System
noogie.img1   *          32      155647       77808    c  W95 FAT32 (LBA)
```
其中的start是32,要转换下：32X512=16384B，这个很重要，下面的mount命令中参数offset中要用到
# 挂载分区
```
sudo mount -o loop,offset=16384 noogie.img /mnt/
```
