/*************************************************************************
	> File Name:    6.线程求婚.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月04日 星期四 11时46分04秒
*************************************************************************/

/*
3、编写一个多线程程序,子线程得到用户的输入,主
线程倒计时,如果十秒钟用户没有输入“I love you”,
就打印“都老了,没戏了!”,否则打印“结婚吧,生
娃吧!”,10秒钟后要结束输入线程。
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


int n = 0;
void *fun()
{

    char buf[255] = {0};
    while(1)
    {
        fgets(buf, sizeof(buf), stdin);
        if(0 == strcmp(buf, "I love you"))
        {
            n =1;
            printf("aaa");
            break;
        }
    }
}
int main(int argc, char* argv[])
{
    time_t start, now;
    pthread_t pthid;
    pthread_create(&pthid, NULL, fun, NULL);

    time(&start);
    while(1)
    {
        time(&now);
        if(now-start >10)
        {
            printf("结婚吧，生娃吧！\n");
            break;
        }
        else if(1 == n)
        {
            printf("好吧，我们结婚吧！\n");
            break;
        }
    }

    return 0;
}
