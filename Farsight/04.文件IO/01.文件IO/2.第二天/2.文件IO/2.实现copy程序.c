/*************************************************************************
	> File Name:    2.实现copy程序.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月07日 星期日 17时34分08秒
*************************************************************************/

/*
        1。 使用非缓冲I/O方式，实现一个copy程序，该程序的第一个命令行
            参数为源文件，第二个命令行参数为目标文件，程序实现将源文
            件中的内容复制到目标文件
        2。 命令行参数可以使用argv[1]访问第一参数，argv[2]访问第二个
            参数
        3。 使用diff工具检查目标文件与源文件是否一致

*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fds, fdd;
    char buf[1024] = {0};
    int n;
    if(3 != argc)
    {
        printf("input two files\n");
        return -1;
    }

    if(-1 == (fds = open(argv[1],  O_RDONLY)))
    {
        perror("source file!\n");
        return -1;
    }

    if(-1 == (fdd = open(argv[2],  O_WRONLY | O_TRUNC | O_CREAT, 0644)))
    {
        perror("dest file!\n");
        return -1;
    }

    while(n = read(fds, buf, sizeof(buf))) 
    {
       write(fdd, buf, n); 
    }
    close(fds);
    close(fdd);

}
