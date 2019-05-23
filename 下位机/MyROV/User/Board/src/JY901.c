#include "JY901.h"
#include "string.h"
#include "usart2.h"

struct SAcc 		   stcAcc;
struct SGyro 			 stcGyro;
struct SAngle 		 stcAngle;




void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}


short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}


/**
 *@brief	����2�жϵ��ú���������ÿ�յ�һ�����ݣ�����һ�����������
 *@param	ucData�����յ�������
 *@retval
 *@addition
*/
void JY901_DataReceive(uint8_t ucData)
{
  static unsigned char ucRxBuffer[250];
	static unsigned char ucRxCnt = 0;	
	
	ucRxBuffer[ucRxCnt++]=ucData;	//���յ������ݴ��뻺������
	if (ucRxBuffer[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
		//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		switch(ucRxBuffer[1])
		{
			//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ���
			case 0x51:	memcpy(&stcAcc,&ucRxBuffer[2],8);break;
			case 0x52:	memcpy(&stcGyro,&ucRxBuffer[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucRxBuffer[2],8);break;
		}
		ucRxCnt=0;//��ջ�����
	}
	
	//���ݻ���
	JY901_Val.acc_x = (float)stcAcc.a[0]/32768*16;
	JY901_Val.acc_y = (float)stcAcc.a[1]/32768*16;
	JY901_Val.acc_z = (float)stcAcc.a[2]/32768*16;
	JY901_Val.gyro_x = (float)stcGyro.w[0]/32768*2000;
	JY901_Val.gyro_y = (float)stcGyro.w[1]/32768*2000;
	JY901_Val.gyro_z = (float)stcGyro.w[2]/32768*2000;
	JY901_Val.angle_x = (float)stcAngle.Angle[0]/32768*180;
	JY901_Val.angle_y = (float)stcAngle.Angle[1]/32768*180;
	JY901_Val.angle_z = (float)stcAngle.Angle[2]/32768*180;
}


