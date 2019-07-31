#include "string.h"
#include "stdio.h"
#include "usart1.h"
#include "datapocket.h"
#include "JY901.h"
#include "servo.h"
#include "systick.h"
#include "control.h"
#include "MS5837.h"
#include "stepper.h"

/**************************************************************
 * @brief ������ʼ��startbit������λ��������Ӧ��ROV������Ϣ
 * @param startbit����ʼλ
 * @retval
 * @addition
**************************************************************/
void PackDataUp(uint8_t startbit)
{
	uint8_t i;
	uint8_t checkbit=(0x00)^startbit;	//У��λ
	TX_JY901_Buff_Union 		TX_JY901_Data;
	TX_MS5837_Buff_Union 		TX_MS5837_Data;
	TX_SEVRO_Buff_Union 		TX_SERVO_Data;
	TX_PID_Buff_Union				TX_PID_Data;

	//������ʼ�뽫���ݴ������
	switch(startbit)
	{
		//�������ͷ��Ӧ JY901
		case(TX_StartBit_JY901):
		{
			//��������ݸ�ֵ������������Ӧ��Ա
			TX_JY901_Data.motiondata.acc_x	 = JY901_Val.acc_x;
			TX_JY901_Data.motiondata.acc_y	 = JY901_Val.acc_y;
			TX_JY901_Data.motiondata.acc_z	 = JY901_Val.acc_z;
			TX_JY901_Data.motiondata.angle_x = JY901_Val.angle_x;
			TX_JY901_Data.motiondata.angle_y = JY901_Val.angle_y;
			TX_JY901_Data.motiondata.angle_z = JY901_Val.angle_z;
			TX_JY901_Data.motiondata.gyro_x	 = JY901_Val.gyro_x;
			TX_JY901_Data.motiondata.gyro_y	 = JY901_Val.gyro_y;
			TX_JY901_Data.motiondata.gyro_z	 = JY901_Val.gyro_z;
			//���ݴ������
			USART1_PutChar(startbit);//��������ͷ
			for(i=0;i<TX_JY901_BUFF_LEN;i++)
			{
				USART1_PutChar(TX_JY901_Data.TX_JY901_BUFF[i]);//���ν���������ÿһ���ֽڷ���
				checkbit ^=TX_JY901_Data.TX_JY901_BUFF[i];//ͬʱ��ÿ���ֽڼӵ�У������
			}		
			USART1_PutChar(checkbit);	//���������֮���У��λ
			break;
		}
		
		
		//�������ͷ��Ӧ MS5837
		case(TX_StartBit_MS5837):
		{
			//��������ݸ�ֵ������������Ӧ��Ա
			TX_MS5837_Data.ms5837data.depth		 = MS5837_Val.depth;
			TX_MS5837_Data.ms5837data.temp		 = MS5837_Val.temp;
			TX_MS5837_Data.ms5837data.pressure = MS5837_Val.pressure;
			TX_MS5837_Data.ms5837data.offset	 = MS5837_Val.offset;
			
			//���ݴ������
			USART1_PutChar(startbit);//��������ͷ
			for(i=0;i<TX_MS5837_BUFF_LEN;i++)
			{
				USART1_PutChar(TX_MS5837_Data.TX_MS5837_BUFF[i]);//���ν���������ÿһ���ֽڷ���
				checkbit ^=TX_MS5837_Data.TX_MS5837_BUFF[i];//ͬʱ��ÿ���ֽڼӵ�У������
			}		
			USART1_PutChar(checkbit);	//���������֮���У��λ
			break;
		}
		
		
		//�������ͷ��Ӧ���
		case(TX_StartBit_SERVO):
		{
			//��������ݸ�ֵ������������Ӧ��Ա
			TX_SERVO_Data.servodata.FinTail_Front_StartingPosition = Servo_Val.FinTail_Front_StartingPosition;  //β�������ǰ�� ��ʼλ��
			TX_SERVO_Data.servodata.FinTail_Front_EndingPosition	 = Servo_Val.FinTail_Front_EndingPosition;    //β�������ǰ�� ��ֹλ��
			TX_SERVO_Data.servodata.FinTail_Front_EachCCR					 = Servo_Val.FinTail_Front_EachCCR;           //β�������ǰ�� ÿ�θı��ռ�ձ�
			TX_SERVO_Data.servodata.FinTail_Front_DelayTime				 = Servo_Val.FinTail_Front_DelayTime;         //β�������ǰ�� ��ʱ����
			
			TX_SERVO_Data.servodata.FinTail_Rear_StartingPosition = Servo_Val.FinTail_Rear_StartingPosition;  //β��������� ��ʼλ��
			TX_SERVO_Data.servodata.FinTail_Rear_EndingPosition	  = Servo_Val.FinTail_Rear_EndingPosition;    //β��������� ��ֹλ��
			TX_SERVO_Data.servodata.FinTail_Rear_EachCCR					= Servo_Val.FinTail_Rear_EachCCR;           //β��������� ÿ�θı��ռ�ձ�
			TX_SERVO_Data.servodata.FinTail_Rear_DelayTime				= Servo_Val.FinTail_Rear_DelayTime;         //β��������� ��ʱ����

			TX_SERVO_Data.servodata.Camera_Position =	Servo_Val.Camera_Position;      //�������̨��� λ�� 
			TX_SERVO_Data.servodata.Pulse_Num = Servo_Val.Pulse_Num;									//������� λ��
			
			//���ݴ������
			USART1_PutChar(startbit);//��������ͷ
			for(i=0;i<TX_SERVO_BUFF_LEN;i++)
			{
				USART1_PutChar(TX_SERVO_Data.TX_SERVO_BUFF[i]);//���ν���������ÿһ���ֽڷ���
				checkbit ^=TX_SERVO_Data.TX_SERVO_BUFF[i];//ͬʱ��ÿ���ֽڼӵ�У������
			}		
			USART1_PutChar(checkbit);	//���������֮���У��λ
			break;
		}
		
		//�������ͷ��ӦPID
		case(TX_StartBit_PID):
		{
			//��������ݸ�ֵ������������Ӧ��Ա
			TX_PID_Data.PID_Parameter.Depth_Kp		 =PID_Depth.Kp;
			TX_PID_Data.PID_Parameter.Depth_Ki		 =PID_Depth.Ki;
			TX_PID_Data.PID_Parameter.Depth_Kd		 =PID_Depth.Kd;
			TX_PID_Data.PID_Parameter.Depth_Target =PID_Depth.SetValue;
			
						
			TX_PID_Data.PID_Parameter.Pitch_Kp		 =PID_Pitch.Kp;
			TX_PID_Data.PID_Parameter.Pitch_Ki		 =PID_Pitch.Ki;
			TX_PID_Data.PID_Parameter.Pitch_Kd		 =PID_Pitch.Kd;
			TX_PID_Data.PID_Parameter.Pitch_Target =PID_Pitch.SetValue;
			
			TX_PID_Data.PID_Parameter.AngleSpeedY_Kp		   =PID_AngleSpeedY.Kp;
			TX_PID_Data.PID_Parameter.AngleSpeedY_Ki		 	 =PID_AngleSpeedY.Ki;
			TX_PID_Data.PID_Parameter.AngleSpeedY_Kd		 	 =PID_AngleSpeedY.Kd;
			TX_PID_Data.PID_Parameter.AngleSpeedY_Target 	 =PID_AngleSpeedY.SetValue;		
			
			TX_PID_Data.PID_Parameter.AccelerationY_Kp		   =PID_AccelerationY.Kp;
			TX_PID_Data.PID_Parameter.AccelerationY_Ki		 	 =PID_AccelerationY.Ki;
			TX_PID_Data.PID_Parameter.AccelerationY_Kd		 	 =PID_AccelerationY.Kd;
			TX_PID_Data.PID_Parameter.AccelerationY_Target 	 =PID_AccelerationY.SetValue;			
			
			//���ݴ������
			USART1_PutChar(startbit);//��������ͷ
			for(i=0;i<TX_PID_BUFF_LEN;i++)
			{
				USART1_PutChar(TX_PID_Data.TX_PID_BUFF[i]);//���ν���������ÿһ���ֽڷ���
				checkbit ^=TX_PID_Data.TX_PID_BUFF[i];//ͬʱ��ÿ���ֽڼӵ�У������
			}		
			USART1_PutChar(checkbit);	//���������֮���У��λ
			break;
		}

	}
}

/**************************************************************
 * @brief	�����ݰ����н���У��
 * @param	data����ǰ���յ�һ�ֽ�����
 * @retval
 * @addition	У��ͨ���󣬵��ö�Ӧ�ĺ��������ѽ��յ�������
**************************************************************/
void Command_ReceiveAndCheck(uint8_t data)
{

	static RX_SEVRO_Buff_Union RX_SEVRO_Data;
	static RX_PID_Buff_Union 	 RX_PID_Data;
	static RX_MODE_Buff_Union  RX_MODE_Data;
	
	static uint8_t RX_Cnt = 0;	//���ռ���
	static uint8_t startbit;		//��ʼλ
	uint8_t i,checkbit;
	
	RX_Cnt++;	//���ռ���������һ����ʾ��ǰ���ݰ��ѽ��յ����ֽ���
	if (RX_Cnt == 1)	//��ʾ���ֽ�Ϊ���ݰ���ʼλ
	{
		startbit = data;
		if (startbit != RX_StartBit_MODE &&
				startbit != RX_StartBit_SERVO &&
				startbit != RX_StartBit_PID)			//��ʼλ������Ҫ��������ǰ�ѽ��յ�������
		{
			RX_Cnt = 0;		//���������㣬���¿�ʼ����
		}
		return;
	}
	
	switch (startbit)	//�����ͽ����ݴ洢����Ӧ�Ĺ�������
	{				
		case(RX_StartBit_MODE):
		{			
			if (RX_Cnt <= RX_MODE_BUFF_LEN + 1)
			{
				RX_MODE_Data.RX_MODE_BUFF[RX_Cnt-2] = data;
				return;
			}
			break;
		}
		
		case(RX_StartBit_SERVO):
		{
			if (RX_Cnt <= RX_SERVO_BUFF_LEN + 1)
			{
				RX_SEVRO_Data.RX_SERVO_BUFF[RX_Cnt-2]=data;
				return;
			}
			break;
		}
		
		case(RX_StartBit_PID):
		{
			if (RX_Cnt <= RX_PID_BUFF_LEN + 1)
			{
				RX_PID_Data.RX_PID_BUFF[RX_Cnt-2]=data;
				return;
			}
			break;
		}
	}
	
	//���ˣ����ݰ�������ϣ������ݽ���У��
	checkbit=0x00^startbit;
	switch (startbit)
	{		
		case(RX_StartBit_MODE):
		{
			for (i = 0;i < RX_MODE_BUFF_LEN; i++)
			checkbit ^= RX_MODE_Data.RX_MODE_BUFF[i];
			if (checkbit != data)		//У��λ��ƥ�����������ݣ����¿�ʼ��ƥ�����������
			{
				RX_Cnt = 0;
				return;
			}
			else
			{
				RX_MODE_DataHandler(RX_MODE_Data);
			}
			break;
		}
		
		case(RX_StartBit_SERVO):
		{
			for (i = 0; i < RX_SERVO_BUFF_LEN; i++)
			checkbit ^= RX_SEVRO_Data.RX_SERVO_BUFF[i];
			if (checkbit != data)		//У��λ��ƥ�����������ݣ����¿�ʼ��ƥ�����������
			{
				RX_Cnt = 0;
				return;
			}
			else
			{
				RX_SERVO_DataHandler(RX_SEVRO_Data);
			}
			break;
		}
		
		case(RX_StartBit_PID):
		{
			for (i = 0; i < RX_PID_BUFF_LEN; i++)
			checkbit ^= RX_PID_Data.RX_PID_BUFF[i];
			if (checkbit != data)		//У��λ��ƥ�����������ݣ����¿�ʼ��ƥ�����������
			{
				RX_Cnt = 0;
				return;
			}
			else
			{
				RX_PID_DataHandler(RX_PID_Data);
			}
			break;
		}
	}
}


/**************************************************************
 * @brief	�޸Ŀ���ģʽ
 * @param	Data������ģʽ������
 * @retval
 * @addition
**************************************************************/
void RX_MODE_DataHandler(RX_MODE_Buff_Union Data)
{
	Mode_Val.Control_mode 		 = Data.mode.Control_mode;
	Mode_Val.DepthMode 				 = Data.mode.DepthMode;
	Mode_Val.PitchMode 				 = Data.mode.PitchMode;
	Mode_Val.AngleSpeedYMode 	 = Data.mode.AngleSpeedYMode;
	Mode_Val.AccelerationYMode = Data.mode.AccelerationYMode;
}


/**************************************************************
 * @brief	���¶������
 * @param	Data�����������
 * @retval
 * @addition
**************************************************************/
void RX_SERVO_DataHandler(RX_SEVRO_Buff_Union Data)
{
  Servo_Val.FinTail_Front_StartingPosition = Data.servodata.FinTail_Front_StartingPosition;  //β�������ǰ�� ��ʼλ��
  Servo_Val.FinTail_Front_EndingPosition   = Data.servodata.FinTail_Front_EndingPosition;    //β�������ǰ�� ��ֹλ��
  Servo_Val.FinTail_Front_EachCCR          = Data.servodata.FinTail_Front_EachCCR;           //β�������ǰ�� ÿ�θı��ռ�ձ�
  Servo_Val.FinTail_Front_DelayTime        = Data.servodata.FinTail_Front_DelayTime;         //β�������ǰ�� ��ʱ����

	Servo_Val.FinTail_Rear_StartingPosition = Data.servodata.FinTail_Rear_StartingPosition;  //β��������� ��ʼλ��
  Servo_Val.FinTail_Rear_EndingPosition   = Data.servodata.FinTail_Rear_EndingPosition;    //β��������� ��ֹλ��
  Servo_Val.FinTail_Rear_EachCCR          = Data.servodata.FinTail_Rear_EachCCR;           //β��������� ÿ�θı��ռ�ձ�
  Servo_Val.FinTail_Rear_DelayTime        = Data.servodata.FinTail_Rear_DelayTime;         //β���������	��ʱ����
	
  Servo_Val.Camera_Position = Data.servodata.Camera_Position;      //�������̨��� λ��
	Servo_Val.Pulse_Num = Data.servodata.Pulse_Num;									 //������� λ��
	
	Servo_PositionSet();	//���¶��λ��
	//AbsPosition(Servo_Val.Pulse_Num);
}


/**************************************************************
 *@brief	����PID����
 *@param	Data��PID������
 *@retval
 *@addition
**************************************************************/
void RX_PID_DataHandler(RX_PID_Buff_Union Data)
{
	PID_Depth.Kp 			 = Data.PID_Parameter.Depth_Kp;
	PID_Depth.Ki			 = Data.PID_Parameter.Depth_Ki;
	PID_Depth.Kd			 = Data.PID_Parameter.Depth_Kd;
	PID_Depth.SetValue = Data.PID_Parameter.Depth_Target;
			
	PID_Pitch.Kp			 = Data.PID_Parameter.Pitch_Kp;
	PID_Pitch.Ki			 = Data.PID_Parameter.Pitch_Ki;
	PID_Pitch.Kd			 = Data.PID_Parameter.Pitch_Kd;
	PID_Pitch.SetValue = Data.PID_Parameter.Pitch_Target;
			
	PID_AngleSpeedY.Kp				 = Data.PID_Parameter.AngleSpeedY_Kp;
	PID_AngleSpeedY.Ki				 = Data.PID_Parameter.AngleSpeedY_Ki;
	PID_AngleSpeedY.Kd				 = Data.PID_Parameter.AngleSpeedY_Kd;
	PID_AngleSpeedY.SetValue	 = Data.PID_Parameter.AngleSpeedY_Target;		
			
	PID_AccelerationY.Kp			 = Data.PID_Parameter.AccelerationY_Kp;
	PID_AccelerationY.Ki			 = Data.PID_Parameter.AccelerationY_Ki;
	PID_AccelerationY.Kd			 = Data.PID_Parameter.AccelerationY_Kd;
	PID_AccelerationY.SetValue = Data.PID_Parameter.AccelerationY_Target;	
}
