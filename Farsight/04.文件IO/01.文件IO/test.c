/*************************************************************************
	> File Name:    test.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月07日 星期日 14时33分28秒
*************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fdr, fdw;
    char buf[1024] = {0};
    int n;

    fdr = open("/dev/input/event4", O_RDONLY);
    fdw = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(-1 == fdr || -1 == fdw)
    {
        perror("open");
        return -1;
    }

    while(1)
    {
        n = read(fdr, buf, sizeof(buf));
        if(n > 8)
        {
            write(1, buf, n);
            //break;

        }
    }

    return 0;
}
