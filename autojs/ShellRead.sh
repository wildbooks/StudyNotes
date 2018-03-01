#!/system/bin/sh

#am start -p "com.mx.browser";
# #	随机数
#
function rand(){
	min=$1;
	max=$(($2-$min+1));
	num=$((($RANDOM$RANDOM>>5)+100000000));
	echo $(($num%$max+$min));
}

#
#	随机滑动屏幕
#
function RandSwipe(){
	rnd=$(rand 0 100);
	x0=$(($rnd+$1));
	y0=$(($rnd+$2));
	x1=$(($rnd+$3));
	y1=$(($rnd+$4));
	duration=$(($rnd+$5));
	input swipe $x0 $y0 $x1 $y1 $duration;
}

function RandHenSwipe(){
}


#
#	随机延时ms
#
function RandSleep(){
	nu=$(($1000+$(rand 500 4000)));
	usleep $nu;
}

#
#	随机点击
#
function RandTap(){
	rnd=$(rand 0 100);
	x=$(($rnd+$1));
	y=$(($rnd+$2));
    input tap $x $y;
}

#
#	刷新界面
#
function RandRefresh(){
	RandSwipe 540 400 540 1200 1000;
}

#
#	main()
#
while true ; do

	for k in 1 2 3 4 5 6 7 8 9;do	#右滑动
		RandSwipe 1000 1000 200 1000 1000;
		for j in 1 2 3 4 5 6 7 8 9;do	#同类阅读

			RandSleep 2000;
			RandRefresh;
			RandSleep 2000;
			RandTap 540 1060;
			RandSleep 1000;
			for i in 1 2 3; do	#阅读
				RandSleep 2000;
				RandSwipe 540 1300 540 400 1000;
				RandSleep 2000;
				RandSwipe 540 400 540 1300 1000;
			done

			input keyevent 4  #返回
		done
	done

	for k in 1 2 3 4 5 6 7 8 9;do	#左滑动
		RandSwipe 200 1000 1000 1000 1000;
		for j in 1 2 3 4 5 6 7 8 9;do	#同类阅读

			RandSleep 2000;
			RandRefresh;
			RandSleep 2000;
			RandTap 540 1060;
			RandSleep 1000;
			for i in 1 2 3; do	#阅读
				RandSleep 2000;
				RandSwipe 540 1300 540 400 1000;
				RandSleep 2000;
				RandSwipe 540 400 540 1300 1000;
			done

			input keyevent 4  #返回
		done
	done
done

#
#	x:3种状态：左翻页，右翻页，none
#	y:向上，向下翻页
