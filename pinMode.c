#include "stdint.h"
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"


void pinMode(volatile uint32_t * px,volatile uint32_t mode)       //for input  mode=0   for output  mode=1
{
	uint32_t port   = (uint32_t)px & 0x1000 ; 
	uint32_t offset = ((uint32_t)px & 0x111 )/4; 

	if(port==0x8000) //port A
	{
		SYSCTL_RCGCGPIO_R |= 0x1;
		while ((SYSCTL_PRGPIO_R & 0x1)==0) {};
		GPIO_PORTA_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTA_CR_R   |= offset ;             //commit reg
		GPIO_PORTA_DIR_R = (mode)? (GPIO_PORTA_DIR_R | offset) : (GPIO_PORTA_DIR_R & (!offset) ) ;
		GPIO_PORTA_DEN_R  |= offset;             //digital enable

	}

	else if(port==0x9000) //port B
	{
		SYSCTL_RCGCGPIO_R |= 0x2;
		while ((SYSCTL_PRGPIO_R & 0x2)==0) {};
		GPIO_PORTB_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTB_CR_R   |= offset ;             //commit reg
		GPIO_PORTB_DIR_R   = (mode)? (GPIO_PORTB_DIR_R | offset) : (GPIO_PORTB_DIR_R & (!offset) ) ;
		GPIO_PORTB_DEN_R  |= offset;              //digital enable
	}

	else if(port==0xA000) //port C
	{
		SYSCTL_RCGCGPIO_R |= 0x4;
		while ((SYSCTL_PRGPIO_R & 0x4)==0) {};
		GPIO_PORTC_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTC_CR_R   |= offset ;             //commit reg
		GPIO_PORTC_DIR_R   = (mode)? (GPIO_PORTC_DIR_R | offset) : (GPIO_PORTC_DIR_R & (!offset) ) ;
		GPIO_PORTC_DEN_R  |= offset;              //digital enable
	}

	else if(port==0xB000) //port D
	{
		SYSCTL_RCGCGPIO_R |= 0x8;
		while ((SYSCTL_PRGPIO_R & 0x8)==0) {};
		GPIO_PORTD_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTD_CR_R   |= offset ;             //commit reg
		GPIO_PORTD_DIR_R   = (mode)? (GPIO_PORTD_DIR_R | offset) : (GPIO_PORTD_DIR_R & (!offset) ) ;
		GPIO_PORTD_DEN_R  |= offset;              //digital enable
	}

	else if(port==0xC000) //port E
	{
		SYSCTL_RCGCGPIO_R |= 0x10;
		while ((SYSCTL_PRGPIO_R & 0x10)==0) {};
		GPIO_PORTE_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTE_CR_R   |= offset ;             //commit reg
		GPIO_PORTE_DIR_R   = (mode)? (GPIO_PORTE_DIR_R | offset) : (GPIO_PORTE_DIR_R & (!offset) ) ;
		GPIO_PORTE_DEN_R  |= offset;              //digital enable
	}

	if(port==0xD000) //port F
	{
		SYSCTL_RCGCGPIO_R |= 0x20;
		while ((SYSCTL_PRGPIO_R & 0x20)==0) {};
		GPIO_PORTF_LOCK_R  = 0x4C4F434B ;         //magic value to unlcok
	    GPIO_PORTF_CR_R   |= offset ;             //commit reg
		GPIO_PORTF_DIR_R   = (mode)? (GPIO_PORTF_DIR_R | offset) : (GPIO_PORTF_DIR_R & (!offset) ) ;
		GPIO_PORTF_DEN_R  |= offset;              //digital enable
	}
}