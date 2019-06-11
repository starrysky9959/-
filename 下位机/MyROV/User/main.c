/******************************************************************************
  * @file    main.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-24
  * @brief   �ҵ�ROV��λ�����������һ�г�ʼ�������ܷ������ݣ���ָ���ж�
	* @attention �д��ڣ���ʱ��JY901��̬��������MS5837��ȴ���������ʱ��
*******************************************************************************/
  
#include "stm32f4xx.h"
#include "usart1.h" 
#include "usart2.h"
#include "systick.h"
#include "servo.h"
#include "JY901.h"
#include "tick.h"
#include "MS5837.h"
#include "timeslice.h"
#include "control.h"
#include "datapocket.h"

SERVO_ValTypedef 	 Servo_Val={0};
JY901_ValTypedef	 JY901_Val={0};
Mode_ValTypedef 	 Mode_Val={0};
STEP_ValTypedef 	 Step_Val={0};
struct TS TimeSclice={0};
/**************************************************************
 * @brief	������
 * @param
 * @retval
 * @addition
**************************************************************/
int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	SysTick_Init();	//��ʱ������ʼ��
  USART1_Init(115200);  //��ʼ��USART1 ��λ��<����>PC��
	USART2_Init(9600);		//��ʼ��USART2	JY901����>��λ��
	TIM1_Init();					//�����ض�ʱ����ʼ��
	TIM8_Init();					//�����ض�ʱ����ʼ��
	MS5837_Init();				//��ȴ�������ʼ��
	Servo_Reset();				//���λ�ó�ʼ��
	//Servo_Calculation();  //�������ֵ����
	TICK_TIM_Init();			//��ʱ�Ķ�ʱ����ʼ��

	//������
	while (1)
	{				
//		TIM_SetCompare2(TIM1,  3400);
//			delay_ms(1000);
//		TIM_SetCompare1(TIM1, 4400);
//		delay_ms(1000);
		//Servo_PositionSet();	//���λ�ø���
		Servo_WorkingLoop();	//����ڶ�
	}
}
