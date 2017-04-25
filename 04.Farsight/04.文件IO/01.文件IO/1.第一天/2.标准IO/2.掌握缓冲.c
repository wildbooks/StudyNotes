/*************************************************************************
	> File Name:    2.掌握缓冲.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月07日 星期日 20时33分46秒
*************************************************************************/
/*
    全缓冲：当填满IO缓冲后才进行实际的IO操作
    行缓冲：当在输入和输出中遇到新换行符('\n')时，进行I/O操作
    不带缓冲：标准I/O库不队字符进行缓冲，例如：stderr

*/
#include <stdio.h>

int main(int argc, char* argv[])
{
    int i = 0;
    for(i=0; i<379; i++) //每次向缓冲区内写三个字符
    {
        if(i>=100)
            fprintf(stdout, "%d", i);
        else if(i>=10)
            fprintf(stdout, "0%d", i);
        else if(i>=0)
            fprintf(stdout, "00%d", i);
    }
    while(1);
    return 0;
}
