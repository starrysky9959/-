/******************************************************************************
  * @file    servo.c
  * @author  ½չ
  * @version V1.0
  * @date    2019-4-24
  * @brief   ��ʱ����ش���
	* @attention ����TIM1_Init();TIM8_Init();��ɳ�ʼ��
*******************************************************************************/

#include "servo.h"
#include "systick.h"
#include "timeslice.h"
/**************************************************************
 * @brief	TIM1 ��ʱ�� GPIO�빤��ģʽ����
 * @param	
 * @retval
 * @addition	
**************************************************************/
void TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//������ص� GPIO��TIM1 ʱ��
	TIM1_RCC_ENABLE;

	//��ʱ��ͨ���������� 														   
	GPIO_InitStructure.GPIO_Pin = FinLeft_Attitude_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(FinLeft_Attitude_GPIO_PORT, &GPIO_InitStructure);
	
	//�������ţ���������ͨ��
	GPIO_InitStructure.GPIO_Pin = FinLeft_Thrash_GPIO_PIN;	
	GPIO_Init(FinLeft_Thrash_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = FinRight_Attitude_GPIO_PIN;	
	GPIO_Init(FinRight_Attitude_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = FinRight_Thrash_GPIO_PIN;	
	GPIO_Init(FinRight_Thrash_GPIO_PORT, &GPIO_InitStructure);	
	
  //��ʱ��ͨ�����Ÿ��� 
	GPIO_PinAFConfig(FinLeft_Attitude_GPIO_PORT,  FinLeft_Attitude_GPIO_PINSOURCE, 	FinLeft_Attitude_GPIO_AF); 
	GPIO_PinAFConfig(FinLeft_Thrash_GPIO_PORT, 	  FinLeft_Thrash_GPIO_PINSOURCE, 		FinLeft_Thrash_GPIO_AF); 
	GPIO_PinAFConfig(FinRight_Attitude_GPIO_PORT, FinRight_Attitude_GPIO_PINSOURCE, FinRight_Attitude_GPIO_AF); 
	GPIO_PinAFConfig(FinRight_Thrash_GPIO_PORT, 	FinRight_Thrash_GPIO_PINSOURCE, 	FinRight_Thrash_GPIO_AF);	
	//����ģʽ����
	//����
  TIM_TimeBaseStructure.TIM_Period = TIM1_Period;       
	//Ԥ��Ƶϵ��
  TIM_TimeBaseStructure.TIM_Prescaler = TIM1_Prescaler;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	//PWMģʽ����
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;	    				//����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;														//ռ�ձ�
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  	  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);	 							//ʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);			//ʹ��ͨ��1����
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);	 							//ʹ��ͨ��2
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);			//ʹ��ͨ��2����
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);	 							//ʹ��ͨ��3
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);			//ʹ��ͨ��3����
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);	 							//ʹ��ͨ��4
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);			//ʹ��ͨ��4����	
	
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM1, ENABLE);	
	//�������ʹ��
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


/**************************************************************
 * @brief	TIM8 ��ʱ�� GPIO�빤��ģʽ����
 * @param	
 * @retval
 * @addition	
**************************************************************/
void TIM8_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	//������ʱ����ص�GPIO����ʱ��
	TIM8_RCC_ENABLE;

  //ָ�����Ÿ��ù��� 
	GPIO_PinAFConfig(FinTail_Advance_GPIO_PORT,FinTail_Advance_GPIO_PINSOURCE, FinTail_Advance_GPIO_AF); 
	GPIO_PinAFConfig(Camera_Position_GPIO_PORT,Camera_Position_GPIO_PINSOURCE, Camera_Position_GPIO_AF); 
	
	//��ʱ��ͨ���������� 														   
	GPIO_InitStructure.GPIO_Pin = FinTail_Advance_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_Init(FinTail_Advance_GPIO_PORT, &GPIO_InitStructure);
	
	//�������ţ���������ͨ��
	GPIO_InitStructure.GPIO_Pin = Camera_Position_GPIO_PIN;		
	GPIO_Init(Camera_Position_GPIO_PORT, &GPIO_InitStructure);
	
	//����
  TIM_TimeBaseStructure.TIM_Period = TIM8_Period;
	//Ԥ��Ƶϵ��
  TIM_TimeBaseStructure.TIM_Prescaler = TIM8_Prescaler;	
  // ����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  // ������ʽ
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  // �ظ�������
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��TIMx, x[1,8]
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);
	
  //PWMģʽ����
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

  TIM_OC1Init(TIM8, &TIM_OCInitStructure);	   			//ʹ��ͨ��1
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);	//ʹ��ͨ��1����
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);	   			//ʹ��ͨ��2
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);	//ʹ��ͨ��2����
		
	// ʹ�ܶ�ʱ��
	TIM_Cmd(TIM8, ENABLE);	
	
	//�������ʹ��
  TIM_CtrlPWMOutputs(TIM8, ENABLE);
}


/**************************************************************
 * @brief	���ж��λ�ó�ʼ��
 * @param	
 * @retval
 * @addition	������ʼʱֱ�ӵ���
**************************************************************/
void Servo_Reset()
{
	Servo_Val.FinTail_Advance_EachCCR      = 65;
	Servo_Val.FinLeft_Thrash_Down_EachCCR  = 100; 
	Servo_Val.FinLeft_Thrash_Up_EachCCR    = 100;
	Servo_Val.FinRight_Thrash_Down_EachCCR = 100;
	Servo_Val.FinRight_Thrash_Up_EachCCR   = 100;
	
	Servo_Val.FinTail_Advance_DelayTime			 = 25;
	Servo_Val.FinLeft_Thrash_Down_DelayTime  = 10;
	Servo_Val.FinLeft_Thrash_Up_DelayTime    = 15;
	Servo_Val.FinRight_Thrash_Down_DelayTime = 10;
	Servo_Val.FinRight_Thrash_Up_DelayTime   = 15;
	
	Servo_Val.FinTail_Advance_StartingPosition = 3400;  //β���ƽ���� ��ʼλ��
  Servo_Val.FinTail_Advance_EndingPosition   = 4700;   //β���ƽ���� ��ֹλ��
  Servo_Val.FinLeft_Attitude_Position        = 2650;   			//���������̬��� ��ֹλ��
  Servo_Val.FinLeft_Thrash_StartingPosition	 = 5000;   //���������ˮ��� ��ʼλ��
  Servo_Val.FinLeft_Thrash_EndingPosition		 = 5000;     //���������ˮ��� ��ֹλ��
  Servo_Val.FinRight_Attitude_Position			 = 1700;  			//�Ҳ�������̬��� ��ֹλ��
	Servo_Val.FinRight_Thrash_StartingPosition = 1700;  //�Ҳ�������ˮ��� ��ʼλ��
  Servo_Val.FinRight_Thrash_EndingPosition	 = 3700;    //�Ҳ�������ˮ��� ��ֹλ��
	Servo_Val.Camera_Position									 = 1700;                   //�������̨��� λ��  
	
	TIM_SetCompare1(TIM8, Servo_Val.Camera_Position);
	TIM_SetCompare2(TIM8, Servo_Val.FinTail_Advance_StartingPosition);
	TIM_SetCompare1(TIM1, Servo_Val.FinRight_Thrash_StartingPosition);
	TIM_SetCompare2(TIM1, Servo_Val.FinLeft_Thrash_StartingPosition);
	TIM_SetCompare3(TIM1, Servo_Val.FinRight_Attitude_Position);
	TIM_SetCompare4(TIM1, Servo_Val.FinLeft_Attitude_Position);
}


/**************************************************************
 * @brief	����������������ͷ��̨λ�ø���
 * @param	
 * @retval
 * @addition	������������ֱ�ӵ���Servo_PositionSet();
**************************************************************/
void Servo_PositionSet()
{
	TIM_SetCompare4(TIM1, Servo_Val.FinLeft_Attitude_Position);
	TIM_SetCompare3(TIM1, Servo_Val.FinRight_Attitude_Position);
	TIM_SetCompare1(TIM8, Servo_Val.Camera_Position);
}


/**************************************************************
 * @brief	���������������ݼ���
 * @param	
 * @retval
 * @addition	������������ֱ�ӵ���Servo_Calculation();
**************************************************************/
void Servo_Calculation()
{
	int i,sign;
	//�����
	if (Servo_Val.FinLeft_Thrash_StartingPosition < Servo_Val.FinLeft_Thrash_EndingPosition) 
		   sign = 1;
	else sign = -1;
	Step_Val.Len_Left = 0;
	Step_Val.Len_Left_Down = 0;
	Step_Val.Len_Left_Up = 0;
	//����������ʱ�Ĳ���ֵ
	i = Servo_Val.FinLeft_Thrash_StartingPosition;
	while (i != Servo_Val.FinLeft_Thrash_EndingPosition)
	{
		Step_Val.Len_Left++;
		Step_Val.Len_Left_Down++;
		Step_Val.Left[Step_Val.Len_Left] = i;
		i += sign*Servo_Val.FinLeft_Thrash_Down_EachCCR;
	}
	//����������ʱ�Ĳ���ֵ
	sign = (-1)*sign;
	i = Servo_Val.FinLeft_Thrash_EndingPosition;
	while (i != Servo_Val.FinLeft_Thrash_StartingPosition)
	{
		Step_Val.Len_Left++;
		Step_Val.Len_Left_Up++;
		Step_Val.Left[Step_Val.Len_Left] = i;
		i += sign*Servo_Val.FinLeft_Thrash_Up_EachCCR;
	}
	
	//�Ҳ���
	if (Servo_Val.FinRight_Thrash_StartingPosition < Servo_Val.FinRight_Thrash_EndingPosition) 
		   sign = 1;
	else sign = -1;
	Step_Val.Len_Right = 0;
	Step_Val.Len_Right_Down = 0;
	Step_Val.Len_Right_Up = 0;
	//����������ʱ�Ĳ���ֵ
	i = Servo_Val.FinRight_Thrash_StartingPosition;
	while (i != Servo_Val.FinRight_Thrash_EndingPosition)
	{
		Step_Val.Len_Right++;
		Step_Val.Len_Right_Down++;
		Step_Val.Right[Step_Val.Len_Right] = i;
		i += sign*Servo_Val.FinRight_Thrash_Down_EachCCR;
	}
	//����������ʱ�Ĳ���ֵ
	sign = (-1)*sign;
	i = Servo_Val.FinRight_Thrash_EndingPosition;
	while (i != Servo_Val.FinRight_Thrash_StartingPosition)
	{
		Step_Val.Len_Right++;
		Step_Val.Len_Right_Up++;
		Step_Val.Right[Step_Val.Len_Right] = i;
		i += sign*Servo_Val.FinRight_Thrash_Up_EachCCR;
	}
}
/**************************************************************
 * @brief	����������β�����ѭ���ڶ�
 * @param	
 * @retval
 * @addition	���ض�ʱ�̽����жϣ�����ʱ�䶼��ת�����
							��ʵ������� StartingPosition �� EndingPosition �Ĵ�С�ı�����
**************************************************************/
void Servo_WorkingLoop()
{
	int i,j,k;
//	int tot;
//	
//	tot = 0;
//	i = Servo_Val.FinTail_Advance_StartingPosition;

//	
//	//β���ƽ�������˶�
//	while (tot < 20)
//	{
//		TIM_SetCompare2(TIM8, i);
//		i += Servo_Val.FinTail_Advance_EachCCR;
//		tot++;
//		delay_ms(Servo_Val.FinTail_Advance_DelayTime);
//	}
//	
//	tot = 0;
//	i = Servo_Val.FinTail_Advance_EndingPosition;
//	
//	//β���ƽ�������˶�
//	while (tot < 20)
//	{
//		TIM_SetCompare2(TIM8, i);
//		i -= Servo_Val.FinTail_Advance_EachCCR;
//		tot++;
//		delay_ms(Servo_Val.FinTail_Advance_DelayTime);
//	}
//	
	for (i = Servo_Val.FinTail_Advance_StartingPosition; i <= Servo_Val.FinTail_Advance_EndingPosition; i += Servo_Val.FinTail_Advance_EachCCR) 	
	{
		TIM_SetCompare2(TIM8, i);
		delay_ms(Servo_Val.FinTail_Advance_DelayTime);
	}
	for (i = Servo_Val.FinTail_Advance_EndingPosition; i >= Servo_Val.FinTail_Advance_StartingPosition; i -= Servo_Val.FinTail_Advance_EachCCR) 	
	{
		TIM_SetCompare2(TIM8, i);
		delay_ms(Servo_Val.FinTail_Advance_DelayTime);
	}

}
