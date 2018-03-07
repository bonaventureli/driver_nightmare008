#ifdef STM32F103ZE_BUTTON

PASSWORD passwordtext1[]={
	{7,0},
	{3,1},
	{9,2},
	{7,3},
	{4,4},
};

#define password_numtext1 sizeof(passwordtext1)/sizeof(PASSWORD)
	
BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOE, 8 	,	0	},
{ GPIOE, 13 	,	1	},
};

osTimerDef		 (timer0_Object, callback);
osTimerId timerID0;
void callback(void const *param){
	GetState_Pin_BUTTON2(HIGH2LOW);
}

void Init_osTimer (void) {
	timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	osTimerStart(timerID0, 1000);	
}

void app_password(void){
	uint8_t err;
 while(1){
	err=fun_password_single(passwordtext1);
			 if(err==0){}
	else if(err==1){}
	else if(err==2){}
	else if(err==3){}
	else if(err==4){}
	else if(err==5){break;}
	
	if(passwordtext1[0].flag==1){}
	if(passwordtext1[1].flag==1){}
	if(passwordtext1[2].flag==1){}
	if(passwordtext1[3].flag==1){}
	if(passwordtext1[4].flag==1){}
}
}
#endif
