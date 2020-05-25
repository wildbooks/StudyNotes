# 确认设备树方法
* 确认手机使用的设备树
    ```bash
    $ adb shell
    $ cat /sys/firmware/devicetree/base/model
    Qualcomm Technologies, Inc. MSM8937-PMI8940 MTP #返回结果
    #然后把返回的结果再设置数目录下搜索，确认设备树为msm8937-pmi8940-mtp.dts
Qualcomm Technologies, Inc. MSM8937-PMI8937 QRD SKU2
    ```
* 根据设备树文件确认使用的设备树清单
    ```bash
    python dts_list.pyc -e  msm8937-pmi8940-mtp.dts
    ```
    相关python脚本文件dts_list.pyc gv.pyc
# 设备树编译(dts->dtb)
    在编译设备树时，Makefile会首先寻找xxx.dts,然后再寻找xxx.dtsi，然后编译生成xxx.dtb
#

# DTS编译为DTB：
    $ scripts/dtc/dtc -I dts -O dtb -o /path/to/my-tree.dtb /path/to/my-tree.dts
    这样就创建了my-tree.dtb二进制文件。dtc是主机上的一个程序。如果内核没有编译过，则先需要编译好DTS编译器：配置内核，也可以复制一份已有的配置文件到内核根目录下的.config。如下：
    $ make ARCH=arm digilent_zed_defconfig生成DTS编译器：
    $ make ARCH=arm scriptsdtc
# 提取设备树，并反编译成dts
也可以从一个DTB文件或/proc/device-tree文件系统反编译。例如从DTB反编译：
$ scripts/dtc/dtc -I dtb -O dts -o /path/to/fromdtb.dts/path/to/booted_with_this.dtb生成的dts文件仍然可以被用来生成dtb。但最好还是使用最初的DTS文件，因为一些参考标签在反编译的DTS文件中显示为数字。从运行中的内核生成DTS文件：
# scripts/dtc/dtc -I fs -O dts -o ~/effective.dts /proc/device-tree/设备树结构
