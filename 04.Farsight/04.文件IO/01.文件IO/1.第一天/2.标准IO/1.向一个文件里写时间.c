/*************************************************************************
	> File Name:    1.向一个文件里写时间.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月07日 星期日 11时52分03秒
*************************************************************************/
/*
    1.编程读写一个文件test.txt,每隔1秒向文件中写入一行数据，类似这样：
        1，2007-7-30- 15：16：42
        2，2008-7-30- 15：16：42
        该程序应该无限循环，直到按Ctrl-C中断程序。
        再次启动程序写文件时可以追加到原文件之后，并且序号能够接续上
        次的序号，比如：
        1，2007-7-30- 15：16：42
        2，2008-7-30- 15：16：42
        3，2009-7-30- 15：16：42
        4，2010-7-30- 15：16：42


*/


#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    time_t now;
    struct tm *tm;
    int n = 0;
    char buf[1024] = {0};
    if(NULL == (fp = fopen("test.txt", "a+")))
    {
        perror("open");
        return -1;
    }

    /* 判断行数*/
    while(0 != fgets(buf, sizeof(buf), fp))
        n++;

    while(1)
    {

        sleep(1);
        n++;
        time(&now);
        tm = localtime(&now);
        fprintf(fp, "%d, %d-%d-%d %d:%d:%d\n", n, tm->tm_year + 1900, tm->tm_mon
                + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
        fflush(fp);   //fprintf存在缓存，所以需要刷新缓存
    }

}


