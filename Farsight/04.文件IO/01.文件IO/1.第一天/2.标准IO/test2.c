/*************************************************************************
	> File Name:    test2.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月01日 星期一 13时59分12秒
*************************************************************************/

#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
    FILE *fpr, *fpw;
    int ret;
    char buf[1024] = {0};
    fpr = fopen("ilove", "r");
    fpw = fopen("i", "w");
    if(NULL == fpw || NULL == fpr)
    {
        perror("fopen");
        return -1;
    }    
    ret = fread(buf, 1, sizeof(buf), fpr);
    fwrite(buf, 1, ret, fpw);
    return 0;
}
