# 代码
    Documentation/devicetree/bindings/regulator/rpmh-regulator.txt
    arch/arm64/boot/dts/qcom/sdm670-regulator.dtsi
    drivers/regulator/rpmh-regulator.c
# regulator的get/put接口
    regulator_get / regulator_put               正常的get,非独占、可重复
    devm_regulator_get / devm_regulator_put     正常的get,非独占、可重复
    regulator_get_exclusive                     独占的get,独占、不可重复
    devm_regulator_get_exclusive
    regulator_get_optional                      optional的get，非独占、不可重复get
    devm_regulator_get_optional
    调试节点：/d/regulator/
# regulator别名相关接口
    regulator_register_supply_alias
    regulator_unregister_supply_alias
    devm_regulator_register_supply_alias
    devm_regulator_unregister_supply_alias
    devm_regulator_bulk_register_supply_alias
# regulator的控制、状态获取接口
    regulator_enable/regulator_disable  开启/关闭电源
    regulator_force_disable             强制关闭电源
    regulator_is_enabled                判断电源是否开启
    regulator_disable_deferred          延时一段时间后关闭电源
    regulator_can_change_voltage
    regulator_count_voltages            返回电源使用次数
    regulator_list_voltage              返回能被设置的电压
    regulator_is_supported_voltage      检测是否支持该电压范围
    regulator_get_linear_step
    regulator_set_voltage               设置电压范围
    regulator_get_voltage               获取电压
    regulator_set_current_limit         设置电源输出电流限制
    regulator_get_current_limit         获取电源输出电流限制
    regulator_set_mode                  设置模式
    regulator_get_mode
    rdev_get_drvdata                    设置/获取driver的私有数据
    regulator_get_drvdata
    regulator_set_drvdata

