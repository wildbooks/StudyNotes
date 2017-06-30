# batterystats
# 分析battery历史状态
# 54s开始
# dumpsys教程
sudo adb shell dumpsys batterystats|tee bugreport-"$(date +%Y-%m-%d\ %R)"_con.log#
sudo adb shell sleep 5 && dumpsys batterystats --reset  #清空日志
sudo adb bugreport > bugreport-"$(date +%Y-%m-%d\ %R)"_changjin1.log
