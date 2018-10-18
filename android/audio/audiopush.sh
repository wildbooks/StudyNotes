echo "archermind" | sudo -S adb root &&sudo adb remount
sudo adb push out/target/product/msm8937_64/system/vendor/lib/libacdbloader.so /vendor/lib/libacdbloader.so                                    #acdbloader
sudo adb push out/target/product/msm8937_64/system/vendor/lib/hw/audio.primary.msm8937.so /vendor/lib/hw/audio.primary.msm8937.so                   #so
sudo adb push hardware/qcom/audio/configs/msm8937/mixer_paths_mtp.xml /vendor/etc/                                                                #xml
sudo adb shell rm -rf /vendor/etc/acdbdata/MTP/*
sudo adb push vendor/qcom/proprietary/mm-audio-cal/audcal/acdbdata/8937/MTP/* /vendor/etc/acdbdata/MTP/   #acdb

sudo adb reboot
