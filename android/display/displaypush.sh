adb root &&adb remount

# media
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudioclient.so /system/lib/

adb push $ANDROID_BUILD_TOP/hardware/qcom/audio/configs/msm8937/mixer_paths_qrd_sku2.xml /vendor/etc/                                                                #xml
adb push $ANDROID_BUILD_TOP/hardware/qcom/audio/configs/msm8937/audio_policy_configuration.xml /vendor/etc/                                                                #xml
adb shell rm -rf /vendor/etc/acdbdata/QRD/*
adb push $ANDROID_BUILD_TOP/vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/QRD/msm8952-sku2-snd-card/ /vendor/etc/acdbdata/QRD/   #acdb

adb push $ANDROID_PRODUCT_OUT/system/lib/libaudioroute.so /system/lib/
adb push $ANDROID_PRODUCT_OUT/system/vendor/lib/libacdbloader.so /vendor/lib/                                    #acdbloader

# FG
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudioflinger.so /system/lib/
adb push $ANDROID_PRODUCT_OUT/system/lib/libserviceutility.so /system/lib/

# APM
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudiopolicyenginedefault.so /system/lib/
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudiopolicyservice.so /system/lib/
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudiopolicymanagerdefault.so /system/lib/
adb push $ANDROID_PRODUCT_OUT/system/lib/libaudiopolicymanager.so /system/lib/

# HAL
adb push $ANDROID_PRODUCT_OUT/system/vendor/lib/hw/audio.primary.msm8937.so /vendor/lib/hw/                   #so
adb push $ANDROID_PRODUCT_OUT/system/lib/hw/audio.a2dp.default.so system/lib/hw/ #a2dp

#usb
#wifi
#a2dp
adb push $ANDROID_PRODUCT_OUT/system/lib64/android.hardware.bluetooth.a2dpy@1.0.so /system/lib64/
adb push $ANDROID_PRODUCT_OUT/system/lib64/hw/audio.a2dp.default.so /system/lib64/

adb reboot
