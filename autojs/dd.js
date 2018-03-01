auto();
内容();
function 内容(){
  if(confirm("开始运行？")){
    setScreenMetrics(1080,1920);
    launch("com.mx.browser");
    sleep(7000);
      sleep(1000);
      swipe(540,400,540,1200,1000);
      click(120,280);
      while(1){
        sleep(random(800, 1000));
        swipe(540,400,540,1200,1000);
        sleep(random(2800,3000));
        click(540,1060);
        for (var i=0;i<=10;i++){
          sleep(random(1800, 2000));
          swipe(540,1300,540,400,1000);
          sleep(random(3400, 3500));
          swipe(540,400,540,1300,1000);
          sleep(random(1400, 1500));
          toast("正在运行中!");
        }
        //click(100,125);
        back();
      }
  }
}
