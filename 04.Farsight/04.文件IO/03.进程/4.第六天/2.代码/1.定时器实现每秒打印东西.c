/*************************************************************************
	> File Name:    1.定时器实现每秒打印东西.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 09时18分35秒
*************************************************************************/
/*
    信号处理
       精准定时模型

    用定时器实现每1秒，打印一个字符'o'


*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void fun()
{
    alarm(1);
    printf("o\n");
}
int main(int argc, char* argv[])
{
    signal(SIGALRM, fun);
    alarm(1);
    while(1)
        pause();  //用它等待，它不怎么占用资源
    return 0;
}
