# 刷机后无法正常引导设置
登录google账号后没退出，刷入其他版本无法正常引导设置手机
刷userdebug版本
adb root
adb remount
adb shell settings put secure user_setup_complete 1
adb reboot
