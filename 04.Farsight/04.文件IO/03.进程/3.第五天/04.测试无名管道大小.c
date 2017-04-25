/*************************************************************************
	> File Name:    4.测试无名管道大小.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月05日 星期五 11时37分04秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int pbuf[2];
    pipe(pbuf);
    int i = 0;
    while(1)
    {
        write(pbuf[1], "1", 1);
        i++;
        printf("%d\n", i);
    }
    return 0;
}
