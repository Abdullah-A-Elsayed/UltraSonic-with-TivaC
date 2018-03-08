#include "functions.h"



int main ()
{
	portMode(PA,0xFF);
	portMode(PB,0xF7);
	portMode(PD,0xFF);
	portMode(PE,0xFF);
	pinMode(PF4,1);
	pinMode(PF1,1);
	pinMode(PC7,1);
	
	uint32_t time ,distance;
	
	p trig = PB2;
	p echo = PB3;
	
	while(1)
	{
		trigger_MS ( trig , 12 );
		time=pulseIn(echo, 1);
		distance = time / 58 ;
		
		decoder((distance)?get_1_Cms (distance):10,PB5,PB0,PD0,PB1,PD1,PE4,PD2);
		decoder((distance)?get_10_Cms(distance):10,PE5,PD3,PB4,PE1,PA5,PE2,PA6);	
		decoder((distance)?get_Meters(distance):10,PF1,PC7,PA4,PD6,PA3,PF4,PA2);
	}
}
