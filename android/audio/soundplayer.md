[toc]

# 前言

> Android系统在实现播放音乐以及播放视频功能均是通过使用MediaPlayer实现的。本篇文章主要介绍如何借助MediaPlayer实现**后台播放音乐**功能。本章节内容主要参考android源码**packages/apps/SoundRecorder**

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

- ACC、ACC-ELD、AMR_NB、AMR_WB、DEFAULT、HE_AAC、OPUS、VORBIS

## 输出格式

- AAC_ADTS、AMR_NB、AMR_WB、DEFAULT、MPEG_2_TS、MPEG_4、OGG、THREE_GPP、WEBM

## 开始播放

```java
mPlayer = new MediaPlayer(); //创建对象
mPlayer.setDataSource(mSampleFile.getAbsolutePath()); //////媒体文件路径
mPlayer.setOnCompletionListener(this);
mPlayer.setOnErrorListener(this);
mPlayer.prepare(); //准备播放
mPlayer.start(); //开始播放
```

## 结束播放

```java
mPlayer.stop(); //停止播放
mPlayer.release(); //释放MediaPlayer占用的资源
mPlayer=null; //指向空，避免野指针
```

