/*************************************************************************
	> File Name:    8.创建有名管道.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 14时42分27秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;
    int ret;
    char buf[1024] = {0};
    if( -1 == access("efg", F_OK))
    {
        /*创建有名管道*/
         if(-1 == mkfifo("efg", 0644))
        {
            perror("mkfifo");
            return -1;
        }

    }
    /*打开有名管道*/
    fd = open("efg", O_RDWR);
    ret = write(fd, "hello World", 20);
    read(fd, buf, ret);
    printf("%s\n", buf);
    return 0;
}
