#include "stdint.h"
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"

#define fn1(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _LOCK_R  = 0x4C4F434B ;      \
	GPIO_PORT ## X ## _CR_R    = 0xFF ;            \
	GPIO_PORT ## X ## _DIR_R   = mode;             \
	GPIO_PORT ## X ## _DEN_R   = 0xFF;             \
	break;                                         \
}                                                  \

#define fn2(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _LOCK_R  = 0x4C4F434B ;      \
	GPIO_PORT ## X ## _CR_R   |= mode ;            \
	GPIO_PORT ## X ## _DIR_R  |= mode;             \
	GPIO_PORT ## X ## _DEN_R  |= mode;             \
	break;                                         \
}                                                  \

#define fn3(X,NUM)                                 \
{                                                  \
	SYSCTL_RCGCGPIO_R |= NUM;                      \
	while ((SYSCTL_PRGPIO_R & NUM)==0) {};         \
	GPIO_PORT ## X ## _LOCK_R  = 0x4C4F434B ;      \
	GPIO_PORT ## X ## _CR_R   |= mode ;            \
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
