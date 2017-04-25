#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
 
#define MAGIC_NUM 'J'
#define PWM_STOP 		_IO(MAGIC_NUM, 0)
#define PWM_SET_FRE 	_IO(MAGIC_NUM, 1)

main()
{
	int fd;

	fd = open("/dev/beep",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
	ioctl(fd, PWM_SET_FRE, 200);
	sleep(1);
	ioctl(fd, PWM_SET_FRE, 100);
	sleep(1);
	ioctl(fd, PWM_STOP);



	close(fd);

}
