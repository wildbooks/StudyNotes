/*************************************************************************
	> File Name:    4.waitpid用法.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 11时51分01秒
*************************************************************************/
/*
    fork一个子进程,让子进程sleep(100),父进程每秒调用
    waitpid监测子进程的状态,如果子进程还活着,就打印
    “这个月生活费1000元。”,否则打印“你毕业了,自
    己花钱自己挣!”,期间手动杀掉子进程,观察打印,
    体会waitpid的用法。

*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    int ret = 0;
    int status;
    pid_t pid = fork();
    if(0 == pid)
    {
        sleep(5);
    }
    else
    {
        while(1)    
        {
            ret = waitpid(pid, &status, WNOHANG); 
            if(ret > 0)
            {
                printf("你毕业了，自己花钱自己挣！\n");
                break;
            }
            sleep(1);
            printf("这个月生活费1000元\n");
        }
    }
    return 0;
}
