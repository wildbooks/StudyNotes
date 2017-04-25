/*************************************************************************
	> File Name:    1.A.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 15时38分42秒
*************************************************************************/

/*
2、改造实验2.1,将进程A运行在root权限,将从管道中取
得的内容作为指令运行,进程B可写方式打开这个管道,
且每次运行的时候将想要以root权限运行的指令写入管道
中。(注意如果进程A要新创建这个有名管道,权限设为
你当前用户可写,如mask为0666)

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*  A   root 只读*/
int main(int argc, char* argv[])
{
    int fd;
    int ret;
    char buf[1024] = {0};
    /*1.创建有名管道*/
    if(-1 == access("efg", F_OK))
    {
        if(mkfifo("efg", 0644))
        {
            perror("mkfifo");
            return -1;
        }
    }

    /*2.打开有名管道*/
    fd = open("efg", O_RDONLY);    
    while(1)
    {
        ret = read(fd, buf,sizeof(buf));
        buf[ret] = 0;
        if(ret > 0)
        {
            printf("size = %d\n %s", ret, buf);
            execlp("ls", "ls", NULL);
        }
    }

    return 0;
}
