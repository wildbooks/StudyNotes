/*************************************************************************
	> File Name:    3.创建无名管道.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 11时23分51秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pfd[2]={0};
    int n;
    char a[] = "I love you!";
    char c[50] = {0};
    pipe(pfd);
    n = write(pfd[1], a, sizeof(a));
    read(pfd[0], c, n);
    printf("%s\n", c);
    return 0;
}
