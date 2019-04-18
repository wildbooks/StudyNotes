adb root && adb wait-for-device
adb remount

# frameworks/base/core/java/android/hardware
adb push $ANDROID_PRODUCT_OUT/system/framework/arm/boot-framework.art /system/framework/arm/
adb push $ANDROID_PRODUCT_OUT/system/framework/arm/boot-framework.oat /system/framework/arm/
adb push $ANDROID_PRODUCT_OUT/system/framework/arm/boot-framework.art.rel /system/framework/arm/
adb push $ANDROID_PRODUCT_OUT/system/framework/arm64/boot-framework.art /system/framework/arm64/
adb push $ANDROID_PRODUCT_OUT/system/framework/arm64/boot-framework.oat /system/framework/arm64/
adb push $ANDROID_PRODUCT_OUT/system/framework/arm64/boot-framework.art.rel /system/framework/arm64/
adb push $ANDROID_PRODUCT_OUT/system/framework/boot-framework.vdex /system/framework/
adb push $ANDROID_PRODUCT_OUT/system/framework/framework.jar /system/framework/

# frameworks/base/core/jni
adb push $ANDROID_PRODUCT_OUT/system/lib64/libandroid_runtime.so /system/lib64/ #SensorManager

# frameworks/native/services/sensorservice
adb push $ANDROID_PRODUCT_OUT/system/lib64/libsensorservicehidl.so /system/lib64/ #HidlSensorManager
adb push $ANDROID_PRODUCT_OUT/system/lib64/libsensorservice.so /system/lib64/ #SensorService

# frameworks/native/libs/sensor
adb push $ANDROID_PRODUCT_OUT/system/lib64/libsensor.so /system/lib64/ #Sensors

# hardware/interfaces/sensors/1.0/default

# hal => vendor/qcom/proprietary/sensors/dsps/libhalsensors
adb push $ANDROID_PRODUCT_OUT/system/lib64/hw/sensors.msm8937_64.so /system/lib64/hw/ #qti_sensors_hal
# Sensor1 library => vendor/qcom/proprietary/sensors/dsps/libsensor1
adb push $ANDROID_PRODUCT_OUT/system/vendor/lib/libsensor1.so  /vendor/lib/  #libsensor1
# Sensors daemon => vendor/qcom/proprietary/sensors/dsps/sensordaemon
adb push $ANDROID_PRODUCT_OUT/system/vendor/bin/sensors.qti /vendor/bin/ #Sensors

# regester
adb shell rm /persist/sensors/sns.reg
adb push $ANDROID_BUILD_TOP/vendor/qcom/proprietary/sensors/dsps/reg_defaults/sensor_def_qcomdev.conf /system/vendor/etc/sensors/sensor_def_qcomdev.conf

adb reboot
