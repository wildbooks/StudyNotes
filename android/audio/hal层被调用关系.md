# 下步机会

audiotrack/audiorecord 时创建设备 搞清楚

## 切换设备流程

* 通话中，切换电话流程

  ```c++
  ##setForceUse() 手动切换设备
  setSpeakerphoneOn() ->... -> onSetForceUse() -> AudioSystem.setForceUse() -> binder -> AudioPolicyService::setForceUse() -> AudioPolicyManagerCustom::setForceUse() -> Engine::setForceUse()
  ```

  ```c++
  # 切换设备
  ## getDeviceForInputSource()
  AudioPolicyService::setPhoneState() -> AudioPolicyManagerCustom::setPhoneState() -> AudioPolicyManager::checkForDeviceAndOutputChanges() -> AudioPolicyManager::checkOutputForAllStrategies() -> AudioPolicyManagerCustom::checkOutputForAttributes() -> Engine::getOutputDevicesForAttributes -> Engine::getDevicesForProductStrategy() -> Engine::getDeviceForStrategyInt() -> Engine::getDeviceForInputSource()
  
  ## getDeviceForStrategyInt()
  AudioPolicyService::setPhoneState() -> AudioPolicyManagerCustom::setPhoneState() -> AudioPolicyManager::checkForDeviceAndOutputChanges() -> AudioPolicyManager::checkOutputForAllStrategies() -> AudioPolicyManagerCustom::checkOutputForAttributes() -> Engine::getOutputDevicesForAttributes() -> Engine::getDevicesForProductStrategy() -> Engine::getDeviceForStrategyInt()
  ```

  ```c++
  adb push  system/lib64/libaudioflinger.so system/lib64/libaudioflinger.so
  adb push system/lib64/libaudiopolicyenginedefault.so /system/lib64/libaudiopolicyenginedefault.so
  ```

+ 耳机插拔切换流程

  ```c++
  # 电话状态插拔耳机
  AudioPolicyService::setDeviceConnectionState() -> AudioPolicyManager::setDeviceConnectionState() -> AudioPolicyManagerCustom::setDeviceConnectionStateInt() -> AudioPolicyManager::checkForDeviceAndOutputChanges() -> AudioPolicyManager::checkOutputForAllStrategies() -> AudioPolicyManagerCustom::checkOutputForAttributes() -> Engine::getOutputDevicesForAttributes() -> Engine::getDevicesForProductStrategy() -> Engine::getDeviceForStrategyInt()
  ```

  ```
  # 普通状态插拔耳机 output
  BnAudioPolicyService::onTransact() -> AudioPolicyService::setDeviceConnectionState() -> AudioPolicyManager::setDeviceConnectionState() -> AudioPolicyManagerCustom::setDeviceConnectionStateInt() -> AudioPolicyManager::checkOutputsForDevice() -> SwAudioOutputDescriptor::open() -> AudioPolicyService::AudioPolicyClient::openOutput() -> AudioFlinger::openOutput() -> AudioFlinger::openOutput_l() -> AudioStreamOut::open()-> DeviceHalHidl::openOutputStream()
  ```

  ```
  # 普通状态插拔耳机 input
  AudioPolicyService::setDeviceConnectionState() -> AudioPolicyManager::setDeviceConnectionState() ->  AudioPolicyManagerCustom::setDeviceConnectionStateInt() -> AudioPolicyManager::checkInputsForDevice() -> AudioInputDescriptor::open() -> AudioPolicyService::AudioPolicyClient::openInput() -> AudioFlinger::openInput() -> AudioFlinger::openInput_l() -> DeviceHalHidl::openInputStream()
  ```

  

  ```bash
  adb push  system/lib64/libaudioflinger.so system/lib64/libaudioflinger.so
  adb push system/lib64/libaudiopolicyenginedefault.so /system/lib64/libaudiopolicyenginedefault.so
  ```



# open/close流程

## DevicesFactoryHalHybrid()被初始化流程

```c++
audioserver -> AudioFlinger::AudioFlinger() -> DevicesFactoryHalInterface::create() -> createDevicesFactoryHal() -> DevicesFactoryHalHybrid::DevicesFactoryHalHybrid()
```

## adev_open()被上层调用流程

该步骤主要对应Hal层的adev_open()函数。通过DevicesFactoryHalHidl::openDevice()函数和hidl通信方式和Hal层建立联系。

+ DevicesFactoryHalHidl

```c++
audioserver -> AudioPolicyService::onFirstRef() -> createAudioPolicyManager() -> AudioPolicyManagerCustom::AudioPolicyManagerCustom() -> AudioPolicyManager::initialize() -> AudioPolicyService::AudioPolicyClient::loadHwModule() -> AudioFlinger::loadHwModule() -> AudioFlinger::loadHwModule_l() -> DevicesFactoryHalHybrid::openDevice() -> DevicesFactoryHalHidl::openDevice()
```

+ DevicesFactoryHalLocal

```c++
audioserver -> AudioPolicyService::onFirstRef() -> createAudioPolicyManager() -> AudioPolicyManagerCustom::AudioPolicyManagerCustom() -> AudioPolicyManager::initialize() -> AudioPolicyService::AudioPolicyClient::loadHwModule() -> AudioFlinger::loadHwModule() -> AudioFlinger::loadHwModule_l() -> DevicesFactoryHalHybrid::openDevice() -> DevicesFactoryHalLocal::openDevice()
```

DevicesFactoryHalHidl和DevicesFactoryHalLocal区别

> 设备不一样

+ hal层被hwinder调用关系

```


DevicesFactoryHalHidl::openDevice() -> factory->openDevice() == BpHwDevicesFactory::openDevice()
BpHwDevicesFactory::_hidl_openDevice() ->
android::hardware::BHwBinder::transact() ->
hardware::audio::V5_0::BnHwDevicesFactory::onTransact() ->
hardware::audio::V5_0::BnHwDevicesFactory::_hidl_openDevice() ->
hardware::audio::V5_0::implementation::DevicesFactory::openDevice() -> hardware::audio::V5_0::implementation::DevicesFactory::openDevice() ->
implementation::DevicesFactory::loadAudioInterface() ->
adev_open()

# 一下为hal层的hidl服务
/vendor/bin/hw/android.hardware.audio@2.0-service
此处用到hwbinder机制，以上为其具体流程。
```



## adev_open_output_stream()被上层调用流程

```c++
audioserver -> AudioPolicyService::onFirstRef() -> createAudioPolicyManager() -> AudioPolicyManagerCustom::AudioPolicyManagerCustom() -> AudioPolicyManager::initialize() -> SwAudioOutputDescriptor::open() -> AudioPolicyService::AudioPolicyClient::openOutput() -> AudioFlinger::openOutput() -> AudioFlinger::openOutput_l() -> AudioStreamOut::open() -> DeviceHalHidl::openOutputStream() -> ...hwbinder ... -> adev_open_output_stream()
```

```
DeviceHalHidl::openOutputStream() ->
(mDevice->openOutputStream()) == BpHwDevice::openOutputStream() ->
hardware::audio::V5_0::BpHwDevice::_hidl_openOutputStream() ->
hardware::BHwBinder::transact() ->
hardware::audio::V5_0::BnHwPrimaryDevice::onTransact() ->
:hardware::audio::V5_0::BnHwDevice::_hidl_openOutputStream() ->
hardware::audio::V5_0::implementation::PrimaryDevice::openOutputStream() ->
hardware::audio::V5_0::implementation::Device::openOutputStream() ->
hardware::audio::V5_0::implementation::Device::openOutputStreamImpl() ->
adev_open_output_stream()

# 一下为hal层的hidl服务
/vendor/bin/hw/android.hardware.audio@2.0-service
```



## adev_open_input_stream()被上层调用流程

```c++
audioserver -> AudioPolicyService::onFirstRef() -> createAudioPolicyManager() -> AudioPolicyManagerCustom::AudioPolicyManagerCustom() -> AudioPolicyManager::initialize() -> AudioInputDescriptor::open() -> AudioPolicyService::AudioPolicyClient::openInput() -> AudioFlinger::openInput() -> AudioFlinger::openInput_l() -> DeviceHalHidl::openInputStream() -> ...hwbinder ... -> adev_open_input_stream()
```

```
DeviceHalHidl::openInputStream() ->

BpHwDevice::openInputStream() ->
hardware::audio::V5_0::BpHwDevice::_hidl_openInputStream() ->
hardware::BHwBinder::transact() ->
hardware::audio::V5_0::BnHwPrimaryDevice::onTransact() ->
hardware::audio::V5_0::BnHwDevice::_hidl_openInputStream() ->
hardware::audio::V5_0::implementation::PrimaryDevice::openInputStream() ->
hardware::audio::V5_0::implementation::Device::openInputStream() ->
hardware::audio::V5_0::implementation::Device::openInputStreamImpl() ->
adev_open_input_stream()
```







## adev_open_output_stream()

```
PrimaryDevice::openOutputStream() -> Device::openOutputStream() -> openOutputStreamImpl() -> open_output_stream() -> adev_open_output_stream()
```

## start_input_stream()

```
## adev_open_output_stream()
start() -> out_start() -> start_input_stream()
#打开输入设备
```

```

adb push system/lib64/libaudiohal@5.0.so system/lib64/libaudiohal@5.0.so #
adb push vendor/lib64/hw/android.hardware.audio@5.0-impl.so vendor/lib64/hw/android.hardware.audio@5.0-impl.so
```



```c++
adb push system/lib64/libaudiohal@5.0.so system/lib64/ #libaudiohal
adb push system/lib64/libaudioflinger.so system/lib64/ #audioflinger
adb push system/lib64/libaudioclient.so system/lib64/ #AudioRecord.cpp
adb push system/lib64/libaudioprocessing.so system/lib64/ #AudioMixer.cpp
adb push system/lib64/libmediaplayerservice.so system/lib64/ #MediaPlayerService.cpp
adb push system/lib64/libaudiopolicymanagerdefault.so system/lib64/ #AudioPolicyManager.cpp
adb push system/lib64/libaudiopolicyservice.so system/lib64/ #AudioPolicyService.cpp
adb push vendor/lib/hw/audio.primary.sdm660.so /vendor/lib/hw/ #so
```



```
make -j6 -C /work1/Q_SDM636_M1_dev/kernel/msm-4.4 M=/home/archermind/Downloads/hello_dri O=/work1/Q_SDM636_M1_dev/out/target/product/sdm660_64/obj/kernel/msm-4.4 
HOSTCC=/work1/Q_SDM636_M1_dev/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-gcc HOSTAR=/work1/Q_SDM636_M1_dev/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ar HOSTLD=/work1/Q_SDM636_M1_dev/prebuilts/gcc/linux-x86/host/x86_64-linux-glibc2.17-4.8/bin/x86_64-linux-ld 
HOSTCFLAGS="-I/usr/include -I/usr/include/x86_64-linux-gnu -L/usr/lib -L/usr/lib/x86_64-linux-gnu" 
HOSTLDFLAGS="-L/usr/lib -L/usr/lib/x86_64-linux-gnu" 
ARCH=arm64 
CROSS_COMPILE=/work1/Q_SDM636_M1_dev/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-  
KCFLAGS=-mno-android modules 

```

