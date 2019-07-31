/******************************************************************************
  * @file    timeslice.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-5-1
  * @brief   ʱ��Ƭ��ѯ
	* @attention ����ѭ���е���ROV_Running();
*******************************************************************************/

#include "timeslice.h"
#include "control.h"
#include "MS5837.h"
#include "servo.h"
#include "PID.h"
#include "datapocket.h"
#include "usart1.h"


/*****************************************************
 * @brief  ʱ��Ƭ��ѯ����
 * @param  
 * @retval 
 * @addition	ÿ20ms PID�ջ��������
							ÿ50ms 
							ÿ100ms ��ȡMS5837���ݣ��ϴ�һ��MS5837��JY901����
							ÿ200ms �ϴ�һ�ζ������
							ÿ5000ms �ϴ�PIDϵ��
******************************************************/
void SpecialAction(void)
{
	if (TimeSlice.Count_20ms>=20)
	{
		TimeSlice.Count_20ms = 0;
		Loop_20ms();
	}
	
	if (TimeSlice.Count_50ms>=50)
	{
		TimeSlice.Count_50ms = 0;
		Loop_50ms();
	}
		
	if (TimeSlice.Count_100ms>=100)
	{
		TimeSlice.Count_100ms = 0;
		Loop_100ms();
	}
		
	if (TimeSlice.Count_200ms>=200)
	{
		TimeSlice.Count_200ms = 0;
		Loop_200ms();
	}
		
	if (TimeSlice.Count_5000ms>=5000)
	{
		TimeSlice.Count_5000ms = 0;
//		Loop_5000ms();
	}
}


/*****************************************************
 * @brief  ÿ20ms PID�ջ��������
 * @param  
 * @retval 
 * @addition
******************************************************/
void Loop_20ms(void)
{
	if (Mode_Val.Control_mode==1) ClosedLoop_Control();
}


/*****************************************************
 * @brief  ÿ50ms �������ж���Ĳ���
 * @param  
 * @retval 
 * @addition
******************************************************/
void Loop_50ms(void)
{

}


/*****************************************************
 * @brief  ÿ100ms ��ȡMS5837���ݣ��ϴ�һ��MS5837��JY901����
 * @param  
 * @retval 
 * @addition
******************************************************/
void Loop_100ms(void)
{
	MS5837_Read();
	PackDataUp(TX_StartBit_JY901);
	PackDataUp(TX_StartBit_MS5837);
}


/*****************************************************
 * @brief  ÿ200ms �ϴ�һ�ζ������
 * @param  
 * @retval 
 * @addition
******************************************************/
void Loop_200ms(void)
{
	PackDataUp(TX_StartBit_SERVO);
}


/*****************************************************
 * @brief  ÿ5000ms �ϴ�һ�ζ������
 * @param  
 * @retval 
 * @addition
******************************************************/
void Loop_5000ms(void)
{
	PackDataUp(TX_StartBit_PID);
}
