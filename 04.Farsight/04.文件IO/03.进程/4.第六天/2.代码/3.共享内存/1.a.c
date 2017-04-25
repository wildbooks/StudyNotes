/*************************************************************************
	> File Name:    3.创建共享内存.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 11时07分28秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(int argc, char* argv[])
{
    key_t key;
    char *pbuf;
    /*生成一个共享内存的标识符*/
    key = ftok(".", 16);
    printf("key = %d\n", key);
    /*申请一段共享内存*/
    int shmid = shmget(key, 1024, IPC_CREAT| 0600);
    /*将共享内存映射到本进程的虚拟空间中*/
    printf("shmid = %d\n", shmid);

    pbuf = shmat(shmid, NULL, 0);
    strcpy(pbuf, "hello world!");
    printf("%s\n", pbuf);
    strcpy(pbuf, "i love youafasfa!");
    printf("%s\n", pbuf);
    strcpy(pbuf, "i love you!");
    printf("%s\n", pbuf);
    return 0;
}
