# 用于判断是否为系统性能差异导致系统破音
adb root
adb shell stop thermal-engine
adb shell stop mpdecision
adb shell stop perf-hal-1-0
adb shell "echo 4 > /sys/devices/system/cpu/cpu0/core_ctl/min_cpus"
adb shell "echo 4 > /sys/devices/system/cpu/cpu4/core_ctl/min_cpus"
adb shell "echo 1 > /sys/devices/system/cpu/cpu0/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu1/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu2/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu3/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu4/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu5/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu5/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu6/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu6/cpufreq/scaling_governor"
adb shell "echo 1 > /sys/devices/system/cpu/cpu7/online"
adb shell "echo performance > /sys/devices/system/cpu/cpu7/cpufreq/scaling_governor"
adb shell "echo Y > /sys/module/lpm_levels/parameters/sleep_disabled"
