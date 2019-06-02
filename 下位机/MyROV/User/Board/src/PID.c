#include "PID.h"
#include "string.h"
#include "math.h"

/**************************************************************
 * @brief	PID�ṹ�������ʼ��
 * @param	*pidData����Ӧ PID �ṹ�崫ַ����
	 @param  Kp������ϵ��
	 @param  Ki������ϵ��
	 @param  Kd��΢��ϵ��
	 @param  MaxOut�����ض����������
	 @param  IMax�����ֵ����������
	 @param  FuzzInterval��ģ������
 * @retval
 * @addition ������ֵ��������������
**************************************************************/
void PID_Init(struct PID *pidData, float Kp, float Ki, float Kd, float MaxOut, float IMax, float FuzzInterval)
{				
	pidData->Kp = Kp;						
	pidData->Ki = Ki;						
	pidData->Kd = Kd;						
	pidData->MaxOut = MaxOut;				
	pidData->IMax = IMax;						
	pidData->FuzzyInterval = FuzzInterval;
	pidData->P = 0;						
	pidData->I = 0;						
	pidData->D = 0;		
	pidData->CurrentError = 0; 
	pidData->LastError = 0;		
	pidData->dError = 0;	
	pidData->Out = 0;	
}


/**************************************************************
 * @brief	�����ݽ����޶�
 * @param	Ans�������������
	 @param	max�����ݷ�Χ���� 
	 @param	min�����ݷ�Χ����
 * @retval
 * @addition Ans �����޶��������
**************************************************************/
float Limitation(float Ans, float max, float min)
{
	if (Ans>max) Ans = max;
	else if (Ans<min) Ans = min;
	return Ans;
}


/**************************************************************
 * @brief	PID�������
 * @param	*pidData����Ӧ PID �ṹ�崫ַ����
 * @retval
 * @addition
**************************************************************/
void Calculate(struct PID *pidData)
{
	//���㵱ǰƫ��
	pidData->CurrentError = pidData->SetValue - pidData->CurrentValue;
	//ģ������
	if (fabs(pidData->CurrentError) <= pidData->FuzzyInterval)
			// ��ǰƫ��ֵ������ģ�����䣬��Ϊ0����������ģ�����俿£
			 pidData->CurrentError = 0;
	else if (pidData->CurrentError > 0) 
			 pidData->CurrentError -= pidData->FuzzyInterval;
	else pidData->CurrentError += pidData->FuzzyInterval;
	
	pidData->dError = pidData->CurrentError - pidData->LastError;		//����΢��ƫ��
	pidData->P = pidData->Kp * pidData->CurrentError;								//��������������
	//���޶���Χ���ۼӻ�������
	pidData->I += Limitation((pidData->Ki) * (pidData->CurrentError), pidData->IMax/10, -pidData->IMax/10);
	pidData->I = Limitation(pidData->I, pidData->IMax, -pidData->IMax);
	if (pidData->Ki==0)		//�������ϵ��Ϊ�㣬������ֵ��������ۼ���,��ֹ���û��ֵ���ʱ֮ǰ����������Ӱ��
		pidData->I = 0;
	pidData->D = (pidData->Kd) * (pidData->dError);									//����΢������
	pidData->LastError = pidData->CurrentError;											//����ƫ��ֵ
}


/**************************************************************
 * @brief	PID��λ
 * @param	*pidData����Ӧ PID �ṹ�崫ַ����
 * @retval
 * @addition
**************************************************************/
void ResetPID(struct PID *pidData)
{
	pidData->P = 0;						
	pidData->I = 0;						
	pidData->D = 0;		
	pidData->CurrentError = 0; 
	pidData->LastError = 0;		
	pidData->dError = 0;	
}


/**************************************************************
 * @brief	�������ù���
 * @param	*pidData����Ӧ PID �ṹ�崫ַ����
 * @retval
 * @addition
**************************************************************/
void ResetI(struct PID *pidData)
{			
	pidData->I = 0;						
}


/**************************************************************
 * @brief	ָ��ʹ�ñ��������֡�΢���еļ������е���
 * @param	*pidData����Ӧ PID �ṹ�崫ַ����
	 @param	*pFlag����Ӧ��ͬ�������͵ı�־�ַ�
 * @retval
 * @addition
**************************************************************/
void DebugPID(struct PID *pidData, char *pFlag)
{			
	//���ݱ�־�ַ�ѡ���������
	if (strcmp(pFlag,"P")==0)
		pidData->Out = pidData->P;
	if (strcmp(pFlag,"PI")==0)
		pidData->Out = pidData->P + pidData->I;
	if (strcmp(pFlag,"PD")==0)
		pidData->Out = pidData->P + pidData->D;
	if (strcmp(pFlag,"PID")==0)
		pidData->Out = pidData->P + pidData->I + pidData->D;

	pidData->Out = Limitation(pidData->Out, pidData->MaxOut, -pidData->MaxOut);
}
