/*************************************************************************
	> File Name:    5.execl族函数.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月03日 星期三 13时49分42秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{

    printf("I want creat ls process!\n");
    execlp("ls", "ls", "-lt", NULL);
    perror("exec");
    return 0;
}
