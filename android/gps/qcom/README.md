* apps
	frameworks/base/location/java/android/location/LocationManager.java
* frameworks
	frameworks/base/services/core/java/com/android/server/LocationManagerService.java
* hal
	hardware/libhardware_legacy/include/hardware_legacy/gps.h
	hardware/qcom/gps/
	vendor/qcom/proprietary/gps

* kernel
# config
	vendor/qcom/proprietary/gps/etc/sap.conf
	vendor/qcom/proprietary/gps/etc/izat.conf
	hardware/qcom/gps/etc/gps.conf
# shell
	/etc/izat.conf
	/etc/sap.conf
	/etc/gps.conf
	/system/etc/izat.conf
	/system/etc/sap.conf
	/system/etc/gps.conf
	/system/lib/libloc_core.so
	/system/lib64/libloc_core.so
	/system/lib/libloc_eng.so
	/system/lib/libgps.utils.so
	/system/lib64/libgps.utils.so
# 排除问题
	1. 相关的库及文件是否已经在客户机上
