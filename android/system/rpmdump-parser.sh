rpmroot="/work1/AOSP_pie_sku2-4_ZD553KL_dev/amss_codes/RPM.BF.2.2"
rpm_path="$rpmroot/rpm_proc/core/bsp/rpm/scripts/hansei"
#rpmelf="$rpmroot/rpm_proc/core/bsp/rpm/build/8937/RPM_AAAAANAAR_rpm.elf"
#rpmelf="$rpmroot/rpm_proc/core/bsp/rpm/build/8937/RPM_AAAAANAAR.elf"
dump_root_path="/work/asus/sku2-4p/ramdump/Port_COM41"
rpmelf="$dump_root_path/RPM_AAAAANAAR.elf"
dump_files="$dump_root_path/CODERAM.BIN $dump_root_path/DATARAM.BIN $dump_root_path/MSGRAM.BIN"

output=$(pwd)

cd $rpm_path
pwd
cmd="python hansei.py --elf $rpmelf --output $output $dump_files"
echo $cmd
$($cmd)
