/*************************************************************************
	> File Name:    2.b.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 20时49分38秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char *shmp;
    key_t key;
    int shmid;
    if(-1 == (key = ftok(".", 25)))
    {
        perror("ftok");
        return -1;
    }

    if(-1 == (shmid = shmget(key, 1024, IPC_CREAT | 0600)))
    {
        perror("shmget");
        return -1;
    }
    
    if((void *)-1 == (shmp = (char *)shmat(shmid, NULL, 0)))
    {
        perror("shmat");
        return -1;
    }
    printf("%s\n", shmp);
    return 0;
}
