/******************************************************************************
  * @file    tick.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-27
  * @brief   ��ʱ����ش���
	* @attention ���� TICK_TIM_Init(); ��ɳ�ʼ��
*******************************************************************************/

#include "tick.h"
#include "control.h"
#include "usart1.h"

/**************************************************************
 *@brief	�߼���ʱ�� ����ģʽ���ж� ����
 *@param	
 *@retval
 *@addition	
**************************************************************/
void TICK_TIM_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	//������ʱ����ص�����ʱ��
	TICK_TIM_RCC_ENABLE;

	//����
  TIM_TimeBaseStructure.TIM_Period = TICK_TIM_Period;
	//Ԥ��Ƶϵ��
  TIM_TimeBaseStructure.TIM_Prescaler = TICK_TIM_Period;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  // �ظ�������
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��TIM4
	TIM_TimeBaseInit(TICK_TIM, &TIM_TimeBaseStructure);
	//����жϱ�־λ 
	TIM_ClearFlag(TICK_TIM, TIM_FLAG_Update); 
	//ʹ��ָ����TIM�ж�   �������ж�Դ �����ж�Դ
	TIM_ITConfig(TICK_TIM, TIM_IT_Update , ENABLE);         
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;	//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;				//�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
		
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TICK_TIM, ENABLE);	
}

/***************************************************************
 *@brief TIM8 �жϴ�����
 *@param
 *@retval
 *@addition
****************************************************************/
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TICK_TIM, TIM_IT_Update) != RESET)
  {
		//�������Ҫ������
		TimeSlice.Count_20ms += 10;
		TimeSlice.Count_50ms += 10;
		TimeSlice.Count_100ms += 10;
		TimeSlice.Count_200ms += 10;
		TimeSlice.Count_5000ms += 10;
		TIM_ClearITPendingBit(TICK_TIM, TIM_IT_Update);
  }
}
