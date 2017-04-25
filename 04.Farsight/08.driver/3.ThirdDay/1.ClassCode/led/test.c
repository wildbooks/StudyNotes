#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> 

main()
{
	int fd;
	int i,ledno;

	fd = open("hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}


	for(i=0;i<1000;i++)
	{
		ledno = i%4 +1;
	
		write(fd,&ledno,sizeof(int));
		sleep(1);
		ledno = -1;
		write(fd,&ledno,sizeof(int));
	}
	
	close(fd);

}
