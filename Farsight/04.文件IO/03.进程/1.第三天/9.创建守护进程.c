/*************************************************************************
	> File Name:    9.创建守护进程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 20时03分35秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    daemon(0, 0);
    sleep(20);
    close(0);
    return 0;
}
