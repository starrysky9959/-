/******************************************************************************
  * @file    stepper.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-7-23
  * @brief   ��ʱ����ش���
	* @attention ���� Stepper_Init(); ��ɳ�ʼ��
*******************************************************************************/
#include "stm32f4xx.h"  
#include "stepper.h"
#include "systick.h"

extern int32_t current_pos;
/**************************************************************
 *@brief	�������� EN��DIR������IO�ڳ�ʼ��
 *@param
 *@retval
 *@addition	PC0��EN+  ����ѻ���������
						PC1��DIR+ ���������ת��������
						���ѻ����ܺ󣬵��ת�Ӵ������ɲ�����״̬����������ת������ʱ���������źŲ���Ӧ���رմ��źź������������ź�������ת��
**************************************************************/
void Stepper_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	STEPPER_RCC_ENABLE;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 	  //����GPIO�ܽ�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;			//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;				//����
	GPIO_Init(GPIOA, &GPIO_InitStructure); 										//��ʼ��GPIO
	
	GPIO_SetBits(GPIOA, GPIO_Pin_9);													//����ߵ�ƽ ˳ʱ����ת
	GPIO_SetBits(GPIOA, GPIO_Pin_10);	
}


/**************************************************************
 *@brief	���ָ����������ʹ���������ָ��������ת
 *@param	dir������
					num��������
 *@retval
 *@addition	
**************************************************************/
void Direction(int32_t dir, int32_t num)
{
	int32_t i;
	switch (dir)
	{
		case (ACW):	//��ʱ��
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_9);			//��ʱ��
			for(i = 0; i < num; i++) 						// 1000 ������
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);  //����͵�ƽ
				delay_us(30);
				GPIO_SetBits(GPIOA, GPIO_Pin_10);		//����ߵ�ƽ
				delay_us(30);
			}
			current_pos -= num;
			GPIO_ResetBits(GPIOA, GPIO_Pin_10); 		//��ͣ
			break;
		}
		
		case (CW):	//˳ʱ��
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);			//˳ʱ��
			for(i = 0; i < num; i++) 						// 1000 ������
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_10);  //����͵�ƽ
				delay_us(30);
				GPIO_SetBits(GPIOA, GPIO_Pin_10);		//����ߵ�ƽ
				delay_us(30);
			}
			current_pos += num;
			GPIO_ResetBits(GPIOA, GPIO_Pin_10); 		//��ͣ
			break;
		}	
	}
}


/**************************************************************
 *@brief	ʹ���ת����ָ��λ��
 *@param	
 *@retval
 *@addition	
**************************************************************/
void AbsPosition(int32_t pos)
{
	if (pos < current_pos)
	{
		Direction(ACW, current_pos - pos);
	}else
	{
		Direction(CW, pos - current_pos);
	}
}
