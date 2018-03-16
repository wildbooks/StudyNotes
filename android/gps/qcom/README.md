	Location -> LocationManager -> LocationManagerService
* apps
	#属于package: android.location
	frameworks/base/location/java/android/location/LocationManager.java	#位置服务管理类
	frameworks/base/location/java/android/location/LocationProvider.java #位置源提供者
	frameworks/base/location/java/android/location/Location.java #位置对象
	frameworks/base/location/java/android/location/LocationListener.java #位置监听接口
	# 获取GPS定位步骤
		1. 获取LocationMangager对象
		2. 新建Location对象
		...
* frameworks
	frameworks/base/services/core/java/com/android/server/LocationManagerService.java
* jni
	frameworks/base/core/java/android/hardware/location
	frameworks/base/services/core/jni/com_android_server_location_FlpHardwareProvider.cpp
	frameworks/base/services/core/jni/com_android_server_location_GnssLocationProvider.cpp
* hal
	hardware/qcom/gps
	vendor/qcom/proprietary/gps
	vendor/qcom/opensource/location
	device/common/gps/
	hardware/libhardware/

	hardware/libhardware/include/hardware/gps.h			#gps_device_t
	hardware/libhardware/include/hardware/gps_internal.h
	hardware/qcom/gps/loc_api/libloc_api_50001/gps.c	#gps_device_t
	gps_device_t -> hardware/qcom/gps/loc_api/libloc_api_50001/loc.cpp

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
