/*************************************************************************
	> File Name:    5.倒序打印一个文件.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月01日 星期一 15时16分43秒
*************************************************************************/

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
   FILE *fp, *fpw;
    char buf[1024];
    fp = fopen("i", "r+");
    fpw = fopen("ilove", "w+");

    int ret = fread(buf, 1, 1024, fp);
    buf[ret]=0;
    printf("%s\n", buf);
    printf("%d\n", ret);
    for(int i=0; i<ret; i++)
    {
        buf[i] ^=0x12;
    }
    
    fwrite(buf, 1, ret, fpw);












    for(int i=0; i<ret; i++)
    {
        buf[i] ^=0x12;
    }
    printf("%s\n", buf);
    
    return 0;
}
