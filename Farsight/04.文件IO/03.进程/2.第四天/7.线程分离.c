/*************************************************************************
	> File Name:    4.线程分离.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 13时48分20秒
*************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



void *fun(void *para)
{
    printf("this is a new thread\n");
    return 0;
}

int main(int argc, char* argv[])
{
    pthread_t thid;
    time_t start, now;
    while(1)
    {
        if(0 != pthread_create(&thid, NULL, fun, NULL))
        {
            perror("pthread_create");
            return -1;
        }
        sleep(1);
    }

    return 0;
}
