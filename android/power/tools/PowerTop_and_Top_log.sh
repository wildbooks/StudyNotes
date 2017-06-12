# 捕捉PowerTop和Top数据
sleep 3 && while true;
do echo "=======================================";
   cat /proc/uptime;
   top -m 25 -d 1 -n 1 -t;
   echo "---------------------------------------";
   /data/powertop -r -d -t 5
done > data/dumptop.txt &
