#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       #include <unistd.h>
       #include <stdio.h>
 

int main()
{
	int fd;
	int minor;

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
	//sleep(3);
	read(fd,&minor,4);
	printf("minor===%d \n",minor);
	close(fd);

}
