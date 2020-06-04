[toc]

# Dynamic PCM

## 简介

动态PCM允许ALSA PCM设备在PCM流运行期间以数字方式将其PCM音频路由到各种数字端点。例如，PCM0可以将数字音频路由到I2S DAI0，I2S DAI1或PDM DAI2。这对于公开多个ALSA PCM并可以路由到多个DAI的SoC DSP驱动程序很有用。

DPCM运行时路由由ALSA混频器设置确定，其方式与在ASoC编解码器驱动程序中路由模拟信号的方式相同。DPCM使用表示DSP内部音频路径的DAPM图，并使用混音器设置来确定每个ALSA PCM使用的路径。

DPCM重用了所有现有的组件编解码器，平台和DAI驱动程序，无需进行任何修改。

### 具有Soc基于DSP的电话音频系统

考虑以下电话音频子系统。本文档中的所有示例都将使用它：

```
| Front End PCMs    |  SoC DSP  | Back End DAIs | Audio devices |

                    *************
PCM0 <------------> *           * <----DAI0-----> Codec Headset
                    *           *
PCM1 <------------> *           * <----DAI1-----> Codec Speakers
                    *   DSP     *
PCM2 <------------> *           * <----DAI2-----> MODEM
                    *           *
PCM3 <------------> *           * <----DAI3-----> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

此图显示了一个简单的智能手机音频子系统。它支持蓝牙，FM数字广播，扬声器，耳机插孔，数字麦克风和蜂窝调制解调器。该声卡公开了4个DSP前端（FE）ALSA PCM设备，并支持6个后端（BE）DAI。每个FE PCM都可以将音频数据以数字方式路由到任何BE DAI。FE PCM设备还可以将音频路由到多个BE DAI。

### 示例-DPCM将播放从DAI0切换到DAI1

正在将音频播放到耳机。一段时间后，用户取下耳机，音频继续在扬声器上播放。

在PCM0上播放到耳机看起来像：-

```
                    *************
PCM0 <============> *           * <====DAI0=====> Codec Headset
                    *           *
PCM1 <------------> *           * <----DAI1-----> Codec Speakers
                    *   DSP     *
PCM2 <------------> *           * <----DAI2-----> MODEM
                    *           *
PCM3 <------------> *           * <----DAI3-----> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

用户已将耳机从插孔中拔出，因此现在必须使用扬声器：

```
                    *************
PCM0 <============> *           * <----DAI0-----> Codec Headset
                    *           *
PCM1 <------------> *           * <====DAI1=====> Codec Speakers
                    *   DSP     *
PCM2 <------------> *           * <----DAI2-----> MODEM
                    *           *
PCM3 <------------> *           * <----DAI3-----> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

音频驱动程序如下处理：

1. 机器驱动程序收到Jack移除事件。
2. 机器驱动程序或音频HAL禁用耳机路径。
3. 由于现在已禁用路径，DPCM在耳机的DAI0上运行PCM触发（停止），hw_free()，shutdown()操作。
4. 机器驱动程序或音频HAL启用扬声器路径。
5. 由于启用了路径，DPCM为DAI1扬声器运行了startup()，hw_params()，prepare()和trigger(start)的PCM op。

在此示例中，机器驱动程序或用户空间音频HAL可以更改路由，然后DPCM将负责管理DAI PCM操作以使链路接通或断开。在此过渡期间，音频播放不会停止。

## DPCM机器驱动程序

启用DPCM的ASoC机器驱动程序与普通机器驱动程序类似，除了我们还必须：-

1. 定义FE和BE DAI链接。
2. 定义任何FE / BE PCM操作。
3. 定义widget graph连接。

### FE和BE DAI链接

```
| Front End PCMs    |  SoC DSP  | Back End DAIs | Audio devices |

                    *************
PCM0 <------------> *           * <----DAI0-----> Codec Headset
                    *           *
PCM1 <------------> *           * <----DAI1-----> Codec Speakers
                    *   DSP     *
PCM2 <------------> *           * <----DAI2-----> MODEM
                    *           *
PCM3 <------------> *           * <----DAI3-----> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

对于上面的示例，我们必须定义4个FE DAI链接和6个BE DAI链接。FE DAI链接定义如下：

```c
static struct snd_soc_dai_link machine_dais[] = {
      {
              .name = "PCM0 System",
              .stream_name = "System Playback",
              .cpu_dai_name = "System Pin",
              .platform_name = "dsp-audio",
              .codec_name = "snd-soc-dummy",
              .codec_dai_name = "snd-soc-dummy-dai",
              .dynamic = 1,//设置为支持DPCM FE
              .trigger = {SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POST},//
              .dpcm_playback = 1,//FE流方向
      },
      .....< other FE and BE DAI links here >
};
```

此FE DAI链接与常规DAI链接非常相似，不同之处在于，我们还将DAI链接设置为`dynamic = 1`的DPCM FE。受支持的FE流方向也应使用`dpcm_playback`和`dpcm_capture`标志设置。 还有一个选项可以为每个FE指定触发调用的顺序。 这允许ASoC内核在其他组件之前或之后触发DSP（因为某些DSP对订购DAI / DSP启动和停止序列有严格的要求）。



上面的FE DAI将编解码器和代码DAI设置为虚拟设备，因为BE是动态的，并将根据运行时配置进行更改。

BE DAI的配置如下：

```c
static struct snd_soc_dai_link machine_dais[] = {
      .....< FE DAI links here >
      {
              .name = "Codec Headset",
              .cpu_dai_name = "ssp-dai.0",
              .platform_name = "snd-soc-dummy",
              .no_pcm = 1,//设置为1,表明此dai为BE DAI
              .codec_name = "rt5640.0-001c",
              .codec_dai_name = "rt5640-aif1",
              .ignore_suspend = 1,
              .ignore_pmdown_time = 1,
              .be_hw_params_fixup = hswult_ssp0_fixup,
              .ops = &haswell_ops,
              .dpcm_playback = 1,//支持的流方向设置标志
              .dpcm_capture = 1,//支持的流方向设置标志
      },
      .....< other BE DAI links here >
};
```

此BE DAI链接将DAI0连接到编解码器（在本例中为RT5460 AIF1）。 它使用上面的dpcm_playback和dpcm_capture设置no_pcm标志来标记它具有BE，并为支持的流方向设置标志。

BE还设置了忽略挂起和PM停机时间的标志。 这使BE可以在无主机模式下工作，在该模式下主机CPU不会像BT电话那样传输数据：

```
                    *************
PCM0 <------------> *           * <----DAI0-----> Codec Headset
                    *           *
PCM1 <------------> *           * <----DAI1-----> Codec Speakers
                    *   DSP     *
PCM2 <------------> *           * <====DAI2=====> MODEM
                    *           *
PCM3 <------------> *           * <====DAI3=====> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

这样，在DSP，MODEM DAI和BT DAI仍在运行时，主机CPU可以进入睡眠状态。

如果编解码器是外部管理的设备，则BE DAI链接也可以将编解码器设置为虚拟设备。

同样，如果CPU DAI由DSP固件管理，则BE DAI也可以设置虚拟cpu DAI。

### FE / BE PCM操作

上面的BE还会导出一些PCM操作和一个`fixup`回调。修补程序回调由机器驱动程序用于根据FE hw参数对DAI进行（重新）配置。也就是说，DSP可以从FE到BE执行SRC或ASRC。

例如，DSP将所有FE hw参数转换为以48k，16位，DAI0立体声的固定速率运行。这意味着必须在机器驱动程序中为DAI0修复所有FE hw_params，以便无论FE配置如何，DAI都能以所需配置运行。

```
static int dai0_fixup(struct snd_soc_pcm_runtime *rtd,
                      struct snd_pcm_hw_params *params)
{
      struct snd_interval *rate = hw_param_interval(params,
                      SNDRV_PCM_HW_PARAM_RATE);
      struct snd_interval *channels = hw_param_interval(params,
                                              SNDRV_PCM_HW_PARAM_CHANNELS);

      /* The DSP will convert the FE rate to 48k, stereo */
      rate->min = rate->max = 48000;
      channels->min = channels->max = 2;

      /* set DAI0 to 16 bit */
      params_set_format(params, SNDRV_PCM_FORMAT_S16_LE);
      return 0;
}
```

其他PCM操作与常规DAI链接相同。根据需要使用。

### Widget图连接

BE DAI链接通常会在初始化时通过ASoC DAPM内核连接到图形。但是，如果BE编解码器或BE DAI是虚拟的，则必须在驱动程序中明确设置：

```
/* BE for codec Headset -  DAI0 is dummy and managed by DSP FW */
{"DAI0 CODEC IN", NULL, "AIF1 Capture"},
{"AIF1 Playback", NULL, "DAI0 CODEC OUT"},
```

## 编写DPCM DSP驱动程序

DPCM DSP驱动程序看起来很像标准平台类ASoC驱动程序，结合了编解码器类驱动程序中的元素。DSP平台驱动程序必须实现：

1. Front End PCM DAIs -即struct snd_soc_dai_driver。
2. DAPM图显示了DSP音频从FE DAIs到BE的路由。
3. DSP图形中的DAPM Widget。
4. 增益，路由等的混音器
5. DMA配置。
6. BE AIF widgets.

第6项对于将音频路由到DSP外部很重要。需要为每个BE和每个流方向定义AIF。例如，对于上面的BE DAI0，我们会有：-

```
SND_SOC_DAPM_AIF_IN("DAI0 RX", NULL, 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("DAI0 TX", NULL, 0, SND_SOC_NOPM, 0, 0),
```

BE AIF用于将DSP图形连接到其他组件驱动程序的图形（例如，编解码器图形）。

## 无主机PCM流

无主机PCM流是未通过主机CPU路由的流。一个例子是从手机到调制解调器的电话。

```
                    *************
PCM0 <------------> *           * <----DAI0-----> Codec Headset
                    *           *
PCM1 <------------> *           * <====DAI1=====> Codec Speakers/Mic
                    *   DSP     *
PCM2 <------------> *           * <====DAI2=====> MODEM
                    *           *
PCM3 <------------> *           * <----DAI3-----> BT
                    *           *
                    *           * <----DAI4-----> DMIC
                    *           *
                    *           * <----DAI5-----> FM
                    *************
```

在这种情况下，PCM数据通过DSP路由。在这种用例中，主机CPU仅用于控制，并且可以在流的运行期间进入睡眠状态。

主机可以通过以下方式控制无主机链接：

> 1. 将链接配置为CODEC <-> CODEC样式链接。在这种情况下，可以通过DAPM图形的状态来启用或禁用链接。这通常意味着存在一个混合器控件，可用于连接或断开两个DAI之间的路径。
> 2. 无主机的FE。该FE与DAPM图上的BE DAI链接具有虚拟连接。然后由FE作为常规PCM操作执行控制。该方法可以更好地控制DAI链接，但是需要更多的用户空间代码来控制链接。除非您的硬件需要更细粒度的PCM ops排序，否则建议使用CODEC <-> CODEC。

### 编解码器<->编解码器链接

当DAPM在DAPM图中检测到有效路径时，将启用此DAI链接。机器驱动程序为DAI链接设置了一些附加参数，即

```
static const struct snd_soc_pcm_stream dai_params = {
      .formats = SNDRV_PCM_FMTBIT_S32_LE,
      .rate_min = 8000,
      .rate_max = 8000,
      .channels_min = 2,
      .channels_max = 2,
};

static struct snd_soc_dai_link dais[] = {
      < ... more DAI links above ... >
      {
              .name = "MODEM",
              .stream_name = "MODEM",
              .cpu_dai_name = "dai2",
              .codec_dai_name = "modem-aif1",
              .codec_name = "modem",
              .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
                              | SND_SOC_DAIFMT_CBM_CFM,
              .params = &dai_params,
      }
      < ... more DAI links here ... >
```

当DAPM检测到有效路径，然后调用PCM操作以启动链接时，这些参数用于配置DAI hw_params（）。当路径不再有效时，DAPM还将调用适当的PCM操作以禁用DAI。

### 无主机FE

DAI链接由不读取或写入任何PCM数据的FE启用。这意味着创建与虚拟路径连接到两个DAI链接的新FE。DAI链接将在启动FE PCM时启动，并在FE PCM停止时停止。请注意，在此配置中，FE PCM无法读取或写入数据。

## 为ALSA dapm创建编解码器到编解码器Dai链接

通常，音频流总是从CPU到编解码器，因此您的系统如下所示：

```
 ---------          ---------
|         |  dai   |         |
    CPU    ------->    codec
|         |        |         |
 ---------          ---------
```

如果您的系统如下所示：

```
                     ---------
                    |         |
                      codec-2
                    |         |
                    ---------
                         |
                       dai-2
                         |
 ----------          ---------
|          |  dai-1 |         |
    CPU     ------->  codec-1
|          |        |         |
 ----------          ---------
                         |
                       dai-3
                         |
                     ---------
                    |         |
                      codec-3
                    |         |
                     ---------
```

假设编解码器2是蓝牙芯片，编解码器3连接到扬声器，并且您遇到以下情况：编解码器2将接收音频数据，并且用户希望通过编解码器3播放音频而不涉及CPU。当使用编解码器到编解码器的连接时，上述情况是理想的情况。

您的dai_link应该在机器文件中显示如下：

```c
/*
 * this pcm stream only supports 24 bit, 2 channel and
 * 48k sampling rate.
 */
static const struct snd_soc_pcm_stream dsp_codec_params = {
       .formats = SNDRV_PCM_FMTBIT_S24_LE,
       .rate_min = 48000,
       .rate_max = 48000,
       .channels_min = 2,
       .channels_max = 2,
};

{
   .name = "CPU-DSP",
   .stream_name = "CPU-DSP",
   .cpu_dai_name = "samsung-i2s.0",
   .codec_name = "codec-2,
   .codec_dai_name = "codec-2-dai_name",
   .platform_name = "samsung-i2s.0",
   .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
           | SND_SOC_DAIFMT_CBM_CFM,
   .ignore_suspend = 1,
   .params = &dsp_codec_params,
},
{
   .name = "DSP-CODEC",
   .stream_name = "DSP-CODEC",
   .cpu_dai_name = "wm0010-sdi2",
   .codec_name = "codec-3,
   .codec_dai_name = "codec-3-dai_name",
   .dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF
           | SND_SOC_DAIFMT_CBM_CFM,
   .ignore_suspend = 1,
   .params = &dsp_codec_params,
},
```

上面的代码段是由sound/soc/samsung/speyside.c驱动的。

请注意“ params”回调，该回调使dapm知道此dai_link是编解码器与编解码器的连接。

在dapm核心中，将在cpu_dai播放小部件(Widget)和codec_dai捕获小部件(Widget)之间创建一条路径作为播放路径，反之亦然。为了触发上述路由，DAPM需要找到一个有效端点，该端点可以是分别对应于回放和捕获路径的接收器或源窗口小部件。

为了触发此dai_link小部件，可以创建扬声器放大器的瘦编解码器驱动程序，如wm8727.c文件中所示，即使不需要控制，它也会为设备设置适当的约束。

确保命名相应的cpu和编解码器回放，并捕获分别以“ Playback”和“ Capture”结尾的dai名称，因为dapm core将基于该名称链接并为这些dais供电。

当链接上的所有DAI都属于编解码器组件时，“简单音频卡”中的dai_link将自动检测为编解码器。dai_link将使用链接上所有DAI支持的流参数（通道，格式，采样率）的子集进行初始化。由于无法在设备树中提供这些参数，因此这对于与简单的固定功能编解码器（例如蓝牙控制器或蜂窝调制解调器）进行通信非常有用。