/*************************************************************************
	> File Name:    3.文件目录操作编程.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月07日 星期日 21时11分48秒
*************************************************************************/

/*
    本实验通过一个简单的ls程序，完成读目录内容程序，了解基本的读目录
    读的基本步骤
*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char* argv[])
{
    DIR *dp;
    if(NULL ==(dp = opendir("/tmp")))
    {
        perror("opendir");
        return -1;
    }

    return 0;
}
