#include "stdint.h"
#include "C:\Keil\EE319Kware\inc\tm4c123gh6pm.h"
#include "C:\Users\Aladdin\Desktop\tiva github\UltraSonic-with-TivaC\bit_specific_addressing.h"

#define p volatile uint32_t*





uint32_t pulseIn(volatile uint32_t*, uint32_t) ;

uint32_t get_Meters(uint32_t);
uint32_t get_10_Cms(uint32_t);
uint32_t get_1_Cms (uint32_t);

void trigger_MS (volatile uint32_t * , uint32_t );

void systic_MS(uint32_t);

void display(uint32_t ,p,p,p,p);


void pinMode(volatile uint32_t *, uint32_t);
void portMode(volatile uint32_t *, uint8_t);
void portSetOutputs(volatile uint32_t *, uint8_t);
void portSetInputs(volatile uint32_t *, uint8_t);
void decoder (uint32_t n, p a, p b, p c, p d,p e, p f, p g);
