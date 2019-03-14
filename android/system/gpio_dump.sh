# 上下拉
#  输入/输出
#
# GPIO(0):EN(), DIR(IN), PULL(NO), DRV(12ma), VAL(HIGH)
# GPIO(1):EN(), DIR(IN), PULL(NO), DRV(12ma), VAL(HIGH)


#TLMM_GPIO_CFGn
# DRV= (val >> 6) & 0x7
# PULL=val & 0x3

# TLMM_GPIO_IN_OUTn
# DIR=val

TLMM_GPIO_INTR_CFGn
TLMM_GPIO_INTR_STATUSn

/system/bin/r 0x1013000-0x101300C
