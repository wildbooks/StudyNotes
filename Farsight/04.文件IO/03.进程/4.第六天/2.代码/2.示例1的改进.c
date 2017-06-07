/*************************************************************************
	> File Name:    2.示例1的改进.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月08日 星期一 10时13分37秒
*************************************************************************/
/*
    将上面的使用改造成一个进程接收并处理信号（打印一个字符'o'），另一个
    进程给它发信号！
*/
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t  pid;
    
    pid = fork();

    if(0 == pid)
    {
        ;
    }
    else if(pid > 0)
    {
        ;
    }
    else
    {
        perror("fork");
        return -1;

    }
    return 0;
}
