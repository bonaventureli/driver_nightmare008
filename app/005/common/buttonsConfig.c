#ifdef STM32F103ZE_BUTTON
void callback2(void const *param);
PASSWORD passwordtext1[]={
	{0,0},
	{2,1},
	{0,0},
	{1,1},
};

#define password_numtext1 sizeof(passwordtext1)/sizeof(PASSWORD)
	
BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOD, 3 	,	0	},
{ GPIOD, 4 	,	1	},
{ GPIOD, 5 	,	2	},
{ GPIOD, 6 	,	3	},
};

osTimerDef		 (timer0_Object, callback);
osTimerDef		 (timer1_Object, callback2);
osTimerId timerID0;
osTimerId timerID1;
uint8_t flag_time0;
uint8_t flag_time1;
void callback(void const *param){
	flag_time0=1;
}
void callback2(void const *param){
	flag_time1=1;
	
}
void Init_osTimer (void) {
	timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	timerID1 = osTimerCreate(osTimer(timer1_Object), osTimerPeriodic, (void *)0);	
	
	osTimerStart(timerID0, 1000);//
	osTimerStart(timerID1, 10);
		
}

void app_password(void){
	uint8_t err;
  while(1){
	err=fun_password_single(passwordtext1);
 if(err==100){
//	 LED_On(0);//Open the box
	break;
	}
 else{
	 //SendOneInstructionB2(USART1,10,0);
 }
	
	if(passwordtext1[0].flag==1){
		//SendOneInstructionB2(USART1,10,1);
	}
	if(passwordtext1[1].flag==1){
		//SendOneInstructionB2(USART1,10,1);
	}
	if(passwordtext1[2].flag==1){
		//SendOneInstructionB2(USART1,10,1);
	}
	if(passwordtext1[3].flag==1){
		//SendOneInstructionB2(USART1,10,1);
	}
}
}
#endif
