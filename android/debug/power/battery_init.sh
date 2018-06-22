#!/system/bin/sh
####################################################
#
#   1.  init for log
#       adb push battery_init.sh /sdcard/
#       adb push battery.sh /sdcard/
#       adb shell sh /sdcard/battery_init.sh
#
#   2.  get log
#       adb push battery.sh /sdcard/ && adb shell sh /sdcard/battery.sh
####################################################

#####################################
## Environment Variables
#####################################
LOGHOME="/sdcard/logs_home"
SLEEPTIME=5

#####################################
## logs home
#####################################
DATALOGHOME=$LOGHOME/`date +%Y%m%d-%T`
OLDLOGHOME=$LOGHOME/old
if [ ! -d $LOGHOME ]; then
    mkdir -p $OLDLOGHOME
else
    mv $LOGHOME/[0-9]*  $OLDLOGHOME     #backup
fi
mkdir -p $DATALOGHOME


setprop persist.alarm.debug 1
echo "8" > /proc/sys/kernel/printk
#echo 'file phy-msm-usb.c +p' > /sys/kernel/debug/dynamic_debug/control
#echo 'file ehci-hcd.c +p' > /sys/kernel/debug/dynamic_debug/control
#echo 'file ehci-msm.c +p' > /sys/kernel/debug/dynamic_debug/control
#echo 'file hub.c +p' > /sys/kernel/debug/dynamic_debug/control
#echo 'file qpnp-vm-bms.c +p' > /sys/kernel/debug/dynamic_debug/control
#echo 'file qpnp-linear-charger.c +p' > /sys/kernel/debug/dynamic_debug/control


#####################################
##   kernel debug mask
#####################################
echo 1 > /sys/kernel/debug/clk/debug_suspend                    #enable clk log
echo 1 > /sys/module/msm_show_resume_irq/parameters/debug_mask  #唤醒相关的kernel log
echo 4 > /sys/module/wakelock/parameters/debug_mask             #互斥锁相关
echo 1 > /sys/module/lpm_levels/parameters/debug_mask
echo 0x16 > /sys/module/smd/parameters/debug_mask
echo 32 > /sys/module/msm_pm/parameters/debug_mask
echo 9 > /sys/module/mpm_of/parameters/debug_mask
echo 0x2 > /sys/module/ipc_router_core/parameters/debug_mask
echo 1 > /sys/module/kernel/parameters/initcall_debug
echo 0 >/sys/module/qpnp_rtc/parameters/poweron_alarm

#####################################
##  ftrace init
#####################################
cd /sys/kernel/debug/tracing
echo 0 > tracing_on; #关闭
echo 100000 > buffer_size_kb;#设置缓存区大小
echo "" > set_event #清空事件类型
echo "" > trace #清空缓冲区

echo "msm_low_power:* sched:sched_cpu_hotplug sched:sched_switch" >> set_event
echo "sched:sched_wakeup sched:sched_wakeup_new sched:sched_enq_deq_task" >> set_event
echo "power:cpu_idle power:cpu_frequency power:cpu_frequency_switch_start" >> set_event
#echo "msm_bus:bus_update_request" >> set_event
echo "power:suspend_resume" >> set_event
echo "power:wakeup_source_deactivate power:wakeup_source_activate" >> set_event

echo "power:clock_state power:clock_disable power:clock_enable power:clock_set_rate power:clock_enable power:clock_disable" >> set_event    #clock
echo "irq:irq_handler_entry" >> set_event       # irq
echo "gpio:*" >> set_event      # GPIO
#echo "mdss:mdp_mixer_update mdss:mdp_sspp_change mdss:mdp_commit" >> set_event
echo "kgsl:kgsl_pwrlevel kgsl:kgsl_buslevel kgsl:kgsl_pwr_set_state" >> set_event   #GPU


#####################################
## clear log
#####################################
dmesg -c
logcat -c
dumpsys batterystats --reset
echo "1" > /sys/kernel/debug/tracing/tracing_on #start trace

#####################################
## 获取参考log
#####################################
echo "$(date +%H-%M-%S),$(cat /proc/interrupts)" >> $DATALOGHOME/intterupt.log&
echo "$(date +%H-%M-%S),$(cat /d/wakeup_sources)" >> $DATALOGHOME/wakeup_sources.log&
