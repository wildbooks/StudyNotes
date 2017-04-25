
struct mpu6050_data
{
	unsigned short x;
	unsigned short y;
	unsigned short z;
	short temp;
};


#define MPU6050_GET_GYRO _IOR('K',0,struct mpu6050_data)
#define MPU6050_GET_TEMP _IOR('k',1,struct mpu6050_data)
#define MPU6050_GET_ACCEL _IOR('K',2,struct mpu6050_data)


