* apps
	frameworks/base/location/java/android/location/LocationManager.java
* frameworks
	frameworks/base/services/core/java/com/android/server/LocationManagerService.java
* jni
	meworks/base/core/java/android/hardware/location

* hal
	hardware/qcom/gps/
	vendor/qcom/proprietary/gps
	vendor/qcom/opensource/location

	device/common/gps/
	hardware/libhardware/include/hardware/gps.h
	hardware/libhardware/include/hardware/gps_internal.h
	hardware/libhardware/

# 仓库
	modem
	hardware/qcom/gps/
	vendor/qcom/proprietary/gps/
	vendor/qcom/opensource/location/
	device/common/
	hardware/libhardware/
	hardware/libhardware_legacy/
	
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
