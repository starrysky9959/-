#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f4xx.h"
#include "PID.h"
#include "timeslice.h"

/*****************************************����ģʽ�ṹ������***********************************************/
typedef struct 
{
	int Control_mode;
	int DepthMode;
	int PitchMode;           
	int AngleSpeedYMode;
	int AccelerationYMode;
}Mode_ValTypedef;

extern Mode_ValTypedef Mode_Val;

extern struct PID PID_Depth;
extern struct PID PID_Pitch;
extern struct PID PID_AngleSpeedY;
extern struct PID PID_AccelerationY;


/************************************************��������*********************************************/
extern void ClosedLoop_Control(void);

#endif
