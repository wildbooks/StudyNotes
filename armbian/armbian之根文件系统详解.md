原来对mkinitrd不是很了解。最近做内核升级，需要制作信息的initrd文件，发现出错。所以就看看了关于mkinitrd的一些资料。

 

mkinitrd就是制作boot目录下面的initrd文件。这个文件最开始是ext2文件系统，现在基本不用了。目前都是用cpio格式的文件。该文件一般是经过gzip压缩制作的。



## cpio形式的initrd文件系统解析

基本流程如下：

```bash
[root@localhost init]# file initrd-2.6.28.9.img 
initrd-2.6.28.9.img: gzip compressed data, from Unix, last modified: Thu May 21 10:43:12 2009, max compression
[root@localhost init]# mv initrd-2.6.28.9.img initrd-2.6.28.9.img.gz
[root@localhost init]# gunzip initrd-2.6.28.9.img.gz 
[root@localhost init]# file initrd-2.6.28.9.img 
initrd-2.6.28.9.img: ASCII cpio archive (SVR4 with no CRC)
[root@localhost init]# cpio -i < initrd-2.6.28.9.img 
10933 blocks
```

对于老的内核initrd，是使用的ext2文件系统

```bash
[root@redhat init]# file initrd-2.4.20-8.img 
initrd-2.4.20-8.img: gzip compressed data, from Unix, max compression
[root@redhat init]# mv initrd-2.4.20-8.img initrd-2.4.20-8.img.gz
[root@redhat init]# gunzip initrd-2.4.20-8.img.gz 
[root@redhat init]# file initrd-2.4.20-8.img 
initrd-2.4.20-8.img: Linux rev 1.0 ext2 filesystem data
[root@redhat init]# mkdir mnt
[root@redhat init]# mount initrd-2.4.20-8.img mnt/ -t ext2
mount: initrd-2.4.20-8.img is not a block device (maybe try `-o loop'?)
[root@redhat init]# mount initrd-2.4.20-8.img mnt/ -o loop
```

这样就可以对里面的文件进行分析。

在这里我们仅仅对cpio模式的进行分析。

看代码发现，mkinitrd就是个shell 脚本文件。所以可以根据脚本文档进行分析。

 

我的内核从2.6.18升级到2.6.28时，出现dm-mem-cache.ko找不到的情况，我分析了下，发现mkinitrd的问题，因为我 使用的mkinitrd指定如果要包含raid模块，就要包含该模块。但是在新的mkinitrd模块中，使用一个工具dmraid来做处理。

 

所以在mkinitrd时，出现找不到模块时，我们可以根据配置去掉一些功能的模块，具体man mkinitrd的说明。还有就是改变mkinird，可能会解决问题。