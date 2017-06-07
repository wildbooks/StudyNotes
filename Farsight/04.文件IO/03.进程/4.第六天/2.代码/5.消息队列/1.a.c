/*************************************************************************
	> File Name:    1.a.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 15时30分22秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msgbuf
{
    long mtype;
    char mtext[];
};

int main(int argc, char* argv[])
{
    key_t key;
    char buf[1024] = "";
    struct msgbuf *msgp = (struct msgbuf *)buf;
    int msqid;
    int n;
    if(-1 == (key = ftok(".", 16)))
    {
        perror("ftok");
        return -1;
    }
    if(-1 == (msqid = msgget(key, IPC_CREAT | 0600)))
    {
        perror("msgget");
        return -1;
    }
    printf("msqid = %d\n", msqid);
    /*发送消息队列*/
    msgp->mtype = 520;
    /*从终端读数据*/
    while(1)
    {
        if(n = read(0, msgp->mtext, sizeof(buf) - sizeof(long)))
        {
            if(-1 == msgsnd(msqid, msgp, strlen(msgp->mtext), 0))
            {
                perror("msgsnd");
                return -1;
            }
            else
                printf("n=%d\nbuf = %s\n", n, msgp->mtext);
        }
    }
}
