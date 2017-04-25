/*************************************************************************
	> File Name:    9.读写进程中的有名管道.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 15时07分02秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
    进程A创建一个有名管道”/tmp/pipetest”,然后一直读
    管道内容并打印;进程B可写方式打开这个管道,且每次
    运行的时候将自己的参数写入管道中。

*/

/*进程A*/
int main(int argc, char* argv[])
{
    int fd;
    int ret; 
    char buf[1024] = {0};
    
    fd = open("efg", O_WRONLY);
    while(1)
    {
        printf("please input!\n");
        ret = read(0, buf, 1024);
        write(fd, buf, ret);
        //printf("size = %d\n%s", ret, buf); 
    }

    

    return 0;
}
