#ifndef  __MS5837_H
#define  __MS5837_H

#include "stm32f4xx.h"
#include "I2C.h"

/********************************************�궨��********************************************/
#define MS5837_ADDRESS		0xec

#define 		MS5837_ReadBuffer			I2C_ReadBuffer//�궨�屾.c�ļ���IIC��ȡΪI2C_simu.c�ļ��ж�ȡ����
#define			MS5837_WriteBuffer		I2C_WriteBuffer//�궨�屾.c�ļ���IIC��ȡΪI2C_simu.c�ļ��ж�ȡ����
#define			MS5837_ReadByte				I2C_Single_Read//�궨�屾.c�ļ���IIC��ȡΪI2C_simu.c�ļ��ж�ȡ����
#define			MS5837_WriteByte			I2C_Single_Write//�궨�屾.c�ļ���IIC��ȡΪI2C_simu.c�ļ��ж�ȡ����

/********************************************MS5837���ݽṹ��********************************************/
typedef struct 
{
	float depth;
	float temp;
	float pressure;
	float offset;
}MS5837_ValueTypeDef;
extern MS5837_ValueTypeDef MS5837_Val;

/********************************************��������********************************************/
extern void MS5837_Init(void);
extern void MS5837_Read(void);
extern float MS5837_pressure(float conversion);
extern float MS5837_temperature(void);
extern float MS5837_depth(void);
extern void MS5837_SetOffset(float offset);
#endif

