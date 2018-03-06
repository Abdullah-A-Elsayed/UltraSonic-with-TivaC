volatile uint32_t pulseIn(volatile uint32_t* pin , uint32_t value){
	uint32_t turns=0 , counter_value , time_in_us , counts;
	/*----initialize counter but don't enable it-------*/
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_RELOAD_R = 0xFF;  //around 1 second
	NVIC_ST_CTRL_R = 4;//clk src from cpu, but not enabled
	
	
	/*-----wait untill pin goes to value---------------*/
	while(*pin==value){} 
	while(*pin==!value){} //now i'm sure value just started
		
	/*-----enable counter untill pin goes to !value----*/
	NVIC_ST_CTRL_R |= 1;//enabled
	while(*pin==value)
	{
		if(NVIC_ST_CTRL_R&0x10000)
			turns = turns + 1;
	}//wait
	NVIC_ST_CTRL_R = 0;  //disabled
	counter_value = NVIC_ST_CURRENT_R;
	
		
	/*---------------get real time---------------------*/
	counts = turns * 0xFF + 0xFF - counter_value;
	time_in_us = counts / 16;
	return time_in_us;
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