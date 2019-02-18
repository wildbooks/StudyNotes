adb root &&adb remount

# selinux
#$ANDROID_BUILD_TOP
adb push $ANDROID_PRODUCT_OUT/system/etc/selinux /sysetm/etc/selinux
adb push $ANDROID_PRODUCT_OUT/vendor/etc/selinux /vendor/etc/selinux
adb reboot
