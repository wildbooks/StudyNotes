#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

main()
{
	int fd;
	int i,adc;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
	for(i=0;i<100;i++)
	{
		read(fd,&adc,sizeof(int));
		printf("-------adc%0.2fV------",1.8*adc/4096);
	}
	
	close(fd);

}
