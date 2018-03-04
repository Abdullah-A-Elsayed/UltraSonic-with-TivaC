#include "stdint.h"
#include "E:\tiva\tm4c123gh6pm.h"

void delayMicroseconds( int  t)       
{
	int i;
	for(i=0; i<t ;i++)
	{
	NVIC_ST_CTRL_R    = 0;
	NVIC_ST_RELOAD_R  = 16-1;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R    = 5;
	while((NVIC_ST_CTRL_R&0x10000)==0){}
	}
	
}