/*************************************************************************
	> File Name:    2.创建线程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 09时43分11秒
*************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *fun(void *para)
{
    int i = 1000;
    while(i--)
    {
        printf("-");
        fflush(stdout);
        usleep(1000);
    }
}
int main(int argc, char* argv[])
{
    int i = 1000;
    pthread_t thid;
    pthread_create(&thid, NULL, fun, NULL);
    while(i--)
    {
        printf("*");
        fflush(stdout);
        usleep(1000);
    }
    return 0;
}
