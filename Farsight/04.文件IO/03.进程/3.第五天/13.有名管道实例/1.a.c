/*************************************************************************
	> File Name:    1.a.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 23时04分37秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int fd2;
/*fd2只写*/
void *writefile()
{
    int n = 10;
    char buf[1024] = "faff";

    while(n--)
    {
        printf("please input !\n",n);
        /*终端写到文件*/
        n = read(0, buf, sizeof(buf)); 
        if(n > 0)
        {
            printf("n = %d, fd2 = %d\n", n, fd2);
            write(fd2, buf, n);
        }
    }
}



int main(int argc, char* argv[])
{
    int fd1;
    int n;
    pthread_t thid;
    char buf[1024] = {0};
    
    /*1.创建有名管道*/
    if(-1 == access("file", F_OK))
    {
        if(-1 == mkfifo("file", 0644))
        {
            perror("mkfifo");
            return -1;
        }
    }

    if(-1 == access("file1", F_OK))
    {
        if(-1 == mkfifo("file1", 0644))
        {
            perror("mkfifo");
            return -1;
        }
    }
    fd1 = open("file", O_RDONLY);
    fd2 = open("file1", O_WRONLY);

    if(fd1  == -1 || fd2 == -1)
    {
        perror("open");
        return -1;
    }

    /*创建子线程*/
    pthread_create(&thid, NULL, writefile, NULL);

    /*fd1 只读*/
    while(1)
    {
        /*读文件到终端*/
        n = read(fd1, buf, sizeof(buf)); 
        if(n > 0)
            write(1, buf, n);
        printf("hello world = %d!\n", n);
    }
    return 0;
}
