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
{ GPIOE, 6 	,	0	},	//BUTTON0
{ GPIOE, 5 	,	1	},	//BUTTON1
{ GPIOE, 9 	,	2	},	//BUTTON2
{ GPIOE, 2 	,	3	},	//BUTTON3
{ GPIOE, 0 	,	4	},	//BUTTON4
{ GPIOE, 4 	,	5	},	//BUTTON5
{ GPIOE, 8 	,	6	},	//BUTTON6
{ GPIOE, 7 	,	7	},	//BUTTON7
{ GPIOE, 3 	,	8	},	//BUTTON8
{ GPIOE, 1 	,	9	},	//BUTTON9
{ GPIOE, 10 	,	10	},	//BUTTON10
{ GPIOE, 11 	,	11	},	//BUTTON11
{ GPIOE, 12 	,	12	},	//BUTTON12
{ GPIOE, 13 	,	13	},	//BUTTON13
{ GPIOE, 14 	,	14	},	//BUTTON14
{ GPIOD, 4	,	15	},	//BUTTON15

};	
BUTTON_PIN_ID Pin_BUTTON_pass[] = {
{ GPIOE, 6 	,	0	},	//BUTTON0
{ GPIOE, 5 	,	1	},	//BUTTON1
{ GPIOE, 9 	,	2	},	//BUTTON2
{ GPIOE, 2 	,	3	},	//BUTTON3
{ GPIOE, 0 	,	4	},	//BUTTON4
{ GPIOE, 4 	,	5	},	//BUTTON5
{ GPIOE, 8 	,	6	},	//BUTTON6
{ GPIOE, 7 	,	7	},	//BUTTON7
{ GPIOE, 3 	,	8	},	//BUTTON8
{ GPIOE, 1 	,	9	},	//BUTTON9


};	
BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOE, 6 	,	0	},	//BUTTON0
{ GPIOE, 5 	,	1	},	//BUTTON1
{ GPIOE, 9 	,	2	},	//BUTTON2
{ GPIOE, 2 	,	3	},	//BUTTON3
{ GPIOE, 0 	,	4	},	//BUTTON4
{ GPIOE, 4 	,	5	},	//BUTTON5
{ GPIOE, 8 	,	6	},	//BUTTON6
{ GPIOE, 7 	,	7	},	//BUTTON7
{ GPIOE, 3 	,	8	},	//BUTTON8
{ GPIOE, 1 	,	9	},	//BUTTON9
{ GPIOE, 10 	,	10	},	//BUTTON10
{ GPIOE, 11 	,	11	},	//BUTTON11
{ GPIOE, 12 	,	12	},	//BUTTON12
{ GPIOE, 13 	,	13	},	//BUTTON13
{ GPIOE, 14 	,	14	},	//BUTTON14
{ GPIOD, 4	,	15	},	//BUTTON15

};
BUTTON_PIN_ID2 Pin_BUTTON_pass2[] = {
{ GPIOE, 6 	,	0	},	//BUTTON0
{ GPIOE, 5 	,	1	},	//BUTTON1
{ GPIOE, 9 	,	2	},	//BUTTON2
{ GPIOE, 2 	,	3	},	//BUTTON3
{ GPIOE, 0 	,	4	},	//BUTTON4
{ GPIOE, 4 	,	5	},	//BUTTON5
{ GPIOE, 8 	,	6	},	//BUTTON6
{ GPIOE, 7 	,	7	},	//BUTTON7
{ GPIOE, 3 	,	8	},	//BUTTON8
{ GPIOE, 1 	,	9	},	//BUTTON9


};
osTimerDef		 (timer0_Object, callback);
osTimerId timerID0;
void callback(void const *param){
	GetState_Pin_BUTTON2(HIGH2LOW);
}

void Init_osTimer (void) {
	timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	osTimerStart(timerID0, 10);	
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
