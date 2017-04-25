#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main()
{
	int fd;
	int i,keyno;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
	for(i=0;i<100;i++)
	{
		read(fd,&keyno,sizeof(int));
		printf("-------key%d------\n",keyno);
	}
	
	close(fd);

}
