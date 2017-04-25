#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

 

void main()
{
	int fd;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open\n");
	}
	printf("open successful\n");
	sleep(8);
	printf("88\n");
	
	close(fd);

}
