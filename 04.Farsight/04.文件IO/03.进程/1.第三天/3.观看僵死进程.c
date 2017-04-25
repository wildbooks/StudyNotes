/*************************************************************************
	> File Name:    3.观看僵死进程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 11时28分06秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
/*
    1、用fork创建一个子进程,子进程打印”This is a
    child”,父进程打印”This is a father ” 。
*/

int main(int argc, char* argv[])
{
    pid_t pid;
    pid = fork();
    if(0 == pid)
        printf("child game over!\n");    
    else
    {
        printf("I sleep!\n");    
        wait(NULL);
        sleep(100);
    }
        

    return 0;
}
