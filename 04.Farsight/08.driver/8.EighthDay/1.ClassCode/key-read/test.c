#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void main()
{
	int fd;
	int i,keyno;

	fd = open("/dev/key",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
		return ;
	}
	for(i=0;i<100;i++)
	{
		read(fd,&keyno,sizeof(int));
		printf("-------key%d------\n",keyno);
	}
	
	close(fd);

}
