#! /system/bin/sh

echo -e "The Monkey begin $(date)\n\n" > /sdcard/monkey.log

#monkey -p com.tct.camera -v -v 10000 >> /sdcard/monkey.log &

monkey -p  com.tcl.ota -p com.tct.calculator -p com.jrdcom.filemanager -p com.tct.gallery3d -p com.blackberry.retaildemo -p com.tct.fmradio -p com.tct.weather -v -v  --ignore-crashes --ignore-timeouts --ignore-security-exceptions  --monitor-native-crashes --ignore-native-crashes  999999 >>/sdcard/monkey.log &

sleep 1 #延时等待脚本成功运行

# 获取PID
monkeypid=$(pgrep monkey)

sleep 8640 #24小时=24*60*60=86400

kill ${monkeypid}
echo -e "The Monkey end $(date)\n\n" >> /sdcard/monkey.log
