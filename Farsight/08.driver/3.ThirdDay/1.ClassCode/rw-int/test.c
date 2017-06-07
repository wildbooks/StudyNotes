#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd,len;
	int num;
	
	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
	}
	

	/*len = read(fd,&num,4);

	printf("len=%d num:%d\n",len,num);
	num = 5;*/
	do
	{
		num=1;
		len = write(fd,&num,sizeof(int));
		sleep(1);
		num++;
		if(num>4)
		{
			num = 0;
		}
	}while(num<5);
	

		
	
	close(fd);

}
