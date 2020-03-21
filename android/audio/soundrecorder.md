[toc]

# 前言

> Android系统在实现录音以及录像的功能均是通过使用MediaRecorder实现的。本篇文章主要介绍如何借助MediaRecorder实现**后台录音**功能。本章节内容主要参考android源码**packages/apps/SoundRecorder**

## audiosource的来源设置

|             来源             | 描述                                                         |
| :--------------------------: | ------------------------------------------------------------ |
|          CAMCORDER           | 录音来源于同方向的相机麦克风相同，若相机无内置相机或无法识别，则使用预设的麦克风 |
|           DEFAULT            | 默认音频源                                                   |
|             MIC              | 录音来源为主麦克风                                           |
|        REMOTE_SUBMIX         | 用于远程呈现的音频流的子混音的音频源，需要Manifest.permission.CAPTURE_AUDIO_OUTPUT权限，第三方应用无法申请 |
|         UNPROCESSED          | 与默认相同                                                   |
|          VOICE_CALL          | 记录上行与下行音频源，需要Manifest.permission.CAPTURE_AUDIO_OUTPUT权限，第三方应用无法申请 |
|     VOICE_COMMUNICATION      | 麦克风音频源针对VoIP等语音通信进行了调整,可以接收到通话的双方语音 |
| VOICE_DOWNLINK、VOICE_UPLINK | 上行下行的语音，需要Manifest.permission.CAPTURE_AUDIO_OUTPUT权限，第三方应用无法申请 |
|      VOICE_PERFORMANCE       | 捕获音频的来源意味着要实时处理并播放以进行现场演出           |
|      VOICE_RECOGNITION       | 用于获取语音进行语音识别                                     |

## 编码格式

| 音频编码 | 编码详解 |
| -------- | -------- |
| DEFAULT  |          |
| AMR_NB   |          |
| AMR_WB   |          |
| AAC      |          |
| HE_AAC   |          |
| AAC_ELD  |          |
| VORBIS   |          |
| OPUS     |          |
| EVRC     |          |
| QCELP    |          |
| LPCM     |          |
| MPEGH    |          |

## 输出格式

| 音频格式         | 音频格式详解                                                 |
| ---------------- | ------------------------------------------------------------ |
| DEFAULT          |                                                              |
| THREE_GPP        |                                                              |
| MPEG_4           |                                                              |
| AUDIO_ONLY_START | 以下为音频格式                                               |
| RAW_AMR          | 音频格式                                                     |
| AMR_NB           | 音频格式                                                     |
| AMR_WB           | 音频格式                                                     |
| AAC_ADIF         | 音频格式                                                     |
| AAC_ADTS         | 音频格式                                                     |
| AUDIO_ONLY_END   | 以下为视频格式                                               |
| RTP_AVP          |                                                              |
| MPEG2TS          | 编码方式H.264/AAC                                            |
| WEBM             | [WebM](https://baike.baidu.com/item/WebM/2455966?fr=aladdin)是Google开放免费的媒体文件格式。编码方式为VP8、Ogg Vorbis。 |
| HEIF             | 编码方式HEIC                                                 |
| OGG              |                                                              |
| QCP              |                                                              |
| WAVE             | [WAVE](https://baike.baidu.com/item/WAVE/13872619)是录音时用的标准的windows文件格式。 |

## 开始录制

```java
mRecorder = new MediaRecorder(); //
mRecorder.setAudioSource(MediaRecorder.AudioSource.MIC); //设置音频记录的音频源
mRecorder.setOutputFormat(outputfileformat); //设置记录的媒体文件的输出转换格式
mRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB); //设置音频记录的编码方式
mRecorder.setOutputFile(mSampleFile.getAbsolutePath()); //媒体文件输出路径
mRecorder.prepare(); //准备录制 _setOutputFile() _prepare()
mRecorder.start(); //开始录制
```

```c++
android_media_MediaRecorder_native_setup()
android_media_MediaRecorder_setAudioSource()
android_media_MediaRecorder_setOutputFormat()
android_media_MediaRecorder_setAudioEncoder()
android_media_MediaRecorder_setOutputFileFD()
android_media_MediaRecorder_prepare()
android_media_MediaRecorder_start()
```

### android_media_MediaRecorder_native_setup

```
mediarecorder.cpp -> IMediaPlayerService.cpp -> MediaPlayerService.cpp -> MediaRecorderClient.cpp -> StagefrightRecorder.cpp
MediaRecorder() -> createMediaRecorder() -> transact(CREATE_MEDIA_RECORDER, data, &reply); <-> IMediaPlayerService.createMediaRecorder -> MediaRecorderClient ->createStagefrightRecorder() ->StagefrightRecorder(opPackageName)
```



![图1 录音从Java层调到StagefrightRecorder的流程图](img/录音从java层调到StagefrightRecorder的流程.png)

### android_media_MediaRecorder_setAudioSource

```
android_media_MediaRecorder.cpp -> mediarecorder.cpp -> IMediaRecorder.cpp ->MediaRecorderClient.cpp -> StagefrightRecorder.cpp
setAudioSource() -> transact(SET_AUDIO_SOURCE, data, &reply) <-> onTransact() ->setAudioSource() -> setAudioSource()
```

### android_media_MediaRecorder_setOutputFormat

```c++
android_media_MediaRecorder.cpp -> MediaRecorder.cpp -> IMediaRecorder.cpp -> MediaRecorderClient.cpp -> StagefrightRecorder.cpp
    setOutputFormat() -> setOutputFormat()-> transact(SET_OUTPUT_FORMAT, data, &reply) <-> onTransact() ->setOutputFormat() -> setOutputFormat()
```

### android_media_MediaRecorder_setAudioEncoder

```c++
android_media_MediaRecorder.cpp -> MediaRecorder.cpp -> IMediaRecorder.cpp -> MediaRecorderClient.cpp -> StagefrightRecorder.cpp
android_media_MediaRecorder_setAudioEncoder() -> setAudioEncoder()-> transact(SET_AUDIO_ENCODER, data, &reply) <-> onTransact() -> setAudioEncoder() -> setAudioEncoder()
```

### android_media_MediaRecorder_setOutputFileFD

```c++
MediaRecorder.java -> android_media_MediaRecorder.cpp -> MediaRecorder.cpp -> IMediaRecorder.cpp -> MediaRecorderClient.cpp -> StagefrightRecorder.cpp
prepare()-> _setOutputFile() -> android_media_MediaRecorder_setOutputFileFD() -> setOutputFile() -> transact(SET_OUTPUT_FILE_FD, data, &reply) <-> onTransact() -> setOutputFile() -> setOutputFile()
```

### android_media_MediaRecorder_prepare

```c++
MediaRecorder.java -> android_media_MediaRecorder.cpp -> MediaRecorder.cpp -> IMediaRecorder.cpp -> MediaRecorderClient.cpp -> StagefrightRecorder.cpp
prepare() -> _prepare() -> android_media_MediaRecorder_prepare() ->prepare()-> transact(PREPARE, data, &reply) <-> onTransact() -> prepare() -> prepare() -> prepareInternal() ->
```

```
setupMPEG4orWEBMRecording() //录像录音
setupAMRRecording() //录音
setupAACRecording() //录音
setupRTPRecording() //录像录音
setupMPEG2TSRecording() //录像录音
setupOggRecording() //录音
```

## 结束录制

```java
mRecorder.stop(); //停止录制
mRecorder.release(); //释放MediaRecorder占用的资源
mRecorder=null; //指向空，避免野指针
```

```c++
android_media_MediaRecorder_stop()
android_media_MediaRecorder_release()
```



# 源码

```java
frameworks/base/media/java/android/media/MediaRecorder.java
frameworks/base/media/jni/android_media_MediaRecorder.cpp
frameworks/av/media/libmedia/mediarecorder.cpp
frameworks/av/media/libmediaplayerservice/MediaPlayerService.cpp
frameworks/av/media/libmediaplayerservice/StagefrightRecorder.cpp
MPEG4Writer.cpp
```

