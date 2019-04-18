# 参考文档 80-NV324-1 C
# compress offload playback是通过NuPlayer而不是AwesomePlayer，此功能是把cpu做的音频解码工作交给adsp解码,支持的解码类型有MP3, AAC, AC3, EAC3, and FLAC(16bit/24bit)
# 音频播放序列： MediaPlayerService → NuPlayer → AudioTrack →  AudioFlinger →  audio_hw → Kernel compress driver →  QDSP6 ASM driver→ ADSP
#  NuPlayer:
#       Data source ：解析器从文件中提取编码的音频数据
#       NuPlayerDecoder：用于压缩卸载重放的音频数据软件解码器; 设置为直通模式
#       NuPlayerRenderer:创建AudioSink和直接输出AudioTrack
#
#       NuPlayer查询Audio Policy Manager(APM)来决定视频流(stream)是否能offloaded，APM配置文件audio_policy.conf，文件中的关键词compress_offload
#       offload工作
# 客制化(device/qcom/msm8937_64/system.prop )
# audio.offload.disable 禁止offload模式总开关
# adb shell setprop audio.offload.disable 0
# adb shell setprop audio.offload.buffer.size.kb 32 #设置offload缓存区大小
# adb shell setprop audio.offload.gapless.enabled true  #为无间隙播放启用offload
# adb shell setprop av.offload.enable true  #为AV(Audio/Video)播放启用offload模式
# adb shell setprop av.streaming.offload.enable true #视频刘
# adb shell setprop audio.offload.multiple.enabled true
# adb shell setprop audio.offload.min.duration.secs 60

adb root && adb wait-for-device
adb remount
#echo 8 > /proc/sys/kernel/printk
echo "file sound/soc/msm/qdsp6v2/msm-compress-q6-v2.c +p" >>/d/dynamic_debug/control
echo "file sound/soc/msm/qdsp6v2/q6adm.c +p" >>/d/dynamic_debug/control
echo "file sound/soc/soc-compress.c +p">> /d/dynamic_debug/control
echo "file sound/core/compress_offload.c +p" >>/d/dynamic_debug/control
echo "file sound/core/pcm_compat.c +p" >>/d/dynamic_debug/control
echo "file sound/core/pcm_native.c +p" >>/d/dynamic_debug/control
echo "file sound/soc/msm/qdsp6v2/msm-pcm-routing-v2.c +p">>/d/dynamic_debug/control
