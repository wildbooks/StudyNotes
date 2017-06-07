#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 

void main()
{
	int fd,i;
	char buf[64];

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
		return ;
	}
	printf("open ok\n");
	 
	for(i=0;i<100;i++)
	{
		read(fd,buf,sizeof(buf));
		printf("buf:%s\n");
	}

	
	printf("88\n");
	close(fd);
}
