#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;

    fd = open("hello",O_RDWR);

    sleep(2);

    close(fd);

}
