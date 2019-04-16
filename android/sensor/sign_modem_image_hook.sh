#!/bin/bash
#
# file create by liunianliang for sign the mbn in NON-HLOS.bin
#
# 2017.03.17
#


#
# set env
#
# set -x
myDir=`pwd`
tempOriginDir="$myDir/.hideTemp/origin"
tempSignDir="$myDir/.hideTemp/sign"
mpssDir="$1"
if [[ "$@" =~ "init" ]];then
    init=true
fi
if [[ "$@" =~ "clean" ]];then
    clean=true
fi
sign_xml="$2"
platform="`basename $sign_xml | awk -F '_' '{print $1}'`"
sectool_dir="$3"

echo "SongPeng 1=$1 2=$2 3=$3 4=$4 5=$5"

MODEM_MCFG_PATH=$myDir/$mpssDir/modem_proc/mcfg
MODEM_PLATFORM_MCFG_PATH=$MODEM_MCFG_PATH/mbns/generic_$5
if [ -d $MODEM_PLATFORM_MCFG_PATH ];then
  rm -rf $MODEM_MCFG_PATH/configs/mcfg_sw/generic
  cp -r $MODEM_PLATFORM_MCFG_PATH $MODEM_MCFG_PATH/configs/mcfg_sw/generic
  echo "cp -r $MODEM_PLATFORM_MCFG_PATH $MODEM_MCFG_PATH/configs/mcfg_sw/generic"
fi

SHOLUD_SIGN_FILE="$mpssDir/modem_proc/build/ms/bin/8937.genns.prod/mbc.mbn"
SHOLUD_SIGN_FILE+=" `find $myDir/$mpssDir/modem_proc/mcfg/configs/ -type f -name \"*\" `"
#
# sign one mbn
#
function sign_item_mbn() {
    local mbn=$1
    local mbnName="`basename $mbn`"
    local originMbn=".`echo $mbn | awk -F $tempOriginDir '{print $NF}'`"
    python $sectool_dir/sectools.py secimage -i $mbn -c $sign_xml -sa -o $tempSignDir
    fullPath="`find $tempSignDir/$platform -type f -name $mbnName`"
    echo "CopySignFile: $fullPath --> $originMbn"
    `cp -rf $fullPath $originMbn`
}


#
# sign all mbn
#
function sign_all_mbn() {
    for mbn in `find $tempOriginDir -type f` ;do
        if [ -e "$mbn" ];then
            echo -e "begin to sign: $mbn"
            sign_item_mbn $mbn
        else
            echo -e "Warning: can't find mbn: $mbn !!!"
        fi
    done
    unset mbn
}

#
# create temp dir and file
#
function createTempDir() {

    if [ -n "$init" ];then
        `rm -rf $tempOriginDir`
    fi
    `rm -rf $tempSignDir` ; `mkdir -p $tempSignDir`
    if [ ! -d "$tempOriginDir" ];then
        `mkdir -p $tempOriginDir`
        for f in ${SHOLUD_SIGN_FILE};do
			echo "$f"
            suffix=$mpssDir`echo $f | awk -F $mpssDir '{print $NF}'`
            if [ -e "$suffix" ];then
                echo "CopyFile: $suffix"
                ((count++))
                itemdir="$tempOriginDir/`dirname $suffix`"
                `mkdir -p $itemdir` ; `cp -rf $suffix $itemdir`
            else
                echo "Warning: can't find $suffix !"
            fi
        done
        echo -e "\n--------------------------- Copy Done ! Total count: $count ------------------------\n"
        unset f
    fi
}

#
# checkout all sign mbn
#
function restoreMbn() {
    cd $myDir/$mpssDir
    for i in `find modem_proc/mcfg/configs/ -type f`;do
        echo "Checkout: $i"
        `git checkout $i`
    done
    cd $myDir
}

function run() {
    if [ "$clean" == "true" ];then
        restoreMbn
    else
        createTempDir
        sign_all_mbn
    fi
}

run
