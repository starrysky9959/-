#ifndef __DATAPOCKET_H
#define __DATAPOCKET_H

#include "stm32f4xx.h"

/*************************************************�궨��*********************************************/
//�������ݰ�
#define TX_JY901_BUFF_LEN 				36			//����λ������JY901��̬���������ݰ�
#define TX_MS5837_BUFF_LEN 				16			//����λ������MS5837��ȴ��������ݰ�
#define TX_SERVO_BUFF_LEN 				20			//����λ�����Ͷ�����ݰ�
#define TX_PID_BUFF_LEN       		64			//����λ������PIDϵ�����ݰ�

#define TX_StartBit_JY901					0xAA		//����λ������JY901��̬����������
#define	TX_StartBit_MS5837				0xAB		//����λ������MS5837��ȴ���������
#define	TX_StartBit_SERVO				  0xAC		//����λ������������
#define	TX_StartBit_PID						0xAD		//����λ������PID����


//�������ݰ�
//#define RX_STEPPER_BUFF_LEN				4				//������λ���Ĳ������ָ�����ݰ�
#define RX_MODE_BUFF_LEN					20			//������λ���Ĳ���ģʽ���ָ�����ݰ�
#define RX_SERVO_BUFF_LEN 				20			//������λ���Ķ��ָ�����ݰ�
#define RX_PID_BUFF_LEN						64			//������λ����PIDָ�����ݰ�

//#define RX_StartBit_STEPPER				0xAA		//������λ���Ĳ������ָ��
#define	RX_StartBit_MODE      		0xAB    //������λ���Ĳ���ģʽ���ָ��
#define	RX_StartBit_SERVO         0xAC		//������λ���Ķ��ָ��
#define	RX_StartBit_PID           0xAD    //������λ����PIDָ��


/********************************************��λ�������ϴ��ṹ��*******************************************/
// JY901 �������ݹ�����
typedef union 
{
	struct
		{
			float acc_x;
			float acc_y;
			float acc_z;
			float gyro_x;
			float gyro_y;
			float gyro_z;
			float angle_x;
			float angle_y;
			float angle_z;
		}motiondata;
	uint8_t TX_JY901_BUFF[TX_JY901_BUFF_LEN];
}TX_JY901_Buff_Union;

//MS5837 ��ȴ�����������
typedef union 
{
	struct
	{
		float depth;
		float temp;
		float pressure;
		float offset;
	}ms5837data;
	uint8_t TX_MS5837_BUFF[TX_MS5837_BUFF_LEN];
}TX_MS5837_Buff_Union;

//PID ϵ��������
typedef union
{
	struct
	{
		float Depth_Kp;
		float Depth_Ki;
		float Depth_Kd;
		float Depth_Target;
		
		float Pitch_Kp;
		float Pitch_Ki;
		float Pitch_Kd;
		float Pitch_Target;
		
		float AngleSpeedY_Kp;
		float AngleSpeedY_Ki;
		float AngleSpeedY_Kd;
		float AngleSpeedY_Target;
		
		float AccelerationY_Kp;
		float AccelerationY_Ki;
		float AccelerationY_Kd;
		float AccelerationY_Target;		
	}PID_Parameter;
	uint8_t TX_PID_BUFF[TX_PID_BUFF_LEN];
}TX_PID_Buff_Union;


//����������ݹ�����
typedef union 
{
	struct
	{
		uint16_t FinTail_Front_StartingPosition;  		//β�������ǰ�� ��ʼλ��
		uint16_t FinTail_Front_EndingPosition;    		//β�������ǰ�� ��ֹλ��
		uint16_t FinTail_Front_EachCCR;           		//β�������ǰ�� ÿ�θı��ռ�ձ�
		uint16_t FinTail_Front_DelayTime;         		//β�������ǰ�� ��ʱ����
			
		uint16_t FinTail_Rear_StartingPosition; 	 		//β��������� ��ʼλ��
		uint16_t FinTail_Rear_EndingPosition;    			//β��������� ��ֹλ��
		uint16_t FinTail_Rear_EachCCR;           			//β��������� ÿ�θı��ռ�ձ�
		uint16_t FinTail_Rear_DelayTime;         			//β��������� ��ʱ����

		uint16_t Camera_Position;                   //�������̨��� λ��  
		uint16_t Pulse_Num;                         	//������
	}servodata;
	uint8_t TX_SERVO_BUFF[TX_SERVO_BUFF_LEN];
}TX_SEVRO_Buff_Union;



/********************************************��λ��ָ��ͽṹ��*******************************************/

//����ģʽ������
typedef union
{
	struct
	{
		int Control_mode;
		int DepthMode;
		int PitchMode;           
    int AngleSpeedYMode;
    int AccelerationYMode;
	}mode;
	uint8_t RX_MODE_BUFF[RX_MODE_BUFF_LEN];
}RX_MODE_Buff_Union;

//PID ϵ��������
typedef union
{
	struct
	{
		float Depth_Kp;
		float Depth_Ki;
		float Depth_Kd;
		float Depth_Target;
		
		float Pitch_Kp;
		float Pitch_Ki;
		float Pitch_Kd;
		float Pitch_Target;
		
		float AngleSpeedY_Kp;
		float AngleSpeedY_Ki;
		float AngleSpeedY_Kd;
		float AngleSpeedY_Target;
		
		float AccelerationY_Kp;
		float AccelerationY_Ki;
		float AccelerationY_Kd;
		float AccelerationY_Target;		
	}PID_Parameter;
	uint8_t RX_PID_BUFF[RX_PID_BUFF_LEN];
}RX_PID_Buff_Union;

//����������ݹ�����
typedef union 
{
	struct
	{
		uint16_t FinTail_Front_StartingPosition;  		//β�������ǰ�� ��ʼλ��
		uint16_t FinTail_Front_EndingPosition;    		//β�������ǰ�� ��ֹλ��
		uint16_t FinTail_Front_EachCCR;           		//β�������ǰ�� ÿ�θı��ռ�ձ�
		uint16_t FinTail_Front_DelayTime;         		//β�������ǰ�� ��ʱ����
			
		uint16_t FinTail_Rear_StartingPosition; 	 		//β��������� ��ʼλ��
		uint16_t FinTail_Rear_EndingPosition;    			//β��������� ��ֹλ��
		uint16_t FinTail_Rear_EachCCR;           			//β��������� ÿ�θı��ռ�ձ�
		uint16_t FinTail_Rear_DelayTime;         			//β��������� ��ʱ����

    uint16_t Camera_Position;                   	//�������̨��� λ��
		uint16_t Pulse_Num;     	                    //������		
	}servodata;
	uint8_t RX_SERVO_BUFF[RX_SERVO_BUFF_LEN];
}RX_SEVRO_Buff_Union;


/**********************************************��������***********************************************/
extern void PackDataUp(uint8_t startbit);
extern void Command_ReceiveAndCheck(uint8_t Data);
extern void RX_MODE_DataHandler(RX_MODE_Buff_Union Data);
extern void RX_SERVO_DataHandler(RX_SEVRO_Buff_Union Data);
extern void RX_PID_DataHandler(RX_PID_Buff_Union Data);

#endif

