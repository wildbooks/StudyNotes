#!/usr/bin/env bash
declare -A IMGDIC

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
    #vendor/amt/sepolicy/ze620kl_ara/system_server.te
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
    $DEFCONFIG
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
    $DEFCONFIG
    #device/qcom/sdm660_64/AndroidBoard.mk
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

    #framework
    #frameworks/av/media/libaudioclient/AudioRecord.cpp
    #frameworks/av/media/libaudioclient/AudioTrack.cpp
    #frameworks/av/services/audioflinger/Threads.cpp

    #hal
    #vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_extn/audio_extn.h
    #vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_extn/fm.c
    #vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_hw.c

    #kernel
    #$DEFCONFIG
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

function selinux(){
    local files=(
    vendor/amt/sepolicy/ze620kl_ara/system_server.te
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

function add_image(){
    IMGDIC[boot]='boot.img'
    #IMGDIC[boot]='boot-debug.img'
    IMGDIC[system]='system.img'
    IMGDIC[vendor]='vendor.img'
    #IMGDIC[persist]='persist.img'
    #IMGDIC[recovery]='recovery.img'
}

function cp_imgs(){
    add_image
    for img in ${IMGDIC[@]};
    do
        scp_file $OUT/$img 1 || let 'total++'
    done

    if [ "$total" == '' ]; then
        debug info "-------------- cp imgs sucessful --------------"
    else
        debug error "-------------- cp imgs fail:$total --------------"
    fi
}

function flash_image(){
    local img=$1
    debug cmd "fastboot flash $img $OUT/${IMGDIC[$img]}"
    fastboot flash $img $OUT/${IMGDIC[$img]}
    retVal=$?

    if [ $retVal -ne 0 ]; then
        local msg=$(perror $retVal)
        debug error "===============${IMGDIC[$img]} : ${msg#*:}============="
    fi
    return $retVal
}

function flash_imgs(){
    add_image
    for img in ${!IMGDIC[@]};
    do
        flash_image $img || let 'total++'
    done
    if [ "$total" == '' ]; then
        debug info "-------------- flash sucessful --------------"
        fastboot reboot
    else
        debug error "-------------- flash fail:$total --------------"
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
            PRODUCT_DEVICE=sdm660_64
            DEFCONFIG="kernel/msm-4.4/arch/arm64/configs/sdm660-perf_defconfig"
            ;;
        Q_SDM636_M1_dev)
            TARGET_PRODUCT='sdm660_64'
            DEST_PROJECT='/work/ASUS/ZB601KL_Q'
            PRODUCT_DEVICE=sdm660_64
            DEFCONFIG="kernel/msm-4.4/arch/arm64/configs/ql1650-perf_defconfig"
            ;;
        Q_SDM636_M2_dev)
            TARGET_PRODUCT='sdm660_64'
            DEST_PROJECT='/work/ASUS/ZB630KL_Q'
            PRODUCT_DEVICE=sdm660_64
            DEFCONFIG="kernel/msm-4.4/arch/arm64/configs/ql1820-perf_defconfig"
            ;;
        Q_ZA550KL_dev)
            TARGET_PRODUCT='msm8937_64'
            DEST_PROJECT='/work/ASUS/ZA550KL_Q'
            PRODUCT_DEVICE=msm8937_64
            ;;
        Q_ZB555KL_dev)
            TARGET_PRODUCT='msm8937_64'
            DEST_PROJECT='/work/ASUS/ZB555KL_Q'
            PRODUCT_DEVICE=msm8937_64
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
            flash)
                flash_imgs
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
