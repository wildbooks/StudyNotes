/*************************************************************************
	> File Name:    8.互诉锁交替打印.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 15时57分24秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutexa, mutexb;

void *fun()
{
    int i = 1000;
    while(i--)
    {
        pthread_mutex_lock(&mutexa);
        //sleep(1);
        printf("-\n");
        pthread_mutex_unlock(&mutexb);
    }
}

int main(int argc, char* argv[])
{
    int i = 1000;
    pthread_t pthid;
    pthread_create(&pthid, NULL, fun, NULL);
    pthread_mutex_init(&mutexa, NULL);
    pthread_mutex_init(&mutexb, NULL);
    pthread_mutex_lock(&mutexa);

    while(i--)
    {
        pthread_mutex_lock(&mutexb);
        sleep(2);
        printf("+\n");
        pthread_mutex_unlock(&mutexa);
    }
    pthread_mutex_unlock(&mutexb);
    pthread_join(pthid, NULL);
    pthread_mutex_destroy(&mutexa);
    pthread_mutex_destroy(&mutexb);
    return 0;
}
