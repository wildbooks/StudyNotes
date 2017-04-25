#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include "head.h"
int main(int argc, const char *argv[])
{
	int fd;
	int ret;
	float mytemp;
	struct mpu6050_data data;
	if((fd=open("mpu6050",O_RDWR))<0)
	{
		perror("open");
			return 0;
	}
	else
	{
		printf("open success\n");
	}
	while(1)
	{
#if 1
		ioctl(fd,MPU6050_GET_TEMP,&data);
		mytemp =(float)data.temp/340.0 +36.53;
		printf("************temperture******************\n");
		printf("temp = %f\n",mytemp);
		printf("****************************************\n");
		sleep(1);
#endif
#if 0
		ioctl(fd,MPU6050_GET_GYRO,&data);
		printf("************GYRO************************\n");
		printf("x = %d\ty = %d\tz=%d\t\n\n",data.x,data.y,data.z);
		printf("****************************************\n");
		sleep(1);

		ioctl(fd,MPU6050_GET_ACCEL,&data);
		printf("***************ACELL*********************\n");
		printf("x = %d\ty = %d\tz=%d\t\n\n",data.x,data.y,data.z);
		printf("****************************************\n");
		sleep(1);
#endif
	}

//	char buf[64];
//	ret=read(fd,buf,sizeof(buf));
//	printf("%s\n",buf);

	return 0;
}
