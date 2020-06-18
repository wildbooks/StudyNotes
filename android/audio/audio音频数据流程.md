# 播放



FastMixer.cpp -> FastMixer::onWork() 快速混音

PlaybackThread::threadLoop_write()

 AudioFlinger::RecordThread::threadLoop() #录音





    AudioTrack::set() -> 
      	mAudioTrackThread = new AudioTrackThread(*this);
        mAudioTrackThread->run("AudioTrack", ANDROID_PRIORITY_AUDIO, 0 /*stack*/); //会调用 AudioTrack::AudioTrackThread::threadLoop()
        ->  AudioTrack::AudioTrackThread::threadLoop()  -> AudioFlinger::PlaybackThread::threadLoop()

```c++
//数据流程
 -> mMixerBuffer混音 -> mEffectBuffer音效处理 -> msinkbuffer -> 硬件
                    -> msinkbuffer -> 硬件
```



## MixerThread

```
AudioFlinger::MixerThread::MixerThread()
-> mFastMixer->run("FastMixer", PRIORITY_URGENT_AUDIO); 
```



```c++
PlaybackThread::onFirstRef()
-> run(mThreadName, ANDROID_PRIORITY_URGENT_AUDIO);
-> 
```



# 录音

## FastCapture

```
AudioFlinger::RecordThread::RecordThread()
-> mFastCapture->run("FastCapture", ANDROID_PRIORITY_URGENT_AUDIO);
```





# 参考文档

[Android Framework中的线程Thread及它的threadLoop方法](https://blog.csdn.net/briblue/article/details/51104230?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522159049503819725219917012%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=159049503819725219917012&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v3~pc_rank_v3-1-51104230.first_rank_ecpm_v3_pc_rank_v3&utm_term=threadLoop)

