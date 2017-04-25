/*************************************************************************
	> File Name:    1.a.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 20时14分23秒
*************************************************************************/

/*
    1、申请或打开一段共享内存,将内存映射到进程空间中,一个进程写入
    字符串“this is a message from shm”,并给另一个进程发信号,另一个
    进程收到信号后打印该字符串。
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    key_t key;
    int shmid;
    char *shmmp;
    
    if(-1 ==(key = ftok(".", 25)))
    {
        perror("ftok");
        return -1;
    }

    if(-1 == (shmid = shmget(key, 1024, IPC_CREAT|0600)))
    {
        perror("shmget");
        return -1;
    }

    if((void *)-1 == (shmmp = (char *)shmat(shmid, NULL, 0)))
       {
           perror("shmat");
           return -1;
       }
    strcpy(shmmp, "this is a message from shm");
    printf("shmmp = %s\n", shmmp);
}
