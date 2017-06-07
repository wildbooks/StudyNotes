#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
		return ;
	}
	printf("open ok\n");
	sleep(10;
	printf("88\n");
	close(fd);
}
