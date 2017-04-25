/*************************************************************************
	> File Name:    8.互诉锁交替打印.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 15时57分24秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
sem_t sem1, sem2 ;
void *fun()
{
    int i = 1000;
    while(i--)
    {
        sem_wait(&sem1);
        printf("-");
        sem_post(&sem2);
    }
}

int main(int argc, char* argv[])
{
    int i = 1000;
    pthread_t pthid;
    pthread_create(&pthid, NULL, fun, NULL);
    sem_init(&sem2, 0, 0);
    sem_init(&sem1, 0, 1);
    while(i--)
    {
        sem_wait(&sem2); //相当于上锁
        printf("+");     //后打印
        sem_post(&sem1);
    }
    pthread_join(pthid, NULL);
    return 0;
}
