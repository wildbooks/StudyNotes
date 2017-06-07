#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd;

	fd = open("/dev/led",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
#if 0
	ioctl(fd, 1, 1);
	ioctl(fd, 2, 0);
	ioctl(fd, 3, 0);
	ioctl(fd, 4, 0);
#endif

	sleep(3);
	
	close(fd);

}
