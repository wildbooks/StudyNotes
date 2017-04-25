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
    float tmp;
    short var=0;

    fd = open("/dev/ds18b20",O_RDWR);
    if(fd<0)
    {
        perror("open fail\n");
    }
    while(1)
    {
        read(fd, &var, sizeof(var));
        var &= 0x7FF;
        tmp = 0.0625*var;
        printf("tmp:%f\n",  tmp);
        sleep(1);
    }

    printf("please input :\n");

    close(fd);

}
