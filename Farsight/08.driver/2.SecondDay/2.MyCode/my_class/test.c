#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 

main()
{
	int fd;

	fd = open("hello",O_RDWR);

	sleep(2);

	close(fd);

}
