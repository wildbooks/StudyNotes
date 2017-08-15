#   adb root 
#   adb push xxx.sh /data/ 
#   adb shell chmod 777 /data/xxx.sh
#   ./data/xxx.sh > data/kmsg.txt
#   adb pull /data/kmsg.txt
local count=0
local utime 
local ktime 
local pause_time=10
if [ -n "$1" ]; then
    pause_time=$1
fi
dump_peripheral () {
    local base=$1 #第一个参数
    local size=$2 #第二个参数
    local dump_path=$3 #第三个参数
    echo $base > $dump_path/address
    echo $size > $dump_path/count
    cat $dump_path/data
}
echo "Starting dumps!"
echo "Dump path = $dump_path, pause time = $pause_time"
echo "SRAM and SPMI Dump"
dump_peripheral 0x0 0x400 "/sys/kernel/debug/fg_memif"
while true
do
    if [ $(( $count % 6 )) -eq 5 ]; then
        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "Charger Dump Started at ${ktime}"
        dump_peripheral 0x21000 0x700 "/sys/kernel/debug/spmi/spmi-0"
        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "Charger Dump done at ${ktime}"

        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "FG Dump Started at ${ktime}"
        dump_peripheral 0x24000 0x700 "/sys/kernel/debug/spmi/spmi-0"
        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "FG Dump done at ${ktime}"

        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "PS Capture Started at ${ktime}"
        cat /sys/class/power_supply/bms/uevent
        cat /sys/class/power_supply/battery/uevent
        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "PS Capture done at ${ktime}"
    else
        utime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "SRAM Dump Started at ${ktime}"
        dump_peripheral 0x400 0x200 "/sys/kernel/debug/fg_memif"
        uptime=$(cat /proc/uptime)
        ktime=${utime[0]}
        echo "SRAM Dump done at ${ktime}"
    fi
    sleep $pause_time #休眠10秒
    let count=$count+1
done
