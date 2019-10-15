#!/usr/bin/env bash

function debug(){
    case $1 in
        cmd)
            echo -e "$2"
            ;;
        info) #Green
            echo -e "\033[0;32m$2\033[0m\t"
            ;;
        warn) #Yellow
            echo -e "\033[0;33m$2\033[0m\t"
            ;;
        error) #Red
            echo -e "\033[0;31mERROR: $2\033[0m\t"
            ;;
        *) WARN "debug:Don't have this choise!"
    esac
}

function help(){
    echo 'help'
}

function cmd(){
    debug cmd "$@"
    $@
    local retVal=$?

    if [ $retVal -ne 0 ]; then
        local msg=$(perror $retVal)
        debug error "=============== : ${msg#*:}============="
    fi
    return $retVal

}

function switch_host(){
    local name=$1
    case $name in

        main)
            host="archermind@10.20.11.11"
            continue
            ;;
        help)
            echo "help world"
            continue
            ;;
    esac
}

function scp_file(){
    local img=$1
    local switch=$2
    debug cmd "scp -r $img archermind@10.20.11.11:/work/ASUS/ZB630KL_Q/${img%/*}"
    scp -r $img archermind@10.20.11.11:/work/ASUS/ZB630KL_Q/${img%/*}
    #cp -r $img /work1/Q_SDM636_M1_dev/${img%/*}
    retVal=$?

    if [ $retVal -ne 0 ]; then
        local msg=$(perror $retVal)
        debug error "===============${IMGDIC[$img]} : ${msg#*:}============="
    fi
    return $retVal
}

function sensor(){
    local files=(
#    device/qcom/sdm660_64/BoardConfig.mk
#    vendor/amt/config/zb630kl_m2/init.amt.target.rc
#    vendor/amt/config/common/init.amt.rc
    #selinux
    #device/qcom/sdm660_64/BoardConfig.mk
    #vendor/amt/config/zb630kl_m2/init.amt.target.rc
    #vendor/amt/config/common/init.amt.rc
    vendor/amt/sepolicy/zb630kl_m2/file.te
    vendor/amt/sepolicy/zb630kl_m2/file_contexts
    #hal
    #device/qcom/sdm660_64/sensors/hals.conf
    #vendor/qcom/proprietary/native_sensors
    #kernel
    #kernel/msm-4.4/drivers/sensors/stk3x3x/stk3x3x.c
    )
    for img in ${files[@]};
    do
        scp_file $img || let 'total++'
    done
}

function audio(){
    local files=(
    #device/qcom/sdm660_64/BoardConfig.mk
    #vendor/amt/config/zb630kl_m2/init.amt.target.rc
    #vendor/amt/config/common/init.amt.rc
    #selinux
    #device/qcom/sdm660_64/BoardConfig.mk
    #vendor/amt/config/zb630kl_m2/init.amt.target.rc
    #vendor/amt/config/common/init.amt.rc
    #vendor/amt/sepolicy/zb630kl_m2/file.te
    #vendor/amt/sepolicy/zb630kl_m2/file_contexts
    #hal
    vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_extn/audio_extn.h
    vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_extn/fm.c
    vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_hw.c
    #kernel
    )
    for img in ${files[@]};
    do
        scp_file $img || let 'total++'
    done
}

function cp_imgs(){
    local imgs=(
    #out/target/product/sdm660_64/boot.img
    #    out/target/product/sdm660_64/vendor.img
    #    out/target/product/sdm660_64/system.img
    #    out/target/product/sdm660_64/persist.img
    #    out/target/product/sdm660_64/recovery.img
    #out/target/product/sdm660_64/vendor/etc/selinux
    out/target/product/sdm660_64/vendor/lib/hw/audio.primary.sdm660.so
    )
    for img in ${imgs[@]};
    do
        debug cmd "scp -r archermind@10.20.11.11:/work/ASUS/ZB630KL_Q/$img ${img%/*}"
        scp -r archermind@10.20.11.11:/work/ASUS/ZB630KL_Q/$img ${img%/*} || let 'total++'
    done
}

debug info $@
for command in $@; do
    case $command in

        sensor)
            sensor
            continue
            ;;
        audio)
            audio
            continue
            ;;
        selinux)
            selinux
            continue
            ;;
        img)
            cp_imgs
            continue
            ;;
        help)
            help
            continue
            ;;
    esac
done


