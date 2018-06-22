# 开启USB调试端口
echo   0 > /sys/class/android_usb/android0/enable
echo  05c6 > /sys/class/android_usb/android0/idVendor
echo 1 > /sys/class/android_usb/android0/enable
start adbd
sleep 10
