[toc]

> 安卓中播放视频一般有两个接口，一个是mediaplayer，一个是mediacodec，其中mediaplayer是对mediacodec / genericsource / render 的封装，对APP而言使用比较方便。相比而言mediacodec留给用户发挥的空间更多，APP可以自己实现很多功能。目前只有MXplayer使用的是mediaplayer接口，其他APP一般都是使用的mediacodec接口。本文接下来就会讲解mediacodec的具体实现过程。

![MediaCodec框架](img/MEdiaCodec.png)

# API

```java
createDecoderByType() //通过解码类型创建解码器，MediaCodec()。类编码类型在MediaFormat类中定义。
createEncoderByType() //更加编码类型创建编码器，MediaCodec().
createByCodecName() //根据实例化的组件创建编解码器。
configure() //配置编解码器
start()  //启动编解码器
dequeueInputBuffer() //从输入流队列中取数据进行编码操作
getInputBuffers() //获取需要编码数据的输入流队列，返回的是一个ByteBuffer数组
queueInputBuffer() //输入流入队列

dequeueOutputBuffer() //从输出队列中取出编码操作之后的数据
getOutputBuffers() //获取编解码之后的数据输出流队列，返回的是一个ByteBuffer数组
releaseOutputBuffer() //处理完成，释放ByteBuffer数据 
```

# 基本使用

> 所有的同步模式的 MediaCodec API都遵循一个模式：
>
> 创建并配置一个 MediaCodec 对象 
>  循环直到完成: 
>  如果输入缓冲区就绪，读取一个输入块，并复制到输入缓冲区中 
>  如果输出缓冲区就绪，复制输出缓冲区的数据 
>  释放 MediaCodec 对象

```java
//cts/tests/tests/media/src/android/media/cts/MediaCodecTest.java
private void testAsyncReset(boolean audio, boolean swap, final boolean testStop)
        throws Exception, InterruptedException {
    String mimeTypePrefix  = audio ? "audio/" : "video/";
    final MediaExtractor mediaExtractor = getMediaExtractorForMimeType(
            INPUT_RESOURCE_ID, mimeTypePrefix);
    MediaFormat mediaFormat = mediaExtractor.getTrackFormat(
            mediaExtractor.getSampleTrackIndex());
    if (!MediaUtils.checkDecoderForFormat(mediaFormat)) {
        return; // skip
    }
    
    //设置视频输出
    OutputSurface outputSurface = audio ? null : new OutputSurface(1, 1);
    final Surface surface = outputSurface == null ? null : outputSurface.getSurface();

    String mimeType = mediaFormat.getString(MediaFormat.KEY_MIME);
    //1、创建解码器，根据视频/音频编码类型，创建解码器
    final MediaCodec mediaCodec = MediaCodec.createDecoderByType(mimeType);

    try {
        //2、配置编码器
        mediaCodec.configure(mediaFormat, surface, null /* crypto */, 0 /* flags */);
        //3、启动编码器
        mediaCodec.start();

        //4、数据交互。请看runDecodeTillFirstOutput()函数实现
        assertTrue(runDecodeTillFirstOutput(mediaCodec, mediaExtractor));

        Thread flushingThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    if (testStop) {
                        mediaCodec.stop();
                    } else {
                        mediaCodec.flush();
                    }
                } catch (IllegalStateException e) {
                    // This is okay, since we're simulating a race between flush and reset.
                    // If reset executed first, flush could fail.
                }
            }
        });

        Thread resettingThread = new Thread(new Runnable() {
            @Override
            public void run() {
                mediaCodec.reset();
            }
        });

        // start flushing (or stopping) and resetting in two threads
        if (swap) {
            flushingThread.start();
            resettingThread.start();
        } else {
            resettingThread.start();
            flushingThread.start();
        }

        // wait for at most 5 sec, and check if the thread exits properly
        flushingThread.join(5000);
        assertFalse(flushingThread.isAlive());

        resettingThread.join(5000);
        assertFalse(resettingThread.isAlive());
    } finally {
        if (mediaCodec != null) {
            mediaCodec.release();
        }
        if (mediaExtractor != null) {
            mediaExtractor.release();
        }
        if (outputSurface != null) {
            outputSurface.release();
        }
    }
}
  
private static boolean runDecodeTillFirstOutput(
        MediaCodec mediaCodec, MediaExtractor mediaExtractor) {
    final int TIME_OUT_US = 10000;

    assertTrue("Wrong test stream which has no data.",
            mediaExtractor.getSampleTrackIndex() != -1);
    boolean signaledEos = false;
    MediaCodec.BufferInfo outputBufferInfo = new MediaCodec.BufferInfo();
    while (!Thread.interrupted()) {
        // Try to feed more data into the codec.
        if (!signaledEos) {
            //1、请求一个输入缓存的bufferIndex
            int bufferIndex = mediaCodec.dequeueInputBuffer(TIME_OUT_US /* timeoutUs */);
            if (bufferIndex != -1) {
                //2、根据bufferIndex得到buffer
                ByteBuffer buffer = mediaCodec.getInputBuffer(bufferIndex);
                //3、给buffer中写入数据
                int size = mediaExtractor.readSampleData(buffer, 0 /* offset */);
                long timestampUs = mediaExtractor.getSampleTime();
                mediaExtractor.advance();
                signaledEos = mediaExtractor.getSampleTrackIndex() == -1;
                //4、buffer入队
                mediaCodec.queueInputBuffer(bufferIndex,
                        0 /* offset */,
                        size,
                        timestampUs,
                        signaledEos ? MediaCodec.BUFFER_FLAG_END_OF_STREAM : 0);
                Log.i("DEBUG", "queue with " + signaledEos);
            }
        }

        //请求一个输出缓存的队列outputBufferIndex
        int outputBufferIndex = mediaCodec.dequeueOutputBuffer(
                outputBufferInfo, TIME_OUT_US /* timeoutUs */);

        if (outputBufferIndex == MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED
                || outputBufferIndex == MediaCodec.INFO_OUTPUT_FORMAT_CHANGED
                || outputBufferIndex == MediaCodec.INFO_TRY_AGAIN_LATER) {
            continue;
        }
        assertTrue("Wrong output buffer index", outputBufferIndex >= 0);

        PersistableBundle metrics = mediaCodec.getMetrics();
        Log.d(TAG, "getMetrics after first buffer metrics says: " + metrics);

        int encoder = metrics.getInt(MediaCodec.MetricsConstants.ENCODER, -1);
        if (encoder != 0) {
            fail("getMetrics() returns bad encoder value " + encoder);
        }
        String theCodec = metrics.getString(MediaCodec.MetricsConstants.CODEC, null);
        if (theCodec == null) {
            fail("getMetrics() returns null codec value ");
        }

        mediaCodec.releaseOutputBuffer(outputBufferIndex, false /* render */);
        boolean eos = (outputBufferInfo.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0;
        Log.i("DEBUG", "Got a frame with eos=" + eos);
        if (eos && outputBufferInfo.size == 0) {
            return false;
        } else {
            return true;
        }
    }

    return false;
}
```



1. 创建编/解码器、配置、启动编/解码器

   > MediaCodec主要提供了createEncoderByType(String  type)、createDecoderByType(String  type)两个方法来创建编/解码器，它们均需要传入一个MIME类型多媒体格式。常见的MIME类型多媒体格式如下

   ```java
   mediaCodec = MediaCodec.createDecoderByType(mime);　 //1.1、创建解码器，根据视频/音频编码类型，创建解码器
   mediaCodec.configure();  //1.2、配置编码器
   mediaCodec.start(); //1.1 启动编解码器
   ```

2. 编解码数据处理

   ```java
   //2.1 从编解码读数据
   MediaCodec.BufferInfo outputBufferInfo = new MediaCodec.BufferInfo();
   int outputBufferIndex = mediaCodec.dequeueOutputBuffer(outputBufferInfo, TIMEOUT_USEC);
   outputBuffers = mediaCodec.getOutputBuffers();
   configData.put(outputBuffers[outputBufferIndex]);
   mediaCodec.releaseOutputBuffer(outputBufferIndex, false /* render */);
   
   //2.2向编解码写数据
   // step1 请求一个输入缓存的bufferIndex
   int bufferIndex = mediaCodec.dequeueInputBuffer(TIME_OUT_US /* timeoutUs */);
   // step2 根据bufferIndex得到buffer
   ByteBuffer buffer = mediaCodec.getInputBuffer(bufferIndex);
   // step3 给buffer中写入数据
   int size = mediaExtractor.readSampleData(buffer, 0 /* offset */);
   // step4 buffer入队
   mediaCodec.queueInputBuffer(bufferIndex,0 /* offset */,size,
       timestampUs,
       signaledEos ? MediaCodec.BUFFER_FLAG_END_OF_STREAM : 0);
   
   ```

3. 结束编解码

   ```java
   mediaCodec.stop(); // stop
   mediaCodec.release(); // release
   ```

# api源码实现

## createDecoderByType

```java
createDecoderByType() -> MediaCodec() -> android_media_MediaCodec_native_setup()->CreateByType()
```

```c++
sp<MediaCodec> MediaCodec::CreateByType(
        const sp<ALooper> &looper, const AString &mime, bool encoder, status_t *err, pid_t pid,
        uid_t uid) {
    Vector<AString> matchingCodecs;

    //遍历成功匹配的所有编解码
    MediaCodecList::findMatchingCodecs(
            mime.c_str(),
            encoder,
            0,
            &matchingCodecs);

    if (err != NULL) {
        *err = NAME_NOT_FOUND;
    }
    
    //遍历注册编解码，直到成功为止。
    for (size_t i = 0; i < matchingCodecs.size(); ++i) {
        sp<MediaCodec> codec = new MediaCodec(looper, pid, uid);
        AString componentName = matchingCodecs[i];
        status_t ret = codec->init(componentName, true);
        if (err != NULL) {
            *err = ret;
        }
        if (ret == OK) {
            return codec;
        }
        ALOGD("Allocating component '%s' failed (%d), try next one.",
                componentName.c_str(), ret);
    }
    return NULL;
}
```

```c++
status_t MediaCodec::init(const AString &name, bool nameIsType) {
    mResourceManagerService->init();

    // save init parameters for reset
    mInitName = name;

    // Current video decoders do not return from OMX_FillThisBuffer
    // quickly, violating the OpenMAX specs, until that is remedied
    // we need to invest in an extra looper to free the main event
    // queue.

    mCodecInfo.clear();

    bool secureCodec = false;
    AString tmp = name;
    if (tmp.endsWith(".secure")) {
        secureCodec = true;
        tmp.erase(tmp.size() - 7, 7);
    }

    //make sure if the component name contains qcom/qti, we don't return error
    //as these components are not present in media_codecs.xml and MediaCodecList won't find
    //these component by findCodecByName
    //Video and Flac decoder are present in list so exclude them.
    if ((!(name.find("qcom", 0) > 0 || name.find("qti", 0) > 0 || name.find("filter", 0) > 0)
          || name.find("video", 0) > 0 || name.find("flac", 0) > 0 || name.find("c2.qti", 0) >= 0)
          && !(name.find("tme",0) > 0)) {
        const sp<IMediaCodecList> mcl = MediaCodecList::getInstance();
        if (mcl == NULL) {
            mCodec = NULL;  // remove the codec.
            return NO_INIT; // if called from Java should raise IOException
        }
        for (const AString &codecName : { name, tmp }) {
            ssize_t codecIdx = mcl->findCodecByName(codecName.c_str());
            if (codecIdx < 0) {
                continue;
            }
            mCodecInfo = mcl->getCodecInfo(codecIdx);
            Vector<AString> mediaTypes;
            mCodecInfo->getSupportedMediaTypes(&mediaTypes);
            for (size_t i = 0; i < mediaTypes.size(); i++) {
                if (mediaTypes[i].startsWith("video/")) {
                    mIsVideo = true;
                    break;
                }
            }
            break;
        }
        if (mCodecInfo == nullptr) {
            ALOGE("component not found");
            return NAME_NOT_FOUND;
        }
    }
    const char *owner = "default";
    if (mCodecInfo !=NULL)
        owner = mCodecInfo->getOwnerName();

    mCodec = GetCodecBase(name, owner);
    if (mCodec == NULL) {
        return NAME_NOT_FOUND;
    }
    if (mIsVideo) {
        // video codec needs dedicated looper
        if (mCodecLooper == NULL) {
            mCodecLooper = new ALooper;
            mCodecLooper->setName("CodecLooper");
            mCodecLooper->start(false, false, ANDROID_PRIORITY_AUDIO);
        }

        mCodecLooper->registerHandler(mCodec);
    } else {
        mLooper->registerHandler(mCodec);
    }

    mLooper->registerHandler(this);

    mCodec->setCallback(
            std::unique_ptr<CodecBase::CodecCallback>(
                    new CodecCallback(new AMessage(kWhatCodecNotify, this))));
    mBufferChannel = mCodec->getBufferChannel();
    mBufferChannel->setCallback(
            std::unique_ptr<CodecBase::BufferCallback>(
                    new BufferCallback(new AMessage(kWhatCodecNotify, this))));

    sp<AMessage> msg = new AMessage(kWhatInit, this);
    msg->setObject("codecInfo", mCodecInfo);
    // name may be different from mCodecInfo->getCodecName() if we stripped
    // ".secure"
    msg->setString("name", name);
    msg->setInt32("nameIsType", nameIsType);

    if (mAnalyticsItem != NULL) {
        mAnalyticsItem->setCString(kCodecCodec, name.c_str());
        mAnalyticsItem->setCString(kCodecMode, mIsVideo ? kCodecModeVideo : kCodecModeAudio);
    }

    status_t err;
    Vector<MediaResource> resources;
    MediaResource::Type type =
            secureCodec ? MediaResource::kSecureCodec : MediaResource::kNonSecureCodec;
    MediaResource::SubType subtype =
            mIsVideo ? MediaResource::kVideoCodec : MediaResource::kAudioCodec;
    resources.push_back(MediaResource(type, subtype, 1));
    for (int i = 0; i <= kMaxRetry; ++i) {
        if (i > 0) {
            // Don't try to reclaim resource for the first time.
            if (!mResourceManagerService->reclaimResource(resources)) {
                break;
            }
        }

        sp<AMessage> response;
        err = PostAndAwaitResponse(msg, &response);
        if (!isResourceError(err)) {
            break;
        }
    }
    return err;
}
```



IMediaCodecList

```java
MediaCodec.java
android_media_MediaCodec.cpp
MediaCodec.cpp
```

## configure

```cpp
configure() -> native_configure() -> android_media_MediaCodec_native_configure()->configure() -> configure()
```

## start

```c++
start() -> native_start() -> android_media_MediaCodec_start() -> start() -> start()
```





# 参考文档

```java
解析xml的代码frameworks/av/media/libstagefright/xmlparser
frameworks/av/media/libstagefright/data/media_****.xml
device/qcom/sdm660_64/media_***.xml
hardware/qcom/media
```



