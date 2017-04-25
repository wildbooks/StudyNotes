/*************************************************************************
	> File Name:    4.获取文件大小.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月01日 星期一 15时04分28秒
*************************************************************************/

#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    fp = fopen("i", "r");
    if(fp == NULL)
    {
        perror("fopen");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp);
    printf("%d\n",n);
    return 0;
}
