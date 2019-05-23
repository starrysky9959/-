#ifndef __TICK_H
#define __TICK_H

#include "stm32f4xx.h"
/********************************************�궨��********************************************/
//��ʱ��
#define TICK_TIM_RCC_ENABLE       		   		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);																				
#define TICK_TIM           		    					TIM4

#define TICK_TIM_Period											(1000-1)
#define TICK_TIM_Prescaler 									(720-1)

/********************************************��������********************************************/
extern void TICK_TIM_Init(void);

#endif
