/*************************************************************************
	> File Name:    2.以只写方式打开文件.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月02日 星期二 09时46分34秒
*************************************************************************/
/*
    打开按键文件
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/input.h>
int main(int argc, char* argv[])
{
    int fd;
    struct input_event *buf;
    fd = open("/dev/input/event3", O_RDWR);
    int fdlog = open("keylog", O_RDWR | O_CREAT , 0644);
    buf = calloc(1, sizeof(struct input_event));
    if(fd<3)
    {
        perror("open");    
        return -1;
    }
    int count;

    alarm(20);
    while(1)
    {
        count = read(fd, buf, sizeof(struct input_event));
        if(count == sizeof(struct input_event))
        {
            perror("read");
   //         return -1;
        }
        printf("get your key\n");
        write(fdlog, buf, count);
        usleep(10000);
    }
    close(fd);
    return 0;
}
