/*************************************************************************
	> File Name:    6.无名管道示例.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 13时46分34秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int fd[2];
    char buf[1024] = {0};
    int ret;

    if(-1 == pipe(fd))
    {
        perror("pipe");
        return -1;
    }
    

    pid = fork();
    if(0 == pid)
    {
        dup2(fd[1], STDOUT_FILENO);
        execlp("ifconfig", "ifconfig", NULL);
    }
    else if(pid > 0 )
    {
        wait(NULL);
        ret = read(fd[0], buf, sizeof(buf));
        printf("read %d bytes from pipe!\n%s",ret, buf);
    }
    else
    {
        perror("fork");
        return -1;
    }
    return 0;
}
