#!/usr/bin/env bash

platform=`fastboot getvar platform 2>&1 | grep platform | awk '{print $NF}'`

echo "platform is $platform"


function flash_image() {
  if fastboot flash $1 $2 $3 $4; then
    let 'total++'; return 0;
  else
    echo "${1}--FAILED!--"; return 1;
  fi
}

function unlock() {
  fastboot oem enable-unlock-once
  fastboot erase config
}

function lock() {
  echo dasf
}

function __flash_images__() {
  # non-hlos
  flash_image modem ${platform}_NON-HLOS.bin || return 1;

  # hlos
  flash_image cache cache.img || return 1;
  flash_image userdata userdata.img || return 1;
  flash_image recovery recovery.img || return 1;
  flash_image system system.img || return 1;
  flash_image boot boot.img || return 1;
  flash_image vendor vendor.img || return 1;
  flash_image aboot ${platform}_emmc_appsboot.mbn || return 1;

  # ---backup partition---
}

# main
unlock;
__flash_images__;
