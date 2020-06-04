[TOC]
# 便携式设备的动态音频电源管理

## 描述

动态音频电源管理（DAPM）旨在允许便携式Linux设备始终在音频子系统内使用最少的电源。它独立于其他内核PM，因此可以轻松地与其他PM系统共存。

由于所有电源切换均在ASoC内核内完成，因此DAPM对所有用户空间应用程序也是完全透明的。用户空间应用程序不需要更改或重新编译代码。DAPM根据设备中的任何音频流（捕获/播放）活动和音频混合器设置来做出电源切换决策。

DAPM涵盖了整个机器。它涵盖了整个音频子系统中的电源控制，其中包括内部编解码器电源块和机器级电源系统。

DAPM中有4个电源域

>**编解码器偏置域**(Codec bias domain)
>
>VREF，VMID（核心编解码器和音频功率）
>
>通常可以在编解码器探测/删除和挂起/恢复上进行控制，但是如果不需要侧音等电源，也可以在流时间进行设置。
>
>**平台/机器领域**(Platform/Machine domain)
>
>物理连接的输入和输出
>
>是特定于平台/机器和用户操作的，由机器驱动程序配置并响应异步事件（例如，插入HP时）
>
>**路径域**(Path domain)
>
>音频子系统信号路径
>
>用户更改混音器和多路复用器设置时自动设置。例如alsamixer, amixer.
>
>**流域**(Stream domain)
>
>DAC和ADC。
>
>分别启动和停止流播放/捕获时启用和禁用。例如aplay, arecord.

通过咨询整个机器的音频路由图，可以自动做出所有DAPM电源切换决策。该映射特定于每台机器，并且由每个音频组件（包括内部编解码器组件）之间的互连组成。以下所有影响功率的音频组件都称为小部件。

## DAPM Widgets

音频DAPM Widgets可分为以下几种：

| 名称          | 功能                                                         |      |
| ------------- | ------------------------------------------------------------ | ---- |
| **Mixer**     | 将几个模拟信号混合成一个模拟信号。                           |      |
| **Mux**       | 一个模拟开关，仅输出多个输入之一。                           |      |
| **PGA**       | 可编程增益放大器或衰减小部件。                               |      |
| **ADC**       | 模数转换器                                                   |      |
| **DAC**       | 数模转换器                                                   |      |
| **Switch**    | 模拟开关                                                     |      |
| **Input**     | 编解码器输入引脚                                             |      |
| **Output**    | 编解码器输出引脚                                             |      |
| **Headphone** | 耳机（和可选的插孔）                                         |      |
| **Mic**       | 麦克风（和可选的插孔）                                       |      |
| **Line**      | 线路输入/输出（和可选的插孔）                                |      |
| **Speaker**   | 扬声器                                                       |      |
| **Supply**    | 其他窗口小部件使用的电源或时钟供应窗口小部件。               |      |
| **Regulator** | 为音频组件供电的外部稳压器。                                 |      |
| **Clock**     | 为音频组件提供时钟的外部时钟。                               |      |
| **AIF IN**    | 音频接口输入（带有TDM插槽掩码）。                            |      |
| **AIF OUT**   | 音频接口输出（带有TDM插槽掩码）。                            |      |
| **Siggen**    | 信号发生器。                                                 |      |
| **DAI IN**    | 数字音频接口输入。                                           |      |
| **DAI OUT**   | 数字音频接口输出。                                           |      |
| **DAI Link**  | DAI两个DAI结构之间的链接                                     |      |
| **Pre**       | 特殊的PRE小部件（在所有其他控件之前执行）                    |      |
| **Post**      | 特殊的POST小部件（在所有其他属性之后执行）                   |      |
| **Buffer**    | DSP中的小部件间音频数据缓冲区。                              |      |
| **Scheduler** | DSP内部调度程序，用于调度组件/管道处理工作。                 |      |
| **Effect**    | 执行音频处理效果的小部件。                                   |      |
| **SRC**       | DSP或CODEC中的采样率转换器                                   |      |
| **ASRC**      | DSP或CODEC中的异步采样率转换器                               |      |
| **Encoder**   | 将音频数据从一种格式（通常为PCM）编码为另一种通常压缩后的格式的小部件。 |      |
| **Decoder**   | 将音频数据从压缩格式解码为未压缩格式（如PCM）的小部件。      |      |

（小部件(Widgets)在include /sound /soc-dapm.h中定义）

可以通过任何组件驱动程序类型将小部件添加到声卡。在soc-dapm.h中定义了一些便利宏，这些宏可用于快速构建编解码器和计算机DAPM窗口小部件的列表。

大多数widgets都有名称，寄存器，移位和反转。一些widgets具有用于流名称和kcontrols的额外参数。

### 流域Widgets

流域Widgets与流功率域有关，仅由ADC（模拟到数字转换器），DAC（数字到模拟转换器），AIF IN和AIF OUT组成。

流窗口小部件具有以下格式：

```c
SND_SOC_DAPM_DAC(name, stream name, reg, shift, invert),
SND_SOC_DAPM_AIF_IN(name, stream, slot, reg, shift, invert)
```

注意：流名称必须与编解码器snd_soc_codec_dai中的相应流名称匹配。

例如用于HiFi播放和捕获的流小部件

```c
SND_SOC_DAPM_DAC("HiFi DAC", "HiFi Playback", REG, 3, 1),
SND_SOC_DAPM_ADC("HiFi ADC", "HiFi Capture", REG, 2, 1),
```

例如，AIF的流小部件

```c
SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
```

### 路径域Widgets

路径域Widgets具有控制或影响音频子系统内的音频信号或音频路径的能力。它们具有以下形式：

```
SND_SOC_DAPM_PGA(name, reg, shift, invert, controls, num_controls)
```

所有的widget kcontrols必须设置controls和num_controls成员。

例如Mixer小部件（首先声明kcontrols）

```
/* Output Mixer */
static const snd_kcontrol_new_t wm8731_output_mixer_controls[] = {
SOC_DAPM_SINGLE("Line Bypass Switch", WM8731_APANA, 3, 1, 0),
SOC_DAPM_SINGLE("Mic Sidetone Switch", WM8731_APANA, 5, 1, 0),
SOC_DAPM_SINGLE("HiFi Playback Switch", WM8731_APANA, 4, 1, 0),
};

SND_SOC_DAPM_MIXER("Output Mixer", WM8731_PWR, 4, 1, wm8731_output_mixer_controls,
      ARRAY_SIZE(wm8731_output_mixer_controls)),
```

如果您不希望使用混音器小部件名称作为混音器元素的前缀，则可以改用SND_SOC_DAPM_MIXER_NAMED_CTL。参数与SND_SOC_DAPM_MIXER相同。

### 机器域Widgets

机器域Widgets与编解码器Widgets的不同之处在于，它们没有与之关联的编解码器寄存器位。将一个机器域Widgets分配给可以独立供电的每个机器音频组件(component)（非编解码器或DSP）。例如

- Speaker功放
- 麦克风偏置
- 插孔连接器

机器小部件可以具有可选的回调。

例如，用于外部麦克风的Jack连接器小部件，当插入Mic时启用Mic Bias：-：

```c
static int spitz_mic_bias(struct snd_soc_dapm_widget* w, int event)
{
      gpio_set_value(SPITZ_GPIO_MIC_BIAS, SND_SOC_DAPM_EVENT_ON(event));
      return 0;
}

SND_SOC_DAPM_MIC("Mic Jack", spitz_mic_bias),
```

### 编解码器（BIAS）域

编解码器偏置电源域没有窗口小部件，由编解码器DAPM事件处理程序处理。当编解码器电源状态更改为任何流事件或内核PM事件时，将调用此处理程序。

### 虚拟Widgets

有时，编解码器或机器音频映射中存在没有任何相应软功率控件的Widgets。在这种情况下，有必要创建一个虚拟控件-一个没有控制位的控件，例如

```
SND_SOC_DAPM_MIXER("AC97 Mixer", SND_SOC_DAPM_NOPM, 0, 0, NULL, 0),
```

这可以用于合并以在软件中一起发出信号路径。

定义完所有小部件之后，可以通过调用分别将它们添加到DAPM子系统[`snd_soc_dapm_new_control()`](https://www.kernel.org/doc/html/latest/sound/kernel-api/alsa-driver-api.html#c.snd_soc_dapm_new_control)。

## 编解码器/ DSP Widget互连

小部件通过音频路径(audio paths)（称为互连）在编解码器，平台和机器内相互连接。必须定义每个互连，以便创建小部件之间所有音频路径的映射。

使用编解码器或DSP的图表（以及机器音频系统的示意图）最容易做到这一点，因为它需要通过其音频信号路径将小部件连接在一起。

例如，从WM8731输出混频器（wm8731.c）

WM8731输出混频器具有3个输入（源）

1. 线路旁路输入
2. DAC（HiFi播放）
3. 麦克风侧音输入

在此示例中，每个输入都有一个与之关联的kcontrol（在上面的示例中定义），并通过其kcontrol名称连接到输出混合器。现在，我们可以将目标Widgets（音频信号）与其源Widgets连接起来。

```c
/* output mixer */
{"Output Mixer", "Line Bypass Switch", "Line Input"},
{"Output Mixer", "HiFi Playback Switch", "DAC"},
{"Output Mixer", "Mic Sidetone Switch", "Mic Bias"},
```

所以我们有：

- 目标Widget<===路径名<===源Widget，或者
- 接收器，路径，源或
- `Output Mixer`和`DAC`通过路径名`HiFi Playback Switch`链接到一起

如果没有连接Widget的路径名（例如直接连接），我们将路径名传递为NULL。

通过以下方式创建互连：

```
snd_soc_dapm_connect_input(codec, sink, path, source);
```

最后，在所有Widget和互连(audio paths)都已注册到内核之后，必须调用`snd_soc_dapm_new_widgets(codec)`。这使内核扫描编解码器和计算机，以使内部DAPM状态与计算机的物理状态匹配。

### 机器Widget互连

机器Widget互连的创建方式与编解码器相同，并将编解码器引脚直接连接到机器级Widget。

例如，将扬声器输出编解码器引脚连接到内部扬声器。

```c
/* ext speaker connected to codec pins LOUT2, ROUT2  */
{"Ext Spk", NULL , "ROUT2"},
{"Ext Spk", NULL , "LOUT2"},
```

这样，DAPM可以打开和关闭已连接（和正在使用）的引脚和NC引脚的电源。

## 端点Widget

端点是机器内音频信号的起点或终点（Widget），包括编解码器。例如

- 耳机插孔
- 内部扬声器
- 内部麦克风
- 麦克·杰克
- 编解码器引脚

将端点添加到DAPM图中，以便可以确定其用法以节省功耗。例如，NC编解码器引脚将关闭，未连接的插孔也可以关闭。

## DAPM Widget事件

一些小部件可以在PM事件中向DAPM核心注册其兴趣。例如，带有放大器的扬声器注册了一个小部件，因此只有在使用spk时才能为放大器供电

```
/* turn speaker amplifier on/off depending on use */
static int corgi_amp_event(struct snd_soc_dapm_widget *w, int event)
{
      gpio_set_value(CORGI_GPIO_APM_ON, SND_SOC_DAPM_EVENT_ON(event));
      return 0;
}

/* corgi machine dapm widgets */
static const struct snd_soc_dapm_widget wm8731_dapm_widgets =
      SND_SOC_DAPM_SPK("Ext Spk", corgi_amp_event);
```

请参阅soc-dapm.h了解支持事件的所有其他Widget。

# dapm_widgets和dapm_routes讲解及注册

# snd_soc_dapm_new_controls

snd_soc_dapm_new_controls()实际上，这个函数只是创建widget的第一步，它为每个widget分配内存，初始化必要的字段，然后把这些widget挂在代表声卡的snd_soc_card的widgets链表字段中

```c
static int msm_routing_probe(struct snd_soc_platform *platform)
{
	snd_soc_dapm_new_controls(&platform->component.dapm, msm_qdsp6_widgets,
			   ARRAY_SIZE(msm_qdsp6_widgets));
    ...............
}
```

```
            { "DACL Mux", "Left", "AIFINL" },
            { "DACL Mux", "Right", "AIFINR" },
            { "DACR Mux", "Left", "AIFINL" },
            { "DACR Mux", "Right", "AIFINR" },
            ......
            { "SPKL", "DAC Switch", "DACL" },
            { "SPKL", NULL, "CLK_SYS" },
            { "SPKR", "DAC Switch", "DACR" },
            { "SPKR", NULL, "CLK_SYS" },
```
# snd_soc_dapm_widget讲解

```
SoC动态音频电源管理
我们最多可以有4个电源域
1.编解码器域(Codec domain) -VREF，VMID
  比如VREF和VMID等提供参考电压的widget，这些widget通常在codec的probe/remove回调中进行控制，当然，在工作中如果没有音频流时，也可以适当地进行控制它们的开启与关闭。
 2.platform域(Platform/Machine domain)-物理连接的输入和输出
   位于该域上的widget通常是针对平台或板子的一些需要物理连接的输入/输出接口，例如耳机、扬声器、麦克风，因为这些接口在每块板子上都可能不一样，所以通常它们是在machine驱动中进行定义和控制，并且也可以由用户空间的应用程序通过某种方式来控制它们的打开和关闭。
3.音频路径域(path domain)-内部编解码器路径混合器
   一般是指codec内部的mixer、mux等控制音频路径的widget，这些widget可以根据用户空间的设定连接关系，自动设定他们的电源状态
4.音频数据流域(Stream domain)-DAC和ADC。
 是指那些需要处理音频数据流的widget，例如ADC、DAC等等
```

**codec域widget的定义**

这种widget一般是对普通kcontrol控件的再封装，增加音频路径和电源管理功能

## snd_soc_dapm_widget结构体

```c
/* dapm widget */
struct snd_soc_dapm_widget {
	enum snd_soc_dapm_type id;
	const char *name;		/* widget name */
	const char *sname;	/* stream name */
	struct list_head list;
	struct snd_soc_dapm_context *dapm;

	void *priv;				/* widget specific data */
	struct regulator *regulator;		/* attached regulator */
	const struct snd_soc_pcm_stream *params; /* params for dai links */
	unsigned int num_params; /* number of params for dai links */
	unsigned int params_select; /* currently selected param for dai link */

	/* dapm control */
	int reg;				/* negative reg = no direct dapm */
	unsigned char shift;			/* bits to shift */
	unsigned int mask;			/* non-shifted mask */
	unsigned int on_val;			/* on state value */
	unsigned int off_val;			/* off state value */
	unsigned char power:1;			/* block power status */
	unsigned char active:1;			/* active stream on DAC, ADC's */
	unsigned char connected:1;		/* connected codec pin */
	unsigned char new:1;			/* cnew complete */
	unsigned char force:1;			/* force state */
	unsigned char ignore_suspend:1;         /* kept enabled over suspend */
	unsigned char new_power:1;		/* power from this run */
	unsigned char power_checked:1;		/* power checked this run */
	unsigned char is_supply:1;		/* Widget is a supply type widget */
	unsigned char is_ep:2;			/* Widget is a endpoint type widget */
	int subseq;				/* sort within widget type */

	int (*power_check)(struct snd_soc_dapm_widget *w);

	/* external events */
	unsigned short event_flags;		/* flags to specify event types */
	int (*event)(struct snd_soc_dapm_widget*, struct snd_kcontrol *, int);

	/* kcontrols that relate to this widget */
	int num_kcontrols;
	const struct snd_kcontrol_new *kcontrol_news;
	struct snd_kcontrol **kcontrols;
	struct snd_soc_dobj dobj;

	/* widget input and output edges */
	struct list_head edges[2];

	/* used during DAPM updates */
	struct list_head work_list;
	struct list_head power_list;
	struct list_head dirty;
	int endpoints[2];

	struct clk *clk;
};
```

# snd_soc_dapm_add_routes

route: 在 DAPM widgets控件之间添加通路。该文章主要讲解routes的使用流程。主要以高通平台进行讲解。源代码为msm-pcm-routing-v2.c

```c
struct snd_soc_dapm_route {
	const char *sink; //接收器是接收音频信号的小部件，
	const char *control;
	const char *source; //而源是音频信号的发送者。

	/* Note: currently only supported for links where source is a supply */
	int (*connected)(struct snd_soc_dapm_widget *source,
			 struct snd_soc_dapm_widget *sink);
};
```

## snd_soc_dapm_add_routes注册

```c
static int msm_routing_probe(struct snd_soc_platform *platform)
{
    snd_soc_dapm_new_controls(&platform->component.dapm, msm_qdsp6_widgets,
                              ARRAY_SIZE(msm_qdsp6_widgets));
    snd_soc_dapm_add_routes(&platform->component.dapm, intercon,
                            ARRAY_SIZE(intercon));

	snd_soc_dapm_new_widgets(platform->component.dapm.card);
    ...................
}
```

```c
static const struct snd_soc_dapm_route intercon[] = {
	{"PRI_RX Audio Mixer", "MultiMedia1", "MM_DL1"},
	{"PRI_RX Audio Mixer", "MultiMedia2", "MM_DL2"},
	{"PRI_RX Audio Mixer", "MultiMedia3", "MM_DL3"},
	{"PRI_RX Audio Mixer", "MultiMedia4", "MM_DL4"},
	{"PRI_RX Audio Mixer", "MultiMedia5", "MM_DL5"},
	{"PRI_RX Audio Mixer", "MultiMedia6", "MM_DL6"},
	{"PRI_RX Audio Mixer", "MultiMedia7", "MM_DL7"},
	{"PRI_RX Audio Mixer", "MultiMedia8", "MM_DL8"}, //以此进行讲解
	{"PRI_RX Audio Mixer", "MultiMedia9", "MM_DL9"},
	{"PRI_RX Audio Mixer", "MultiMedia10", "MM_DL10"},
	{"PRI_RX Audio Mixer", "MultiMedia11", "MM_DL11"},
	{"PRI_RX Audio Mixer", "MultiMedia12", "MM_DL12"},
	{"PRI_RX Audio Mixer", "MultiMedia13", "MM_DL13"},
	{"PRI_RX Audio Mixer", "MultiMedia14", "MM_DL14"},
	{"PRI_RX Audio Mixer", "MultiMedia15", "MM_DL15"},
	{"PRI_RX Audio Mixer", "MultiMedia16", "MM_DL16"},
	{"PRI_RX Audio Mixer", "MultiMedia26", "MM_DL26"},
	{"PRI_I2S_RX", NULL, "PRI_RX Audio Mixer"},

	{"SEC_RX Audio Mixer", "MultiMedia1", "MM_DL1"},
```

# 定义

```c
static const struct snd_kcontrol_new pri_i2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("MultiMedia1", MSM_BACKEND_DAI_PRI_I2S_RX ,
	MSM_FRONTEND_DAI_MULTIMEDIA1, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia2", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA2, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia3", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA3, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia4", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA4, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia5", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA5, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia6", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA6, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia7", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA7, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),
	SOC_SINGLE_EXT("MultiMedia8", MSM_BACKEND_DAI_PRI_I2S_RX,
	MSM_FRONTEND_DAI_MULTIMEDIA8, 1, 0, msm_routing_get_audio_mixer,
	msm_routing_put_audio_mixer),		// 重点
	..................
}
```

```c
 SOC_SINGLE_EXT("MultiMedia8", MSM_BACKEND_DAI_PRI_I2S_RX,
 	MSM_FRONTEND_DAI_MULTIMEDIA8, 1, 0, msm_routing_get_audio_mixer,
 	msm_routing_put_audio_mixer),

 ->

 #define SOC_SINGLE_EXT(xname, xreg, xshift, xmax, xinvert,\
 	 xhandler_get, xhandler_put) \
 {	.iface = SNDRV_CTL_ELEM_IFACE_MIXER,
     .name = "MultiMedia8",
	.info = snd_soc_info_volsw, \
 	.get = msm_routing_get_audio_mixer,
 	.put = msm_routing_put_audio_mixer,
 	.private_value = SOC_SINGLE_VALUE(MSM_BACKEND_DAI_PRI_I2S_RX, MSM_FRONTEND_DAI_MULTIMEDIA8, 1, 0, 0)
}

 ->
 #define SOC_SINGLE_VALUE(xreg, xshift, xmax, xinvert, xautodisable) \
 	SOC_DOUBLE_VALUE(MSM_BACKEND_DAI_PRI_I2S_RX, MSM_FRONTEND_DAI_MULTIMEDIA8, MSM_FRONTEND_DAI_MULTIMEDIA8,
 	1, 0, 0)

-> 
#define SOC_DOUBLE_VALUE(xreg, shift_left, shift_right, xmax, xinvert, xautodisable)
	((unsigned long)&(struct soc_mixer_control)
	{.reg = MSM_BACKEND_DAI_PRI_I2S_RX,
	.rreg = MSM_BACKEND_DAI_PRI_I2S_RX,
	.shift = MSM_FRONTEND_DAI_MULTIMEDIA8,
	.rshift = MSM_FRONTEND_DAI_MULTIMEDIA8,
	.max = 1,
	.platform_max = 1,
	.invert = 0,
	.autodisable = 0})
```

# 参考文档

https://blog.csdn.net/wenjin359/article/details/82772231?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522159101608019195188444883%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=159101608019195188444883&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v3~pc_rank_v3-3-82772231.first_rank_ecpm_v3_pc_rank_v3&utm_term=snd_soc_dapm_widget

[Asoc dapm(三) - dapm widgets & dapm kcontrol & dapm route](https://blog.csdn.net/luckywang1103/article/details/50151649) 抓要讲解route的链接扩普图

