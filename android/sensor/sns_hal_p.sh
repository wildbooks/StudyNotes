adb root
adb wait-for-device
adb shell setprop debug.sns.daemon.ftrace 1
adb shell setprop debug.sns.hal.ftrace 1
adb shell setprop debug.vendor.sns.daemon 1 #Sensors
adb shell setprop debug.vendor.sns.libsensor1 1 #libsensor1
adb shell setprop persist.vendor.debug.sensors.hal 1 #qti_sensors_hal
adb shell stop
adb shell stop sensors
adb shell start sensors
adb shell start
#adb logcat -c;adb logcat -s Sensors -s libsensor1 -s qti_sensors_hal
