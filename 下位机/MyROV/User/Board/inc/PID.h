#ifndef __PID_H
#define __PID_H

#include "stm32f4xx.h"

/********************************************* PID �ṹ��********************************************/
struct PID
{
	float P;						//�����������
	float I;						//���ֵ������
	float D;						//΢�ֵ������
	float Kp;						//����ϵ��
	float Ki;						//����ϵ��
	float Kd;						//΢��ϵ��
	float CurrentError; //����ƫ��ֵ
	float LastError;		//�ϴ�ƫ��ֵ
	float dError;				//΢��ƫ��
	float CurrentValue; //��ǰֵ
	float SetValue;			//�趨ֵ
	float MaxOut;				//���ض����������
	float IMax;					//�������ֵ
	float Out;					//���ض�������
	float FuzzyInterval;//ģ������
};
/************************************************��������*********************************************/

extern void PID_Init(struct PID *pidData, float Kp, float Ki, float Kd, float MaxOut, float IMax, float FuzzInterval);
extern float Limitation(float Ans, float max, float min);
extern void Calculate(struct PID *pidData);
extern void ResetPID(struct PID *pidData);
extern void ResetI(struct PID *pidData);
extern void DebugPID(struct PID *pidData, char *pFlag);

#endif
