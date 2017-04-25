/*************************************************************************
	> File Name:    2.b.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 15时57分17秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msgbuf 
{
    long mtype;
    char mtext[];
};
int main(int argc, char* argv[])
{
    key_t key;
    char buf[1024] = "";
    struct msgbuf * msgp = (struct msgbuf *)buf;
    int n;
    int msqid;
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
    //while(1)
    //{
        if(0<(n = msgrcv(msqid, msgp, sizeof(buf)-sizeof(long), 520,  0)))
        {
            n = write(1, msgp->mtext, n);
            printf("n = %d\n", n);
        }
        else if(n == -1)
        {
            perror("msgrcv");
            return -1;
        }
    //}
}



