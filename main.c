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
		trigger_MS ( trig , 10 );
	  time=pulseIn(echo, 1);
	  distance=(time*170)/10000;
		
	  decoder(get_1_Cms (distance),PB5,PB0,PD0,PB1,PD1,PE4,PD2);
    decoder(get_10_Cms(distance),PE5,PD3,PB4,PE1,PA5,PE2,PA6);	
		decoder(get_Meters(distance),PF1,PC7,PA4,PD6,PA3,PF4,PA2);
		
		//*PF1=0xff;
		//*PC7=0;
		
		/*
		*PB5=0;
		*PB0=0xff;
		*PD0=0;
		*PB1=0;
		*PD1=0xff;
		*PE4=0;
		*PD2=0;*/
	}
}
