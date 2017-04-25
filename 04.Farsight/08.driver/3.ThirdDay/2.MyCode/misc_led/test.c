#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd;

	fd = open("/dev/leds",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}

	sleep(2);
	
	ioctl(fd, 1, 0);
	ioctl(fd, 5, 0);
	ioctl(fd, 3, 0);
	ioctl(fd, 4, 0);


	sleep(2);

	ioctl(fd, 1, 1);
	ioctl(fd, 5, 1);
	ioctl(fd, 3, 1);
	ioctl(fd, 4, 1);

	sleep(2);
	close(fd);

}
