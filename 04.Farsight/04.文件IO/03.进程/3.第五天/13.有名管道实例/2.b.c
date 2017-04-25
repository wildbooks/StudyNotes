/*************************************************************************
	> File Name:    2.b.c
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
void *writefile()
{
    int n;
    char buf[1024] = {0};

    while(1)
    {
        printf("hello world\n");
        /*读文件到终端*/
        n = read(fd2, buf, sizeof(buf)); 
        printf("hello world = %d\n", n);
        if(n > 0)
            write(1, buf, n);

    }
}



int main(int argc, char* argv[])
{
    pthread_t thid;
    int fd1;
    int  n;
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
    fd1 = open("file", O_WRONLY);
    fd2 = open("file1", O_RDONLY);
    if(fd1  == -1 || fd2 == -1)
    {
        perror("open");
        return -1;
    }
    /*创建子线程*/
    pthread_create(&thid, NULL, writefile, NULL);


    /*fd2 只读*/
    while(1)
    {
        printf("please input!\n");
        /*终端写到文件*/
        n = read(0, buf, sizeof(buf)); 
        if(n > 0)
            write(fd1, buf, n);
        printf("i love you = %d\n", n);
    }
    return 0;
}
