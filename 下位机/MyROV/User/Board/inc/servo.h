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

//ͨ��1 �����������̨λ�õĶ��
#define FinTail_Advance_GPIO_PIN          			GPIO_Pin_6            
#define FinTail_Advance_GPIO_PORT       				GPIOC                      
#define FinTail_Advance_GPIO_PINSOURCE					GPIO_PinSource6
#define FinTail_Advance_GPIO_AF									GPIO_AF_TIM8

//ͨ��2 ����β���ƽ��Ķ��
#define Camera_Position_GPIO_PIN          			GPIO_Pin_7            
#define Camera_Position_GPIO_PORT       				GPIOC                      
#define Camera_Position_GPIO_PINSOURCE					GPIO_PinSource7
#define Camera_Position_GPIO_AF									GPIO_AF_TIM8



/********************************************������ݽṹ��********************************************/
typedef struct
{
  uint16_t FinTail_Advance_StartingPosition;  //β���ƽ���� ��ʼλ��
  uint16_t FinTail_Advance_EndingPosition;    //β���ƽ���� ��ֹλ��
  uint16_t FinTail_Advance_EachCCR;           //β���ƽ���� ÿ�θı��ռ�ձ�
  uint16_t FinTail_Advance_DelayTime;         //β���ƽ���� ��ʱ����

	uint16_t FinLeft_Attitude_Position;   			//���������̬��� ��ֹλ��

	uint16_t FinLeft_Thrash_StartingPosition;   //���������ˮ��� ��ʼλ��
  uint16_t FinLeft_Thrash_EndingPosition;     //���������ˮ��� ��ֹλ��
  uint16_t FinLeft_Thrash_Down_EachCCR;       //���������ˮ��� ������ˮʱ ÿ�θı��ռ�ձ�
  uint16_t FinLeft_Thrash_Down_DelayTime;     //���������ˮ��� ������ˮʱ ��ʱ����
  uint16_t FinLeft_Thrash_Up_EachCCR;         //���������ˮ��� ������ˮʱ ÿ�θı��ռ�ձ�
  uint16_t FinLeft_Thrash_Up_DelayTime;       //���������ˮ��� ������ˮʱ ��ʱ����        

  uint16_t FinRight_Attitude_Position;  			//�Ҳ�������̬��� ��ֹλ��

  uint16_t FinRight_Thrash_StartingPosition;  //�Ҳ�������ˮ��� ��ʼλ��
  uint16_t FinRight_Thrash_EndingPosition;    //�Ҳ�������ˮ��� ��ֹλ��
  uint16_t FinRight_Thrash_Down_EachCCR;      //�Ҳ�������ˮ��� ������ˮʱ ÿ�θı��ռ�ձ�
  uint16_t FinRight_Thrash_Down_DelayTime;    //�Ҳ�������ˮ��� ������ˮʱ ��ʱ����
  uint16_t FinRight_Thrash_Up_EachCCR;        //�Ҳ�������ˮ��� ������ˮʱ ÿ�θı��ռ�ձ�
  uint16_t FinRight_Thrash_Up_DelayTime;      //�Ҳ�������ˮ��� ������ˮʱ ��ʱ����    

  uint16_t Camera_Position;                   //�������̨��� λ��  
}SERVO_ValTypedef;

extern SERVO_ValTypedef Servo_Val;

typedef struct
{
	int Left[120];
	int Right[120];
	int Len_Left;
	int Len_Left_Down;
	int Len_Left_Up;
	int Len_Right;
	int Len_Right_Down;
	int Len_Right_Up;
}STEP_ValTypedef;

extern STEP_ValTypedef Step_Val;

/********************************************��������********************************************/
extern void TIM1_Init(void);
extern void TIM8_Init(void);
extern void Servo_PositionSet(void);
extern void Servo_WorkingLoop(void);
extern void Servo_Reset(void);
extern void Servo_Calculation(void);
#endif
