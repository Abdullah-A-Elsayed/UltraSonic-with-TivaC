#include "functions.h"


void SystemInit(){}


uint32_t pulseIn(volatile uint32_t* pin , uint32_t value){
	
	/*----initialize counter but don't enable it-------*/
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_RELOAD_R = 0xFFFFFF;  //around 1 second
	NVIC_ST_CTRL_R = 4;           //clk src from cpu, but not enabled
	
	/*-----wait untill pin goes to value---------------*/
	//while( ((*pin)&&(value)) || ((!*pin)&&(!value)) ){} 
	
	while( ((*pin)&&(!value)) || ((!*pin)&&(value)) ){}   //now i'm sure value just started
		
		
	/*-----enable counter untill pin goes to !value----*/
	NVIC_ST_CTRL_R |= 1;          //enabled
	while( ((*pin)&&(value)) || ((!*pin)&&(!value)) )
	{
		if(NVIC_ST_CTRL_R&0x10000)
			return 0;        //if it takes more than 1 second so there is no object in front of the sensor
	}//wait

	NVIC_ST_CTRL_R = 0;            //disabled
	
	/*---------------get real time---------------------*/
	return ((0xFFFFFF - NVIC_ST_CURRENT_R) / 16);
}



uint32_t get_Meters(uint32_t cms){
	return cms/100;
}

uint32_t get_10_Cms(uint32_t cms){
	return (cms%100)/10;
}


uint32_t get_1_Cms(uint32_t cms){
	return cms%10;
}



void trigger_MS (volatile uint32_t *px , uint32_t Ms)
{ 
	*px=0;
	systic_MS(10);
	*px=0xFF;
	systic_MS( Ms);
	*px=0;
}



void systic_MS(uint32_t Ms)
{
	uint32_t counts=( Ms*1000)/62.5;
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R=counts-1;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=5;
	while((NVIC_ST_CTRL_R & 0x10000) ==0)
    {}
}



void display(uint32_t m ,p p0 ,p p1 ,p p2  ,p p3)
{
	*p0 = (m&0x8)?0xFF:0;
	*p1 = (m&0x4)?0xFF:0;
	*p2 = (m&0x2)?0xFF:0;
	*p3 = (m&0x1)?0xFF:0;
}




#define fn1(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _DIR_R   = mode;             \
	GPIO_PORT ## X ## _DEN_R   = 0xFF;             \
	break;                                         \
}                                                  \

#define fn2(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _DIR_R  |= mode;             \
	GPIO_PORT ## X ## _DEN_R  |= mode;             \
	break;                                         \
}                                                  \

#define fn3(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _DIR_R  &= (~mode);          \
	GPIO_PORT ## X ## _DEN_R  |= mode;             \
	break;                                         \
}                                                  \

#define create(NAME,X)                             \
void NAME(volatile uint32_t * px, uint8_t mode)    \
{                                                  \
	switch((uint32_t)px)                           \
	{                                              \
		case 0x40004000 : fn ## X(A , 0x1)         \
		case 0x40005000 : fn ## X(B , 0x2)         \
		case 0x40006000 : fn ## X(C , 0x4)         \
		case 0x40007000 : fn ## X(D , 0x8)         \
		case 0x40024000 : fn ## X(E , 0x10)        \
		case 0x40025000 : fn ## X(F , 0x20)        \
	}                                              \
}                                                  \

create(portMode,1)
create(portSetOutputs,2)
create(portSetInputs,3)





#define fn(X,NUM)                                \
{                                                \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	if(mode)GPIO_PORT ## X ## _DIR_R |= offset;    \
	else    GPIO_PORT ## X ## _DIR_R &= (~offset); \
	GPIO_PORT ## X ## _DEN_R  |= offset;           \
	break;                                         \
}                                                \


void pinMode(volatile uint32_t * px, uint32_t mode)       //for input  mode=0   for output  mode=1
{
	uint32_t port   = (uint32_t)px  & 0xFF000 ; 
	uint32_t offset = ((uint32_t)px & 0xFFF )/4;  
	switch(port)
	{
		case 0x4000  : fn(A , 0x1)      // port A
		case 0x5000  : fn(B , 0x2)      // port B
		case 0x6000  : fn(C , 0x4)      // port C
		case 0x7000  : fn(D , 0x8)      // port D
		case 0x24000 : fn(E , 0x10)     // port E
		case 0x25000 : fn(F , 0x20)     // port F
	}
}


void decoder (uint32_t n, p a, p b, p c, p d,p e, p f, p g){
	if(n == 0){
		*a = 0;
		*b = 0;
		*c = 0;
		*d = 0;
		*e = 0;
		*f = 0;
		*g = 0xFF;
	}
	else if(n == 1){
		*a = 0xFF;
		*b = 0;
		*c = 0;
		*d = 0xFF;
		*e = 0xFF;
		*f = 0xFF;
		*g = 0xFF;
	}
	else if(n == 2){
		*a = 0;
		*b = 0;
		*c = 0xFF;
		*d = 0;
		*e = 0;
		*f = 0xFF;
		*g = 0;
	}
	else if(n == 3){
		*a = 0;
		*b = 0;
		*c = 0;
		*d = 0;
		*e = 0xFF;
		*f = 0xFF;
		*g = 0;
	}
	else if(n == 4){
		*a = 0xFF;
		*b = 0;
		*c = 0;
		*d = 0xFF;
		*e = 0xFF;
		*f = 0;
		*g = 0;
	}
	else if(n == 5){
		*a = 0;
		*b = 0xFF;
		*c = 0;
		*d = 0;
		*e = 0xFF;
		*f = 0;
		*g = 0;
	}
	else if(n == 6){
		*a = 0;
		*b = 0xFF;
		*c = 0;
		*d = 0;
		*e = 0;
		*f = 0;
		*g = 0;
	}
	else if(n == 7){
		*a = 0;
		*b = 0;
		*c = 0;
		*d = 0xFF;
		*e = 0xFF;
		*f = 0xFF;
		*g = 0xFF;
	}
	else if(n == 8){
		*a = 0;
		*b = 0;
		*c = 0;
		*d = 0;
		*e = 0;
		*f = 0;
		*g = 0;
	}
	else if(n == 9){
		*a = 0;
		*b = 0;
		*c = 0;
		*d = 0;
		*e = 0xFF;
		*f = 0;
		*g = 0;
	}
	else{//display H
		*a = 0xFF;
		*b = 0;
		*c = 0;
		*d = 0xFF;
		*e = 0;
		*f = 0;
		*g = 0;
	}
}
