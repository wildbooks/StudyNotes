/*************************************************************************
	> File Name:    7.创建守护进程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 15时45分47秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int fdtablesize; 

    /*1.创建子进程，退出父进程*/
    pid = fork();
    if(pid)
        exit(0);
    /*2.在子进程中创建新会话*/
    setsid();
    /*3.改变当前目录为根目录*/
    chdir("/tmp");
    /*4.重设文件权限掩码*/
    umask(0);
    /*5.关闭文件描述符*/
    fdtablesize = getdtablesize();
    for(int fd = 0; fd<fdtablesize; fd++)
    {
        close(fd);
    }
    sleep(100); 
    

    return 0;
}
