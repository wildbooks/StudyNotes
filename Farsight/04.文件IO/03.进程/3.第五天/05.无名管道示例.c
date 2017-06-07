/*************************************************************************
	> File Name:    5.无名管道示例.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 11时56分54秒
*************************************************************************/
/*
    3、创建一个管道,再创建一个子进程,父进程每ms写20
    个字符进管道,子进程每ms读7个字符出管道,体会管道
    传递速度的木桶效应。
*/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pfd[2];
    char buf[] = "abcdefghijklmnopqrxtuvwsyz";
    char buff[50] = {0};
    pid_t fid;
    if(pipe(pfd))
    {
        perror("pipe");
    }
    pipe(pfd);
    fid = fork();
    /*子*/
    if(0 == fid)
    {
        while(1)
        {
            usleep(1000);
            read(pfd[0], buff, 7);
            printf("%s\n", buff);
            buff[0] = 0;
        }

    }
    /*父进程*/
    else if (fid >0)
    {
        while(1)
        {
            usleep(20000);
            write(pfd[1], buf, 20);
        }
        
    }
    else
        perror("fork");

    return 0;
}
