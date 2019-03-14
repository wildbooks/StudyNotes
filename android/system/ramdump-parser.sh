# ramdump-parser.sh
 
#! /bin/bash
echo ""
echo "Start ramdump parser.."
 
ROOT=/work1/AOSP_pie_sku2-4_ZD553KL_dev
local_path=$PWD
ramdump=/work/asus/sku2-4p/ramdump/Port_COM275
vmlinux=/work/asus/sku2-4p/ramdump/Port_COM275/vmlinux
out=$local_path
 

gdb=$ROOT/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-gdb
gdb64=$ROOT/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-gdb
nm=$ROOT/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin/arm-linux-androideabi-nm
nm64=$ROOT/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-nm
objdump=$ROOT/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin/arm-linux-androideabi-objdump
objdump64=$ROOT/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-objdump
# git clone git://codeaurora.org/quic/la/platform/vendor/qcom-opensource/tools
ramparse_dir=$ROOT/vendor/qcom/opensource/tools/linux-ramdump-parser-v2
########################################################################################
 
echo "cd $ramparse_dir"
cd $ramparse_dir
echo ""
 
cmd="python ramparse.py -v $vmlinux -g $gdb  -n $nm64  -j $objdump64 -a $ramdump -o $out -x --force-hardware 8937"
echo $cmd

${cmd}
echo ""
 
 
cd $local_path
echo "out: $out"
echo ""
exit 0
