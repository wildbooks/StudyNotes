/*************************************************************************
	> File Name:    1.创建进程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 09时58分06秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid =  getpid();
    pid_t ppid = getppid();
    printf("pid=%d\tppid=%d\n", pid, ppid);
    sleep(5);
    return 0;
}
