/*************************************************************************
	> File Name:    5.综合实例.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 10时34分54秒
*************************************************************************/
/*
    4、创建一个多线程程序,打开一个文件,主线程在文
    件的奇数位写“*”,子线程在偶数位写“-”,各写
    1000个。
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

int fd;
pthread_mutex_t mutex;
void *fun(void *arg)
{
    int i=1000;
    int n=0;
    while(i--)
    {
        //pthread_mutex_lock(&mutex);
        lseek(fd, n, SEEK_SET);
        write(fd, "-", 1);
        pthread_mutex_unlock(&mutex);
        n+=2;
        printf("sls\n");
    }
}
int main(int argc, char* argv[])
{
    int i=1000;
    int n=1;

    pthread_t pthid;
    fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd < 3)
    {
        perror("open");
        return -1;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&pthid, NULL, fun, NULL);
    while(i--)
    {

        pthread_mutex_lock(&mutex);
        lseek(fd, n, SEEK_SET);
        write(fd, "*", 1);
       // pthread_mutex_unlock(&mutex);
        n+=2;
        printf("ls\n");
    }
        printf("ssss\n");
    pthread_join(pthid, NULL);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}
