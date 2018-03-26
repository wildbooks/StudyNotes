# Linux Audio Device Management

# 目的
    主要讲解添加新音频设备的过程。主要配置了xml文件和acdb文件
        添加设备
        校准设备
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
