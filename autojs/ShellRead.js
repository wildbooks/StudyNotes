auto();
内容();
function 内容(){
  if(confirm("开始运行？")){
    setScreenMetrics(1080,1920);
    launch("com.mx.browser");
    var sh = new Shell(true);
    sleep(8000);
    sh.exec( "input swipe 540 400 540 1200 1000");
    while(1){
      sleep(1000);
      sh.exec( "input swipe 540 400 540 1200 1000");
      sleep(3000);
      sh.exec( "input tap 540, 1060");
      for (var i=0;i<=3;i++){
        sleep(2000);
        sh.exec( "input swipe 540 1300 540 400 1000");
        sleep(3500);
        sh.exec( "input swipe 540 400 540 1300 1000");
        sleep(1500);
        toast("正在运行中!");
      }
      back();
    }
  }
}
