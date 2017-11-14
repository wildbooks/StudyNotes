#! /system/bin/sh

#
#  使用教程
#   --throttle 3 一次事件3微妙
#  PACKAGS:把需要的报名添加到该变量中，具体格式仿写下面的就行
#  COUNT: 测试点击次数
#
#  adb push monkey.sh /sdcard/
#  sh /sdcard/monkey.sh

#Calculator : package="com.tct.calculator.bb"
#FileManager : package="com.jrdcom.filemanager.bb"
#Gallery : package="com.tct.gallery3d.bb" #自己装
# com.tct.weather.bb #自己装


OUT=/sdcard/monkey
rm -rf ${OUT}
mkdir ${OUT}

# --throttle 3 3微妙点击一次
#FLAGS="-v -v -v --ignore-crashes --ignore-timeouts --ignore-security-exceptions --monitor-native-crashes --ignore-native-crashes --throttle 3"
PACKAGS="com.jrdcom.filemanager.bb com.tct.gallery3d.bb com.tct.weather.bb com.tct.calculator.bb"
PACKAGS="com.tct.soundrecorder.bb"

#每个包测两小时计算方式:2*60*60*1000/3=2400000
COUNT=2400000
#COUNT=2400
#COUNT=120


for i in ${PACKAGS};
do
    mkdir ${OUT}/${i}
    echo "=================${i} test=====================">>${OUT}/monkey_all.txt
    echo -e "The Monkey of ${i} begin $(date)\n\n" >${OUT}/${i}/error_${i}.txt
    echo -e "The Monkey of ${i} begin $(date)\n\n" >${OUT}/${i}/info_${i}.txt

    logcat -c
    #logcat -d -v threadtime > ${OUT}/${i}/logcat.txt&
    logcat > ${OUT}/${i}/logcat.txt &
    monkey -p ${i} -s ${RANDOM} ${FLAGS}  ${COUNT}  2>>${OUT}/${i}/error_${i}.txt 1>${OUT}/${i}/info_${i}.txt

    #失败判断

    logcat -d -b radio -v threadtime > ${OUT}/${i}/radio.txt
    logcat -d -b events -v threadtime > ${OUT}/${i}/events.txt
    logcat -d -b system -v threadtime > ${OUT}/${i}/system.txt
    getprop > ${OUT}/${i}/props.txt
    env > ${OUT}/${i}/env.txt
    dmesg > ${OUT}/${i}/dmesg.txt
    #cat /proc/last_kmsg > ${OUT}/${i}/last_kmsg.txt
    ps > ${OUT}/${i}/ps.txt
    ps -e > ${OUT}/${i}/ps_t.txt
    cat /proc/cmdline > ${OUT}/${i}/cmdline.txt
    ls -lR /data  > ${OUT}/${i}/userdata_check.txt
    echo 1 > /proc/sys/kernel/sysrq
    echo w > /proc/sysrq-trigger
    dmesg > ${OUT}/${i}/dmesg_sysrq.txt
    echo "getting screenshot ..."
    screencap -p   ${OUT}/${i}/screenshot.png
    echo "getting bugreport ... "
    # bugreport > ${OUT}/${i}/bugreport.txt  #错误在这里
    echo "getting dropbox,anr,tombstones,logd"
    cp -fr /data/system/dropbox ${OUT}/${i}/dropbox
    cp -fr /data/anr ${OUT}/${i}/anr
    cp -fr /data/tombstones ${OUT}/${i}/tombstones
    cp -fr /data/misc/logd ${OUT}/${i}/logd

    echo "deleting dropbox,anr,tombstones,logd"
    rm -rf /data/system/dropbox/*
    rm -rf /data/anr/*
    rm -rf /data/tombstones/*
    rm -rf /data/misc/logd/*


    echo -e "The Monkey of ${i} end $(date)\n\n" >>${OUT}/${i}/error_${i}.txt
    echo -e "The Monkey of ${i} end $(date)\n\n" >>${OUT}/${i}/info_${i}.txt
done
