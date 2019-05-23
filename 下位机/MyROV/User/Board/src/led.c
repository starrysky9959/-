/******************************************************************************
  * @file    led.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-34
  * @brief   LED����ش���
	* @attention ����LED_Init();��ɳ�ʼ��
							 ������ƵƲμ�led.h
*******************************************************************************/
#include "led.h"   

/**************************************************************
 *@brief	LED�Ƴ�ʼ��
 *@param	
 *@retval
 *@addition	
**************************************************************/
void LED_Init(void)
{		
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//����LED��ص�GPIO����ʱ��
	RCC_AHB1PeriphClockCmd ( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE); 
														   
	GPIO_InitStructure.GPIO_Pin = LED1_PIN;							//ѡ��Ҫ���Ƶ�GPIO����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   		//��������ģʽΪ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	    //�������ŵ��������Ϊ�������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			  //��������Ϊ����ģʽ 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  //������������Ϊ2MHz

	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	//���ÿ⺯����ʹ���������õ�GPIO_InitStructure��ʼ��GPIO
  
	//ͬ������LED2��LED3										   
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;	
  GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);	
														   
	GPIO_InitStructure.GPIO_Pin = LED3_PIN;	
  GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);	
	//�ص�
	LED1_OFF;
	LED2_OFF;
	LED3_OFF;	
}
