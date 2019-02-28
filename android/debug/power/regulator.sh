# regulator电源消耗情况
regulator_path="/d/regulator"
for path in `ls /d/regulator`
do
  consumers=$regulator_path/$path/consumers
  echo $consumers
  if [ -f "$consumers" ]; then
    cat $consumers
  fi
done
