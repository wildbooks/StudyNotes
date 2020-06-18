# widget讲解

# widget创建方式

platform:

codec:

方式一：

snd_soc_register_codec();该方法会把snd_soc_codec_driver中的controls、dapm_widgets、dapm_routes链接到codec->component。虽然没有显示的调用`snd_soc_dapm_new_controls()`和`snd_soc_dapm_add_routes()`注册dapm widgets和dapm route，但是创建声卡时会通过该`snd_soc_register_card()`函数中的某个函数调用`snd_soc_dapm_new_controls()`和`snd_soc_dapm_add_routes()`
方式二

```
snd_soc_add_codec_controls
snd_soc_dapm_new_controls
```

machine:



|              | platform                        | codec                                                     | machine                                                 |
| ------------ | ------------------------------- | --------------------------------------------------------- | ------------------------------------------------------- |
| kcontrol     | snd_soc_add_platform_controls() | `snd_soc_register_codec()`/`snd_soc_add_codec_controls()` | `snd_soc_register_card()`/`snd_soc_add_card_controls()` |
| dapm widgets |                                 | `snd_soc_register_codec()`/`snd_soc_dapm_new_widgets()`   | `snd_soc_register_card()`                               |
| dapm route   |                                 | `snd_soc_register_codec()`/snd_soc_dapm_add_routes()      | `snd_soc_register_card()`/snd_soc_dapm_add_routes()     |
|              |                                 |                                                           |                                                         |





# routes

platform:

codec:

方式一：

snd_soc_register_codec();该方法会把snd_soc_codec_driver中的controls、dapm_widgets、dapm_routes链接到codec->component。

方式一虽然没有显示的调用snd_soc_dapm_new_controls和snd_soc_dapm_add_routes注册dapm widgets和dapm route，但是在将struct snd_soc_codec_driver注册到asoc core里的时候会通过这两个函数注册。
方式二

```
snd_soc_dapm_add_routes
```

machine:

# mux

MUX只能从多个输入里选择一个作为输出。主要讲解mux类型创建

```c
static const char * const rdac2_mux_text[] = {
	"ZERO", "RX2", "RX1"
};

static const struct soc_enum rdac2_mux_enum =
	SOC_ENUM_SINGLE(MSM89XX_PMIC_DIGITAL_CDC_CONN_HPHR_DAC_CTL,
		0, 3, rdac2_mux_text);

static const struct snd_kcontrol_new rdac2_mux =
	SOC_DAPM_ENUM("RDAC2 MUX Mux", rdac2_mux_enum);

static const struct snd_soc_dapm_widget msm_anlg_cdc_dapm_widgets[] = {
    ...
    SND_SOC_DAPM_MUX("RDAC2 MUX", SND_SOC_NOPM, 0, 0, &rdac2_mux),
    ...
}
static struct snd_soc_codec_driver soc_codec_dev_sdm660_cdc = {
	.probe	= msm_anlg_cdc_soc_probe,
	.remove	= msm_anlg_cdc_soc_remove,
	.suspend = msm_anlg_cdc_suspend,
	.resume = msm_anlg_cdc_resume,
	.reg_word_size = 1,
	.controls = msm_anlg_cdc_snd_controls,
	.num_controls = ARRAY_SIZE(msm_anlg_cdc_snd_controls),
	.dapm_widgets = msm_anlg_cdc_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(msm_anlg_cdc_dapm_widgets),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.get_regmap = msm_anlg_get_regmap,
};
```





# mixer

mixer可以混合多个输入到输出



# dapm widget链表更新

有几个操作和dapm widget链表更新相关
1) 初始化的时候，snd_soc_instantiate_card里调用snd_soc_dapm_new_widgets，最终会调用dapm_power_widgets
2) 在用户空间通过tinymix设置路径，在SOC_DAPM_ENUM中的put或者get函数最终会调用dapm_power_widgets
3) 在用户空间通过tinyplay播放或者录音是的soc_pcm_prepare和soc_pcm_close，最终会调用dapm_power_widgets

以上3个地方最终会引发dapm widget链表的更新，都会调用一个很关键的函数dapm_power_widgets

