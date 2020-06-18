# Kcontrol

# Kcontrol注册方法

Kcontrol注册方法，实际上是通过snd_soc_add_controls()函数实现的。

platform注册方法

```c
snd_soc_add_card_controls(card, card->controls, card->num_controls);
snd_soc_add_component_controls
snd_soc_add_card_controls
snd_soc_add_dai_controls
```

snd_soc_add_component_controls

snd_soc_add_card_controls

snd_soc_add_dai_controls

codec注册方法

1、snd_soc_codec_driver结构体中的num_controls和controls。进行注册进去

2、snd_soc_add_codec_controls(codec, impedance_detect_controls,
				   ARRAY_SIZE(impedance_detect_controls));

machine注册方法

```c
static struct snd_soc_card byt_max98090_card = {
	.name = "byt-max98090",
	.owner = THIS_MODULE,
	.dai_link = byt_max98090_dais,//重点dai_link
	.num_links = ARRAY_SIZE(byt_max98090_dais),
	.dapm_widgets = byt_max98090_widgets,//重点dapm_widgets
	.num_dapm_widgets = ARRAY_SIZE(byt_max98090_widgets),
	.dapm_routes = byt_max98090_audio_map,//重点dapm_routes
	.num_dapm_routes = ARRAY_SIZE(byt_max98090_audio_map),
	.controls = byt_max98090_controls,//重点controls
	.num_controls = ARRAY_SIZE(byt_max98090_controls),
	.fully_routed = true,
};
ret_val = devm_snd_soc_register_card(&pdev->dev, &byt_max98090_card);

## machine设备实例化dai_link、dapm_widgets、dapm_routes、controls的方法。具体位置
devm_snd_soc_register_card() -> snd_soc_init_multicodec()
devm_snd_soc_register_card() -> snd_soc_instantiate_card() -> snd_soc_add_card_controls()
devm_snd_soc_register_card() -> snd_soc_instantiate_card() -> snd_soc_dapm_add_routes()
devm_snd_soc_register_card() -> snd_soc_instantiate_card() -> snd_soc_dapm_new_controls()
```


# DAPM Widgets注册方法。

platform注册方法

codec注册方法

1、snd_soc_codec_driver结构体中的num_controls和controls。进行注册进去

2、snd_soc_add_codec_controls(codec, impedance_detect_controls,
				   ARRAY_SIZE(impedance_detect_controls));

machine注册方法

		snd_soc_add_card_controls(card, card->controls, card->num_controls);

snd_soc_add_component_controls

snd_soc_add_card_controls

snd_soc_add_dai_controls




```c
struct snd_kcontrol_new {
	snd_ctl_elem_iface_t iface;	/* control类型，通常是SNDRV_CTL_ELEM_IFACE_MIXER  */
	unsigned int device;		/* device/client number */
	unsigned int subdevice;		/* subdevice (substream) number */
	const unsigned char *name;	/* kcontrol的名字，名字的命名规则遵循”源-方向-功能” */
	unsigned int index;		/* index of item */
	unsigned int access;		/* access rights */
	unsigned int count;		/* count of same elements */
	snd_kcontrol_info_t *info; //回调函数
	snd_kcontrol_get_t *get;   //回调函数
	snd_kcontrol_put_t *put;   //回调函数
	union {
		snd_kcontrol_tlv_rw_t *c;
		const unsigned int *p;
	} tlv;
	unsigned long private_value;
};
```

kcontrol与dapm kcontrol区别
 kcontrol通常用于控件的音量等控制，而dapm kcontrol相关的kcontrol则是用于widget电源管理的开关。

# SOC_SINGLE/SOC_SINGLE_RANGE

```c
#define SOC_SINGLE_VALUE(xreg, xshift, xmax, xinvert, xautodisable) \
	SOC_DOUBLE_VALUE(xreg, xshift, xshift, xmax, xinvert, xautodisable)

#define SOC_SINGLE(xname, reg, shift, max, invert) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.private_value = SOC_SINGLE_VALUE(reg, shift, max, invert, 0) }

#define SOC_SINGLE_RANGE(xname, xreg, xshift, xmin, xmax, xinvert) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw_range, .get = snd_soc_get_volsw_range, \
	.put = snd_soc_put_volsw_range, \
	.private_value = (unsigned long)&(struct soc_mixer_control) \
		{.reg = xreg, .rreg = xreg, .shift = xshift, \
		 .rshift = xshift,  .min = xmin, .max = xmax, \
		 .platform_max = xmax, .invert = xinvert} }
```

SOC_SINGLE定义最简单的控件，这种控件只有一个控制量，比如一个开关，或者是数值的变化(比如codec中的某个频率，FIFO大小等)
参数：xname(该控件的名字)，reg(该控件对应的寄存器的地址)，shift(控制位在寄存器中的位移)，max(控件可设置的最大值)，invert(设定值是否取反)

SOC_SINGLE_VALUE宏定义private_value字段，目的主要是为了填充struct soc_mixer_control结构体
当上层调用info, get, put函数的时候可以将kcontrol->private_value强制转换为struct soc_mixer_control类型，然后使用这个结构体中的reg, shift, max等数据。

# SOC_SINGLE_TLV

```c
#define SOC_SINGLE_VALUE(xreg, xshift, xmax, xinvert, xautodisable) \
	SOC_DOUBLE_VALUE(xreg, xshift, xshift, xmax, xinvert, xautodisable)

#define SOC_SINGLE_TLV(xname, reg, shift, max, invert, tlv_array) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ |\
		 SNDRV_CTL_ELEM_ACCESS_READWRITE,\
	.tlv.p = (tlv_array), \
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw,\
	.put = snd_soc_put_volsw, \
	.private_value = SOC_SINGLE_VALUE(reg, shift, max, invert, 0) }
```

该宏和SOC_SINGLE类似，唯一不同的是增加了tlv.p字段，适用于那些以dB为单位的kcontrol。

DECLARE_TLV_DB_SCALE(name, min, step, mute)宏来构造变量tlv_array。
参数name是变量的名字，min是最小值，step是步进值，如果mute=1，当该kcontrol处于最小值时会mute。
例子：

```c
/* from 0 to 30 dB in 2 dB steps */
static const DECLARE_TLV_DB_SCALE(digital_gain, 0, 1, 0);
static const struct snd_kcontrol_new msm_dig_snd_controls[] = {
    ................
    SOC_SINGLE_SX_TLV("RX1 Digital Volume",
                      MSM89XX_CDC_CORE_RX1_VOL_CTL_B2_CTL,
                      0, -84, 40, digital_gain),
    .................
}
//寄存器MSM89XX_CDC_CORE_RX1_VOL_CTL_B2_CTL的偏移3bit处定义了'RX1 Digital Volume'，寄存器最大值为40，对应到dB的最小值是，最小值为-84,对应的dB值为.步进值是1*0.01dB=0.01dB，最大值是8*0.25dB=2dB如上这样，寄存器的值与实际增益控制就有一个映射关系了。


static const DECLARE_TLV_DB_SCALE(analog_gain, 0, 25, 1);
//DECLARE_TLV_DB_SCALE宏定义的mixer control，它所代表的值按一个固定的dB值的步长变化。该宏的第一个参数是要定义变量的名字，第二个参数是最小值，以0.01dB为单位。第三个参数是变化的步长，也是以0.01dB为单位。如果该control处于最小值时会做出mute时，需要把第四个参数设为1。

static const struct snd_kcontrol_new msm_anlg_cdc_snd_controls[] = {

	SOC_SINGLE_TLV("ADC3 Volume", MSM89XX_PMIC_ANALOG_TX_3_EN, 3,
					8, 0, analog_gain),
};
ASUS_X01BD_1:/ # tinymix "RX1 Digital Volume"
RX1 Digital Volume: 84 (dsrange 0->124)
ASUS_X01BD_1:/ # tinymix 'ADC3 Volume'
ADC1 Volume: 4 (dsrange 0->8)
//寄存器MSM89XX_PMIC_ANALOG_TX_3_EN的偏移3bit处定义了'ADC3 Volume'，寄存器最大值为8，对应到dB的最小值是0dB，步进值是25*0.01dB=0.25dB，最大值是8*0.25dB=2dB如上这样，寄存器的值与实际增益控制就有一个映射关系了。
```

# SOC_ENUM

```c
/*cut of frequency for high pass filter*/
static const char * const cf_text[] = {
	"MIN_3DB_4Hz", "MIN_3DB_75Hz", "MIN_3DB_150Hz"
};
static const struct soc_enum cf_rxmix1_enum =
	SOC_ENUM_SINGLE(MSM89XX_CDC_CORE_RX1_B4_CTL, 0, 3, cf_text);
static const struct snd_kcontrol_new msm_dig_snd_controls[] = {
    ...
    SOC_ENUM("RX1 HPF cut off", cf_rxmix1_enum),
    ...
}
//通过SOC_ENUM(“RX1 HPF cut off”, cf_rxmix1_enum)定义了名为“RX1 HPF cut off”的mixer控件
//从SOC_ENUM_SINGLE(MSM89XX_CDC_CORE_RX1_B4_CTL, 0, 3, cf_text)看出通过配置寄存器MSM89XX_CDC_CORE_RX1_B4_CTL可以控制这个mixer控件的四个输入源”MIN_3DB_4Hz”, “MIN_3DB_75Hz”, “Minimum2”, “MIN_3DB_150Hz”，输入源可以选择其中的一个或者多个。
```

# SOC_ENUM_EXT

```c
static const char * const msm_anlg_cdc_boost_option_ctrl_text[] = {
		"BOOST_SWITCH", "BOOST_ALWAYS", "BYPASS_ALWAYS",
		"BOOST_ON_FOREVER"};
static const struct soc_enum msm_anlg_cdc_boost_option_ctl_enum[] = {
		SOC_ENUM_SINGLE_EXT(4, msm_anlg_cdc_boost_option_ctrl_text),
static const struct snd_kcontrol_new msm_anlg_cdc_snd_controls[] = {
	SOC_ENUM_EXT("Boost Option", msm_anlg_cdc_boost_option_ctl_enum[0],
		msm_anlg_cdc_boost_option_get, msm_anlg_cdc_boost_option_set),
};
SOC_ENUM_EXT与SOC_ENUM宏很类似，但是，SOC_ENUM中构造private_value字段使用SOC_ENUM_SINGLE或者SOC_ENUM_DOUBLE，这两个宏构造的时候都和具体寄存器的某个或者某两个bit相关，而SOC_ENUM_EXT中构造private_value字段使用SOC_ENUM_SINGLE_EXT，这个宏构造的时候只要初始化字符串数组就行了。
```



# SOC_DOUBLE

```c
#define SOC_DOUBLE(xname, reg, shift_left, shift_right, max, invert) \
{	.iface = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname),\
	.info = snd_soc_info_volsw, .get = snd_soc_get_volsw, \
	.put = snd_soc_put_volsw, \
	.private_value = SOC_DOUBLE_VALUE(reg, shift_left, shift_right, \
					  max, invert, 0) }
```



# 专用名词

| 名词   | 含义                                        |
| ------ | ------------------------------------------- |
| MIXER  | 意味着多种输入：每个人都可以通电和断电      |
| MUX    | 一次意味着一个输入：您只能为MUX选择一个输入 |
| SWITCH | 开/关                                       |
