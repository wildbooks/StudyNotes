# README

> REMOTE_SUBMIX参数可以让系统App录制系统内置的声音，也就是扬声器的声音。下面是一个巨简单的例子来示例如何通过AudioRecord配合REMOTE_SUBMIX参数进行录制。

# CODE

+ hardware/libhardware/modules/audio_remote_submix

# hal debug
```c++
diff --git a/modules/audio_remote_submix/audio_hw.cpp b/modules/audio_remote_submix/audio_hw.cpp
index d47cfba..a8c0c65 100644
--- a/modules/audio_remote_submix/audio_hw.cpp
+++ b/modules/audio_remote_submix/audio_hw.cpp
@@ -41,7 +41,7 @@

 #include <utils/String8.h>

-#define LOG_STREAMS_TO_FILES 0
+#define LOG_STREAMS_TO_FILES 1 //抓取audio_remote的hal层数据
 #if LOG_STREAMS_TO_FILES
 #include <fcntl.h>
 #include <stdio.h>
@@ -53,7 +53,7 @@ extern "C" {
 namespace android {

 // Set to 1 to enable extremely verbose logging in this module.
-#define SUBMIX_VERBOSE_LOGGING 0
+#define SUBMIX_VERBOSE_LOGGING 1 //开启log开关
 #if SUBMIX_VERBOSE_LOGGING
 #define SUBMIX_ALOGV(...) ALOGV(__VA_ARGS__)
 #define SUBMIX_ALOGE(...) ALOGE(__VA_ARGS__)
```

```shell
#编译方法
make audio.r_submix.default -j8
#push到手机里
adb root
adb remount
adb push audio.r_submix.default.so /vendor/lib/
```

