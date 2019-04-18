adb root && adb wait-for-device
adb remount

# selinux
#$ANDROID_BUILD_TOP
adb push $ANDROID_PRODUCT_OUT/system/etc/selinux /sysetm/etc
adb push $ANDROID_PRODUCT_OUT/vendor/etc/selinux /vendor/etc
adb reboot
