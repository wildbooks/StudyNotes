/*************************************************************************
	> File Name:    1.信号量.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 21时47分12秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char* argv[])
{
    key_t key;
    int semid;
    if(-1 == (key = ftok(".", 25)))
    {
        perror("ftok");
        return -1;
    }

    if(-1 == ( semid = semget(key, 1, IPC_CREAT | 0666) ))
    {
        perror("semget");
        return -1;
    }
    semctl(semid, 0, SETVAL, 3);
    

    return 0;
}
