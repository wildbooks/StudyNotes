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

# adsp
	1. 声明驱动程序的入口函数
		adsp_proc/Sensors/dd/qcom/inc/sns_dd.h
		```c
		extern sns_ddf_driver_if_s sns_dd_<new_sensor_model>_if;
		```
	2. 添加驱动文件

		1. 添加驱动文件
				1. 在adsp_proc/Sensors/dd/qcom/src/路径下添加驱动文件
				2. 修改adsp_proc/Sensors/dd/qcom/build/dd_qcom.scons文件
				(或者
				1. 在adsp_proc/Sensors/dd/vendor/src/路径下添加驱动文件
				2. 修改adsp_proc/Sensors/dd/vendor/build/dd_vendor.scons文件
				)
		
		2.修改文件adsp_proc/Sensors/build/Sensors.scons
			env.Append(CPPDEFINES = [”CONFIG_SUPPORT_<NEW_SENSOR_MODEL>”])
	3.生成与新驱动关联的UUID
		1. 生成与新驱动关联的UUID
			(uuid可以用linux命令行uuidgen生成)
			adsp_proc/Sensors/common/inc/sns_reg_common.h
			vendor/qcom/proprietary/sensors/dsps/sensordaemon/common/inc/sns_reg_common.h
		2. 更新传感器管理器(SMGR)函数指针映射,以便SMGR可以将更新的UUID与新的DD函数指针相关联
			在adsp_proc/Sensors/smgr/src/sns_smgr_reg.c 文件里smgr_sensor_fn_ptr_map中添加
			```
			#ifdef CONFIG_SUPPORT_<NEW_SENSOR_MODEL>
			{ SNS_REG_UUID_XXXX, &sns_xxx_xxxx_driver_fn_list},
			#endif
			```
	4. 配置寄存器
		vendor/qcom/proprietary/sensors/dsps/api/sns_reg_api_v02.h
		1. 更新配置文件
			1. 创建sensor_def_<oem>.conf文件
				参考sensors_def_qcomdev.conf
				:key value1 value2
					version
					hardware
					platform
					soc_id
			2. 修改驱动程序对应的寄存器
				驱动器的寄存器ID参考vendor\qcom\proprietary\sensors\dsps\api\sns_reg_api_v02.h
				<Registry ID> <Value> <Version>
				vendor/qcom/proprietary/sensors/dsps/reg_defaults/sensor_def_qcomdev.conf	#修改寄存器对应的值
			3. push "xxx.conf"到相应的位置
					adb root
					adb remount
					adb shell rm /etc/sensors/sensor_def_qcomdev.conf
					adb push sensors_def_<oem>.conf /etc/sensors/sensor_def_<oem>.conf
					adb shell chmod 644 /etc/sensors/sensor_def_<oem>.conf		
		2. 如何让配置文件生效
			1. 初始化解析
				系统在启动时，会根据sensor_def_<oem>.conf文件生成persist/sensors/sns.reg文件
				在sensor_def_<oem>.conf修改后，要删除sns.reg,避免sns.reg没有重新生成
					```bash
					adb shell rm /<SNS_REG_PATH>/sns.reg
					adb shell sync
					adb reboot
					```
			2. 使用版本号来更新特定的寄存器表项
			3. 每次重新启动后使用版本号重新应用注册表项目

	5. 启用已经集成的驱动程序	
		1. adsp_proc/Sensors/build/Sensors.scons
			添加 env.Append(CPPDEFINES = ["CONFIG_SUPPORT_XXXX"])
		2. 更新配置文件
			按照3.4.1节说明，使用UUID更新配置文件与驱动程序相关联并应用正确的配置设置	


