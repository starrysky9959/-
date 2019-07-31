#ifndef __SERVO_H
#define	__SERVO_H

#include "stm32f4xx.h"

/********************************************�궨��********************************************/
//TIM1 ��ʱ�� 
#define TIM1_RCC_ENABLE  												RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);\
																								RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE)																		

#define TIM1_Period															(20000-1)
#define TIM1_Prescaler 													(180-1)

//ͨ��1 �Ҳ���ƻ�ˮ���������
#define FinLeft_Attitude_GPIO_PIN          			GPIO_Pin_8             
#define FinLeft_Attitude_GPIO_PORT       				GPIOA                      
#define FinLeft_Attitude_GPIO_PINSOURCE					GPIO_PinSource8
#define FinLeft_Attitude_GPIO_AF								GPIO_AF_TIM1

//ͨ��2 �����ƻ�ˮ���������
#define FinLeft_Thrash_GPIO_PIN          				GPIO_Pin_9             
#define FinLeft_Thrash_GPIO_PORT       					GPIOA                      
#define FinLeft_Thrash_GPIO_PINSOURCE						GPIO_PinSource9
#define FinLeft_Thrash_GPIO_AF									GPIO_AF_TIM1

//ͨ��3 �Ҳ������̬���������
#define FinRight_Attitude_GPIO_PIN          		GPIO_Pin_10            
#define FinRight_Attitude_GPIO_PORT       			GPIOA                  
#define FinRight_Attitude_GPIO_PINSOURCE				GPIO_PinSource10
#define FinRight_Attitude_GPIO_AF								GPIO_AF_TIM1

//ͨ��4 ��������̬���������
#define FinRight_Thrash_GPIO_PIN          			GPIO_Pin_11          
#define FinRight_Thrash_GPIO_PORT       				GPIOA                      
#define FinRight_Thrash_GPIO_PINSOURCE					GPIO_PinSource11
#define FinRight_Thrash_GPIO_AF									GPIO_AF_TIM1


//TIM8 ��ʱ��
#define TIM8_RCC_ENABLE       		   						RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);\
																								RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);																				

#define TIM8_Period															(20000-1)
#define TIM8_Prescaler 													(180-1)

//ͨ��2 �����������̨λ�õĶ��
#define Camera_Position_GPIO_PIN          			GPIO_Pin_7           
#define Camera_Position_GPIO_PORT       				GPIOC                      
#define Camera_Position_GPIO_PINSOURCE					GPIO_PinSource7
#define Camera_Position_GPIO_AF									GPIO_AF_TIM8

//ͨ��3 ����β�������ǰ��
#define FinTail_Front_GPIO_PIN          				GPIO_Pin_8       
#define FinTail_Front_GPIO_PORT       					GPIOC                      
#define FinTail_Front_GPIO_PINSOURCE						GPIO_PinSource8
#define FinTail_Front_GPIO_AF										GPIO_AF_TIM8

//ͨ��4 ����β���������
#define FinTail_Rear_GPIO_PIN          					GPIO_Pin_9            
#define FinTail_Rear_GPIO_PORT       						GPIOC                      
#define FinTail_Rear_GPIO_PINSOURCE							GPIO_PinSource9
#define FinTail_Rear_GPIO_AF										GPIO_AF_TIM8

/********************************************������ݽṹ��********************************************/
typedef struct
{
	uint16_t FinTail_Front_StartingPosition;  		//β�������ǰ�� ��ʼλ��
  uint16_t FinTail_Front_EndingPosition;    		//β�������ǰ�� ��ֹλ��
  uint16_t FinTail_Front_EachCCR;           		//β�������ǰ�� ÿ�θı��ռ�ձ�
  uint16_t FinTail_Front_DelayTime;         		//β�������ǰ�� ��ʱ����
		
	uint16_t FinTail_Rear_StartingPosition; 	 		//β��������� ��ʼλ��
  uint16_t FinTail_Rear_EndingPosition;    			//β��������� ��ֹλ��
  uint16_t FinTail_Rear_EachCCR;           			//β��������� ÿ�θı��ռ�ձ�
  uint16_t FinTail_Rear_DelayTime;         			//β��������� ��ʱ����
	
  uint16_t Camera_Position;                   //�������̨��� λ�� 
	uint16_t Pulse_Num;                         	//������
}SERVO_ValTypedef;

extern SERVO_ValTypedef Servo_Val;


/********************************************��������********************************************/
extern void TIM1_Init(void);
extern void TIM8_Init(void);
extern void Servo_PositionSet(void);
extern void Servo_WorkingLoop(void);
extern void Servo_Reset(void);
#endif
