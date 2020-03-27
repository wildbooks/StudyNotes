[toc]

# 前言

Android系统在实现录音以及录像的功能均是通过使用MediaRecorder实现的。本篇文章主要介绍如何借助AudioRecord实现**后台录音**功能。本章节内容主要参考android源码**vendor/qcom/proprietary/commonsys/fastmmi/qmmi/src/com/qualcomm/qti/qmmi/testcase/Audio/LoopbackRunnable.java)**

# 关键api

```c++
//获取最小buffer
public int getMinBufferSize(int sampleRateInHz, int channelConfig, int audioFormat)
//创建AudioRecord对象
public AudioRecord(int audioSource, int sampleRateInHz, int channelConfig, int audioFormat,
                   int bufferSizeInBytes)
//开始录音
public void startRecording()
```

# app

```c++
  public class LoopbackRunnable extends BaseRunnable {
  
      final static int SAMPLE_RATE = 8000;//采样率
      private AudioRecord audioRecord = null;
      private AudioTrack audioTrack = null;
  
      public void run() {
  
          LogUtils.logi("LoopBack started");
          setRunning(true);
  
          int bufferSize = AudioRecord
                  .getMinBufferSize(SAMPLE_RATE, AudioFormat.CHANNEL_IN_MONO,
                          AudioFormat.ENCODING_PCM_16BIT);//返回成功创建 audio 记录对象所需的最小缓冲区大小 (以字节为单位)。
          bufferSize = Math.max(bufferSize, AudioTrack.getMinBufferSize(
                  SAMPLE_RATE, AudioFormat.CHANNEL_IN_MONO,
                  AudioFormat.ENCODING_PCM_16BIT));
  
          if (audioRecord == null) {
              audioRecord = new AudioRecord(
                      MediaRecorder.AudioSource.MIC, SAMPLE_RATE,
                      AudioFormat.CHANNEL_IN_MONO,
                      AudioFormat.ENCODING_PCM_16BIT, bufferSize);//创建AudioRecord对象
          }
          if (audioTrack == null) {
              audioTrack = new AudioTrack(
                      AudioManager.STREAM_VOICE_CALL, SAMPLE_RATE,
                      AudioFormat.CHANNEL_OUT_MONO,
                      AudioFormat.ENCODING_PCM_16BIT, bufferSize,
                      AudioTrack.MODE_STREAM);
          }////创建AudioTrack对象
  
          audioTrack.setPlaybackRate(SAMPLE_RATE);//设置采样率
  
          audioRecord.startRecording();//开始录音
          audioTrack.play();//开始播放
  
          byte[] buffer = new byte[bufferSize];
          while (getRunning()) {
              int readSize = audioRecord.read(buffer, 0, bufferSize);//读区录音数据
              if (readSize > 0)
                  audioTrack.write(buffer, 0, readSize);//写入播放数据
          }
  
          audioRecord.stop();//停止录音
          audioRecord.release();//释放录音资源
          audioRecord = null;//避免野指针
  
          audioTrack.stop();
          audioTrack.release();
          audioTrack = null;
      }
  
  }
```

## getMinBufferSize

```c++
AudioRecord.java -> android_media_AudioRecord.cpp -> AudioRecord.cpp -> AudioSystem.cpp	->
-> AudioSystem.cpp -> IAudioFlinger.cpp -> AudioFlinger.cpp
native_get_min_buff_size() -> android_media_AudioRecord_get_min_buff_size() -> getMinFrameCount() -> getInputBufferSize() -> AudioFlingerClient::getInputBufferSize() -> transact(GET_INPUTBUFFERSIZE, data, &reply) <-> onTransact() -> getInputBufferSize()
```

```c++
mPrimaryHardwareDev = playbackThread->getOutput()->audioHwDev;
```

```c++
//frameworks/av/services/audioflinger/AudioFlinger.cpp
size_t AudioFlinger::getInputBufferSize(uint32_t sampleRate, audio_format_t format,
        audio_channel_mask_t channelMask) const
{
    status_t ret = initCheck();
    if (ret != NO_ERROR) {
        return 0;
    }
    if ((sampleRate == 0) ||
            !audio_is_valid_format(format) || !audio_has_proportional_frames(format) ||
            !audio_is_input_channel(channelMask)) {
        return 0;
    }

    AutoMutex lock(mHardwareLock);
    mHardwareStatus = AUDIO_HW_GET_INPUT_BUFFER_SIZE;
    audio_config_t config, proposed;
    memset(&proposed, 0, sizeof(proposed));
    proposed.sample_rate = sampleRate;
    proposed.channel_mask = channelMask;
    proposed.format = format;

    //重点 mPrimaryHardwareDev = playbackThread->getOutput()->audioHwDev;
    //AudioFlinger::PlaybackThread::getOutput
    //本文以primary设备为例子；frameworks/av/media/libaudiohal/impl/DeviceHalHidl.cpp
    //
    sp<DeviceHalInterface> dev = mPrimaryHardwareDev->hwDevice();
    size_t frames;
    for (;;) {
        // Note: config is currently a const parameter for get_input_buffer_size()
        // but we use a copy from proposed in case config changes from the call.
        config = proposed;
        //对应vendor/qcom/opensource/audio-hal/primary-hal/hal/audio_hw.c -> getInputBufferSize()
        status_t result = dev->getInputBufferSize(&config, &frames);
        if (result == OK && frames != 0) {
            break; // hal success, config is the result
        }
        // change one parameter of the configuration each iteration to a more "common" value
        // to see if the device will support it.
        if (proposed.format != AUDIO_FORMAT_PCM_16_BIT) {
            proposed.format = AUDIO_FORMAT_PCM_16_BIT;
        } else if (proposed.sample_rate != 44100) { // 44.1 is claimed as must in CDD as well as
            proposed.sample_rate = 44100;           // legacy AudioRecord.java. TODO: Query hw?
        } else {
            ALOGW("getInputBufferSize failed with minimum buffer size sampleRate %u, "
                    "format %#x, channelMask 0x%X",
                    sampleRate, format, channelMask);
            break; // retries failed, break out of loop with frames == 0.
        }
    }
    mHardwareStatus = AUDIO_HW_IDLE;
    if (frames > 0 && config.sample_rate != sampleRate) {
        frames = destinationFramesPossible(frames, sampleRate, config.sample_rate);
    }
    return frames; // may be converted to bytes at the Java level.
}
```

## AudioRecord

```c++
AudioRecord.java -> android_media_AudioRecord.cpp -> AudioRecord.cpp
AudioRecord() -> android_media_AudioRecord_setup() -> AudioRecord() -> set()
    service/AudioPolicyClientImpl.cpp:status_t AudioPolicyService::AudioPolicyClient::openInput(audio_module_handle_t module,

```

>  openInput_l

```c++
sp<AudioFlinger::ThreadBase> AudioFlinger::openInput_l(audio_module_handle_t module,
                                                         audio_io_handle_t *input,
                                                         audio_config_t *config,
                                                         audio_devices_t devices,
                                                         const String8& address,
                                                         audio_source_t source,
                                                         audio_input_flags_t flags,
                                                         audio_devices_t outputDevice,
                                                         const String8& outputDeviceAddress)
{
    //**重点**: 通过hidl接口获取hal层接口
    //loadHwModule_l() - > mDevicesFactoryHal->openDevice
    //具体实现请看以下路径代码
    //frameworks/av/media/libaudiohal/impl/ #hidl 入口DevicesFactoryHalHybrid()
	//hardware/interfaces/audio/core/all-versions/default/ #hidl
    AudioHwDevice *inHwDev = findSuitableHwDev_l(module, devices);
    if (inHwDev == NULL) {
        *input = AUDIO_IO_HANDLE_NONE;
        return 0;
    }

    // Some flags are specific to framework and must not leak to the HAL.
    flags = static_cast<audio_input_flags_t>(flags & ~AUDIO_INPUT_FRAMEWORK_FLAGS);

    // Audio Policy can request a specific handle for hardware hotword.
    // The goal here is not to re-open an already opened input.
    // It is to use a pre-assigned I/O handle.
    if (*input == AUDIO_IO_HANDLE_NONE) {
        *input = nextUniqueId(AUDIO_UNIQUE_ID_USE_INPUT);
    } else if (audio_unique_id_get_use(*input) != AUDIO_UNIQUE_ID_USE_INPUT) {
        ALOGE("openInput_l() requested input handle %d is invalid", *input);
        return 0;
    } else if (mRecordThreads.indexOfKey(*input) >= 0) {
        // This should not happen in a transient state with current design.
        ALOGE("openInput_l() requested input handle %d is already assigned", *input);
        return 0;
    }

    audio_config_t halconfig = *config;
    sp<DeviceHalInterface> inHwHal = inHwDev->hwDevice();
    sp<StreamInHalInterface> inStream;
    // 用到hidl通信方式: openInputStream()->openInputStream() -> openInputStream() -> open_input_stream() ->hal(open_input_stream)
    //frameworks/av/media/libaudiohal/impl/  hidl客户端
    //hardware/interfaces/audio/ hidl服务端 
    //vendor/qcom/opensource/audio-hal/primary-hal/hal 最后调到hal层的open_input_stream()
    status_t status = inHwHal->openInputStream(
            *input, devices, &halconfig, flags, address.string(), source,
            outputDevice, outputDeviceAddress, &inStream);
    ALOGV("openInput_l() openInputStream returned input %p, devices %#x, SamplingRate %d"
           ", Format %#x, Channels %#x, flags %#x, status %d addr %s",
            inStream.get(),
            devices,
            halconfig.sample_rate,
            halconfig.format,
            halconfig.channel_mask,
            flags,
            status, address.string());

    // If the input could not be opened with the requested parameters and we can handle the
    // conversion internally, try to open again with the proposed parameters.
    if (status == BAD_VALUE &&
        audio_is_linear_pcm(config->format) &&
        audio_is_linear_pcm(halconfig.format) &&
        (halconfig.sample_rate <= AUDIO_RESAMPLER_DOWN_RATIO_MAX * config->sample_rate) &&
        (audio_channel_count_from_in_mask(halconfig.channel_mask) <= FCC_8) &&
        (audio_channel_count_from_in_mask(config->channel_mask) <= FCC_8)) {
        // FIXME describe the change proposed by HAL (save old values so we can log them here)
        ALOGV("openInput_l() reopening with proposed sampling rate and channel mask");
        inStream.clear();
        status = inHwHal->openInputStream(
                *input, devices, &halconfig, flags, address.string(), source,
                outputDevice, outputDeviceAddress, &inStream);
        // FIXME log this new status; HAL should not propose any further changes
    }

    if (status == NO_ERROR && inStream != 0) {
        AudioStreamIn *inputStream = new AudioStreamIn(inHwDev, inStream, flags);
        //内存映射的方式打开硬件设备并创建内存映射线程
        if ((flags & AUDIO_INPUT_FLAG_MMAP_NOIRQ) != 0) {
            sp<MmapCaptureThread> thread =
                    new MmapCaptureThread(this, *input,
                                          inHwDev, inputStream,
                                          primaryOutputDevice_l(), devices, mSystemReady);
            mMmapThreads.add(*input, thread);
            ALOGV("openInput_l() created mmap capture thread: ID %d thread %p", *input,
                    thread.get());
            return thread;
        } else {
            // Start record thread
            // RecordThread requires both input and output device indication to forward to audio
            // pre processing modules
            //创建Record线层
            sp<RecordThread> thread = new RecordThread(this,
                                      inputStream,
                                      *input,
                                      primaryOutputDevice_l(),
                                      devices,
                                      mSystemReady
                                      );
            mRecordThreads.add(*input, thread);
            ALOGV("openInput_l() created record thread: ID %d thread %p", *input, thread.get());
            return thread;
        }
    }

    *input = AUDIO_IO_HANDLE_NONE;
    return 0;
}
```

## startRecording

```c++
AudioRecord.java -> android_media_AudioRecord.cpp -> AudioRecord.cpp
startRecording() -> android_media_AudioRecord_start()->start()
```

> start

```c++
status_t AudioRecord::start(AudioSystem::sync_event_t event, audio_session_t triggerSession)
{
    ALOGV("%s(%d): sync event %d trigger session %d", __func__, mPortId, event, triggerSession);
    SEEMPLOG_RECORD(71,"");

    AutoMutex lock(mLock);
    if (mActive) {
        return NO_ERROR;
    }

    // discard data in buffer
    const uint32_t framesFlushed = mProxy->flush();
    mFramesReadServerOffset -= mFramesRead + framesFlushed;
    mFramesRead = 0;
    mProxy->clearTimestamp();  // timestamp is invalid until next server push

    // reset current position as seen by client to 0
    mProxy->setEpoch(mProxy->getEpoch() - mProxy->getPosition());
    // force refresh of remaining frames by processAudioBuffer() as last
    // read before stop could be partial.
    mRefreshRemaining = true;

    mNewPosition = mProxy->getPosition() + mUpdatePeriod;
    int32_t flags = android_atomic_acquire_load(&mCblk->mFlags);

    // we reactivate markers (mMarkerPosition != 0) as the position is reset to 0.
    // This is legacy behavior.  This is not done in stop() to avoid a race condition
    // where the last marker event is issued twice.
    mMarkerReached = false;
    // mActive is checked by restoreRecord_l
    mActive = true;

    status_t status = NO_ERROR;
    if (!(flags & CBLK_INVALID)) {
        //此处是重点，用到了hidl接口方法。原形在该文件
        //frameworks/av/media/libaudioclient/aidl/android/media/IAudioRecord.aidl
        //该文件在编译的时候会生成IAudioRecord.cpp和IAudioRecord.h。该代码实现客户端BpAudioRecord。原形服务端为BnAudioRecord 。然后 RecordHandle是继承BnAudioRecord类。所以原形在
        status = mAudioRecord->start(event, triggerSession).transactionError();
        if (status == DEAD_OBJECT) {
            flags |= CBLK_INVALID;
        }
    }
    if (flags & CBLK_INVALID) {
        status = restoreRecord_l("start");
    }

    // Call these directly because we are already holding the lock.
    mAudioRecord->setPreferredMicrophoneDirection(mSelectedMicDirection);
    mAudioRecord->setPreferredMicrophoneFieldDimension(mSelectedMicFieldDimension);

    if (status != NO_ERROR) {
        mActive = false;
        ALOGE("%s(%d): status %d", __func__, mPortId, status);
        mMediaMetrics.markError(status, __FUNCTION__);
    } else {
        mTracker->recordingStarted();
        sp<AudioRecordThread> t = mAudioRecordThread;
        if (t != 0) {
            t->resume();
        } else {
            mPreviousPriority = getpriority(PRIO_PROCESS, 0);
            get_sched_policy(0, &mPreviousSchedulingGroup);
            androidSetThreadPriority(0, ANDROID_PRIORITY_AUDIO);
        }

        // we've successfully started, log that time
        mMediaMetrics.logStart(systemTime());
    }
    return status;
}
```

## read

```c++
AudioRecord.java -> android_media_AudioRecord.cpp -> AudioRecord.cpp
read() -> android_media_AudioRecord_readInArray() -> read()
```



## 补充内容

```
#define AUDIO_HARDWARE_MODULE_ID_PRIMARY "primary" //主设备，即手机上的听筒、mic和外放
#define AUDIO_HARDWARE_MODULE_ID_A2DP "a2dp" //蓝牙设备
#define AUDIO_HARDWARE_MODULE_ID_USB "usb" //usb设备
#define AUDIO_HARDWARE_MODULE_ID_REMOTE_SUBMIX "r_submix" //虚拟设备，用于录制系统内置的声音
#define AUDIO_HARDWARE_MODULE_ID_CODEC_OFFLOAD "codec_offload"
#define AUDIO_HARDWARE_MODULE_ID_STUB "stub"
#define AUDIO_HARDWARE_MODULE_ID_HEARING_AID "hearing_aid" //助听器设备
#define AUDIO_HARDWARE_MODULE_ID_MSD "msd"//

```



## 代码路径

```
frameworks/base/media/java/android/media/AudioRecord.java
frameworks/base/core/jni/android_media_AudioRecord.cpp
frameworks/av/media/libaudioclient/AudioRecord.cpp
frameworks/av/media/libaudioclient/AudioSystem.cpp
frameworks/av/media/libaudioclient/IAudioFlinger.cpp
frameworks/av/services/audioflinger/AudioFlinger.cpp
frameworks/av/media/libaudioclient/IAudioPolicyService.cpp
frameworks/av/services/audiopolicy/service/AudioPolicyInterfaceImpl.cpp
system/media/audio/include/system/audio.h
frameworks/av/media/libaudiohal/impl/ #hidl 入口DevicesFactoryHalHybrid()
hardware/interfaces/audio/core/all-versions/default/ #hidl
frameworks/av/media/libaudioclient/aidl/android/media/IAudioRecord.aidl

```

# 知识点

- framework和hal层通过hidl通信 (/dev/hwbinder)
- java和native通过jni通信
- 进程间通过binder通信 (/dev/binder)
- aldl通信通话(/devvndbinder)