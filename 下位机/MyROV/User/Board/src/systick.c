/******************************************************************************
  * @file    systick.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-34
  * @brief   ϵͳ��ʱ����ش���
	* @attention SysTick_Init(); ���ü���
*******************************************************************************/

#include "systick.h"

static __IO u32 TimingDelay;
 
/*****************************************************
 * @brief  ����ϵͳ�δ�ʱ�� SysTick
 * @param  
 * @retval 
 * @addition
******************************************************/
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms�ж�һ��
	 * SystemFrequency / 100000	 10us�ж�һ��
	 * SystemFrequency / 1000000 1us�ж�һ��
	 */
	if (SysTick_Config(SystemCoreClock / 100000))
	{ 
		/* Capture error */ 
		while (1);
	}
}


/*****************************************************
 * @brief  us��ʱ����,10usΪһ����λ
 * @param  
	 	 @arg	 nTime: Delay_us( 1 ) ��ʵ�ֵ���ʱΪ 1 * 10us = 10us
 * @retval 
 * @addition
******************************************************/
void delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}


/*****************************************************
 * @brief  ��ȡ���ĳ���
 * @param  
 * @retval 
 * @addition	�� SysTick �жϺ��� SysTick_Handler()����
******************************************************/
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
