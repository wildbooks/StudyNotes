#!/usr/bin/env bash
PROJECT_ROOT=/work1
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

function check_return_value () {
    retVal=$1
    command=$2
    if [ $retVal -ne 0 ]; then
        debug error "$command"
        exit $retVal
    fi
}

function command () {
    command=$@
    debug info "Command: $command"
    time $command
    retVal=$?
    check_return_value $retVal "$command"
}


usage() {
    cat <<USAGE

Usage:
    bash $0 <TARGET_PRODUCT> [OPTIONS]

Description:
    Builds Android tree for given TARGET_PRODUCT

OPTIONS:
    -c, --clean_build
        Clean build - build from scratch by removing entire out dir

    -d, --debug
        Enable debugging - captures all commands while doing the build

    -h, --help
        Display this help message

    -i, --image
        Specify image to be build/re-build (bootimg/sysimg/usrimg)

    -j, --jobs
        Specifies the number of jobs to run simultaneously (Default: 8)

    -k, --kernel_defconf
        Specify defconf file to be used for compiling Kernel

    -l, --log_file
        Log file to store build logs (Default: <TARGET_PRODUCT>.log)

    -m, --module
        Module to be build

    -p, --project
        Project to be build

    -s, --setup_ccache
        Set CCACHE for faster incremental builds (true/false - Default: true)

    -u, --update-api
        Update APIs

    -v, --build_variant
        Build variant (Default: userdebug)

USAGE
}

set_build_env(){
    local TOOLS_ROOT="/work1/none-hlos-tools"
    case $1 in
        sdm660)
            debug cmd "set_build_env sdm660"
            export SD_LLVM_ROOT=$TOOLS_ROOT/LLVM
            export CLANG38_BIN=$SD_LLVM_ROOT/3.8.4/bin/
            export HEXAGON_ROOT=$TOOLS_ROOT/HEXAGON_Tools
            # ARMTOOLS
            export ARMTOOLS=ARMCT5
            export ARMHOME=$TOOLS_ROOT/ARM_Compiler_5.06u3
            export ARMROOT=$ARMHOME
            export ARMINC=$ARMHOME/include
            export ARMLIB=$ARMHOME/lib
            export ARMBIN=$ARMHOME/bin
            export ARMPATH=$ARMHOME/bin
            export ARMINCLUDE=$ARMHOME/include
            export LM_LICENSE_FILE=8224@10.20.26.73
            export ARMLMD_LICENSE_FILE=8224@10.20.26.73
            #export LM_LICENSE_FILE=$ARMHOME/license.dat
            #export ARMLMD_LICENSE_FILE=$ARMHOME/license.dat
            ;;
        msm8937)
            debug cmd "set_build_env msm8937"
            export HEXAGON_ROOT="$TOOLS_ROOT/HEXAGON_Tools"
            export PATH=$HEXAGON_ROOT:$PATH
            export HEXAGON_RTOS_RELEASE=5.1.05
            # ARMTOOLS
            export ARMTOOLS=ARMCT5
            export ARMHOME=$TOOLS_ROOT/ARM_Compiler_5.06u3
            export ARMROOT=$ARMHOME
            export ARMINC=$ARMHOME/include
            export ARMLIB=$ARMHOME/lib
            export ARMBIN=$ARMHOME/bin
            export ARMPATH=$ARMHOME/bin
            export ARMINCLUDE=$ARMHOME/include
            export LM_LICENSE_FILE=8224@10.20.26.73
            export ARMLMD_LICENSE_FILE=8224@10.20.26.73
            #export LM_LICENSE_FILE=$ARMHOME/license.dat
            #export ARMLMD_LICENSE_FILE=$ARMHOME/license.dat
            # LLVM
            LLVM_VERSION=3.7.6
            export LLVMTOOLS=LLVM
            export LLVMROOT=$TOOLS_ROOT/LLVM/$LLVM_VERSION
            export LLVMBIN=$LLVMROOT/bin
            export LLVMLIB=$LLVMROOT/lib/clang/$LLVM_VERSION/lib/linux
            export MUSLPATH=$LLVMROOT/tools/lib64
            export MUSL32PATH=$LLVMROOT/tools/lib32
            export LLVMINC=$MUSLPATH/include
            export LLVM32INC=$MUSL32PATH/include
            export LLVMTOOLPATH=$LLVMROOT/tools/bin
            ;;
    esac
}

# AP
build_kernel(){
    debug cmd "build kernel"

    KERNEL_ARCH=arm64
    TARGET_KERNEL_SOURCE=$AP/kernel/msm-4.4
    KERNEL_OUT=$AP/out/target/product/sdm660_64/obj/kernel/msm-4.4
    KERNEL_CROSS_COMPILE=$AP/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-
    KERNEL_MODULES_INSTALL=$AP/out/target/product/sdm660_64/system/lib/modules/

    case $1 in
        kernelconfig)
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) menuconfig
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) savedefconfig
            cp $(KERNEL_OUT)/defconfig $(TARGET_KERNEL_SOURCE)/arch/$(KERNEL_ARCH)/configs/$(KERNEL_DEFCONFIG)
            ;;
        kernel)
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) $(KERNEL_DEFCONFIG)
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) KCFLAGS=-mno-android modules
            make -j8 -C $(TARGET_KERNEL_SOURCE) O=$(KERNEL_OUT) INSTALL_MOD_PATH=$(KERNEL_MODULES_INSTALL) INSTALL_MOD_STRIP=1 ARCH=$(KERNEL_ARCH) CROSS_COMPILE=$(KERNEL_CROSS_COMPILE) modules_install
            ;;
    esac
    retVal=$?
    return $retVal
}

build_lk(){
    debug cmd "build lk"
}

function build_android()
{
    debug cmd "build android"
    cd $AP
    source build/envsetup.sh
    lunch ${PRODUCT_DEVICE}-userdebug
    case $MODULE in

        boot)
            build_kernel kernel; retVal=$?
            make -j$CPUCORE bootimage-nodeps; retVal=$?;
            ;;

        lk)
            if [ x$C == x"true" ];then clean_lk; retVal=$?; fi
            if [ x$M == x"true" ];then build_lk; retVal=$?; fi
            ;;

        mmma | mmm)
            $ACTION $MODULE 2>&1 | tee $LOG_PATH/$ACTION.log; result=$?
            ;;

        update-api | aboot | bootimage | systemimage | recoveryimage | vendorimage | userdataimage | cacheimage-nodeps | snod | systemimage-nodeps | vnod | vendorimage-nodeps | bootimage-nodeps | userdataimage-nodeps | ramdisk-nodeps | otapackage | cts  | apdimage | apdimage-nodeps |xromimage)
            make -j$CPUCORE $ACTION 2>&1 | tee $LOG_PATH/$ACTION.log; result=$?
            if [ x"$ACTION" == x"otapackage" ];then
                cd $amssPath/$CHIPID_DIR/common/build/bin/asic/sparse_images
                python $WsRootDir/amss/BOOT.BF.3.3/boot_images/core/storage/tools/ptool/checksparse.py -i ./../../../rawprogram0.xml -s $WsRootDir/out/target/product/$PRODUCT/ -o rawprogram_unsparse.xml
                cd $WsRootDir
            fi
            ;;
        aboot | bootimage | systemimage | recoveryimage | vendorimage | userdataimage | cacheimage-nodeps | snod | systemimage-nodeps | vnod | vendorimage-nodeps | bootimage-nodeps | userdataimage-nodeps | ramdisk-nodeps | otapackage | cts  | apdimage | apdimage-nodeps |xromimage)
    esac

    cd -
    return $retVal
}

# BP
function sectools()
{
    local SECTOOLS_PATH=$META_PATH/common/sectools

    case $1 in
        secimage)
            if [ x$CLEAN == x"c" ];then
                INIMG="$ADSP_PATH/adsp_proc/obj/$ADSP_CHIPSET/signed/adsp.mbn"
                python $SECTOOLS_PATH/sectools.py secimage -i $INIMG -c $SECTOOLS_PATH/config/$CHIPSET/${CHIPSET}_secimage.xml -sa
            else
                python $SECTOOLS_PATH/sectools.py secimage -m $META_PATH -p $ADSP_CHIPSET -sa
            fi
            ;;

        debugpolicy) # qcom:80-P2485-39 E dp_AP_signed.mbn/dp_MSA_signed.mbn
            python $SECTOOLS_PATH/sectools.py debugpolicy -c $SECTOOLS_PATH/config/$ADSP_CHIPSET/${ADSP_CHIPSET}_debugpolicy.xml -e  $SECTOOLS_PATH/config/$ADSP_CHIPSET/${ADSP_CHIPSET}_dbgp_secimage.xml  -ga
            ;;
        fuseblower)
            echo
            ;;

        keyprovision)
            echo
            ;;

        mbngen)
            echo
            ;;
    esac
    retVal=$?
    return $retVal
}

function build_meta(){
    debug info "start build $META"
    CONTENTS_XML=''
    cd $META_PATH/common/build
    python build.py ; retVal=$?
    cd -
    return $retVal
}

function build_mpss(){
    debug info "start build $MPSS"
    #echo "root@123" | sudo -S  ntpdate 10.20.26.73
    cd $MPSS_PATH/modem_proc/build/ms
    if [ x$CLEAN == x"c" ];then
        ./build.sh ${MPSS_CHIPSET}.gen.prod -c
    else
        ./build.sh ${MPSS_CHIPSET}.gen.prod -k
    fi

    retVal=$?
    #./build.sh 8937.genns.prod -k 2>&1|tee $LOG_PATH/mpss.log
    #    if [ "`grep "Build 8937.genns.prod returned code 0" $LOG_PATH/mpss.log`"  ];then
    #        echo -e "\033[40;32m Build MPSS.JO.3.0 Successfully \033[0m"
    #        sleep 2
    #    else
    #        echo -e "\033[40;31m Build MPSS.JO.3.0 failed (>.<) \033[0m"
    #        exit 1
    #    fi
    #echo "root@123" | sudo -S ntpdate cn.pool.ntp.org
    cd -
    return $retVal
}


function build_rpm(){
    debug info "start build $RPM"
    #echo "root@123" | sudo -S  ntpdate 10.20.26.73

    cd $RPM_PATH/rpm_proc/build

    if [ x$CLEAN == x"c" ];then
        ./build_${RPM_CHIPSET}.sh -c
    else
        ./build_${RPM_CHIPSET}.sh
    fi

    retVal=$?
    #if [ "`grep "done building targets" $LOG_PATH/rpm_proc_$CHIP.log`" ];then
    #    echo -e "\033[40;32m Build $RPM Successfully \033[0m"
    #    sleep 2
    #else
    #    echo -e "\033[40;31m Build $RPM failed (>.<) \033[0m"
    #    exit 1
    #fi

    cd -
    #echo "root@123" | sudo -S ntpdate cn.pool.ntp.org
    return $retVal
}

function build_tz(){
    debug info "start build $TZ"
    cd $TZ_PATH/trustzone_images/build/ms
    if [ x$CLEAN == x"c" ];then
        python build_all.py -b TZ.BF.4.0 CHIPSET=sdm660 -c
    else
        python build_all.py -b TZ.BF.4.0 CHIPSET=sdm660 devcfg sampleapp
    fi
    retVal=$?
    #if [ "`grep "done building targets" $LOG_PATH/tz_8917.log`" ];then
    #    echo -e "\033[40;32m Build TZ.BF.4.0.5 Successfully \033[0m"
    #    sleep 2
    #else
    #    echo -e "\033[40;31m Build TZ.BF.4.0.5 failed (>.<) \033[0m"
    #    exit 1
    #fi
    cd -
    return $retVal

}

function build_boot(){
    #echo "root@123" | sudo -S  ntpdate 10.20.26.73
    debug info "========== build $BOOT =========="

     #sdm636
     if [ x"BOOT.XF.1.4" == x$BOOT ]; then
         cd $BOOT_PATH
         if [ x$CLEAN == x"clean" ];then
             python -u boot_images/QcomPkg/buildit.py --variant LA -r RELEASE -t Sdm660Pkg,QcomToolsPkg --build_flags=cleanall
         else
             python -u boot_images/QcomPkg/buildit.py --variant LA -r RELEASE -t Sdm660Pkg,QcomToolsPkg
         fi
     else
         cd $BOOT_PATH/boot_images/build/ms/

         if [ x$CLEAN == x"clean" ];then
             ./build.sh TARGET_FAMILY=$CHIPSET --prod -c
         else
             echo "./build.sh TARGET_FAMILY=$CHIPSET --prod"
             ./build.sh TARGET_FAMILY=$CHIPSET --prod
         fi


     fi

     retVal=$?
     #if [ "`grep "Successfully compile $CHIP" $LOG_PATH/boot_$CHIP.log`" ];then
     #    echo -e "\033[40;32m Build BOOT.BF.3.3 Successfully \033[0m"
     #    sleep 2
     #else
     #    echo -e "\033[40;31m Build BOOT.BF.3.3 failed (>.<) \033[0m"
     #    exit 1
     #fi

     cd -
     #echo "root@123" | sudo -S ntpdate cn.pool.ntp.org
     return $retVal
 }

# build_adsp $ADSP_PATH 8937 all
function build_adsp(){
    debug info "start build $ADSP"

    cd $ADSP_PATH/adsp_proc
    command_array=($1 $2 $3 $4 $5)

    for command in ${command_array[*]}; do

        case $command in

            8917|8937|8940) #CHIPSET
                local CHIPSET="-c msm$command"
                continue
                ;;
            sdm660)
                local CHIPSET="-c sdm660"
                continue
                ;;


            clean) #OTHER_OPTION
                local OPTION="-o clean"
                continue
                ;;
            all)
                local OPTION="-o all"
                continue
                ;;
        esac
    done
    debug cmd "python build/build.py $CHIPSET $OPTION"
    python build/build.py $CHIPSET $OPTION
    cd -
}

#配置参数属性
function confi_prop(){
    cd $WsRootDir
    if [ x$PRODUCT == x"E300L_WW" ] && [ x$CHIP == x"8917" ];then
        CHIPID_DIR=MSM8917.LA.3.0.1
        efuse_sign_files=(${efuse_sign_8917[@]})
        ALL_EFUSE_SIGN_FILES=${ALL_EFUSE_SIGN_FILES}" prog_emmc_firehose_8917_ddr.mbn"
    elif [ x$PRODUCT == x"E300L_WW" ] && [ x$CHIP == x"8937" ];then
        CHIPID_DIR=MSM8937.LA.3.0.1
        efuse_sign_files=(${efuse_sign_8937_in[@]})
        ALL_EFUSE_SIGN_FILES=${ALL_EFUSE_SIGN_FILES}" prog_emmc_firehose_8937_ddr.mbn"
    else
        CHIPID_DIR=MSM8937.LA.3.0.1
        efuse_sign_files=(${efuse_sign_8937[@]})
        ALL_EFUSE_SIGN_FILES=${ALL_EFUSE_SIGN_FILES}" prog_emmc_firehose_8937_ddr.mbn"
    fi
    BASE_FILES=$amssPath/base_files_$CHIP
    SIGN_FILES=$amssPath/sign_files
}

function build_bp(){
    build BP
    build_adsp $ADSP_CHIPSET all
    build_rpm
    build_boot
    build_mpss
    build_tz
    build_meta
}
function build_cp(){
    #BP
    $META_PATH/common/build/emmc/bin/asic/NON-HLOS.bin
    $META_PATH/common/build/bin/asic/dspso.bin
    $META_PATH/common/sectools/resources/build/fileversion2/sec.dat
    $META_PATH/common/build/emmc/rawprogram0.xml
    $BOOT_PATH/boot_images/QcomPkg/Sdm660Pkg/Bin/660/LA/RELEASE/prog_emmc_ufs_firehose_Sdm660_ddr.elf
    $BOOT_PATH/boot_images/QcomPkg/Sdm660Pkg/Bin/660/LA/RELEASE/pmic.elf
    $RPM_PATH/rpm_proc/build/ms/bin/AAAAANAZR/rpm.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/tz.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/hyp.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/km4.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/cmnlib.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/cmnlib64.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/devcfg.mbn
    $TZ_PATH/trustzone_images/build/ms/bin/KAJAANAA/storsec.mbn
    #AP
    declare -A IMGDIC
    IMGDIC=(
    [abl]="$OUT/abl.elf"
    [boot]="$OUT/boot.img"
    [system]="$OUT/system.img"
    [vendor]="$OUT/vendor.img"
    [userdata]="$OUT/userdata.img"
    [persist]="$OUT/persist.img"
    [mdtp]="$OUT/mdtp.img"
    )
}

function flash_image(){
    local img=$1
    debug cmd "fastboot flash $img ${IMGDIC[$img]}"
    fastboot flash $img ${IMGDIC[$img]}
    retVal=$?

    if [ $retVal -ne 0 ]; then
        local msg=$(perror $retVal)
        debug error "===============${IMGDIC[$img]} : ${msg#*:}============="
    fi
    return $retVal
}

function adbpush(){
    adb root
    adb remount
    adb shell mount -o rw,remount  $FIRMWARE
    adb shell mount -o rw,remount  $PERSIST
    adb shell rm $PERSIST/sensors/sns.reg
    #adb push $AP/vendor/qcom/proprietary/sensors/dsps/reg_defaults/sensor_def_qcomdev.conf /vendor/etc/sensors/
    rm $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/SecImage_log.txt
    rm $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/adsp.mbn
    adb push $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/* $FIRMWARE/image
    adb reboot
}

function adbpush(){
    adb root
    adb remount
    rm $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/SecImage_log.txt
    rm $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/adsp.mbn
    adb push $META_PATH/common/sectools/secimage_output/$CHIPSET/adsp/* $FIRMWARE/image
    adb reboot
}

function main(){
    ##################################################################
    #Check parameters
    ##################################################################
    command_array=($1 $2 $3 $4 $5)
    echo "`date +"%F %T"` $0 $1 $2 $3 $4 $5"
    for command in ${command_array[*]}; do

        case $command in
            8940| 8937| 8917)
                CHIPSET=$command
                echo "$CHIPSET"
                continue
                ;;
        esac

        ### set PRODUCT
        case $command in
            help)
                usage
                ;;
            zb555)
                #if [ x$PRODUCT != x"" ];then continue; fi
                PRODUCT="Oreo_ZB555KL_MR"
                ARM=arm64
                CONFIG_NAME=$command
                #AP
                FIRMWARE="/firmware"
                PERSIST="/persist"
                # BP
                if [ $CHIPSET == "8917" ];then
                    META="MSM8917.LA.3.0.1"
                elif [ $CHIPSET == "8937" ];then
                    META="MSM8937.LA.3.0.1"
                else
                    echo "fail"
                    exit 1
                fi
                ADSP_CHIPSET="8937"
                AMSS="amss"
                ADSP="ADSP.8953.2.8.4_WW"
                BOOT=""
                CNSS=""
                CPE=""
                MPSS=""
                MPSS_CHIPSET=8937
                RPM="RPM.BF.2.2"
                RPM_CHIPSET=8937
                TZ=""
                continue
                ;;
            AOSP_pie_sku6-8_ZC554KL_dev)
                # if [ x$PRODUCT != x"" ];then continue; fi
                PRODUCT=$command
                ARM=arm64
                CONFIG_NAME=$command
                DEPEND=msm8937_64

                # BP
                if [ x$CHIPSET == x"8917" ];then
                    META="MSM8917.LA.3.1.2"
                elif [ x$CHIPSET == x"8937" ];then
                    META="MSM8937.LA.3.1.2"
                fi
                AMSS="amss_codes"
                META="MSM8937.LA.3.1.2"
                ADSP="ADSP.VT.3.0"
                ADSP_CHIPSET="8937"
                BOOT="BOOT.BF.3.3"
                CNSS=""
                CPE=""
                MPSS=""
                MPSS_CHIPSET=8937
                RPM="RPM.BF.2.2" TZ=""
                continue
                ;;
            sdm636)
                # if [ x$PRODUCT != x"" ];then continue; fi
                PRODUCT="Q_SDM636_dev"
                PRODUCT_DEVICE=sdm660_64
                ARM=arm64
                CONFIG_NAME=$command
                DEPEND=''
                CHIPSET=sdm663

                # BP
                AMSS="amss_codes"
                META="SDM636.LA.3.0.1"
                ADSP="ADSP.VT.4.1"
                ADSP_CHIPSET="sdm660" #
                BOOT="BOOT.XF.1.4"
                CNSS=""
                CPE=""
                MPSS="MPSS.AT.3.1"
                MPSS_CHIPSET="sdm660"
                RPM="RPM.BF.1.8"
                RPM_CHIPSET=660
                TZ="TZ.BF.4.0.7"
                continue
                ;;
        esac

    done
    set_build_env $ADSP_CHIPSET
    AP=$PROJECT_ROOT/$PRODUCT
    BP=$PROJECT_ROOT/$PRODUCT/$AMSS
    META_PATH=$BP/$META
    ADSP_PATH=$BP/$ADSP
    BOOT_PATH=$BP/$BOOT
    MPSS_PATH=$BP/$MPSS
    RPM_PATH=$BP/$RPM
    TZ_PATH=$BP/$TZ
    OUT=$AP/out/target/product/$PRODUCT_DEVICE

    for command in ${command_array[*]}; do
        case $command in
            bp)
                build_bp
                continue
                ;;
            adsp)
                build_adsp $ADSP_CHIPSET all
                continue
                ;;
            meta)
                build_meta
                continue
                ;;

            mpss)
                build_mpss
                continue
                ;;
            ap)
                build_android
                continue
                ;;
            flash)
                flash_image $2
                continue
                ;;
        esac
    done
}

#main 8937 AOSP_pie_sku6-8_ZC554KL_dev
#main 8917 zb555
main sdm636 $@
