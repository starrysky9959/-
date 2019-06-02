/******************************************************************************
  * @file    MS5837.c
  * @author  ???
  * @version V1.0
  * @date    ????-??-??
  * @brief   MS5837��ȴ��������ɹٷ��ṩ���������루ɾ����û���õ���CRCУ�鲿�֣�ΪROV�ṩ��ȡ��¶ȡ�ѹǿ��Ϣ
	* @attention MS5837-30BA������оƬ�ڽ���I2Cͨ��ʱ�ǲ���ش�Acknowledge�ģ���ô���Խ��ϥ�(?�b�թb)?��ʱ�о��˰��죩��
							 ��˲��������Ƿ�ش�Acknowledge��ȷ��оƬ�Ƿ�����������
							 ʹ�÷���������MS5837_Read���������ɴ�MS5837_Val�ṹ���л�ȡ��������Ϣ
							 ����SDA ����SCL
*******************************************************************************/

#include "MS5837.h"
#include "stm32f4xx.h"
#include "systick.h"

/********************************************�ٷ��������س���********************************************/
#define  Pa 						100.0f
#define  bar  					0.001f
#define  mbar  					1.0f
#define  fluidDensity   997.0f//��ˮ�ܶ�997kg/m3  ����ˮ1029


/********************************************�ٷ��������ر���********************************************/
uint16_t C[8];
uint32_t D1, D2;
int32_t Temp;
int32_t P;

IIC_STRUCT MS5837_I2C;//ģ��I2C����Ľṹ�壬ģ��I2C�����I2C.c
MS5837_ValueTypeDef MS5837_Val={0,0,0,0.02};

/**************************************************************
 * @brief ��MS5837���͸�λָ��,�ϵ��һ���±��븴λ�������޷���������
 * @param
 * @retval ��λ����
 * @addition
**************************************************************/
static uint8_t MS5837_Reset(void) 
{
	return MS5837_WriteByte(MS5837_I2C,MS5837_ADDRESS,0x1e, 0x1e);//0x1eΪ��λָ��
}


/**************************************************************
 * @brief ����ѹ��ֵ���ٷ������ļ��㹫ʽ���룬û��Ȥ���Բ���
 * @param
 * @retval
 * @addition
**************************************************************/
static void MS5837_Calculate(void) 
{
	// Given C1-C6 and D1, D2, MS5837_Calculated Temp and P
	// Do conversion first and then second order temp compensation
	
	int32_t dT;
	int64_t SENS;
	int64_t OFF;
	int32_t SENSi; 
	int32_t OFFi;  
	int32_t Ti;    
	int64_t OFF2;
	int64_t SENS2;
	
	// Terms called
	dT = D2-(uint32_t)(C[5])*256l;
	SENS = (int64_t)(C[1])*32768l+((int64_t)(C[3])*dT)/256l;
	OFF = (int64_t)(C[2])*65536l+((int64_t)(C[4])*dT)/128l;
	
	
	//Temp and P conversion
	Temp = 2000l+(int64_t)(dT)*C[6]/8388608LL;
	P = (D1*SENS/(2097152l)-OFF)/(8192l);
	
	//Second order compensation
	if((Temp/100)<20){         //Low temp
		Ti = (3*(int64_t)(dT)*(int64_t)(dT))/(8589934592LL);
		OFFi = (3*(Temp-2000)*(Temp-2000))/2;
		SENSi = (5*(Temp-2000)*(Temp-2000))/8;
		if((Temp/100)<-15){    //Very low temp
			OFFi = OFFi+7*(Temp+1500l)*(Temp+1500l);
			SENSi = SENSi+4*(Temp+1500l)*(Temp+1500l);
		}
	}
	else if((Temp/100)>=20){    //High temp
		Ti = 2*(dT*dT)/(137438953472LL);
		OFFi = (1*(Temp-2000)*(Temp-2000))/16;
		SENSi = 0;
	}
	
	OFF2 = OFF-OFFi;           //Calculate pressure and temp second order
	SENS2 = SENS-SENSi;
	
	Temp = (Temp-Ti);
	P = (((D1*SENS2)/2097152l-OFF2)/8192l);
}


/**************************************************************
 * @brief �õ��������е�ԭʼ����
 * @param
 * @retval
 * @addition
**************************************************************/
static void MS5837_Getdata(void)
{
	uint8_t bufe[3];
	MS5837_WriteByte(MS5837_I2C,MS5837_ADDRESS,0x48, 0x00);
	I2C_delay_ms(20);
	MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,bufe,0x00, 3);	
	D1=bufe[0]<<16|bufe[1]<<8|bufe[2];
	MS5837_WriteByte(MS5837_I2C,MS5837_ADDRESS,0x58, 0x00);
	I2C_delay_ms(20);
	MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,bufe,0x00, 3);	
	D2=bufe[0]<<16|bufe[1]<<8|bufe[2];	
}


/**************************************************************
 * @brief ����ѹǿ
 * @param conversion��ѹǿ��λת��Ȩֵ
 * @retval ʵ��ѹǿֵ
 * @addition
**************************************************************/
float MS5837_pressure(float conversion) 
{
	return ((float)P)/10.0f*conversion;
}


/**************************************************************
 * @brief �����¶�
 * @param
 * @retval
 * @addition ʵ���¶�ֵ
**************************************************************/
float MS5837_temperature(void) 
{
	return Temp/100.0f;
}

/**************************************************************
 * @brief �������
 * @param
 * @retval
 * @addition ʵ�����(��λ��m)
**************************************************************/
float MS5837_depth(void) 
{
	return (MS5837_pressure(Pa)-101300)/(fluidDensity*9.80665);
}


/**************************************************************
 * @brief ����ˮ����������ֵ
 * @param offset������ֵ
 * @retval
 * @addition 
**************************************************************/
void MS5837_SetOffset(float offset)
{
	MS5837_Val.offset=offset;
}


/**************************************************************
 * @brief ��ʼ��ˮ�����
 * @param 
 * @retval
 * @addition 
**************************************************************/
void MS5837_Init(void) 
{
	uint8_t buf[2];//���ڴ洢��ˮ������ж�ȡ�Ĳ���

	I2C_Struct_Config(&MS5837_I2C,GPIOB,GPIO_Pin_8,GPIOB,GPIO_Pin_9);//��ʼ��ˮ���������ģ��I2C�ṹ�壬�����������
	
	I2C_Simu_Init(MS5837_I2C);//��ʼ��ˮ���������ģ��I2C
	
	MS5837_Reset();//ʹ��ǰ�ȸ�λ
	
  MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xa0, 2);//��ȡ������оƬ����س���ֵ������֮��ļ���
  C[0] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xa2, 2);
  C[1] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xa4, 2);
  C[2] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xa6, 2);
  C[3] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xa8, 2);
  C[4] = buf[0] << 8 |buf[1];
   MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xaa, 2);
  C[5] = buf[0] << 8 |buf[1]; 
    MS5837_ReadBuffer(MS5837_I2C,MS5837_ADDRESS,buf,0xac, 2);
  C[6] = buf[0] << 8 |buf[1];
	MS5837_Read();//��һ�ζ�ȡ
	MS5837_SetOffset(MS5837_depth()*100.0);//�趨��ǰ��Ȼ�׼ֵ��ͬʱ����ȵ�λת��Ϊ����
	
}


/**************************************************************
 * @brief �õ��������е��������ݲ���ֵ����MS5837�ṹ��
 * @param 
 * @retval
 * @addition 
**************************************************************/
void MS5837_Read(void) 
{
	static float last_val_depth=0;
	static float lastest_val_depth=0;
	static float lastestest_val_depth=0;//�����ĸ����������ڴ洢ǰ�Ĵζ�ȡ�������ֵ��֮��ȡƽ���˲���
	float now_val;
	MS5837_Getdata();//��ȡ��ʼֵ
	MS5837_Calculate();//�����ʼֵ�õ���������
	MS5837_Val.temp=MS5837_temperature();//��ȡ�¶ȣ�ûʲô�ã�
	now_val=MS5837_depth();
	
	if(now_val*100.0<-10||now_val*100.0>200)//�쳣ֵ����ʵ��ʹ�������ڸ��ţ��������ȴ��������طǳ�����쳣ֵ�����
		return;
	
	lastestest_val_depth=lastest_val_depth;//˳�Ӹ�ֵ
	lastest_val_depth=last_val_depth;
	last_val_depth=MS5837_Val.depth;
	
	MS5837_Val.depth=((now_val*100.0-MS5837_Val.offset)+last_val_depth+lastest_val_depth+lastestest_val_depth)/4;//��ǰ�Ĵε����ֵȡƽ��
	MS5837_Val.pressure=MS5837_pressure(Pa);//��ȡѹǿ��λΪPa��Ҳûʲô��Ŷ�r(�s_�t)�q��
}
