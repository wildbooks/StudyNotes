#!/usr/bin/env bash

function debug(){
    case $1 in
        cmd)
            echo -e "$2"
            ;;
        info)#Green
            echo -e "\033[0;32m$2\033[0m\t"
            ;;
        warn)#Yellow
            echo -e "\033[0;33m$2\033[0m\t"
            ;;
        error)#Red
            echo -e "\033[0;31mERROR: $2\033[0m\t"
            ;;
        *) WARN "debug:Don't have this choise!"
    esac
}

function add_image(){
    IMGDIC=(
    #[abl]='abl.elf'
    [modem]='NON-HLOS.bin'
    [cache]="cache.img"
    [boot]='boot.img'
    [system]='system.img'
    [vendor]='vendor.img'
    [userdata]='userdata.img'
    [recovery]='recovery.img'
    [aboot]='emmc_appsboot.mbn'
    )
    IMGDIC["xbl_a"]="xbl.elf"
    IMGDIC["xbl_b"]="xbl.elf"
    IMGDIC["tz_a"]="tz.mbn"
    IMGDIC["tz_b"]="tz.mbn"
    IMGDIC["rpm_a"]="rpm.mbn"
    IMGDIC["rpm_b"]="rpm.mbn"
    IMGDIC["hyp_a"]="hyp.mbn"
    IMGDIC["hyp_b"]="hyp.mbn"
    IMGDIC["pmic_a"]="pmic.elf"
    IMGDIC["pmic_b"]="pmic.elf"
    IMGDIC["boot_a"]="boot.img"
    IMGDIC["boot_b"]="boot.img"
    IMGDIC["system_a"]="system.img"
    IMGDIC["system_b"]="system.img"
    IMGDIC["vendor_a"]="vendor.img"
    IMGDIC["vendor_b"]="vendor.img"
    IMGDIC["keymaster_a"]="km4.mbn"
    IMGDIC["keymaster_b"]="km4.mbn"
    IMGDIC["cmnlib_a"]="cmnlib.mbn"
    IMGDIC["cmnlib64_a"]="cmnlib64.mbn"
    IMGDIC["cmnlib_b"]="cmnlib.mbn"
    IMGDIC["cmnlib64_b"]="cmnlib64.mbn"
    IMGDIC["mdtpsecapp_a"]="mdtpsecapp.mbn"
    IMGDIC["mdtpsecapp_b"]="mdtpsecapp.mbn"
    IMGDIC["mdtp_a"]="mdtp.img"
    IMGDIC["mdtp_b"]="mdtp.img"
    IMGDIC["modem_a"]="NON-HLOS.bin"
    IMGDIC["modem_b"]="NON-HLOS.bin"
    IMGDIC["dsp_a"]="dspso.bin"
    IMGDIC["dsp_b"]="dspso.bin"
    IMGDIC["abl_a"]="abl.elf"
    IMGDIC["abl_b"]="abl.elf"
    IMGDIC["bluetooth_a"]="BTFM.bin"
    IMGDIC["bluetooth_b"]="BTFM.bin"
    IMGDIC["devcfg_a"]="devcfg.mbn"
    IMGDIC["devcfg_b"]="devcfg.mbn"
    IMGDIC["storsec"]="storsec.mbn"
    IMGDIC["userdata"]="userdata.img"
    IMGDIC["PrimaryGPT"]="gpt_main0.bin"
    IMGDIC["BackupGPT"]="gpt_backup0.bin"
    IMGDIC["persist"]="persist.img"
    IMGDIC["sec"]="sec.dat"
}

function flash_image(){
    local img=$1
    debug cmd "fastboot flash $img ${IMGDIC[$img]}"
    #fastboot flash $img ${IMGDIC[$img]}
    retVal=$?

    if [ $retVal -ne 0 ]; then
        local msg=$(perror $retVal)
        debug error "===============${IMGDIC[$img]} : ${msg#*:}============="
    fi
    return $retVal
}

function unlock(){
    # get build-type from fastboot command
    buildtype=`fastboot getvar build-type 2>&1 | grep build-type | awk '{print $NF}'`
    secret_key=`fastboot getvar secret-key-opt 2>&1 | grep secret-key-opt | awk '{print $NF}'`

    if [ "$buildtype" = "user" ];then
        echo $secret_key > default_key.bin
        fastboot flash frp-unlock default_key.bin
        fastboot flashing unlock
        fastboot flashing unlock_critical
    fi
}

function lock(){
    # lock the device
    fastboot flashing lock
    fastboot flashing lock_critical
}



#-------------------- main -------------------------
# get platform from fastboot command
platform=`fastboot getvar platform 2>&1 | grep platform | awk '{print $NF}'`
debug info "the CPU of this phone is $platform"
declare -A IMGDIC

add_image
for img in ${!IMGDIC[@]};
do
    flash_image $img || let 'total++'
done

if [ "$total" == '' ]; then
    debug info "-------------- flash sucessful --------------"
else
    debug error "-------------- flash fail:$total --------------"
fi
