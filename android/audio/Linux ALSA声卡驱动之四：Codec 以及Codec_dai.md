# ASoC编解码器类驱动程序

编解码器类驱动程序是通用且独立于硬件的代码，可将编解码器，FM，MODEM，BT或外部DSP配置为提供音频捕获和回放。它不应包含特定于目标平台或计算机的代码。所有平台和机器特定的代码应分别添加到平台和机器驱动程序。

每个编解码器类驱动程序*必须*提供以下功能：

1. 编解码器DAI和PCM配置
2. 编解码器控制IO - 使用RegMap API;例如:I2C、SPI协议的控制接口
3. Mixers和audio controls
4. 编解码器音频操作
5. DAPM描述。
6. DAPM事件处理程序。
7. DAC数字静音控制。(可选）

最好将本指南与sound /soc/codecs /中的现有编解码器驱动程序代码结合使用

### 编解码器DAI和PCM配置

每个编解码器驱动程序必须具有结构snd_soc_dai_driver，以定义其DAI和PCM功能以及操作。导出该结构，以便您的机器驱动程序可以将其注册到内核。

例如

```c
static struct snd_soc_dai_ops wm8731_dai_ops = {
      .prepare        = wm8731_pcm_prepare,
      .hw_params      = wm8731_hw_params,
      .shutdown       = wm8731_shutdown,
      .digital_mute   = wm8731_mute,//大多数编解码器在DAC之前都具有数字静音功能，可用于将任何系统噪声降至最低。静音会阻止任何数字数据进入DAC。应用或释放静音后，可以为每个编解码器DAI创建一个由内核调用的回调。
      .set_sysclk     = wm8731_set_dai_sysclk,
      .set_fmt        = wm8731_set_dai_fmt,
};

struct snd_soc_dai_driver wm8731_dai = {
      .name = "wm8731-hifi",
      .playback = {
              .stream_name = "Playback",
              .channels_min = 1,
              .channels_max = 2,
              .rates = WM8731_RATES,
              .formats = WM8731_FORMATS,},
      .capture = {
              .stream_name = "Capture",
              .channels_min = 1,
              .channels_max = 2,
              .rates = WM8731_RATES,
              .formats = WM8731_FORMATS,},
      .ops = &wm8731_dai_ops,//编解码器音频操作。主要是pcm相关操作。
      .symmetric_rates = 1,
};
```

### 编解码器控制IO

编解码器通常可以通过I2C或SPI样式的接口进行控制（AC97将控制与DAI中的数据结合在一起）。编解码器驱动程序应对所有编解码器IO使用Regmap API。请参阅include/linux/regmap.h和现有的编解码器驱动程序以获取regmap用法示例。

### Mixers和audio controls

可以使用soc.h中定义的便捷宏来定义所有编解码器混合器和音频控件。

```c
#define SOC_SINGLE(xname, reg, shift, mask, invert)
```

定义单个控件，如下所示：

```c
xname = Control name e.g. "Playback Volume"
reg = codec register
shift = control bit(s) offset in register
mask = control bit size(s) e.g. mask of 7 = 3 bits
invert = the control is inverted
```

其他宏包括：-

```c
#define SOC_DOUBLE(xname, reg, shift_left, shift_right, mask, invert)
```

立体声控制

```c
#define SOC_DOUBLE_R(xname, reg_left, reg_right, shift, mask, invert)
```

跨越2个寄存器的立体声控制

```c
#define SOC_ENUM_SINGLE(xreg, xshift, xmask, xtexts)
```

定义单个枚举控件，如下所示：

```c
xreg = register
xshift = control bit(s) offset in register
xmask = control bit(s) size
xtexts = pointer to array of strings that describe each setting

#define SOC_ENUM_DOUBLE(xreg, xshift_l, xshift_r, xmask, xtexts)
```

定义一个立体声枚举控件

### 编解码器音频操作

编解码器驱动程序还支持以下ALSA PCM操作：

```c
/* SoC audio ops */
struct snd_soc_ops {
      int (*startup)(struct snd_pcm_substream *);
      void (*shutdown)(struct snd_pcm_substream *);
      int (*hw_params)(struct snd_pcm_substream *, struct snd_pcm_hw_params *);
      int (*hw_free)(struct snd_pcm_substream *);
      int (*prepare)(struct snd_pcm_substream *);
};
```

有关详细信息，请参阅ALSA驱动程序PCM文档。 http://www.alsa-project.org/~iwai/writing-an-alsa-driver/

### DAPM说明

动态音频电源管理描述描述了编解码器电源组件及其关系以及向ASoC内核的寄存器。请阅读dapm.rst以获取构建说明的详细信息。

另请参见其他编解码器驱动程序中的示例。

### DAPM事件处理程序

此函数是处理编解码器域PM调用和系统域PM调用（例如，挂起和恢复）的回调。不使用时，可将编解码器置于睡眠状态。

电源状态：

```c
SNDRV_CTL_POWER_D0: /* full On */
/* vref/mid, clk and osc on, active */

SNDRV_CTL_POWER_D1: /* partial On */
SNDRV_CTL_POWER_D2: /* partial On */

SNDRV_CTL_POWER_D3hot: /* Off, with power */
/* everything off except vref/vmid, inactive */

SNDRV_CTL_POWER_D3cold: /* Everything Off, without power */
```

### 编解码器DAC数字静音控制

大多数编解码器在DAC之前都具有数字静音功能，可用于将任何系统噪声降至最低。静音会阻止任何数字数据进入DAC。

应用或释放静音后，可以为每个编解码器DAI创建一个由内核调用的回调。

即

```c
static int wm8974_mute(struct snd_soc_dai *dai, int mute)
{
      struct snd_soc_component *component = dai->component;
      u16 mute_reg = snd_soc_component_read32(component, WM8974_DAC) & 0xffbf;

      if (mute)
              snd_soc_component_write(component, WM8974_DAC, mute_reg | 0x40);
      else
              snd_soc_component_write(component, WM8974_DAC, mute_reg);
      return 0;
}
```

# ASoC数字音频接口（DAI）

ASoC当前支持当今在SoC控制器和便携式音频编解码器中发现的三个主要数字音频接口（DAI），即AC97，I2S和PCM。

| 数字音频接口(DAI) | 描述                                                         | 代表产品 |
| ----------------- | ------------------------------------------------------------ | -------- |
| AC97              | AC97是五线接口，通常在许多PC声卡上都可以找到。现在，它在许多便携式设备中也很流行。 |          |
| I2S               | I2S是用于HiFi，STB和便携式设备的常见4线DAI。Tx和Rx线用于音频传输，而位时钟（BCLK）和左/右时钟（LRC）同步链接。 |          |
| PCM               | PCM是另一个4线接口，与I2S非常相似，它可以支持更灵活的协议。  |          |



# 编解码器注册

### snd_soc_register_codec

```c
int snd_soc_register_codec(struct device *dev,
			   const struct snd_soc_codec_driver *codec_drv,
			   struct snd_soc_dai_driver *dai_drv,
			   int num_dai)
{
	struct snd_soc_dapm_context *dapm;
	struct snd_soc_codec *codec;
	struct snd_soc_dai *dai;
	int ret, i;

	dev_dbg(dev, "codec register %s\n", dev_name(dev));

	codec = kzalloc(sizeof(struct snd_soc_codec), GFP_KERNEL);
	if (codec == NULL)
		return -ENOMEM;

	codec->component.codec = codec;

    //codec_drv->component_driver中的controls、dapm_widgets、dapm_routes注册到编解码器组件上(codec->component)
	ret = snd_soc_component_initialize(&codec->component,
			&codec_drv->component_driver, dev);
	if (ret)
		goto err_free;

    //把驱动中(codec_drv)的controls、dapm_widgets、dapm_routes函数注册到编解码器设备组件上(codec->component)
	if (codec_drv->controls) {
		codec->component.controls = codec_drv->controls;
		codec->component.num_controls = codec_drv->num_controls;
	}
	if (codec_drv->dapm_widgets) {
		codec->component.dapm_widgets = codec_drv->dapm_widgets;
		codec->component.num_dapm_widgets = codec_drv->num_dapm_widgets;
	}
	if (codec_drv->dapm_routes) {
		codec->component.dapm_routes = codec_drv->dapm_routes;
		codec->component.num_dapm_routes = codec_drv->num_dapm_routes;
	}
    //把驱动中(codec_drv)的probe/remove/write/read函数注册到平台设备组件上(codec->component)
	if (codec_drv->probe)
		codec->component.probe = snd_soc_codec_drv_probe;
	if (codec_drv->remove)
		codec->component.remove = snd_soc_codec_drv_remove;
	if (codec_drv->write)
		codec->component.write = snd_soc_codec_drv_write;
	if (codec_drv->read)
		codec->component.read = snd_soc_codec_drv_read;
	codec->component.ignore_pmdown_time = codec_drv->ignore_pmdown_time;

	dapm = snd_soc_codec_get_dapm(codec);//codec.dapm
	dapm->idle_bias_off = codec_drv->idle_bias_off;
	dapm->suspend_bias_off = codec_drv->suspend_bias_off;
	if (codec_drv->seq_notifier)
		dapm->seq_notifier = codec_drv->seq_notifier;
	if (codec_drv->set_bias_level)
		dapm->set_bias_level = snd_soc_codec_set_bias_level;
	codec->dev = dev;
	codec->driver = codec_drv;
	codec->component.val_bytes = codec_drv->reg_word_size;

#ifdef CONFIG_DEBUG_FS
	codec->component.init_debugfs = soc_init_codec_debugfs;
	codec->component.debugfs_prefix = "codec";
#endif

	if (codec_drv->get_regmap)
		codec->component.regmap = codec_drv->get_regmap(dev);

	for (i = 0; i < num_dai; i++) {
		fixup_codec_formats(&dai_drv[i].playback);
		fixup_codec_formats(&dai_drv[i].capture);
	}

    //为每个dai_drv创建一个dai(snd_soc_dai)，然后把component、driver把codec->component添加到每个dai的。最后把dai添加到component->dai_list链表中。
    //即：为codec组件创建dai。
	ret = snd_soc_register_dais(&codec->component, dai_drv, num_dai, false);
	if (ret < 0) {
		dev_err(dev, "ASoC: Failed to register DAIs: %d\n", ret);
		goto err_cleanup;
	}

    //把codec添加到每个dai的codec成员中。
	list_for_each_entry(dai, &codec->component.dai_list, list)
		dai->codec = codec;

	mutex_lock(&client_mutex);
    //把codec的组件添加到component_list链表中。
	snd_soc_component_add_unlocked(&codec->component);
    //把codec添加到codec_list链表中。
	list_add(&codec->list, &codec_list);
	mutex_unlock(&client_mutex);

	dev_dbg(codec->dev, "ASoC: Registered codec '%s'\n",
		codec->component.name);
	return 0;

err_cleanup:
	snd_soc_component_cleanup(&codec->component);
err_free:
	kfree(codec);
	return ret;
}
EXPORT_SYMBOL_GPL(snd_soc_register_codec);
```



里面会注册snd_soc_register_dais

# codec_dai

	snd_soc_register_dais



# controls注册

controls注册有两种，直接通过snd_soc_register_codec()函数注册，该函数会调用snd_soc_codec_driver的成员变量controls进行注册。

另外一种，通过snd_soc_add_codec_controls函数进行注册。

# snd_soc_add_codec_controls

该函数的作用：根据给定模板controls，创建Kcontrols实例，并把创建的Kcontrols添加到codec->component->card->snd_card声卡中

模板控件创建一个新的混音器控件。然后把控件实例添加到该声卡中。即：添加到card.controls链表中。

向codec注册controls方法集

## snd_soc_add_codec_controls

```c
int snd_soc_add_codec_controls(struct snd_soc_codec *codec,
	const struct snd_kcontrol_new *controls, unsigned int num_controls)
//snd_soc_add_codec_controls() -> snd_soc_add_component_controls() -> snd_soc_add_controls()
//&codec->component->card->snd_card	== card
//&codec->component->dev == dev
static int snd_soc_add_controls(struct snd_card *card, struct device *dev,
	const struct snd_kcontrol_new *controls, int num_controls,
	const char *prefix, void *data)
{
	int err, i;

	for (i = 0; i < num_controls; i++) {
		const struct snd_kcontrol_new *control = &controls[i];
		err = snd_ctl_add(card, snd_soc_cnew(control, data,
						     control->name, prefix));//通过snd_soc_cnew()从模板控件创建一个新的混音器控件。然后把控件实例添加到该声卡中。即：添加到card.controls链表中。

		if (err < 0) {
			dev_err(dev, "ASoC: Failed to add %s: %d\n",
				control->name, err);
			return err;
		}
	}

	return 0;
}


```



### 使用方法

```bash
ASUS_X01BD_1:/ # tinymix 'SEC_MI2S_RX Channels'
SEC_MI2S_RX Channels: One >Two Three Four Five Six Seven Eight

```

### kcontrol注册方法

```c
static int msm_audrx_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *dig_cdc = rtd->codec_dais[DIG_CDC]->codec;
	struct snd_soc_codec *ana_cdc = rtd->codec_dais[ANA_CDC]->codec;
	struct snd_soc_dapm_context *dapm = snd_soc_codec_get_dapm(ana_cdc);
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct msm_asoc_mach_data *pdata = snd_soc_card_get_drvdata(rtd->card);
	struct snd_card *card;
	int ret = -ENOMEM;

	pr_debug("%s(),dev_name%s\n", __func__, dev_name(cpu_dai->dev));

    //把kcontrol注册到ana_cdc
	ret = snd_soc_add_codec_controls(ana_cdc, msm_snd_controls,
				   ARRAY_SIZE(msm_snd_controls));
..............
}
```

## 结构体变量

```c
struct snd_kcontrol_new {
	snd_ctl_elem_iface_t iface;	/* 接口标识符*/
	unsigned int device;		/* 设备/客户端号 */
	unsigned int subdevice;		/* subdevice (substream) number */
	const unsigned char *name;	/* ASCII name of item */
	unsigned int index;		/* index of item */
	unsigned int access;		/* access rights */
	unsigned int count;		/* count of same elements */
	snd_kcontrol_info_t *info; 	//重点:
	snd_kcontrol_get_t *get;	//重点:
	snd_kcontrol_put_t *put;	//重点:
	union {
		snd_kcontrol_tlv_rw_t *c;
		const unsigned int *p;
	} tlv;
	unsigned long private_value;
};
```

### 创建方法

```c
static const char *const mi2s_ch_text[] = {"One", "Two", "Three", "Four",
					   "Five", "Six", "Seven",
					   "Eight"};

static SOC_ENUM_SINGLE_EXT_DECL(sec_mi2s_rx_chs, mi2s_ch_text);

static int msm_mi2s_rx_ch_get(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	int idx = mi2s_get_port_idx(kcontrol);

	if (idx < 0)
		return idx;

	pr_debug("%s: msm_mi2s_[%d]_rx_ch  = %d\n", __func__,
		 idx, mi2s_rx_cfg[idx].channels);
	ucontrol->value.enumerated.item[0] = mi2s_rx_cfg[idx].channels - 1;

	return 0;
}
static int msm_mi2s_rx_ch_put(struct snd_kcontrol *kcontrol,
			      struct snd_ctl_elem_value *ucontrol)
{
	int idx = mi2s_get_port_idx(kcontrol);

	if (idx < 0)
		return idx;

	mi2s_rx_cfg[idx].channels = ucontrol->value.enumerated.item[0] + 1;
	pr_debug("%s: msm_mi2s_[%d]_rx_ch  = %d\n", __func__,
		 idx, mi2s_rx_cfg[idx].channels);

	return 1;
}
const struct snd_kcontrol_new msm_common_snd_controls[] = {
    ...........
    SOC_ENUM_EXT("SEC_MI2S_RX Channels", sec_mi2s_rx_chs,
                 msm_mi2s_rx_ch_get, msm_mi2s_rx_ch_put),
    ...........
}
```

> SOC_ENUM_SINGLE_EXT_DECL解析

```c
//static const char *const mi2s_ch_text[] = {"One", "Two", "Three", "Four",
					   "Five", "Six", "Seven",
					   "Eight"};
//static SOC_ENUM_SINGLE_EXT_DECL(sec_mi2s_rx_chs, mi2s_ch_text);
#define SOC_ENUM_SINGLE_EXT_DECL(name, xtexts) \
	const struct soc_enum name = SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(xtexts), xtexts)
#define SOC_ENUM_SINGLE_EXT(xitems, xtexts) \
{	.items = xitems, .texts = xtexts }

->
    static const struct soc_enum sec_mi2s_rx_chs = SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(mi2s_ch_text), mi2s_ch_text)
->
    static const struct soc_enum sec_mi2s_rx_chs = {.items =8, .texts=mi2s_ch_text}
```

> SOC_ENUM_EXT

```c
#define SOC_ENUM_EXT(xname, xenum, xhandler_get, xhandler_put) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_enum_double, \
	.get = xhandler_get, .put = xhandler_put, \
	.private_value = (unsigned long)&xenum }

SOC_ENUM_EXT("SEC_MI2S_RX Channels", sec_mi2s_rx_chs,
                 msm_mi2s_rx_ch_get, msm_mi2s_rx_ch_put),
->
{
    .iface = SNDRV_CTL_ELEM_IFACE_MIXER,
    .name = "SEC_MI2S_RX Channels",
    .info = snd_soc_info_enum_double,
    .get = msm_mi2s_rx_ch_get,
    .put = msm_mi2s_rx_ch_put,
    .private_value = (unsigned long)&sec_mi2s_rx_chs //即：{"One", "Two", "Three", "Four","Five", "Six", "Seven","Eight"};
}
```

