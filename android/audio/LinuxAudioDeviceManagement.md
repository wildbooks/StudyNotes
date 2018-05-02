# Linux Audio Device Management

# 目的
    主要讲解添加新音频设备的过程。主要配置了xml文件和acdb文件
        添加设备
        校准设备
## 添加设备
    1. 在音频校准数据库（ACDB）文件中添加设备条目并更新设备的校准数据
    2. 如果新设备是在voice call，VoIP或VoLTE call中选择的Tx或Rx，请在ACDB文件中添加适当的设备对。
    3. 将混音器控制(mixer control)定义和路径定义添加到具有所需序列的混音器路径XML文件中。
    4. 在platform.h和platform.c中添加一个条目到device_table。
    5. 将硬件中的设备ACDB设备ID包含在platform.c文件中的acdb_device_table
    6. 将device_table中提到的设备名称映射到Android设备。这需要更改hardware/qcom/audio/hal/msm8916/platform.c文件中的platform_get_output_snd_device()函数。
## Device table
    hardware/qcom/audio/hal/msm8916/platform.h  #SND_DEVICE_OUT_BEGIN附近
    hardware/qcom/audio/hal/msm8916/platform.c  #device_table
## Mixer path XML
    device/qcom/msm8916_32/mixer_paths.xml
    hardware/qcom/audio/configs/msm8937/mixer_paths.xml
## ACDB device ID table
    hardware/qcom/audio/hal/msm8916/platform.c  #acdb_device_table
    用到工具QACT™
## LOG抓取

# 专有名词
    Audio Calibration Data Base (ACDB)  音频校准数据库
# 参考文档
    80-NL239-28 E
