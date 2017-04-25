/*************************************************************************
	> File Name:    2.创建子进程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 10时36分01秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid, fd, pd;
    fd = getpid();
    printf("父父进程=%d\n",fd);
    pid = fork();
    pd = getpid();
    if(0 == pid)
        printf("父进程=%d\t子进程=%d\n",fd ,pd);
    else
        printf("父进程=%d\t父进程=%d\n",fd ,pd);
    while(0);
    return 0;
}
