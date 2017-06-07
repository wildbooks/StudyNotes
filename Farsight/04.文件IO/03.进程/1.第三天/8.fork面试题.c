/*************************************************************************
    > File Name:    8.fork面试题.c
    > Author:       杨玉春
    > Mail:         www762268@foxmail.com
    > Created Time: 2016年08月03日 星期三 17时04分55秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
/*
    此题考点是缓冲概念
        1. 
            printf("#")
            打印和重定向到文件中都是8个
        2. 
            printf("#\n");
            打印出来是6个，但你重定向到文件中，它就是8个，这是因为printf
            带有buffer，且是行缓冲，/n它会刷新行缓冲；而文件是全缓冲，/n
            不会刷新它的缓存；
        3.
            printf("#");
            fflush(stdout);
            打印出来是6个，重定向也是6个，这是因为缓冲区被刷新

    参考：
        http://blog.csdn.net/ctoday/article/details/38443413
*/
int main(int argc, char* argv[])
{
    int i;
    for(i=0; i<3; i++)
    {
        fork();
        printf("#");
        //fflush(stdout);
    }
    return 0;
}
