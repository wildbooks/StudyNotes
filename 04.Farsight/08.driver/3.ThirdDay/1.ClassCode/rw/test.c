#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd,len;
	char buf[128]={0};

	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}

	len = read(fd,buf,128);

	printf("len=%d buf:%s\n",len,buf);

	len = write(fd,"hello",sizeof("hello"));

		
	
	close(fd);

}
