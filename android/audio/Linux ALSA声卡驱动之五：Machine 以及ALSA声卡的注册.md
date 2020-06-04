# Linux ALSA声卡驱动之七：声卡的创建

# 一、Machine 简介

   Machine 是指某一款机器，可以是某款设备，某款开发板，又或者是某款智能手机，由此可以看出Machine几乎是不可重用的，每个Machine上的硬件实现可能都不一样，CPU不一样，Codec不一样，音频的输入、输出设备也不一样，Machine为CPU、Codec、输入输出设备提供了一个载体，用于描述一块电路板, 它指明此块电路板上用的是哪个Platform和哪个Codec, 由电路板商负责编写此部分代码。绑定platform driver和codec driver

ASoC的一切都从Machine驱动开始，包括声卡的注册，绑定Platform和Codec驱动等等

ASoC机器（或板）驱动程序是将所有组件驱动程序（例如，编解码器，平台和DAI）粘合在一起的代码。它还描述了每个组件之间的关系，包括音频路径，GPIO，中断，时钟，插孔和稳压器。

机器驱动程序可以包含编解码器和平台特定的代码。它使用内核将音频子系统注册为平台设备，并由以下结构表示：




# 二、Machine以及声卡驱动的注册

## 2.1 machine驱动注册的时序图

本文以高通平台进行讲解sdm660-common.c，machine 驱动注册从msm_asoc_machine_probe 调用 devm_snd_soc_register_card ，而devm_snd_soc_register_card 会调用snd_soc_register_card 。声卡驱动的起始是在soc-core.c  soc_probe函数的调用  soc_probe函数最终也会调用snd_soc_register_card。因此后续在讲解声卡驱动的注册，我们就从snd_soc_register_card 函数开始。

```c
//资源管理卡注册函数
/ **
  * devm_snd_soc_register_card-资源管理卡注册
  * @dev：用于管理卡的设备
  * @card：要注册的卡
  *
  *当注销设备时，请使用自动注销注册卡。
devm_snd_soc_register_card()
```

```c
static struct snd_soc_card byt_max98090_card = {
	.name = "byt-max98090",
	.owner = THIS_MODULE,
	.dai_link = byt_max98090_dais,//重点dai_link
	.num_links = ARRAY_SIZE(byt_max98090_dais),
	.dapm_widgets = byt_max98090_widgets,//重点dapm_widgets
	.num_dapm_widgets = ARRAY_SIZE(byt_max98090_widgets),
	.dapm_routes = byt_max98090_audio_map,//重点dapm_routes 机器驱动程序可以选择扩展编解码器电源图，并成为音频子系统的音频电源图。这样可以自动打开/关闭扬声器/ HP放大器等的电源。在机器初始化功能中，可以将编解码器引脚连接到机器的插孔。
	.num_dapm_routes = ARRAY_SIZE(byt_max98090_audio_map),
	.controls = byt_max98090_controls,//重点controls 可以将机器特定的音频混音器控件添加到DAI初始化功能中。
	.num_controls = ARRAY_SIZE(byt_max98090_controls),
	.fully_routed = true,
};
ret_val = devm_snd_soc_register_card(&pdev->dev, &byt_max98090_card);
```

## 机器DAI配置

机器DAI配置将所有编解码器和CPU DAI粘合在一起。它也可以用于设置DAI系统时钟，并且对于任何与机器相关的DAI初始化，例如可以将机器音频映射表连接至编解码器音频映射表，可以将未连接的编解码器引脚设置为此类。

struct snd_soc_dai_link用于设置计算机中的每个DAI。例如

```c
/* corgi digital audio interface glue - connects codec <--> CPU */
static struct snd_soc_dai_link corgi_dai = {
      .name = "WM8731",
      .stream_name = "WM8731",
      .cpu_dai_name = "pxa-is2-dai",
      .codec_dai_name = "wm8731-hifi",
      .platform_name = "pxa-pcm-audio",
      .codec_name = "wm8713-codec.0-001a",
      .init = corgi_wm8731_init,
      .ops = &corgi_ops,
};
```

然后，struct snd_soc_card用其DAI设置计算机。例如

```c
/* corgi audio machine driver */
static struct snd_soc_card snd_soc_corgi = {
      .name = "Corgi",
      .dai_link = &corgi_dai,
      .num_links = 1,
};
```

## devm_snd_soc_register_card函数讲解

devm_snd_soc_register_card会调用snd_soc_register_card()函数，该函数主要完成以下工作



```c
int snd_soc_register_card(struct snd_soc_card *card)
{
	int i, j, ret;

	if (!card->name || !card->dev)
		return -EINVAL;

	for (i = 0; i < card->num_links; i++) {
		struct snd_soc_dai_link *link = &card->dai_link[i];

		ret = snd_soc_init_multicodec(card, link);
		if (ret) {
			dev_err(card->dev, "ASoC: failed to init multicodec\n");
			return ret;
		}

		for (j = 0; j < link->num_codecs; j++) {
			/*
			 * Codec must be specified by 1 of name or OF node,
			 * not both or neither.
			 */
			if (!!link->codecs[j].name ==
			    !!link->codecs[j].of_node) {
				dev_err(card->dev, "ASoC: Neither/both codec name/of_node are set for %s\n",
					link->name);
				return -EINVAL;
			}
			/* Codec DAI name must be specified */
			if (!link->codecs[j].dai_name) {
				dev_err(card->dev, "ASoC: codec_dai_name not set for %s\n",
					link->name);
				return -EINVAL;
			}
		}

		/*
		 * Platform may be specified by either name or OF node, but
		 * can be left unspecified, and a dummy platform will be used.
		 */
		if (link->platform_name && link->platform_of_node) {
			dev_err(card->dev,
				"ASoC: Both platform name/of_node are set for %s\n",
				link->name);
			return -EINVAL;
		}

		/*
		 * CPU device may be specified by either name or OF node, but
		 * can be left unspecified, and will be matched based on DAI
		 * name alone..
		 */
		if (link->cpu_name && link->cpu_of_node) {
			dev_err(card->dev,
				"ASoC: Neither/both cpu name/of_node are set for %s\n",
				link->name);
			return -EINVAL;
		}
		/*
		 * At least one of CPU DAI name or CPU device name/node must be
		 * specified
		 */
		if (!link->cpu_dai_name &&
		    !(link->cpu_name || link->cpu_of_node)) {
			dev_err(card->dev,
				"ASoC: Neither cpu_dai_name nor cpu_name/of_node are set for %s\n",
				link->name);
			return -EINVAL;
		}
	}

	dev_set_drvdata(card->dev, card);
	//初始化链表codec_dev_list、widgets、paths、dapm_list
	snd_soc_initialize_card_lists(card);

	card->rtd = devm_kzalloc(card->dev,
				 sizeof(struct snd_soc_pcm_runtime) *
				 (card->num_links + card->num_aux_devs),
				 GFP_KERNEL);
	if (card->rtd == NULL)
		return -ENOMEM;
	card->num_rtd = 0;
	card->rtd_aux = &card->rtd[card->num_links];

	for (i = 0; i < card->num_links; i++) {
		card->rtd[i].card = card;
		card->rtd[i].dai_link = &card->dai_link[i];
		card->rtd[i].codec_dais = devm_kzalloc(card->dev,
					sizeof(struct snd_soc_dai *) *
					(card->rtd[i].dai_link->num_codecs),
					GFP_KERNEL);
		if (card->rtd[i].codec_dais == NULL)
			return -ENOMEM;
	}

	for (i = 0; i < card->num_aux_devs; i++)
		card->rtd_aux[i].card = card;

	INIT_LIST_HEAD(&card->dapm_dirty);
	INIT_LIST_HEAD(&card->dobj_list);
	card->instantiated = 0;
	mutex_init(&card->mutex);
	mutex_init(&card->dapm_mutex);
	mutex_init(&card->dapm_power_mutex);

    //snd_soc_instantiate_card()函数功能很重要，
    //1、绑定cpu_dai   、codec_dai  platform 到rtd中，具体是由soc_bind_dai_link函数实现，到现在我们之前分析代码都关联一起了
	//2、创建声卡结构体 创建control设备
	//3、创建一些文件系统
	//4、执行cpu_dai probe ,codes     probe 以及platform   probe 函数
	//5、创建pcm设备
	//6、声卡注册
	ret = snd_soc_instantiate_card(card);
	if (ret != 0)
		return ret;

	/* deactivate pins to sleep state */
	for (i = 0; i < card->num_rtd; i++) {
		struct snd_soc_pcm_runtime *rtd = &card->rtd[i];
		struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
		int j;

		for (j = 0; j < rtd->num_codecs; j++) {
			struct snd_soc_dai *codec_dai = rtd->codec_dais[j];
			if (!codec_dai->active)
				pinctrl_pm_select_sleep_state(codec_dai->dev);
		}

		if (!cpu_dai->active)
			pinctrl_pm_select_sleep_state(cpu_dai->dev);
	}

	return ret;
}
EXPORT_SYMBOL_GPL(snd_soc_register_card);
```

```c
static int snd_soc_instantiate_card(struct snd_soc_card *card)
{
	struct snd_soc_codec *codec;
	int ret, i, order;

	mutex_lock(&client_mutex);
	mutex_lock_nested(&card->mutex, SND_SOC_CARD_CLASS_INIT);

    //1、绑定cpu_dai   、codec_dai  platform 到rtd中，具体是由soc_bind_dai_link函数实现，到现在我们之前分析代码都关联一起了
    //绑定cpu_dai   、codec_dai 、codec和 platform 到rtd中
	/* bind DAIs */
	for (i = 0; i < card->num_links; i++) {
		ret = soc_bind_dai_link(card, i);
		if (ret != 0)
			goto base_error;
	}

    //绑定aux设备
	/* bind aux_devs too */
	for (i = 0; i < card->num_aux_devs; i++) {
		ret = soc_bind_aux_dev(card, i);
		if (ret != 0)
			goto base_error;
	}

    //为每个可用的编解码器初始化寄存器缓存
	/* initialize the register cache for each available codec */
	list_for_each_entry(codec, &codec_list, list) {
		if (codec->cache_init)
			continue;
		ret = snd_soc_init_codec_cache(codec);
		if (ret < 0)
			goto base_error;
	}

    //创建声卡结构体 创建control链表
	/* card bind complete so register a sound card */
	ret = snd_card_new(card->dev, SNDRV_DEFAULT_IDX1, SNDRV_DEFAULT_STR1,
			card->owner, 0, &card->snd_card);
	if (ret < 0) {
		dev_err(card->dev,
			"ASoC: can't create sound card for card %s: %d\n",
			card->name, ret);
		goto base_error;
	}

    //创建一些文件系统
	soc_init_card_debugfs(card);

	card->dapm.bias_level = SND_SOC_BIAS_OFF;
	card->dapm.dev = card->dev;
	card->dapm.card = card;
	list_add(&card->dapm.list, &card->dapm_list);

#ifdef CONFIG_DEBUG_FS
	snd_soc_dapm_debugfs_init(&card->dapm, card->debugfs_card_root);
#endif

#ifdef CONFIG_PM_SLEEP
	/* deferred resume work */
	INIT_WORK(&card->deferred_resume_work, soc_resume_deferred);
#endif

    //创建widgets
	if (card->dapm_widgets)
		snd_soc_dapm_new_controls(&card->dapm, card->dapm_widgets,
					  card->num_dapm_widgets);

	if (card->of_dapm_widgets)
		snd_soc_dapm_new_controls(&card->dapm, card->of_dapm_widgets,
					  card->num_of_dapm_widgets);

    //1次声卡初始化
	/* initialise the sound card only once */
	if (card->probe) {
		ret = card->probe(card);
		if (ret < 0)
			goto card_probe_error;
	}

    //配置此卡上cpu_dai、codec_dai、platform上的所有组件
	/* probe all components used by DAI links on this card */
	for (order = SND_SOC_COMP_ORDER_FIRST; order <= SND_SOC_COMP_ORDER_LAST;
			order++) {
		for (i = 0; i < card->num_links; i++) {
			ret = soc_probe_link_components(card, i, order);
			if (ret < 0) {
				dev_err(card->dev,
					"ASoC: failed to instantiate card %d\n",
					ret);
				goto probe_dai_err;
			}
		}
	}

    / *配置此卡上的所有DAI链接* /
	/* probe all DAI links on this card */
	for (order = SND_SOC_COMP_ORDER_FIRST; order <= SND_SOC_COMP_ORDER_LAST;
			order++) {
		for (i = 0; i < card->num_links; i++) {
			ret = soc_probe_link_dais(card, i, order);
			if (ret < 0) {
				dev_err(card->dev,
					"ASoC: failed to instantiate card %d\n",
					ret);
				goto probe_dai_err;
			}
		}
	}

	for (i = 0; i < card->num_aux_devs; i++) {
		ret = soc_probe_aux_dev(card, i);
		if (ret < 0) {
			dev_err(card->dev,
				"ASoC: failed to add auxiliary devices %d\n",
				ret);
			goto probe_aux_dev_err;
		}
	}

    //链接
	snd_soc_dapm_link_dai_widgets(card);
	snd_soc_dapm_connect_dai_link_widgets(card);

    //向SoC卡添加一系列控件controls。
	if (card->controls)
		snd_soc_add_card_controls(card, card->controls, card->num_controls);

    //向SoC卡添加一系列控件dapm_routes。
	if (card->dapm_routes)
		snd_soc_dapm_add_routes(&card->dapm, card->dapm_routes,
					card->num_dapm_routes);

	if (card->of_dapm_routes)
		snd_soc_dapm_add_routes(&card->dapm, card->of_dapm_routes,
					card->num_of_dapm_routes);

	snprintf(card->snd_card->shortname, sizeof(card->snd_card->shortname),
		 "%s", card->name);
	snprintf(card->snd_card->longname, sizeof(card->snd_card->longname),
		 "%s", card->long_name ? card->long_name : card->name);
	snprintf(card->snd_card->driver, sizeof(card->snd_card->driver),
		 "%s", card->driver_name ? card->driver_name : card->name);
	for (i = 0; i < ARRAY_SIZE(card->snd_card->driver); i++) {
		switch (card->snd_card->driver[i]) {
		case '_':
		case '-':
		case '\0':
			break;
		default:
			if (!isalnum(card->snd_card->driver[i]))
				card->snd_card->driver[i] = '_';
			break;
		}
	}

	if (card->late_probe) {
		ret = card->late_probe(card);
		if (ret < 0) {
			dev_err(card->dev, "ASoC: %s late_probe() failed: %d\n",
				card->name, ret);
			goto probe_aux_dev_err;
		}
	}

	snd_soc_dapm_new_widgets(card);

    //声卡注册
	ret = snd_card_register(card->snd_card);
	if (ret < 0) {
		dev_err(card->dev, "ASoC: failed to register soundcard %d\n",
				ret);
		goto probe_aux_dev_err;
	}

	card->instantiated = 1;
	dapm_mark_endpoints_dirty(card);
	snd_soc_dapm_sync(&card->dapm);
	mutex_unlock(&card->mutex);
	mutex_unlock(&client_mutex);

	return 0;

probe_aux_dev_err:
	for (i = 0; i < card->num_aux_devs; i++)
		soc_remove_aux_dev(card, i);

probe_dai_err:
	soc_remove_dai_links(card);

card_probe_error:
	if (card->remove)
		card->remove(card);

	snd_soc_dapm_free(&card->dapm);
	soc_cleanup_card_debugfs(card);
	snd_card_free(card->snd_card);

base_error:
	mutex_unlock(&card->mutex);
	mutex_unlock(&client_mutex);

	return ret;
}

```



sdm660-common.c

# 声卡注册主要

```c
struct snd_soc_card {
	const char *name;
	const char *long_name;
	const char *driver_name;
	struct device *dev;
	struct snd_card *snd_card;
	struct module *owner;

	struct mutex mutex;
	struct mutex dapm_mutex;
	struct mutex dapm_power_mutex;

	bool instantiated;

	int (*probe)(struct snd_soc_card *card);
	int (*late_probe)(struct snd_soc_card *card);
	int (*remove)(struct snd_soc_card *card);

	/* the pre and post PM functions are used to do any PM work before and
	 * after the codec and DAI's do any PM work. */
	int (*suspend_pre)(struct snd_soc_card *card);
	int (*suspend_post)(struct snd_soc_card *card);
	int (*resume_pre)(struct snd_soc_card *card);
	int (*resume_post)(struct snd_soc_card *card);

	/* callbacks */
	int (*set_bias_level)(struct snd_soc_card *,
			      struct snd_soc_dapm_context *dapm,
			      enum snd_soc_bias_level level);
	int (*set_bias_level_post)(struct snd_soc_card *,
				   struct snd_soc_dapm_context *dapm,
				   enum snd_soc_bias_level level);

	long pmdown_time;

	/* CPU <--> Codec DAI links  */
	struct snd_soc_dai_link *dai_link; //重点，数字音频接口链路。指定了Platform、Codec、codec_dai、cpu_dai的名字。稍后Machine驱动将会利用这些名字去匹配已经在系统中注册的platform，codec，dai，这些注册的部件都是在另外相应的Platform驱动和Codec驱动的代码文件中定义的。
	int num_links;
	struct snd_soc_pcm_runtime *rtd;
	int num_rtd;

	/* optional codec specific configuration */
	struct snd_soc_codec_conf *codec_conf;
	int num_configs;

	/*
	 * optional auxiliary devices such as amplifiers or codecs with DAI
	 * link unused
	 */
	struct snd_soc_aux_dev *aux_dev; 		//aux接口类型设备
	int num_aux_devs;
	struct snd_soc_pcm_runtime *rtd_aux;
	int num_aux_rtd;

	const struct snd_kcontrol_new *controls; //重点
	int num_controls;

	/*
	 * Card-specific routes and widgets.
	 * Note: of_dapm_xxx for Device Tree; Otherwise for driver build-in.
	 */
	const struct snd_soc_dapm_widget *dapm_widgets;	 //重点
	int num_dapm_widgets;
	const struct snd_soc_dapm_route *dapm_routes;	 //重点
	int num_dapm_routes;
	const struct snd_soc_dapm_widget *of_dapm_widgets;  //重点
	int num_of_dapm_widgets;
	const struct snd_soc_dapm_route *of_dapm_routes;    //重点
	int num_of_dapm_routes;
	bool fully_routed;

	struct work_struct deferred_resume_work;

	/* lists of probed devices belonging to this card */
	struct list_head codec_dev_list;

	struct list_head widgets;
	struct list_head paths;
	struct list_head dapm_list;
	struct list_head dapm_dirty;

	/* attached dynamic objects */
	struct list_head dobj_list;

	/* Generic DAPM context for the card */
	struct snd_soc_dapm_context dapm;
	struct snd_soc_dapm_stats dapm_stats;
	struct snd_soc_dapm_update *update;

#ifdef CONFIG_DEBUG_FS
	struct dentry *debugfs_card_root;
	struct dentry *debugfs_pop_time;
#endif
	u32 pop_time;

	void *drvdata;
};
```



