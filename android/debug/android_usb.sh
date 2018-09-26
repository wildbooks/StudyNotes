#1. adb root
#     2. adb remount
#     3. adb shell
#     4. chmod 777 /dev/diag
#     5. setenforce 0
#     6. getenforce (confirm that its permissive)
#     7. ps -A | grep “audio”
#        （示例） i.e.
#        audioserver 3669 1 39312 10644 binder_thread_read 0 S android.hardware.audio@2.0-service
#        audioserver 3670 1 51620 11912 binder_thread_read 0 S audioserver
#        Look for the process id for android.hardware.audio@2.0-service and kill the process
#     8. kill 3669
#     9. Now Connect to QACT

# 开启USB调试端口
echo   0 > /sys/class/android_usb/android0/enable
echo  05c6 > /sys/class/android_usb/android0/idVendor
echo 1 > /sys/class/android_usb/android0/enable
start adbd
sleep 10
