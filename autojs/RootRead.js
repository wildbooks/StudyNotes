auto();
内容();

/*
 * 随机滑动屏幕
 */
function RootRandSwipe(ra, a, b, c, d, duration){
  x0=random(a, a+100);
  y0=random(b, b+100);
  x1=random(c, c+100);
  y1=random(d, d+100);
  ra.swipe(x0, y0, x1, y1, duration);
}

/*
 * 随机延时ms
 */
function RandSleep(num){
  sleep(random(num, num+200));
}

function 内容(){
  if(confirm("开始运行？")){
    setScreenMetrics(1080,1920);
    launch("com.mx.browser");
    var ra = new RootAutomator();

    RandSleep(5000);
    RootRandSwipe(ra, 540, 400, 540, 1200, 1000);
    while(1){
      RandSleep(1000);
      RootRandSwipe(ra, 540, 400, 540, 1200, 1000);
      RandSleep(3000);
      ra.tap(540, 1060);
      for (var i=0;i<=3;i++){
        RandSleep(2000);
        RootRandSwipe(ra, 540, 1300, 540, 400, 1000);
        RandSleep(3500);
        RootRandSwipe(ra, 540, 400, 540, 1300, 1000);
        RandSleep(1500);
        toast("正在运行中!");
      }
      back();
    }
  }
}
