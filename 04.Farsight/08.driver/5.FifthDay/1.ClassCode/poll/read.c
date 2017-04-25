#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 #include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h> 

main()
{
	int fd,i,len;
	char buf[64];

	fd_set rfd,wfd;
	

	fd = open("/dev/hello",O_RDWR|O_NONBLOCK);
	if(fd<0)
	{
		perror("open fail\n");
		return ;
	}
	printf("open ok\n");
	 
	read(fd,buf,64);
	printf("%s\n",buf);
	close(fd);
}
