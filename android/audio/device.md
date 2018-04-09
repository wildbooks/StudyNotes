# 
    audio_hw.c
    select_devices
        -> out_snd_device
# 确认audio使用mixer文件
    开机时抓取logcat,搜索mixer
    msm8916_platform: platform_init: mixer path file is /vendor/etc/mixer_paths_mtp.xml
# 确认audio使用acdb文件
# 电话流程
    usecase(compress-voip-call) -> select_devices(in ,out) -> enable_snd_device(in,out)-> audio_route -> ...
            用例                ->      选输入/出设备      ->       使能输入/出设备    ->   选通路    -> ...
        compress-voip-call      ->      

# 关键结构体
    device_table[SND_DEVICE_MAX]    #设备映射表
    acdb_device_table[SND_DEVICE_MAX]
