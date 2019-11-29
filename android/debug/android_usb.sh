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

    setprop sys.usb.config 'diag,serial_smd,rmnet_qti_bam,adb'
    setprop sys.usb.configfs 0
