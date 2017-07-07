#TODO 收集时钟信息
# 捕捉时钟和调节器转储
adb shell
#mount -t debugfs none /sys/kernel/debug
sleep 10 && while true;
do
    echo "================debug/clk/=====================";
    cat /proc/uptime;
    cd /sys/kernel/debug/clk;
    for i in *;   # 遍历当前目录所有文件
    do
        # 检测文件是否为目录
        if [ -d $i ]; then
            if [ "$(cat $i/enable)" == "1" ]; then
                if [ -e $i/measure ]; then
                    echo $i \=\> enable:`cat $i/enable`
                    measure:`cat $i/measure`;
                else echo $i \=\> enable:`cat $i/enable`
                     rate:`cat $i/rate`;
                fi;
            fi;
        fi;
    done;

    echo "=====================================";
    cd /sys/class/regulator;
    for i in *;
    do if [ -d $i ]; then
           if [ -e $i/state ]; then
               if [ "$(cat $i/state)" == "enabled" ]; then
                   if [ -e $i/microvolts ]; then
                       echo $i \=\> name:`cat $i/name` state:`cat $i/state` microvolt:`cat $i/microvolts`;
                   else
                       echo $i \=\> name:`cat $i/name` state:`cat $i/state` microvolt: N\/A;
                   fi;
               fi;
           fi;
       fi;
    done;
    sleep 2; done > /sdcard/dumpclk.txt &

#TODO 采集唤醒锁信息
adb shell cat /sys/kernel/debug/wakeup_sources # 或者adb shelldumpsys power
sleep 60 && cat /d/wakeup_sources > /sdcard/wakelocks.txt&
cat ~/wakelocks.txt | awk '{print $1"\t\t\t\t\t\t"$6}'

#TODO 捕捉PowerTop和Top数据
sleep 3 && while true;
do echo "=======================================";
   cat /proc/uptime;
   top -m 25 -d 1 -n 1 -t;
   echo "---------------------------------------";
   /data/powertop -r -d -t 5
done > /sdcard/dumptop.txt &

adb pull /sdcard/dumptop.txt .

#TODO batterystats
# 分析battery历史状态
# 54s开始
# dumpsys教程
sudo adb shell dumpsys batterystats|tee bugreport-"$(date +%Y-%m-%d\ %R)"_con.log#
sudo adb shell sleep 5 && dumpsys batterystats --reset  #清空日志
sudo adb bugreport > bugreport-"$(date +%Y-%m-%d\ %R)"_changjin1.log
