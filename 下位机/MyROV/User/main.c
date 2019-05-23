/******************************************************************************
  * @file    main.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-24
  * @brief   �հ׹���ģ��
	* @attention �д��ڣ���ʱ��LED�ƣ�PWM���
*******************************************************************************/
  
#include "stm32f4xx.h"
#include "led.h" 
#include "usart1.h" 
#include "usart2.h"
#include "systick.h"
#include "servo.h"
#include "JY901.h"
#include "tick.h"
#include "MS5837.h"
#include "timeslice.h"
#include "control.h"

SERVO_ValTypedef 	 Servo_Val={0};
JY901_ValTypedef	 JY901_Val={0};
Mode_ValTypedef 	 Mode_Val={0};

/**************************************************************
 *@brief	������
 *@param
 *@retval
 *@addition
**************************************************************/
int main(void)
{	
	//int i=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	SysTick_Init();	//��ʱ������ʼ��
  //LED_Init();			//��ʼ��RGB�ʵ�
	//LED1_ON;
  USART1_Init(115200);  //��ʼ��USART3 ��λ��<����>PC��
	USART2_Init(9600);		//��ʼ��USART2	JY901����>��λ��
	TIM1_Init();
	TIM8_Init();
	TICK_TIM_Init();
	MS5837_Init();
	while (1)
	{
		Servo_WorkingLoop();	//����ڶ�
		SpecialAction();			//��ʱ�������⶯��
	}

}
