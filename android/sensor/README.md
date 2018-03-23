# 关键宏
	USE_SENSOR_MULTI_HAL

# framework
  frameworks/base/core/java/android/hardware/Sensor.java
# jni
  frameworks/base/core/jni/android_hardware_SensorManager.cpp
# native
  frameworks/native/services/sensorservice
# hal
# kernel
# bsp
  amss/DSP.8953.2.8.4/adsp_proc/Sensors/build/Sensors.scons

# code
  vendor/qcom/proprietary/sensors/
  ADSP.8953.2.8.4/adsp_proc/Sensors/ #bringup
  frameworks/native/data/etc/
# config
  /system/etc/sensors/	
  sensors/dsps/reg_defaults/sensor_def_qcomdev.conf	#config

# tool
	1. QSensorTest
		vendor/qcom/proprietary/sensors/QSensorTest/
		源代码
