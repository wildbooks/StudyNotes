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
		perror("device is busy\n");
	}
	sleep(8);
	
	close(fd);

}
