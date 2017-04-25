#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
/*
	perror和strerror区别
        用于获取与erno相关的错误信息，区别不大，用法简单
        最大区别在于perror向stderr输出结果，而strerror向stdout输出结果

*/
int main(int argc, char const *argv[])
{
	FILE *fp;
	if(NULL ==(fp = fopen(argv[1], "r")))
	{
		perror("perror");
		printf("strerror:%s\n",strerror(errno));
	}
	exit(0);
}
