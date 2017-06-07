#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
 

void main()
{
	int fd, len;

	char buf[128] = "";
	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}

	len = read(fd, buf, 128);
	printf("len=%d buf:%s\n", len, buf);
	len = write(fd, "hello", sizeof("hello"));
	
	close(fd);

}
