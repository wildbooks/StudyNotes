/*************************************************************************
	> File Name:    11.信号量.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 16时59分47秒
*************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("hello world!\n");
    //raise(SIGKILL);
    kill(getpid(), SIGKILL);
    printf("please don't kill me!\n");
    return 0;
}
