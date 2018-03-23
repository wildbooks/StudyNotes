# 确认设备树方法
* 确认手机使用的设备树
    ```bash
    $ adb shell
    $ cat /sys/firmware/devicetree/base/model
    Qualcomm Technologies, Inc. MSM8937-PMI8940 MTP #返回结果
    #然后把返回的结果再设置数目录下搜索，确认设备树为msm8937-pmi8940-mtp.dts
    ```
* 根据设备树文件确认使用的设备树清单
    ```bash
    python dts_list.pyc -e  msm8937-pmi8940-mtp.dts
    ```
    相关python脚本文件dts_list.pyc gv.pyc
# 设备树编译(dts->dtb)
    在编译设备树时，Makefile会首先寻找xxx.dts,然后再寻找xxx.dtsi，然后编译生成xxx.dtb
