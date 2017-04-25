#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 

main()
{
	int fd;
	int i,ledno;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}

	sleep(5);
	
	close(fd);

}
