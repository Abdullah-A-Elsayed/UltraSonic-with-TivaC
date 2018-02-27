volatile unsigned long pulseIn(volatile unsigned long* pin , int value){
	/*----initialize counter but don't enable it-------*/
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R |= 4;//clk src from cpu, but not enabled
	NVIC_ST_RELOAD_R = 16000000;//around 1 second
	
	/*-----wait untill pin goes to value---------------*/
	while(*pin==value){} 
	while(*pin==!value){} //now i'm sure value just started
		
	/*-----enable counter untill pin goes to !value----*/
	NVIC_ST_CTRL_R |= 1;//enabled
	while(*pin==value){}//wait
	volatile unsigned long counter_value = NVIC_ST_CURRENT_R;
	NVIC_ST_CTRL_R |= 0;//disabled
		
	/*---------------get real time---------------------*/
	volatile unsigned long counts = 16000000 - counter_value;
	volatile unsigned long time_in_us = counts*0.0625;
	return time_in_us;
}