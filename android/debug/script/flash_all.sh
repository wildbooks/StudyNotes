#!/bin/bash

#
#    This file is auto create by scripts
#    For download all img by fastboot
#    2018/03/15
#
#    This file is auto create by scripts
#    For download sku5 img by fastboot
#    2018/03/22
#

# set path
if [ -z "`which fastboot`" ] && [ -e "fastboot" ];then
    for i in `echo $PATH | sed -e 's/:/ /g'`;do
        cp -rf fastboot $i/fastboot > /dev/null
    done
    export PATH=`pwd`:$PATH
fi

# check fastboot tool
if [ -z "`which fastboot`" ];then
    echo -e "Error: No fastboot tool found !!!"
    exit 1
fi

# default platform
default_platform="8937"

# default buildtype
default_buildtype="eng"

# get platform from fastboot command
platform=`fastboot getvar platform 2>&1 | grep platform | awk '{print $NF}'`

# get build-type from fastboot command
buildtype=`fastboot getvar build-type 2>&1 | grep build-type | awk '{print $NF}'`

secret_key=`fastboot getvar secret-key-opt 2>&1 | grep secret-key-opt | awk '{print $NF}'`

if [ -z "$platform" ];then
    platform="$default_platform"
fi

if [ -z "$buildtype" ];then
    buildtype="$default_buildtype"
fi

if [ "$buildtype" = "user" ];then
    echo $secret_key > default_key.bin
    fastboot flash frp-unlock default_key.bin
    fastboot flashing unlock
    fastboot flashing unlock_critical
fi

platform="8937"

# begin download
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_NON-HLOS.bin" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_NON-HLOS.bin\E[00m\n"
    fastboot erase modem
echo "flash id $?"
    fastboot flash modem `dirname $0`/${platform}_NON-HLOS.bin
echo "flash id $?"
elif [ -e "NON-HLOS.bin" ];then
    echo -e "\E[0;32mbegin fastboot download NON-HLOS.bin\E[00m\n"
    fastboot erase modem
    echo "flash id $?"
    fastboot flash modem `dirname $0`/NON-HLOS.bin
    echo "flash id $?"
fi
echo "flash id $?"
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_sbl1.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_sbl1.mbn\E[00m\n"
    fastboot erase sbl1
    echo "flash id $?"
    fastboot flash sbl1 `dirname $0`/${platform}_sbl1.mbn
    echo "flash id $?"
elif [ -e "sbl1.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download sbl1.mbn\E[00m\n"
    fastboot erase sbl1
    fastboot flash sbl1 `dirname $0`/sbl1.mbn
fi
echo "flash id $?"
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_sbl1.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_sbl1.mbn\E[00m\n"
    fastboot erase sbl1bak
    fastboot flash sbl1bak `dirname $0`/${platform}_sbl1.mbn
elif [ -e "sbl1.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download sbl1.mbn\E[00m\n"
    fastboot erase sbl1bak
    fastboot flash sbl1bak `dirname $0`/sbl1.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_rpm.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_rpm.mbn\E[00m\n"
    fastboot erase rpm
    echo "flash id $?"
    fastboot flash rpm `dirname $0`/${platform}_rpm.mbn
elif [ -e "rpm.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download rpm.mbn\E[00m\n"
    fastboot erase rpm
    echo "flash id $?"
    fastboot flash rpm `dirname $0`/rpm.mbn
    echo "flash id $?"
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_rpm.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_rpm.mbn\E[00m\n"
    fastboot erase rpmbak
    echo "flash id $?"
    fastboot flash rpmbak `dirname $0`/${platform}_rpm.mbn
    echo "flash id $?"
elif [ -e "rpm.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download rpm.mbn\E[00m\n"
    fastboot erase rpmbak
    echo "flash id $?"
    fastboot flash rpmbak `dirname $0`/rpm.mbn
    echo "flash id $?"
fi
    echo "flash id $?"
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_tz.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_tz.mbn\E[00m\n"
    fastboot erase tz
    fastboot flash tz `dirname $0`/${platform}_tz.mbn
elif [ -e "tz.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download tz.mbn\E[00m\n"
    fastboot erase tz
    fastboot flash tz `dirname $0`/tz.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_tz.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_tz.mbn\E[00m\n"
    fastboot erase tzbak
    fastboot flash tzbak `dirname $0`/${platform}_tz.mbn
elif [ -e "tz.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download tz.mbn\E[00m\n"
    fastboot erase tzbak
    fastboot flash tzbak `dirname $0`/tz.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_devcfg.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_devcfg.mbn\E[00m\n"
    fastboot erase devcfg
    fastboot flash devcfg `dirname $0`/${platform}_devcfg.mbn
elif [ -e "devcfg.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download devcfg.mbn\E[00m\n"
    fastboot erase devcfg
    fastboot flash devcfg `dirname $0`/devcfg.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_devcfg.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_devcfg.mbn\E[00m\n"
    fastboot erase devcfgbak
    fastboot flash devcfgbak `dirname $0`/${platform}_devcfg.mbn
elif [ -e "devcfg.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download devcfg.mbn\E[00m\n"
    fastboot erase devcfgbak
    fastboot flash devcfgbak `dirname $0`/devcfg.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_adspso.bin" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_adspso.bin\E[00m\n"
    fastboot erase dsp
    fastboot flash dsp `dirname $0`/${platform}_adspso.bin
elif [ -e "adspso.bin" ];then
    echo -e "\E[0;32mbegin fastboot download adspso.bin\E[00m\n"
    fastboot erase dsp
    fastboot flash dsp `dirname $0`/adspso.bin
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_emmc_appsboot.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_emmc_appsboot.mbn\E[00m\n"
    fastboot erase aboot
    fastboot flash aboot `dirname $0`/${platform}_emmc_appsboot.mbn
elif [ -e "emmc_appsboot.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download emmc_appsboot.mbn\E[00m\n"
    fastboot erase aboot
    fastboot flash aboot `dirname $0`/emmc_appsboot.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_emmc_appsboot.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_emmc_appsboot.mbn\E[00m\n"
    fastboot erase abootbak
    fastboot flash abootbak `dirname $0`/${platform}_emmc_appsboot.mbn
elif [ -e "emmc_appsboot.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download emmc_appsboot.mbn\E[00m\n"
    fastboot erase abootbak
    fastboot flash abootbak `dirname $0`/emmc_appsboot.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_boot.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_boot.img\E[00m\n"
    fastboot erase boot
    fastboot flash boot `dirname $0`/${platform}_boot.img
elif [ -e "boot.img" ];then
    echo -e "\E[0;32mbegin fastboot download boot.img\E[00m\n"
    fastboot erase boot
    fastboot flash boot `dirname $0`/boot.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_recovery.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_recovery.img\E[00m\n"
    fastboot erase recovery
    fastboot flash recovery `dirname $0`/${platform}_recovery.img
elif [ -e "recovery.img" ];then
    echo -e "\E[0;32mbegin fastboot download recovery.img\E[00m\n"
    fastboot erase recovery
    fastboot flash recovery `dirname $0`/recovery.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_system.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_system.img\E[00m\n"
    fastboot erase system
    fastboot flash system `dirname $0`/${platform}_system.img
elif [ -e "system.img" ];then
    echo -e "\E[0;32mbegin fastboot download system.img\E[00m\n"
    fastboot erase system
    fastboot flash system `dirname $0`/system.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_cache.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_cache.img\E[00m\n"
    fastboot erase cache
    fastboot flash cache `dirname $0`/${platform}_cache.img
elif [ -e "cache.img" ];then
    echo -e "\E[0;32mbegin fastboot download cache.img\E[00m\n"
    fastboot erase cache
    fastboot flash cache `dirname $0`/cache.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_mdtp.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_mdtp.img\E[00m\n"
    fastboot erase mdtp
    fastboot flash mdtp `dirname $0`/${platform}_mdtp.img
elif [ -e "mdtp.img" ];then
    echo -e "\E[0;32mbegin fastboot download mdtp.img\E[00m\n"
    fastboot erase mdtp
    fastboot flash mdtp `dirname $0`/mdtp.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_cmnlib.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_cmnlib.mbn\E[00m\n"
    fastboot erase cmnlib
    fastboot flash cmnlib `dirname $0`/${platform}_cmnlib.mbn
elif [ -e "cmnlib.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download cmnlib.mbn\E[00m\n"
    fastboot erase cmnlib
    fastboot flash cmnlib `dirname $0`/cmnlib.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_cmnlib.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_cmnlib.mbn\E[00m\n"
    fastboot erase cmnlibbak
    fastboot flash cmnlibbak `dirname $0`/${platform}_cmnlib.mbn
elif [ -e "cmnlib.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download cmnlib.mbn\E[00m\n"
    fastboot erase cmnlibbak
    fastboot flash cmnlibbak `dirname $0`/cmnlib.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_cmnlib64.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_cmnlib64.mbn\E[00m\n"
    fastboot erase cmnlib64
    fastboot flash cmnlib64 `dirname $0`/${platform}_cmnlib64.mbn
elif [ -e "cmnlib64.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download cmnlib64.mbn\E[00m\n"
    fastboot erase cmnlib64
    fastboot flash cmnlib64 `dirname $0`/cmnlib64.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_cmnlib64.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_cmnlib64.mbn\E[00m\n"
    fastboot erase cmnlib64bak
    fastboot flash cmnlib64bak `dirname $0`/${platform}_cmnlib64.mbn
elif [ -e "cmnlib64.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download cmnlib64.mbn\E[00m\n"
    fastboot erase cmnlib64bak
    fastboot flash cmnlib64bak `dirname $0`/cmnlib64.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_keymaster.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_keymaster.mbn\E[00m\n"
    fastboot erase keymaster
    fastboot flash keymaster `dirname $0`/${platform}_keymaster.mbn
elif [ -e "keymaster.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download keymaster.mbn\E[00m\n"
    fastboot erase keymaster
    fastboot flash keymaster `dirname $0`/keymaster.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_keymaster.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_keymaster.mbn\E[00m\n"
    fastboot erase keymasterbak
    fastboot flash keymasterbak `dirname $0`/${platform}_keymaster.mbn
elif [ -e "keymaster.mbn" ];then
    echo -e "\E[0;32mbegin fastboot download keymaster.mbn\E[00m\n"
    fastboot erase keymasterbak
    fastboot flash keymasterbak `dirname $0`/keymaster.mbn
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_userdata.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_userdata.img\E[00m\n"
    fastboot erase userdata
    fastboot flash userdata `dirname $0`/${platform}_userdata.img
elif [ -e "userdata.img" ];then
    echo -e "\E[0;32mbegin fastboot download userdata.img\E[00m\n"
    fastboot erase userdata
    fastboot flash userdata `dirname $0`/userdata.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_misc.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_misc.img\E[00m\n"
    fastboot erase misc
    fastboot flash misc `dirname $0`/${platform}_misc.img
elif [ -e "misc.img" ];then
    echo -e "\E[0;32mbegin fastboot download misc.img\E[00m\n"
    fastboot erase misc
    fastboot flash misc `dirname $0`/misc.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_APD.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_APD.img\E[00m\n"
    fastboot erase APD
    fastboot flash APD `dirname $0`/${platform}_APD.img
elif [ -e "APD.img" ];then
    echo -e "\E[0;32mbegin fastboot download APD.img\E[00m\n"
    fastboot erase APD
    fastboot flash APD `dirname $0`/APD.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_ADF.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_ADF.img\E[00m\n"
    fastboot erase ADF
    fastboot flash ADF `dirname $0`/${platform}_ADF.img
elif [ -e "ADF.img" ];then
    echo -e "\E[0;32mbegin fastboot download ADF.img\E[00m\n"
    fastboot erase ADF
    fastboot flash ADF `dirname $0`/ADF.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_persist.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_persist.img\E[00m\n"
    fastboot erase persist
    fastboot flash persist `dirname $0`/${platform}_persist.img
elif [ -e "persist.img" ];then
    echo -e "\E[0;32mbegin fastboot download persist.img\E[00m\n"
    fastboot erase persist
    fastboot flash persist `dirname $0`/persist.img
fi
echo -e "\n------------------------------------------------------------"
if [ -e "${platform}_splash.img" ];then
    echo -e "\E[0;32mbegin fastboot download ${platform}_splash.img\E[00m\n"
    fastboot erase splash
    fastboot flash splash `dirname $0`/${platform}_splash.img
elif [ -e "splash.img" ];then
    echo -e "\E[0;32mbegin fastboot download splash.img\E[00m\n"
    fastboot erase splash
    fastboot flash splash `dirname $0`/splash.img
fi

# erase boot,force to reboot to bootloader
# fastboot erase boot

# reboot to bootloader
# fastboot reboot bootloader

# wait for device
sleep 5

# re unlock device
#fastboot flash frp-unlock secret_key.bin
#fastboot flashing unlock
#fastboot flashing unlock_critical

# redownload boot
#if [ -e "${platform}_boot.img" ];then
#    fastboot flash boot `dirname $0`/${platform}_boot.img
#elif [ -e "boot.img" ];then
#    fastboot flash boot `dirname $0`/boot.img
#fi

# lock the device
#fastboot flashing lock
#fastboot flashing lock_critical

echo -e "\nAll is download,do you want to reboot(y/n) ?"
read x
if [ "$x" == "y" ] || [ "$x" == "Y" ];then
    fastboot reboot
fi

