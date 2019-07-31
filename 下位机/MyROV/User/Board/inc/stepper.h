#ifndef __STEPPER_H
#define __STEPPER_H 			   
#include "stm32f4xx.h"

/********************************************�궨��********************************************/
#define STEPPER_RCC_ENABLE 						RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//��ת����
#define CW														0
#define ACW														1

/********************************************��������********************************************/
extern void Stepper_Init(void);
extern void Direction(int dir, int num);
extern void AbsPosition(int pos);
#endif

