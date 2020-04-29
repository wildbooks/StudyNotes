# usb耳机分类

usb耳机分为usb模拟耳机和usb数字耳机，

usb模拟耳机本质上还是有线耳机，用usb接口替换jack接口，然后通过元器件链接到耳机控制芯片(例如高通pmic上的mbhc)上。

usb数字耳机，本质是usb声卡，通过usb协议识别的声卡，成功识别后，会走android源码的usb耳机框架。

# usb耳机测试



```bash
# audio playback config
adb root
adb shell
setenforce 0
tinymix 'USB_AUDIO_RX dev_token' <dev_token no>
tinymix 'USB_AUDIO_RX SampleRate' 'KHZ_48'
tinymix 'USB_AUDIO_RX Channels' 'Two'
tinymix 'USB_AUDIO_RX Format' 'S16_LE'
tinymix 'USB_AUDIO_RX Audio Mixer MultiMedia1' 1
tinyplay /sdcard/test.wav

# Audio recording config
adb root
adb shell
setenforce 0
tinymix 'USB_AUDIO_TX dev_token' <dev_token no> //dev_token no计算方式，请看下面备注。
tinymix 'USB_AUDIO_TX SampleRate' 'KHZ_48'
tinymix 'USB_AUDIO_TX Channels' 'Two'
tinymix 'USB_AUDIO_TX Format' 'S16_LE'
tinymix 'MultiMedia1 Mixer USB_AUDIO_TX' 1
tinycap /sdcard/usb-rec.wav

# Dev_token no = (card no << 16) | (PCM device No << 8) | (Use Case Type & 0xFF)
# card no:USB audio card number
# PCM device ID (0)
# use case type (playback –0, recording – 1). 
```

# debug

```bash
# 抓取 qxdm log
adb push diag.cfg /sdcard/diag_logs
/system/bin/diag_mdlog &
# 抓取 kernel log
adb root
adb wait-for-device
adb shell
mount -t debugfs debugfs /sys/kernel/debug
echo "file msm-pcm-routing-v2.c +p" > /sys/kernel/debug/dynamic_debug/control
echo "file msm-dai-q6-v2.c +p" > /sys/kernel/debug/dynamic_debug/control
echo "file msmcobalt.c +p" > /sys/kernel/debug/dynamic_debug/control
echo "file soc-dapm.c +p" > /sys/kernel/debug/dynamic_debug/control
echo "file q6afe.c +p" > /sys/kernel/debug/dynamic_debug/control
echo Y > /sys/module/printk/parameters/ignore_loglevel
echo "file usb_audio_qmi_svc.c +p" > /sys/kernel/debug/dynamic_debug/control
adb logcat -b kernel | tee kmsg.txt

# 抓取 logcat
adb shell setprop audio.usb.enable.debug true
adb logcat -c && adb logcat -v threadtime | tee logcat.txt
```

# log分析

```bash
1检查是否检测到USB耳机的插入和拔出
a）如果插入了带麦克风的USB耳机，请检查以下日志
audio_hw_usb: audio_extn_usb_is_capture_supported: capture_supported 1
b）如果插入了不带麦克风的USB耳机，请检查以下日志
audio_hw_usb: audio_extn_usb_is_capture_supported: capture_supported 0
c）如果移除了USB耳机，请检查以下日志
audio_hw_usb: audio_extn_usb_remove_device: device(0x4000), card(1)
audio_hw_usb: audio_extn_usb_remove_device: card_dev_type (0x4000), card_no(1)
audio_hw_usb: audio_extn_usb_remove_device: bit-width(24) channel(2)
audio_hw_primary: detected USB disconnect .. enable proxy
2检查采样率和位是否与USB耳机兼容，
例如，将日志配置USB耳机设置为48k 24b
```

| State | USB CC1 | USB_AUDIO_EN1 (GPIO_59) | USB_AUDIO_EN1_N(U5 output) | MBHC_HSDET_L(U4 output) | USB_AUDIO_EN2_N(GPIO_60) | Orientation |
| ----- | ------- | ----------------------- | -------------------------- | ----------------------- | ------------------------ | ----------- |
|       |         |                         |                            |                         |                          |             |
|       |         |                         |                            |                         |                          |             |
|       |         |                         |                            |                         |                          |             |
|       |         |                         |                            |                         |                          |             |



State USB CC1 USB_AUDIO_EN1
(GPIO_59) USB_AUDIO_EN1_N
(U5 output) MBHC_HSDET_L
(U4 output) USB_AUDIO_EN2_N
(GPIO_60) 2 Orientation 1
(GPIO_75)
Dongle is removed 1 0 1 1 1 X
Dongle is inserted 0 0 1 1 1 X
USB Type-C host IC identifies
analog audio accessory mode 0 1 0 0 0 0
0 1 0 0 0 1
Dongle is removed 1 1 0 1 0 X
USB Type-C host IC detects
device is not in analog audio
accessory mode 1 0 1 1 1 X

非模拟耳机检查态，有耳机插入后，设置USB_AUDIO_EN1=1,USB_AUDIO_EN2_N进入模拟耳机检测态；然后检测到MBHC_HSDET_L==0,触发耳机插入中断，然后交叉检测设置GPIO_75实现欧美标兼容。

