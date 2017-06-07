/*************************************************************************
	> File Name:    7.无名管道设置ip地址.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 14时12分46秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    char eth0[] = "enp5s0f1";
    char ipv4[10];
    
    int pfd[2];
    char buf[2048] = {0};
    int ret;  
    pid_t pid;

    if(pipe(pfd))
    {
        perror("pipe");
        return -1;
    }
    pid = fork();
    if(0 == pid)
    {
        dup2(pfd[1], STDOUT_FILENO);
        execlp("ifconfig", "ifconfig", NULL); 
    }
    else if(pid > 0)
    {
        wait(NULL);
        ret = read(pfd[0], buf, sizeof(buf));
        printf("read = %d\n%s\n", ret, buf);
    }
    else
    {
        perror("fork");
        return -1;
    }
    return 0;
}
