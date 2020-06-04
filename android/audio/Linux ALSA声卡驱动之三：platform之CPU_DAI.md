



4、cpu -> cpu dai -> codec -> codec dai

注册函数

# snd_soc_register_component()

cpu_dai注册

```c
//devm_snd_soc_register_component() ->snd_soc_register_component()
int snd_soc_register_component(struct device *dev,
			       const struct snd_soc_component_driver *cmpnt_drv,
			       struct snd_soc_dai_driver *dai_drv,
			       int num_dai)
{
	struct snd_soc_component *cmpnt;
	int ret;

	cmpnt = kzalloc(sizeof(*cmpnt), GFP_KERNEL);
	if (!cmpnt) {
		dev_err(dev, "ASoC: Failed to allocate memory\n");
		return -ENOMEM;
	}

	ret = snd_soc_component_initialize(cmpnt, cmpnt_drv, dev);
	if (ret)
		goto err_free;

	cmpnt->ignore_pmdown_time = true;
	cmpnt->registered_as_component = true;

	ret = snd_soc_register_dais(cmpnt, dai_drv, num_dai, true);
	if (ret < 0) {
		dev_err(dev, "ASoC: Failed to register DAIs: %d\n", ret);
		goto err_cleanup;
	}

	snd_soc_component_add(cmpnt);

	return 0;

err_cleanup:
	snd_soc_component_cleanup(cmpnt);
err_free:
	kfree(cmpnt);
	return ret;
}
```



# snd_soc_add_platform_controls()

platform层中添加controls，通过snd_soc_add_platform_controls()函数

snd_soc_add_platform_controls

```c
static const struct snd_kcontrol_new lsm_controls[] = {
	/* kcontrol of lsm_function */
	SOC_ENUM_EXT(SLIMBUS_0_TX_TEXT" "LSM_FUNCTION_TEXT, lsm_func_enum,
		     msm_routing_lsm_func_get, msm_routing_lsm_func_put),
    ...
	/* kcontrol of lsm_port */
	SOC_ENUM_EXT("LSM1 Port", lsm_port_enum,
			  msm_routing_lsm_port_get,
			  msm_routing_lsm_port_put),
    ...
};

static int msm_routing_probe(struct snd_soc_platform *platform)
{
    ...
	snd_soc_add_platform_controls(platform, lsm_controls,
                                  ARRAY_SIZE(lsm_controls));
    ...
}
```

# snd_soc_add_platform_controls

函数作用：根据给定controls模板，创建controls实例，并把controls实例添加到platform->component->card->snd_card声卡中。

```c
//snd_soc_add_platform_controls() -> snd_soc_add_component_controls() -> snd_soc_add_controls()
//&platform->component->card->snd_card	== card
//&platform->component->dev == dev
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

