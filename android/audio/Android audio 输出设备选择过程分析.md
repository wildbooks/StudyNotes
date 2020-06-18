# Android audio 输出设备选择过程分析

众(搞音频的(此处应该有个笑哭的表情)所周知的，要播放一个声音,创建AudioTrack之后，set函数设置参数的时候，会调用createTrack_l函数。

第一步:获取output

createTrack_l用binder去调用AudioFlinger的createTrack创建AudioFlinger::Track之前，首先会去调用getOutputForAttr：

```c++
status = AudioSystem::getOutputForAttr(attr, &output,
                                       mSessionId, &streamType, mClientUid,
                                       &config,mFlags, &mRoutedDeviceId, &mPortId);
```

根据传入的audio_attributes_t等参数，带回output（这是个出参）!



```c++
AudioSystem.cpp -> IAudioPolicyService.cpp              -> AudioPolicyInterfaceImpl.cpp -> AudioPolicyManager.cpp 
getOutputForAttr()-> getOutputForAttr() -> onTransact() -> getOutputForAttr() 			-> AudioPolicyManagerCustom::getOutputForAttr()

AudioPolicyManager.cpp				   -> AudioPolicyManager.cpp
AudioPolicyManager::getOutputForAttr() -> getOutputForAttrInt()
```

# getOutputForAttrInt()

```c++
status_t AudioPolicyManager::getOutputForAttrInt(
        audio_attributes_t *resultAttr,
        audio_io_handle_t *output,
        audio_session_t session,
        const audio_attributes_t *attr,
        audio_stream_type_t *stream,
        uid_t uid,
        const audio_config_t *config,
        audio_output_flags_t *flags,
        audio_port_handle_t *selectedDeviceId,
        bool *isRequestedDeviceForExclusiveUse,
        std::vector<sp<SwAudioOutputDescriptor>> *secondaryDescs)
{
    DeviceVector outputDevices;
    const audio_port_handle_t requestedPortId = *selectedDeviceId;
    DeviceVector msdDevices = getMsdAudioOutDevices();
    const sp<DeviceDescriptor> requestedDevice =
        mAvailableOutputDevices.getDeviceFromId(requestedPortId);

    status_t status = getAudioAttributes(resultAttr, attr, *stream);
    if (status != NO_ERROR) {
        return status;
    }
    if (auto it = mAllowedCapturePolicies.find(uid); it != end(mAllowedCapturePolicies)) {
        resultAttr->flags |= it->second;
    }
    
    //重点EngineBase::getStreamTypeForAttributes() -> ProductStrategy::getStreamTypeForAttributes()
    //获取类型audio_stream_type_t
    *stream = mEngine->getStreamTypeForAttributes(*resultAttr);

    ALOGV("%s() attributes=%s stream=%s session %d selectedDeviceId %d", __func__,
          toString(*resultAttr).c_str(), toString(*stream).c_str(), session, requestedPortId);

    // The primary output is the explicit routing (eg. setPreferredDevice) if specified,
    //       otherwise, fallback to the dynamic policies, if none match, query the engine.
    // Secondary outputs are always found by dynamic policies as the engine do not support them
    sp<SwAudioOutputDescriptor> policyDesc;
    //AudioPolicyMix.cpp
    status = mPolicyMixes.getOutputForAttr(*resultAttr, uid, *flags, policyDesc, secondaryDescs);
    if (status != OK) {
        return status;
    }

    // Explicit routing is higher priority then any dynamic policy primary output
    bool usePrimaryOutputFromPolicyMixes = requestedDevice == nullptr && policyDesc != nullptr;

    // FIXME: in case of RENDER policy, the output capabilities should be checked
    if ((usePrimaryOutputFromPolicyMixes || !secondaryDescs->empty())
        && !audio_is_linear_pcm(config->format)) {
        ALOGD("%s: rejecting request as dynamic audio policy only support pcm", __func__);
        return BAD_VALUE;
    }
    if (usePrimaryOutputFromPolicyMixes) {
        *output = policyDesc->mIoHandle;
        sp<AudioPolicyMix> mix = policyDesc->mPolicyMix.promote();
        sp<DeviceDescriptor> deviceDesc =
                mAvailableOutputDevices.getDevice(mix->mDeviceType,
                                                  mix->mDeviceAddress,
                                                  AUDIO_FORMAT_DEFAULT);
        *selectedDeviceId = deviceDesc != 0 ? deviceDesc->getId() : AUDIO_PORT_HANDLE_NONE;
        ALOGV("getOutputForAttr() returns output %d", *output);
        return NO_ERROR;
    }
    // Virtual sources must always be dynamicaly or explicitly routed
    if (resultAttr->usage == AUDIO_USAGE_VIRTUAL_SOURCE) {
        ALOGW("getOutputForAttr() no policy mix found for usage AUDIO_USAGE_VIRTUAL_SOURCE");
        return BAD_VALUE;
    }
    // explicit routing managed by getDeviceForStrategy in APM is now handled by engine
    // in order to let the choice of the order to future vendor engine
    outputDevices = mEngine->getOutputDevicesForAttributes(*resultAttr, requestedDevice, false);

    if ((resultAttr->flags & AUDIO_FLAG_HW_AV_SYNC) != 0) {
        *flags = (audio_output_flags_t)(*flags | AUDIO_OUTPUT_FLAG_HW_AV_SYNC);
    }

    // Set incall music only if device was explicitly set, and fallback to the device which is
    // chosen by the engine if not.
    // FIXME: provide a more generic approach which is not device specific and move this back
    // to getOutputForDevice.
    // TODO: Remove check of AUDIO_STREAM_MUSIC once migration is completed on the app side.
    if (outputDevices.types() == AUDIO_DEVICE_OUT_TELEPHONY_TX &&
        (*stream == AUDIO_STREAM_MUSIC  || resultAttr->usage == AUDIO_USAGE_VOICE_COMMUNICATION) &&
        audio_is_linear_pcm(config->format) &&
        isInCall()) {
        if (requestedPortId != AUDIO_PORT_HANDLE_NONE) {
            *flags = (audio_output_flags_t)AUDIO_OUTPUT_FLAG_INCALL_MUSIC;
            *isRequestedDeviceForExclusiveUse = true;
        }
    }

    ALOGV("%s() device %s, sampling rate %d, format %#x, channel mask %#x, flags %#x stream %s",
          __func__, outputDevices.toString().c_str(), config->sample_rate, config->format,
          config->channel_mask, *flags, toString(*stream).c_str());

    *output = AUDIO_IO_HANDLE_NONE;
    if (!msdDevices.isEmpty()) {
        *output = getOutputForDevices(msdDevices, session, *stream, config, flags);
        sp<DeviceDescriptor> device = outputDevices.isEmpty() ? nullptr : outputDevices.itemAt(0);
        if (*output != AUDIO_IO_HANDLE_NONE && setMsdPatch(device) == NO_ERROR) {
            ALOGV("%s() Using MSD devices %s instead of devices %s",
                  __func__, msdDevices.toString().c_str(), outputDevices.toString().c_str());
            outputDevices = msdDevices;
        } else {
            *output = AUDIO_IO_HANDLE_NONE;
        }
    }
    if (*output == AUDIO_IO_HANDLE_NONE) {
        *output = getOutputForDevices(outputDevices, session, *stream, config,
                flags, resultAttr->flags & AUDIO_FLAG_MUTE_HAPTIC);
    }
    if (*output == AUDIO_IO_HANDLE_NONE) {
        return INVALID_OPERATION;
    }

    *selectedDeviceId = getFirstDeviceId(outputDevices);

    ALOGV("%s returns output %d selectedDeviceId %d", __func__, *output, *selectedDeviceId);

    return NO_ERROR;
}
```

# 设备选择

getDeviceForStrategyInt()

getDevicesForProductStrategy() -> getDeviceForStrategyInt()

getDeviceForInputSource()





# 疑惑

```c
有两个createAudioPolicyManager() 调用哪个？
```

