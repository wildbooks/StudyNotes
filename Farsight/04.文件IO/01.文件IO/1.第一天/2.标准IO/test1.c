/*************************************************************************
	> File Name:    test1.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月01日 星期一 09时55分11秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
int main(int argc, char* argv[])
{
    FILE *fp, *fp2;
    char c;
    fp = fopen("case2.ppp", "w+");
    fp2 = fopen("case3.ppp", "w+");
    if(fp == NULL || NULL == fp2)
    {
        perror("fopen");
        return -1;
    }
    c='2';
    int i=999;
    while(i--)
    {
        fputc(c,fp);
    }
    fputc('1',fp);
    rewind(fp);
    while((c = fgetc(fp)) != EOF)
    {
        fputc(c, fp2);
        printf("%c\n", c);
        printf("===\n", c);
    }
    rewind(fp);
    while((c = fgetc(fp)))
    {
        usleep(5000);
        printf("%c", c);

    }
    //fprintf(stdout, "%d\n", n);
    fclose(fp);
    fclose(fp2);
    return 0;
}
