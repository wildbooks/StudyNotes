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
#if 1
	ioctl(fd, 1, 1);
	ioctl(fd, 2, 1);
	ioctl(fd, 2, 1);
	ioctl(fd, 3, 1);
	ioctl(fd, 4, 1);


	ioctl(fd, 5, 1);
#endif

	sleep(3);
	
	close(fd);

}
