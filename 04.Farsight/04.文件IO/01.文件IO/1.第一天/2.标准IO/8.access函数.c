/*************************************************************************
	> File Name:    8.access函数.c
	> Author:       杨玉春
	> Mail:         www762268@foxmail.com
	> Created Time: 2016年08月01日 星期一 21时16分28秒
*************************************************************************/

#include <stdio.h>
#include <unistd.h>
/*
    函数功能
        检查文件属性
            R_OK	4		只判断是否有读权限
            W_OK	2       只判断是否有写权限	
            X_OK	1		判断是否有执行权限
            F_OK	0		只判断文件是否存在

*/
int main(int argc, char* argv[])
{
    if(access("a.out", R_OK)==0) 
        printf("read OK\n"); 
    if(access("a.out", W_OK)==0) 
        printf("write OK\n"); 
    if(access("a.out", X_OK)==0) 
        printf("Exec OK\n"); 
    if(access("a.out", F_OK)==0) 
        printf("File exist\n"); 

    return 0;
}
