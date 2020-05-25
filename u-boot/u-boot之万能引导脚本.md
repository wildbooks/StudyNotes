

[toc]

# 介绍

该文档主要讲解使用uboot的环境变量配置万能的引导脚步。

# aml_autoscript.cmd

```bash
#aml_autoscript.cmd
if printenv bootfromsd; then exit; else setenv ab 0; fi;
setenv bootcmd 'run start_autoscript; run storeboot'
setenv start_autoscript 'if mmcinfo; then run start_mmc_autoscript; fi; if usb start; then run start_usb_autoscript; fi; run start_emmc_autoscript'
setenv start_emmc_autoscript 'if fatload mmc 1 1020000 emmc_autoscript; then autoscr 1020000; fi;'
setenv start_mmc_autoscript 'if fatload mmc 0 1020000 s905_autoscript; then autoscr 1020000; fi;'
setenv start_usb_autoscript 'for usbdev in 0 1 2 3; do if fatload usb ${usbdev} 1020000 s905_autoscript; then autoscr 1020000; fi; done'
setenv upgrade_step 2
saveenv
sleep 1
reboot
```

> 该脚本主要完成引导方式识别。引导方式优先级为：
>
> 1. start_mmc_autoscript：nanflash/norflash方式引导。
> 2. start_usb_autoscript：usb引导
> 3. start_emmc_autoscript：SD卡引导

# emmc_autoscript.cmd

```bash
if fatload mmc 1 0x1000000 u-boot.emmc; then go 0x1000000; fi;
setenv dtb_addr 0x1000000 #设备树加载到内存地址
setenv env_addr 0x1040000 #uEnv.txt配置文件加载到内存地址
setenv kernel_addr 0x11000000 #内核加载到内存地址
setenv initrd_addr 0x13000000 #根文件系统加载到内存地址
setenv boot_start booti ${kernel_addr} ${initrd_addr} ${dtb_addr} #开始引导内核
setenv addmac 'if printenv mac; then setenv bootargs ${bootargs} mac=${mac}; elif printenv eth_mac; then setenv bootargs ${bootargs} mac=${eth_mac}; fi'
if fatload mmc 1 ${env_addr} uEnv.txt && env import -t ${env_addr} ${filesize}; setenv bootargs ${APPEND}; then if fatload mmc 1 ${kernel_addr} ${LINUX}; then if fatload mmc 1 ${initrd_addr} ${INITRD}; then if fatload mmc 1 ${dtb_addr} ${FDT}; then run addmac; run boot_start; fi; fi; fi; fi;
```

> 该脚本根据配置文件uEnv.txt选择正确的dtb,kernel,rootfs文件系统。然后设置正确的引导参数(bootargs)。然后使用以下命令完成引导内核
>
> booti ${kernel_addr} ${initrd_addr} ${dtb_addr}
>
> 注意：mmc 1：SD卡
>
> ​			mmc 0：nandflash/norflash

# s905_autoscript.cmd

```bash
echo "start amlogic old u-boot"
if fatload mmc 0 ${loadaddr} boot_android; then if test ${ab} = 0; then setenv ab 1; saveenv; exit; else setenv ab 0; saveenv; fi; fi;
if fatload usb 0 ${loadaddr} boot_android; then if test ${ab} = 0; then setenv ab 1; saveenv; exit; else setenv ab 0; saveenv; fi; fi;
if fatload mmc 0 0x1000000 u-boot.ext; then go 0x1000000; fi;
if fatload usb 0 0x1000000 u-boot.ext; then go 0x1000000; fi;
setenv kernel_addr_r 0x11000000
setenv ramdisk_addr_r 0x13000000
setenv fdt_addr_r 0x1000000
setenv l_mmc "0"
for devtype in "mmc usb" ; do if test "${devtype}" = "usb"; then echo "start test usb"; setenv l_mmc "0 1 2 3"; fi; for devnum in ${l_mmc} ; do if test -e ${devtype} ${devnum} uEnv.txt; then fatload ${devtype} ${devnum} ${loadaddr} uEnv.txt; env import -t ${loadaddr} ${filesize}; setenv bootargs ${APPEND}; if printenv mac; then setenv bootargs ${bootargs} mac=${mac}; elif printenv eth_mac; then setenv bootargs ${bootargs} mac=${eth_mac}; fi; if fatload ${devtype} ${devnum} ${kernel_addr_r} ${LINUX}; then if fatload ${devtype} ${devnum} ${ramdisk_addr_r} ${INITRD}; then if fatload ${devtype} ${devnum} ${fdt_addr_r} ${FDT}; then fdt addr ${fdt_addr_r}; booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r}; fi; fi; fi; fi; done; done;
```

> 先遍历mmc 0。再遍历usb(0->3)是否有uEvn.txt文件；遍历到该文件后就执行以下命令完成引导内核
>
> booti ${kernel_addr_r} ${ramdisk_addr_r} ${fdt_addr_r};
>
> 注意：引导顺序：
>
> mmc 0 -> usb0 -> usb1 -> usb2 -> usb3

# uEnv.txt

```
LINUX=/zImage #内核
INITRD=/uInitrd #根文件系统

# rk-3399
#FDT=/dtb/rockchip/rk3399-rock-pi-4.dtb
#FDT=/dtb/rockchip/rk3399-nanopc-t4.dtb
#APPEND=root=LABEL=ROOTFS rootflags=data=writeback rw console=uart8250,mmio32,0xff1a0000 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0

# rk-3328
#FDT=/dtb/rockchip/rk3328-box.dtb
#APPEND=root=LABEL=ROOTFS rootflags=data=writeback rw console=uart8250,mmio32,0xff130000 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0

# aw h6
#FDT=/dtb/allwinner/sun50i-h6-tanix-tx6.dtb
#APPEND=root=LABEL=ROOTFS rootflags=data=writeback rw console=ttyS0,115200 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0
#APPEND=root=LABEL=ROOTFS rootflags=data=writeback rw console=ttyS0,115200 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0 mem=2048M video=HDMI-A-1:e

# aml s9xxx
FDT=/dtb/amlogic/meson-g12b-odroid-n2.dtb
APPEND=root=LABEL=ROOTFS rootflags=data=writeback rw console=ttyAML0,115200n8 console=tty0 no_console_suspend consoleblank=0 fsck.fix=yes fsck.repair=yes net.ifnames=0
```

# 对脚本进行封装

```bash
mkimage -A ARM -O linux -T script -C none -a 0 -e 0 -n "autoscr aml_autoscript script" -d aml_autoscript.cmd  aml_autoscript
```



