#ifndef __TIMESLICE_H
#define	__TIMESLICE_H

struct TS
{
	int Count_20ms;
	int Count_50ms;
	int Count_100ms;
	int Count_200ms;
	int Count_5000ms;
	int Count_Left;
	int Count_Right;
	int Left_Flag;	 
	int Right_Flag;
};
extern struct TS TimeSlice;

/********************************************��������********************************************/
extern void SpecialAction(void);
extern void Loop_20ms(void);
extern void Loop_50ms(void);
extern void Loop_100ms(void);
extern void Loop_200ms(void);
extern void Loop_5000ms(void);
					
#endif
