#ifndef __AHRS_H
#define __AHRS_H

#include "stm32f10x.h"

#define SAMPLE_HALF_T 0.001f     //采样周期的一半，单位：s
#define FILTER_LENGTH 10					//滑动滤波窗口长度

#define GYRO_G 	0.0610351f				//角速度变成度/S   此参数对应陀螺2000度每秒  Gyro_G=1/16.375=0.0610687
#define GYRO_GR	0.0010653f				//角速度变成弧度/S	此参数对应陀螺2000度每秒

#define IMU_KP /*1.5f */  0 					//比例
#define IMU_KI /*0.002f*/ 0						//积分

typedef struct
{
	float X;
	float Y;
	float Z;
}S_FLOAT_XYZ;

extern volatile S_FLOAT_XYZ Angle;

void Geographic_Coordinate_ReadValue(void);
void Prepare_Data(void);
void IMU_Update(void);
void AHRS_Date_Init(void);

#endif


