#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 
#include <sys/ioctl.h>

#define  MAGIC_NUM 'k'
#define BEEP_ON           _IO(MAGIC_NUM,0)
#define BEEP_OFF              _IO(MAGIC_NUM ,1)
#define BEEP_FRE             _IO(MAGIC_NUM ,2)
main()
{
	int fd;
	int i,ledno;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}

	ioctl(fd,BEEP_ON);
	sleep(5);
	ioctl(fd,BEEP_OFF);
	
	close(fd);

}
