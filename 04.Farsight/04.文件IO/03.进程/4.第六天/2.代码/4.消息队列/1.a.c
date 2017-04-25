/*************************************************************************
	> File Name:    1.a.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 13时40分36秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

struct msgbuf {
    long mtype;
    char mtext[];
};
int main(int argc, char* argv[])
{
    int msqid;
    char buf[1024] = "";
    struct msgbuf *msbuf = (struct msgbuf *)buf;
    key_t key;
    ssize_t n;
    int ret;

    /*1.生成标识符*/
    if(-1 == (key = ftok(".", 19)))
    {
        perror("ftok");
        return -1;
    }
    /*2.创建消息队列*/
    if(-1 ==(msqid = msgget(key, IPC_CREAT | 0600)))
    {
         perror("msgget");
         return -1;
    }
    msbuf->mtype = 520;
    strcpy(msbuf->mtext, "I love you!");
    /*3.发送消息*/
    if(-1 == msgsnd(msqid, msbuf, strlen(msbuf->mtext), 0))
    {
         perror("msgsnd");
         return -1;
    }
    printf("%s\n", msbuf->mtext);

}
