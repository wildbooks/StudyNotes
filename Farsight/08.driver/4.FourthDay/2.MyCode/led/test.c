#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

void main()
{
    int fd;
    int ledno, cmd;

    fd = open("/dev/leds",O_RDWR);
    if(fd<0)
    {
        perror("open fail\n");
    }
    while(1)
    {
        printf("please input :\n");
        scanf("%d%d", &ledno, &cmd);
        printf("leds=%d\tcmd=%d\n", ledno, cmd);
        ioctl(fd, ledno, cmd);
    }

    printf("please input :\n");

    close(fd);

}
