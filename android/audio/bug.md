# 电话铃声(Ringtone)正常，电话拨号(ToneGenerator)声大
  电话铃声和电话拨号声都是使用设备snd_device(2:speaker),route(audio-ull-playback),acdb_id:SPKR_PHONE_SPKR_MONO(device ID:14)，不能从下面修改，只能从上层修改。修改如下
  frameworks/av/media/libaudioclient/include/media/ToneGenerator.h //ToneGenerator案件发音
    static const CONSTEXPR float TONEGEN_GAIN = 0.9; // Default gain passed to WaveGenerator(). //修改此处值(0.0~1)

