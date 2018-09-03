# 参考文档
   Linux Android PMIC GPIO Software(80-P9301-88 Rev. E)
# pmic
## GPIO XBL
    /boot_images/QcomPkg/Include/api/pmic/pm/pm_gpio.h
    /boot_images/QcomPkg/Library/PmicLib/drivers/gpio/src/pm_gpio.c
    /boot_images/QcomPkg/Library/PmicLib/drivers/gpio/src/pm_gpio_driver.c
## GPIO UEFI
    \boot_images\QcomPkg\Include\Protocol\EFIPmicGpio.h
    \boot_images\QcomPkg\Drivers\PmicDxe\PmicGpioProtocol.c
## GPIO HLOS
    /Documentation/devicetree/bindings/pinctrl/qcom,pmic-gpio.txt
    /kernel/include/dt-bindings/pinctrl/qcom,pmic-gpio.h
    /kernel/arch/arm64/boot/dts/qcom/pmi8998.dtsi
    /kernel/arch/arm64/boot/dts/qcom/pm8998.dtsi
    /kernel/arch/arm64/boot/dts/qcom/pm8005.dtsi
    /kernel/arch/arm64/boot/dts/qcom/sdm845-pinctrl.dtsi
    /kernel/arch/arm64/boot/dts/qcom/sdm845-pinctrl-overlay.dtsi
    /kernel/drivers/pinctrl/qcom/pinctrl-spmi-gpio.c
