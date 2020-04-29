[toc]

#  # api

```c

 native_init();
native_setup(Object audioeffect_this, String type,
            String uuid, int priority, int audioSession, int[] id, Object[] desc,
            String opPackageName);
native_finalize();
native_release();
native_setEnabled(boolean enabled);
native_getEnabled();
native_hasControl();
native_setParameter(int psize, byte[] param,
            int vsize, byte[] value);
native_getParameter(int psize, byte[] param,
            int vsize, byte[] value);
native_command(int cmdCode, int cmdSize,
            byte[] cmdData, int repSize, byte[] repData);
native_query_effects();
native_query_pre_processing(int audioSession);
```

# dd

- EffectModule

  EffectModule是一个封装类，封装了3rd音效引擎的实现；可以控制类似process()\command()通过不同进程的并发调用。保存着一个用于同所有客户端进行同步的EffectHandle用于处理音效状态、参数更改；EffectModule同时管控着音效引擎的状态机：重置、使能、以及在状态切换过程中的声音淡入淡出效果。

- EffectHandle

  EffectHandle是IEffect接口的具体实现，他提供了一系列资源来接受参数更新、跟踪效果控制的所有权和状态；并具有一个指向EffectModule的指针控制着EffectModule对象。每个应用只能使用一个EffectHandle来控制。EffectHandle由AudioFlinger::createEffect()创建。

- EffectChain

// EffectChain类表示与一个音频会话关联的一组效果。每个输出混合器线程（PlaybackThread）可以有任意数量的EffectChain对象。 会话ID为AUDIO_SESSION_OUTPUT_MIX的EffectChain包含应用于输出混合的全局效果。 该链中的效果可以是插入的或辅助的。 其他链中的效果（附加到音轨）仅插入。 EffectChain维护一个效果模块的有序列表，该顺序与效果处理顺序相对应。 当附加到轨道（会话ID！= AUDIO_SESSION_OUTPUT_MIX）时，
//它还提供自己的输入缓冲区，轨道将其用作累积缓冲区。

EffectChain展示了一系列音效同audio session之间的关系；每一个output mixer thread (playbackthread)可以关联任意多个EffectChain对象。当EffectChain同ID为0的session关联时，EffectChain作用于所有的output mix。
EffectChain EffectMode EffectHandle这三者的关系类似于MVC.当然这里的view说起来可能有些牵强。但可以这么来理解EffectMode就算这里的Model，EffectHandle就是这里的control,EffectChain就是这里的View。总的来说：EffectChain代表了一系列音效之前的关系，EffectMode是所有音效实现的抽象，EffectHandle是所有音效的操作的抽象。 



# 音效类型

```
    常见的 AudioEffect 类型和作用大致如下：

Equalizer AudioEffect（均衡器）

    均衡器可以被用来改变特定音源输入的频率响应或经混音后的主要输出音频的频率响应。APP 在 Framework 层创建 Equalizer 对象并实例化一个 Equalizer 引擎，通过它们可以对每一个频带的增益进行精确地控制。


Virtualizer AudioEffect（虚拟器）

    虚拟器是对把各个声道进行空间化的这类音效的统称。这类音效的具体行为与设备上输入音频的类型、声道数和输出音频的声道数有关。比如在一个立体声输入、立体声耳机输出的场景中，虚拟器实际执行的是立体声扩展音效。APP 在 Framework 层创建 Virtualizer 对象并实例化一个 Virtualizer 引擎。


BassBoost AudioEffect（低音增强器）

    低音增强器被用于增强音频中的低频部分，相当于一个只能对低频声音进行增益控制的简单均衡器。APP 在 Framework 层创建 BassBoost 对象并实例化一个低音增强引擎。


PresetReverb AudioEffect（预设混响器）

    一个声音在产生后会往各个方向传播。如果这个声音是在室内产生的，接收方会首先听到音源本身发出的声音，然后听到来自墙壁、天花板和地板的回声。这些回声又会在传播到障碍物上时产生二次回声、三次回声...接收方会持续不断地听到声音，这每一次声音的辨识度越来越低，且响度随时间衰减。混响器（Reverb）对于音频接收者的环境建模非常重要，它可以被用于模拟在不同环境中播放音乐产生的效果，或者在游戏中为玩家生成更加沉浸式的音频体验。APP 可以通过预设混响器提前配置全局的混响参数，这种方式在为音乐播放添加混响效果时被广泛使用。如果 APP 需要配置更高级的环境声混响参数，最好使用环境声混响器来实现。APP 在 Framework 层创建 PresetReverb 对象并实例化一个混响引擎。


EnvironmentalReverb AudioEffect（环境声混响器）
```

# 参考文档

(Android源码分析：AudioEffect)[http://blog.sina.com.cn/s/blog_697477dd0101hjql.html]



