/************************************ģ��I2C�ײ���������********************************/
/*
����ģ��I2C��
	��νӲ��I2C��ӦоƬ�ϵ�I2C���裬����ӦI2C������·������ʹ�õ�I2C�ܽ�Ҳ��ר�õģ�
	���I2C��ʹ��GPIO�ܽţ���������ƹܽ�״̬��ģ��I2Cͨ�Ų��Ρ�
	Ӳ��I2C��Ч��ҪԶ��������ģ������I2C���ڲ��ܹܽ����ƣ��ӿڱȽ���
	ģ��I2C ��ͨ��GPIO�����ģ��Ĵ����Ĺ�����ʽ����Ӳ�����̼���I2C��ֱ�ӵ����ڲ��Ĵ����������á�
	���Ҫ�Ӿ���Ӳ��������������ȥ����оƬ�ֲᡣ��Ϊ�̼�I2C�Ķ˿��ǹ̶��ģ����Ի���������

ʹ��˵����
	��.c�ļ�˼·����ͨģ��I2C���в�ͬ�����������������ı��˼·���Զ�����һ��IIC_STRUCT�ṹ�塣
	ʹ��ʱ�ȳ�ʼ��һ���Զ���IIC_STRUCT�ṹ�壬�ں�I2C���ö˿ڡ�ʱ�ӡ����ţ��ٰ��մ˽ṹ����г�ʼ����
	��ʵ��ʹ��ģ��I2Cʱ��Ҳ��Ҫ���ô�IIC_STRUCT�ṹ������õ�ģ��I2C����ָ�ơ�
	�������ĺô��ǣ�ͬһ��.c�ļ�����ʵ�������I2C���Ӷ�ӵ�ж��I2C���ߡ�������I2C���߱����Ϳ���һ�Զ࣬��ôһ�룬����������ûʲô����_(:�٩f��)_��
*/

#include "I2C.h"


/*
IIC_STRUCT�ṹ���ʼ����������ʱ���ߡ��ź��ߵĶ˿ں����ţ���ɶ�IIC_STRUCT�ṹ���ڸ���Ա������
*/
void I2C_Struct_Config(IIC_STRUCT *I2C,GPIO_TypeDef *SCL_GPIO_Port,uint32_t SCL_Pin,GPIO_TypeDef * SDA_GPIO_Port,uint32_t SDA_Pin)
{
	I2C->SCL_GPIO_Port=SCL_GPIO_Port;
	I2C->SDA_GPIO_Port=SDA_GPIO_Port;
	if(SCL_GPIO_Port==GPIOA) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOA;//��Ҳ������switch������ָ�������������switch���أ�
	if(SCL_GPIO_Port==GPIOB) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOB;
	if(SCL_GPIO_Port==GPIOC) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOC;
	if(SCL_GPIO_Port==GPIOD) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOD;
	if(SCL_GPIO_Port==GPIOE) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOE;
	if(SCL_GPIO_Port==GPIOF) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOF;
	if(SCL_GPIO_Port==GPIOG) I2C->SCL_GPIO_CLK=RCC_AHB1Periph_GPIOG;
	
	if(SDA_GPIO_Port==GPIOA) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOA;
	if(SDA_GPIO_Port==GPIOB) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOB;
	if(SDA_GPIO_Port==GPIOC) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOC;
	if(SDA_GPIO_Port==GPIOD) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOD;
	if(SDA_GPIO_Port==GPIOE) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOE;
	if(SDA_GPIO_Port==GPIOF) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOF;
	if(SDA_GPIO_Port==GPIOG) I2C->SDA_GPIO_CLK=RCC_AHB1Periph_GPIOG;
	
	I2C->SCL_Pin=SCL_Pin;
	I2C->SDA_Pin=SDA_Pin;
}

/*
ģ��I2C��ʼ�����򣬸�������IIC_STRUCT�ṹ��ĳ�Ա��Ϣ������ӦGPIO���г�ʼ����
*/
void I2C_Simu_Init(IIC_STRUCT I2C)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//��GPIOʱ�� 
	RCC_AHB1PeriphClockCmd(I2C.SCL_GPIO_CLK|I2C.SDA_GPIO_CLK, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = I2C.SCL_Pin;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(I2C.SCL_GPIO_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = I2C.SDA_Pin;
	GPIO_Init(I2C.SDA_GPIO_Port, &GPIO_InitStructure);
}


//ģ��I2C�Դ�������ʱ
void I2C_delay_ms(uint32_t time)
{
   uint64_t i=13500*time;  
   while(i) 
   { 
     i--; 
   }  
}


//ģ��I2C�Դ���ʱ����ʱʱ�����ͨ�����ʡ���ͨ�����ı���i���ı�ͨ������
void I2C_delay(void)
{
		
   u8 i=75; //��������Ż��ٶ�	����������͵�2����д��
   while(i) 
   { 
     i--; 
   }  
}

/**********************************************************/
//����ע��ȫΪ��GPIO����ģ��I2Cʱ�򣬽��I2Cʱ��ͼ���ɿ�����
/**********************************************************/

void I2C_Ack(IIC_STRUCT I2C)
{	
	SCL_L(I2C);
	I2C_delay();
	SDA_L(I2C);
	I2C_delay();
	SCL_H(I2C);
	I2C_delay();
	SCL_L(I2C);
	I2C_delay();
}  

void I2C_NoAck(IIC_STRUCT I2C)
{	
	SCL_L(I2C);
	I2C_delay();
	SDA_H(I2C);
	I2C_delay();
	SCL_H(I2C);
	I2C_delay();
	SCL_L(I2C);
	I2C_delay();
} 

uint8_t I2C_Start(IIC_STRUCT I2C)
{
	SDA_H(I2C);
	SCL_H(I2C);
	I2C_delay();
	if(!SDA_read(I2C))return 0;	//SDA��Ϊ�͵�ƽ������æ,�˳�
	SDA_L(I2C);
	I2C_delay();
	if(SDA_read(I2C)) return 0;	//SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
	SDA_L(I2C);
	I2C_delay();
	return 1;
}

void I2C_Stop(IIC_STRUCT I2C)
{
	SCL_L(I2C);
	I2C_delay();
	SDA_L(I2C);
	I2C_delay();
	SCL_H(I2C);
	I2C_delay();
	SDA_H(I2C);
	I2C_delay();
} 

uint8_t I2C_WaitAck(IIC_STRUCT I2C) 	 //����Ϊ:=1��ACK,=0��ACK
{
	SCL_L(I2C);
	I2C_delay();
	SDA_H(I2C);			
	I2C_delay();
	SCL_H(I2C);
	I2C_delay();
	if(SDA_read(I2C))
	{
      SCL_L(I2C);
	  I2C_delay();
      return 0;
	}
	SCL_L(I2C);
	I2C_delay();
	return 1;

}

void I2C_WriteByte(IIC_STRUCT I2C,u8 WriteByte) //���ݴӸ�λ����λ//
{
	u8 i=8;
	while(i--)
    {
    SCL_L(I2C);
    I2C_delay();
		if(WriteByte&0x80)
			SDA_H(I2C);  
		else 
			SDA_L(I2C);   
    WriteByte<<=1;
    I2C_delay();
		SCL_H(I2C);
    I2C_delay();
    }
	SCL_L(I2C);
}  

uint8_t I2C_ReadByte(IIC_STRUCT I2C)  //���ݴӸ�λ����λ//
{ 
    u8 i=8;
    u8 ReceiveByte=0;

    SDA_H(I2C);				
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L(I2C);
      I2C_delay();
	  SCL_H(I2C);
      I2C_delay();	
      if(SDA_read(I2C))
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L(I2C);
    return ReceiveByte;
} 

uint8_t I2C_Single_Write(IIC_STRUCT I2C,unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start(I2C))return 0;
    I2C_WriteByte(I2C,SlaveAddress);   //�����豸��ַ+д�ź�//I2C_WriteByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck(I2C)){I2C_Stop(I2C); return 0;}
    I2C_WriteByte(I2C,REG_Address);   //���õ���ʼ��ַ      
    I2C_WaitAck(I2C);	
    I2C_WriteByte(I2C,REG_data);
    I2C_WaitAck(I2C);   
    I2C_Stop(I2C); 
    I2C_delay_ms(1);
    return 1;
}

uint8_t I2C_Single_Read(IIC_STRUCT I2C,unsigned char SlaveAddress,unsigned char REG_Address)
{   unsigned char REG_data;     	
	if(!I2C_Start(I2C))return 0;
    I2C_WriteByte(I2C,SlaveAddress|I2C_WR); //I2C_WriteByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
    if(!I2C_WaitAck(I2C)){I2C_Stop(I2C); return 0;}
    I2C_WriteByte(I2C,(u8) REG_Address);   //���õ���ʼ��ַ      
		
    if(!I2C_WaitAck(I2C))
		{
			I2C_Stop(I2C);
			return 0;
		}
		
    I2C_Start(I2C);
    I2C_WriteByte(I2C,SlaveAddress|I2C_RD);
		
    if(!I2C_WaitAck(I2C))
		{
			I2C_Stop(I2C);
			return 0;
		}

	REG_data= I2C_ReadByte(I2C);
    I2C_NoAck(I2C);
    I2C_Stop(I2C);
	return REG_data;
}		



uint8_t I2C_CheckDevice(IIC_STRUCT I2C,uint8_t address)//1�ɹ� 0ʧ��
{
	uint8_t ack;
	I2C_Start(I2C);
	I2C_WriteByte(I2C,address|I2C_WR);
	ack=I2C_WaitAck(I2C);
	I2C_Stop(I2C);
	return ack;
}

/*
����д��
�ɹ�����1��ʧ�ܷ���0

*/

uint8_t I2C_WriteBuffer(IIC_STRUCT I2C,uint8_t addr, uint8_t * data,uint8_t len)
{
	uint8_t i;
	I2C_Start(I2C);
	I2C_WriteByte(I2C,(addr)|I2C_WR);
	if(!I2C_WaitAck(I2C))
	{
		I2C_Stop(I2C);
		return 0;
	}
  for (i = 0; i < len; i++)
	{
			I2C_WriteByte(I2C,data[i]);
			if(!I2C_WaitAck(I2C))
			{
				I2C_Stop(I2C);
				return 0;
			}
	}
	I2C_Stop(I2C);
    return 1;
}


uint8_t I2C_ReadBuffer(IIC_STRUCT I2C,uint8_t addr, uint8_t* pBuffer, uint8_t readAddr, u16 NumByteToRead)
{
	
	if(!I2C_Start(I2C))return 0;
	
	I2C_WriteByte(I2C,(addr)| I2C_WR);
	if (!I2C_WaitAck(I2C))
			{
				I2C_Stop(I2C);
				return 0;	
			}
			
	I2C_WriteByte(I2C,readAddr);
			
	if (!I2C_WaitAck(I2C))
	{
		I2C_Stop(I2C);
		return 0;	
	}
	
	I2C_Start(I2C);
	
	I2C_WriteByte(I2C,addr| I2C_RD);
	
		if (!I2C_WaitAck(I2C))
	{
		I2C_Stop(I2C);
		return 0;	
	}
	
	 while(NumByteToRead)
  {

		*pBuffer = I2C_ReadByte(I2C);
		pBuffer++;
		if(NumByteToRead > 1)
			I2C_Ack(I2C);
		else
    {
			I2C_NoAck(I2C);
			I2C_Stop(I2C);
    }
		NumByteToRead--;
  }
		I2C_Stop(I2C);
	return 1;
	
}


