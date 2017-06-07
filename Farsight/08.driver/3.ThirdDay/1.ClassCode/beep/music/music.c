/*
 * main.c : test demo driver
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include "pwm_music.h"

/*ioctl 命令*/
#define magic_number 'k'
#define BEEP_ON _IO(magic_number,0)
#define BEEP_OFF _IO(magic_number,1)
#define SET_FRE _IO(magic_number,2)

int main(void)
{
	int i = 0;
	int n = 2;
	int dev_fd;
	int div;
	dev_fd = open("/dev/pwm",O_RDWR | O_NONBLOCK);
	if ( dev_fd == -1 ) {
		perror("open");
		exit(1);
	}

	for(i = 0;i<sizeof(GreatlyLongNow)/sizeof(Note);i++ )
	{
		div = (GreatlyLongNow[i].pitch);
	
		ioctl(dev_fd, SET_FRE, div);
		ioctl(dev_fd, BEEP_ON);
		usleep(GreatlyLongNow[i].dimation * 50); 
		ioctl(dev_fd, BEEP_OFF);
	}
	
	for(i = 0;i<sizeof(MumIsTheBestInTheWorld)/sizeof(Note);i++ )
	{
		div = (MumIsTheBestInTheWorld[i].pitch);
		ioctl(dev_fd, SET_FRE, div);
		ioctl(dev_fd, BEEP_ON);
		
		usleep(MumIsTheBestInTheWorld[i].dimation * 50); 
		ioctl(dev_fd, BEEP_OFF);
	}



	for(i = 0;i<sizeof(FishBoat)/sizeof(Note);i++ )
	{
		div = (FishBoat[i].pitch);
		ioctl(dev_fd, SET_FRE, div);
		ioctl(dev_fd, BEEP_ON);
		usleep(FishBoat[i].dimation * 50); 
		ioctl(dev_fd, BEEP_OFF);
	}
	return 0;
}

