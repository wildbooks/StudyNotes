# 收集时钟信息
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
    sleep 2; done > /data/dumpclk.txt &
