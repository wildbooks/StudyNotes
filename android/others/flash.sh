#! /bin/bash

SRC_HOME=$(pwd)
SRC_OUT_PATH="$SRC_HOME/out/target/product/appassionato"
AndroidDeviceFile=
# 判断设备是否存在
echo ""
echo "  *****************************************************"
echo "  *  1) flash boot.img"
echo "  *  2) reboot && flash boot.img"
echo "  *  3) make && reboot && flash boot.img"
echo "  *  4) make boot.img"
echo "  *  5) make bootimg-nodeps"
echo "  *****************************************************"
echo "  *  6) flash system.img"
echo "  *  7) reboot && flash system.img"
echo "  *  8) make && reboot && flash system.img"
echo "  *  9) make system.img"
echo "  *****************************************************"
echo "  *  10) reboot && flash system.img && flash boot.img"
echo "  *****************************************************"
echo "  *  11) flash aboot"
echo "  *  12) reboot && flash aboot"
echo "  *****************************************************"
echo "  Please input your choise"

read aNum
case $aNum in
    # bootimage-nodeps
    1)  echo "flashing boot"
        sudo fastboot flash boot $SRC_OUT_PATH/boot.img
    ;;
    2)  echo "rebooting && flashing boot"
        adb reboot-bootloader && sudo fastboot flash boot $SRC_OUT_PATH/boot.img
    ;;
    3)  echo "makeing && rebooting && flashing boot"
        make bootimage && adb reboot-bootloader && sudo fastboot flash boot $SRC_OUT_PATH/boot.img
    ;;
    4)  echo "makeing boot"
        make bootimage
    ;;
    5)  echo "makeing bootimg-nodeps"
        make bootimage-nodeps
    ;;

    6)  echo "flashing system"
        sudo fastboot flash system $SRC_OUT_PATH/system.img
    ;;
    7)  echo "rebooting && flashing system"
        adb reboot-bootloader && sudo fastboot flash system $SRC_OUT_PATH/system.img
    ;;
    8)  echo "make && rebooting && flashing system"
        make systemimage && adb reboot-bootloader && sudo fastboot flash system $SRC_OUT_PATH/system.img
    ;;
    9)  echo "make systemimage"
        make systemimage
    ;;
    10) echo "make systemimage"
           
        echo "reboot && flash system.img && flash boot.img"
        adb reboot-bootloader && sudo fastboot flash system $SRC_OUT_PATH/system.img && sudo fastboot flash boot $SRC_OUT_PATH/boot.img
    ;;
    11) echo "flash aboot"
        sudo fastboot flash aboot $SRC_OUT_PATH/emmc_appsboot.mbn
    ;;
    12) echo "reboot && flash aboot"
        adb reboot-bootloader && sudo fastboot flash aboot $SRC_OUT_PATH/emmc_appsboot.mbn
    ;;
    *)   echo "Don't have this choise!"
esac

# bug
# 不能判断设备是否存在
