#ifdef STM32F103ZE_BUTTON

PASSWORD passwordtext1[]={
	{7,0},
	{3,1},
	{9,2},
	{7,3},
	{4,4},
};

#define password_numtext1 sizeof(passwordtext1)/sizeof(PASSWORD)
BUTTON_PIN_ID Pin_BUTTON0[] = {
{ GPIOE, 0 	,	0	},
{ GPIOE, 1 	,	1	},
{ GPIOE, 2 	,	2	},
{ GPIOE, 3 	,	3	},
{ GPIOE, 4 	,	4	},
{ GPIOE, 5 	,	5	},
{ GPIOE, 6 	,	6	},
{ GPIOE, 7 	,	7	},
{ GPIOE, 8 	,	8	},
{ GPIOE, 9 	,	9	},
{ GPIOE, 10 	,	10	},
{ GPIOE, 11 	,	11	},
{ GPIOE, 12 	,	12	},

};	
BUTTON_PIN_ID Pin_BUTTON_pass[] = {
{ GPIOE, 0 	,	0	},
{ GPIOE, 1 	,	1	},
{ GPIOE, 2 	,	2	},
{ GPIOE, 3 	,	3	},
{ GPIOE, 4 	,	4	},
{ GPIOE, 5 	,	5	},
{ GPIOE, 6 	,	6	},
{ GPIOE, 7 	,	7	},
{ GPIOE, 8 	,	8	},
{ GPIOE, 9 	,	9	},
{ GPIOE, 10 	,	10	},
{ GPIOE, 11 	,	11	},
{ GPIOE, 12 	,	12	},

};	
BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOE, 0 	,	0	},
{ GPIOE, 1 	,	1	},
{ GPIOE, 2 	,	2	},
{ GPIOE, 3 	,	3	},
{ GPIOE, 4 	,	4	},
{ GPIOE, 5 	,	5	},
{ GPIOE, 6 	,	6	},
{ GPIOE, 7 	,	7	},
{ GPIOE, 8 	,	8	},
{ GPIOE, 9 	,	9	},
{ GPIOE, 10 	,	10	},
{ GPIOE, 11 	,	11	},
{ GPIOE, 12 	,	12	},

};
BUTTON_PIN_ID2 Pin_BUTTON_pass2[] = {
{ GPIOE, 0 	,	0	},
{ GPIOE, 1 	,	1	},
{ GPIOE, 2 	,	2	},
{ GPIOE, 3 	,	3	},
{ GPIOE, 4 	,	4	},
{ GPIOE, 5 	,	5	},
{ GPIOE, 6 	,	6	},
{ GPIOE, 7 	,	7	},
{ GPIOE, 8 	,	8	},
{ GPIOE, 9 	,	9	},
{ GPIOE, 10 	,	10	},
{ GPIOE, 11 	,	11	},
{ GPIOE, 12 	,	12	},

};
osTimerDef		 (timer0_Object, callback);
osTimerId timerID0;
void callback(void const *param){
	GetState_Pin_BUTTON2(HIGH2LOW);
}

void Init_osTimer (void) {
	timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	osTimerStart(timerID0, 10000);	//10
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
