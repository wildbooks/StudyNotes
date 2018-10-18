# 目的
  以msm8937为例子，在/vendor/etc/acdbdata/MTP/NonCE目录下添加新的acdb文件,NonCE目录不存在
# 需要修改以下文件
  vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/MTP/NonCE/
  vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/Android.mk
  vendor/qcom/proprietary/vendor/qcom/proprietary/common/config/device-vendor.mk
# 步骤如下
  1. 将acdb文件拷贝到vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/MTP/NonCE/目录下
  2. 在文件vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/Android.mk中建立编译规制，以下以拷贝MTP_NonCE_Bluetooth_cal.acdb为例

        +include $(CLEAR_VARS)
        +LOCAL_MODULE            := MTP_NonCE_Bluetooth_cal.acdb
        +LOCAL_MODULE_FILENAME   := Bluetooth_cal.acdb
        +LOCAL_MODULE_TAGS       := optional
        +LOCAL_MODULE_CLASS      := ETC
        +LOCAL_MODULE_PATH       := $(TARGET_OUT_VENDOR_ETC)/acdbdata/MTP/NonCE/
        +LOCAL_SRC_FILES         := MTP/NonCE/Bluetooth_cal.acdb
        +include $(BUILD_PREBUILT)
        +
  3. 将编译规则添加到vendor/qcom/proprietary/vendor/qcom/proprietary/common/config/device-vendor.mk文件中
        +MM_AUDIO += MTP_NonCE_Bluetooth_cal.acdb
# 总结
编译依赖关系
  PRODUCT_PACKAGES -> MM_AUDIO -> MTP_NonCE_Bluetooth_cal.acdb
