/******************************************************************************
  * @file    USART1.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-24
  * @brief   ����3��ش���
	* @attention ����USART1_Init(115200);��ɳ�ʼ��
*******************************************************************************/
 
#include "USART1.h"
#include "datapocket.h"

/**************************************************************
 *@brief	USART1��GPIO�빤��ģʽ����
 *@param	
 *@retval
 *@addition	
**************************************************************/
void USART1_Init(int baudrate)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure; 
	
	//���ʱ��ʹ��
	USART1_RCC_ENABLE;
	
  //GPIO��ʼ��
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  
  //����Tx����Ϊ���ù���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  USART1_TX_PIN  ;  
  GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

  //����Rx����Ϊ���ù���
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin =  USART1_RX_PIN;
  GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

  //���� PXx �� USARTx_Tx
  GPIO_PinAFConfig(USART1_TX_GPIO_PORT,USART1_TX_SOURCE,USART1_TX_AF);
  
	//���� PXx �� USARTx_Rx
  GPIO_PinAFConfig(USART1_RX_GPIO_PORT,USART1_RX_SOURCE,USART1_RX_AF);


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
  //USARTģʽ����	
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //���USART��ʼ������
  USART_Init(USART1, &USART_InitStructure);
	//�������ڽ����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
  //ʹ�ܴ���
  USART_Cmd(USART1, ENABLE);
	
	//�ж�����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
}


/****************************************************************
 *@brief ���һ���ַ�
 *@param DataToSend��Ҫ���͵��ַ�
 *@retval
 *@addition
*****************************************************************/
void USART1_PutChar(char ch)
{
	USART_SendData(USART1, (unsigned char) ch);
	while (!(USART1->SR & USART_FLAG_TXE));
}


/***************************************************************
 *@brief USART1 �жϴ�����
 *@param
 *@retval
 *@addition
****************************************************************/
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
		Command_ReceiveAndCheck(USART_ReceiveData(USART1));	//����1���յ���λ�������Ŀ���ָ�� 			
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
	USART_ClearITPendingBit(USART1,USART_IT_ORE);
}

/**************************************************************
 *@brief	�ض���c�⺯��printf������
 *@param	
 *@retval
 *@addition	�ض�����ʹ��printf����
**************************************************************/
int fputc(int ch, FILE *f)
{
	//����һ���ֽ����ݵ�����
	USART_SendData(USART1, (uint8_t) ch);
		
	//�ȴ��������
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
	return (ch);
}
/**************************************************************
 *@brief	�ض���c�⺯��scanf������
 *@param	
 *@retval
 *@addition	��д����ʹ��scanf��getchar�Ⱥ���
**************************************************************/
int fgetc(FILE *f)
{
		//�ȴ�������������
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}
