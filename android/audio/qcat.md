# 链接
    adb root
    adb remount
    adb shell
    chmod 777 /dev/diag
    setenforce 0
    ps -A | grep "audio"
    （示例） i.e.
        audioserver 3669 1 39312 10644 binder_thread_read 0 S android.hardware.audio@2.0-service
        audioserver 3670 1 51620 11912 binder_thread_read 0 S audioserver
        Look for the process id for android.hardware.audio@2.0-service and kill the process
    kill 3669
    9. 链接qcat
