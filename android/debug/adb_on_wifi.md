# adb通过wifi链接设备
* 确认本机PC没有和任何adb设备链接
* 本机PC和手机在同一个局域网
* 查看手机链接wifi后的ip地址
    adb shell ifconfig
* 用主机ping手机设备，看是否能ping通
    adb ping 192.168.43.233(手机wifi ip)
* 用adb tcpip模式重启adb
    adb tcpip 5555
* 链接手机设备
    adb connect 192.168.43.233
    或 adb connect 192.168.43.233:5555
* 可以使用adb相应命令
    adb shell
