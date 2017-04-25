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
	 


	FD_ZERO(&rfd);
	FD_ZERO(&wfd);

	FD_SET(fd,&rfd);
	FD_SET(fd,&wfd);

	while(1)
	{
		select(fd+1,&rfd,&wfd,NULL,NULL);
		if(FD_ISSET(fd,&rfd))
		{
			printf("can read\n");
		}
		
		if(FD_ISSET(fd,&wfd))
		{
			printf("can write\n");
		}
	}
	close(fd);
}
