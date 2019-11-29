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

function scp_file(){
    local img=$1
    local switch=$2
    if [ $switch -ne 0 ]; then
        debug cmd "scp -r $DEST_HOME/$img $PROJECT_HOME/${img%/*}"
        scp -r $DEST_HOME/$img $PROJECT_HOME/${img%/*}
    else
        debug cmd "scp -r $PROJECT_HOME/$img $DEST_HOME/${img%/*}"
        scp -r $PROJECT_HOME/$img $DEST_HOME/${img%/*}
    fi

    retVal=$?

    if [ $retVal -ne 0 ]; then
        #local msg=$(perror $retVal)
        #debug error "===============$img : ${msg#*:}============="
        debug error "===============$img : ${msg#*:}============="
    fi
    return $retVal
}

function sensor(){
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
    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SAMSensor.cpp
    vendor/qcom/proprietary/sensors/dsps/libhalsensors/src/SensorsContext.cpp
    vendor/qcom/proprietary/sensors/dsps/libsensor1/src/libsensor1.c
    vendor/qcom/proprietary/sensors/dsps/reg_defaults/sensor_def_qcomdev.conf
    vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/inc/sns_reg_common.h
    vendor/qcom/proprietary/sensors/dsps/sensortest/jni/src/sensor_user_cal_algo.c
    #device/qcom/sdm660_64/sensors/hals.conf
    #vendor/qcom/proprietary/native_sensors
    #kernel
    #kernel/msm-4.4/drivers/sensors/stk3x3x/stk3x3x.c
    )
    for img in ${files[@]};
    do
        scp_file $img 0 || let 'total++'
    done

    if [ "$total" == '' ]; then
        debug info "-------------- cp imgs sucessful --------------"
    else
        debug error "-------------- cp imgs fail:$total --------------"
    fi
}

function cp_other(){
    local files=(
    kernel/msm-4.4/arch/arm64/configs/ql1820-perf_defconfig
    kernel/msm-4.4/arch/arm64/configs/ql1820_defconfig
    )
    for img in ${files[@]};
    do
        scp_file $img 0 || let 'total++'
    done

    if [ "$total" == '' ]; then
        debug info "-------------- cp imgs sucessful --------------"
    else
        debug error "-------------- cp imgs fail:$total --------------"
    fi
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
        scp_file $img 0 || let 'total++'
    done

    if [ "$total" == '' ]; then
        debug info "-------------- cp imgs sucessful --------------"
    else
        debug error "-------------- cp imgs fail:$total --------------"
    fi
}

function cp_imgs(){
    local imgs=(
    #out/target/product/sdm660_64/boot.img
    out/target/product/sdm660_64/boot-debug.img
    #out/target/product/sdm660_64/vendor.img
    #out/target/product/sdm660_64/system.img
    #out/target/product/sdm660_64/persist.img
    #out/target/product/sdm660_64/recovery.img
    #out/target/product/sdm660_64/vendor/etc/selinux
    #out/target/product/sdm660_64/vendor/lib/hw/audio.primary.sdm660.so
    )
    for img in ${imgs[@]};
    do
        scp_file $img 1 || let 'total++'
    done

    if [ "$total" == '' ]; then
        debug info "-------------- cp imgs sucessful --------------"
    else
        debug error "-------------- cp imgs fail:$total --------------"
    fi
}

function main(){
    debug info $@
    PROJECT_HOME=`pwd`
    PROJECT=`basename ${PROJECT_HOME}`
    HOSTNAME='archermind@10.20.11.11'

    case $PROJECT in
        Q_SDM636_Ara_dev)
            TARGET_PRODUCT='sdm660_64'
            DEST_PROJECT='/work/ASUS/ZE620KL_Q'
            ;;
        Q_SDM636_M1_dev)
            TARGET_PRODUCT='sdm660_64'
            DEST_PROJECT='/work/ASUS/ZB601KL_Q'
            ;;
        Q_SDM636_M2_dev)
            TARGET_PRODUCT='sdm660_64'
            DEST_PROJECT='/work/ASUS/ZB630KL_Q'
            ;;
        Q_ZA550KL_dev)
            TARGET_PRODUCT='msm8937_64'
            DEST_PROJECT='/work/ASUS/ZA550KL_Q'
            ;;
        Q_ZB555KL_dev)
            TARGET_PRODUCT='msm8937_64'
            DEST_PROJECT='/work/ASUS/ZB555KL_Q'
            ;;
    esac

    DEST_HOME=${HOSTNAME}:${DEST_PROJECT}
    OUT=out/target/product/${TARGET_PRODUCT}
    PROJECT_OUT=${PROJECT_HOME}/${OUT}
    DEST_OUT=${DEST_HOME}/${OUT}

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
            other)
                cp_other
                continue
                ;;
            help)
                help
                continue
                ;;
        esac
    done
}

main $@
