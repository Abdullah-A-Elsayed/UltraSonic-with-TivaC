#include "stdint.h"
#include "E:/tiva/EE319KwareSpring2018/inc/tm4c123gh6pm.h"
void SystemInit(){}

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
void init (void)
{
 uint32_t delay;
	SYSCTL_RCGCGPIO_R |=0x20;
	delay=1;
	GPIO_PORTF_LOCK_R=0x4C4F434B;
	GPIO_PORTF_CR_R=0x1F;
	GPIO_PORTF_AFSEL_R=0;
	GPIO_PORTF_PCTL_R=0;
	GPIO_PORTF_AMSEL_R=0;
	GPIO_PORTF_DIR_R=0x0E;
	GPIO_PORTF_DEN_R=0x1F;
	GPIO_PORTF_PUR_R=0x11;
}
int main()
{
init();

GPIO_PORTF_DATA_R=0;

	
while(1)
{
GPIO_PORTF_DATA_R=0x02;//red
delayMicroseconds(1000000);//1second	
GPIO_PORTF_DATA_R=0x04;//blue
delayMicroseconds(1000000);//1second
GPIO_PORTF_DATA_R=0x08;	//green
delayMicroseconds(1000000);	//1second
GPIO_PORTF_DATA_R=0;	
}


}