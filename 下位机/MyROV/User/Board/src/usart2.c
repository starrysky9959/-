/******************************************************************************
  * @file    usart2.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-24
  * @brief   ����2��ش��� JY901��
	* @attention ����USART2_Init(9600);��ɳ�ʼ��
*******************************************************************************/
 
#include "usart2.h"
#include "JY901.h"

/**************************************************************
 *@brief	USART2��GPIO�빤��ģʽ����
 *@param	
 *@retval
 *@addition	
**************************************************************/
void USART2_Init(int baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	//���ʱ��ʹ��
	USART2_RCC_ENABLE;
	
  //GPIO��ʼ��
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //����Tx����Ϊ���ù���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  USART2_TX_PIN  ;  
  GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  //����Rx����Ϊ���ù���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  USART2_RX_PIN;
  GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);

  //���� PXx �� USARTx_Tx
  GPIO_PinAFConfig(USART2_TX_GPIO_PORT,USART2_TX_SOURCE,USART2_TX_AF);
  
	//���� PXx �� USARTx_Rx
  GPIO_PinAFConfig(USART2_RX_GPIO_PORT,USART2_RX_SOURCE,USART2_RX_AF);


  //����ģʽ����
  //����������
  USART_InitStructure.USART_BaudRate = baudrate;
  //�ֳ�(����λ+У��λ)
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
  //ֹͣλ
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  //У��λѡ��
	USART_InitStructure.USART_Parity = USART_Parity_No;
  //Ӳ��������
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  //USARTģʽ����	USART_ITConfig(DEBUG_USART, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //���USART��ʼ������
  USART_Init(USART2, &USART_InitStructure);
	//�������ڽ����ж�
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	
  //ʹ�ܴ���
  USART_Cmd(USART2, ENABLE);
	
	//�ж�����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}



/***************************************************************
 *@brief USART2 �жϴ�����
 *@param
 *@retval
 *@addition
****************************************************************/

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
		JY901_DataReceive((uint8_t)USART_ReceiveData(USART2));//��������
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  }
}



