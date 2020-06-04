# Platform驱动在ASoC中的作用

   ASoC被分为Machine，Platform和Codec三大部件，Platform驱动的主要作用是完成音频数据的管理，最终通过CPU的数字音频接口（DAI）把音频数据传送给Codec进行处理，最终由Codec输出驱动耳机或者是喇叭的音信信号。在具体实现上，ASoC有把Platform驱动分为两个部分：snd_soc_platform_driver和snd_soc_dai_driver。其中，platform_driver负责管理音频数据，把音频数据通过dma或其他操作传送至cpu dai中，dai_driver则主要完成cpu一侧的dai的参数配置，同时也会通过一定的途径把必要的dma等参数与snd_soc_platform_driver进行交互

ASoC平台驱动程序类别可以分为`音频DMA驱动程序`，`SoC DAI驱动程序`和`DSP驱动程序`。平台驱动程序仅针对SoC CPU，并且不得具有电路板特定的代码。

# platform驱动注册

本文以高通msm-pcm-voice-v2.c驱动为例进行讲解。该驱动程序抓要完成三个驱动程序注册。

> `音频DMA驱动程序`:平台DMA驱动程序主要通过结构体**snd_pcm_ops**完成注册。
>
> `SoC DAI驱动程序`:
>
> `DSP驱动程序`:



snd_soc_register_platform



```c
/ **
  * snd_soc_register_platform-向ASoC内核注册平台
  *
  * @dev：用于平台的设备
  * @platform_drv：平台的驱动程序
  * /
  int snd_soc_register_platform(struct device *dev,
		const struct snd_soc_platform_driver *platform_drv)
```

# 注册流程

```c
rc = snd_soc_register_platform(&pdev->dev,
				       &msm_soc_platform);

->
static struct snd_soc_platform_driver msm_soc_platform = {
	.ops		= &msm_pcm_ops, //音频DMA驱动程序，主要是pcm相关操作方法
	.pcm_new	= msm_asoc_pcm_new,
	.probe		= msm_pcm_voice_probe,//完成snd_kcontrol_new注册
};

//驱动层的open、close、ioctll相关方法的具体实现。
static struct snd_pcm_ops msm_pcm_ops = {
	.open			= msm_pcm_open,
	.hw_params		= msm_pcm_hw_params, //硬件参数配置。比如dma配置
	.close			= msm_pcm_close,
	.prepare		= msm_pcm_prepare,
	.trigger		= msm_pcm_trigger,
	.ioctl			= msm_pcm_ioctl,
	.compat_ioctl		= msm_pcm_ioctl,
};

-> 完成snd_kcontrol_new的注册
static int msm_pcm_voice_probe(struct snd_soc_platform *platform)
{
	snd_soc_add_platform_controls(platform, msm_voice_controls,
					ARRAY_SIZE(msm_voice_controls));

	return 0;
}

struct platform_device {
	const char	*name; //  平台设备的名字
	int		id; //   ID 是用来区分如果设备名字相同的时候(通过在后面添加一个数字来代表不同的设备，因为有时候有这种需求)
	bool		id_auto;
	struct device	dev; //   内置的device结构体
	u32		num_resources; //   资源结构体数量
	struct resource	*resource;

	const struct platform_device_id	*id_entry; //用来进行与设备驱动匹配用的id_table表
	char *driver_override; /* Driver name to force a match */

	/* MFD cell pointer */
	struct mfd_cell *mfd_cell;

	/* arch specific additions */
	struct pdev_archdata	archdata;
};
```

# snd_soc_register_platform()

该函数主要完成以下功能

> 1. 把platform_drv->component_driver中的controls、dapm_widgets、dapm_routes注册到平台设备组件上(platform->component)
> 2. 把驱动中(platform_drv)的probe/remove函数注册到平台设备组件上(platform->component)
> 3. 平台设备的组件注册到component_list链表中
> 4. 平台设备注册到platform_list链表中

```c
// snd_soc_register_platform() -> snd_soc_add_platform()
int snd_soc_add_platform(struct device *dev, struct snd_soc_platform *platform,
		const struct snd_soc_platform_driver *platform_drv)
{
	int ret;

    //把platform_drv->component_driver中的controls、dapm_widgets、dapm_routes注册到平台设备组件上(platform->component)
	ret = snd_soc_component_initialize(&platform->component,
			&platform_drv->component_driver, dev); //重点
	if (ret)
		return ret;

	platform->dev = dev;
	platform->driver = platform_drv;

    //把驱动中(platform_drv)的probe/remove函数注册到平台设备组件上(platform->component)
	if (platform_drv->probe)
		platform->component.probe = snd_soc_platform_drv_probe;
	if (platform_drv->remove)
		platform->component.remove = snd_soc_platform_drv_remove;

#ifdef CONFIG_DEBUG_FS
	platform->component.debugfs_prefix = "platform";
#endif

	mutex_lock(&client_mutex);
    //平台设备的组件注册到component_list链表中
	snd_soc_component_add_unlocked(&platform->component);
      //平台设备注册到platform_list链表中
	list_add(&platform->list, &platform_list);
	mutex_unlock(&client_mutex);

	dev_dbg(dev, "ASoC: Registered platform '%s'\n",
		platform->component.name);

	return 0;
}
EXPORT_SYMBOL_GPL(snd_soc_add_platform);
```

## SoC DAI驱动程序

每个SoC DAI驱动程序必须提供以下功能：

1. 数字音频接口（DAI）说明
2. 数字音频接口配置
3. PCM的描述
4. SYSCLK配置
5. 暂停和继续（可选）

有关项目1-4的描述，请参见codec.rst。

## SoC DSP驱动程序

每个SoC DSP驱动程序通常提供以下功能：

1. DAPM图
2. 混音器控件
3. 与DSP缓冲区之间的DMA IO（如果适用）
4. DSP前端（FE）PCM设备的定义。

请参阅DPCM.txt以获取对项目4的描述。