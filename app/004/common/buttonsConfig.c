#ifdef STM32F103ZE_BUTTON
PASSWORD passwordtext1[]={
	{7,0},
	{3,1},
	{9,2},
	{7,3},
	{4,4},
};

#define password_numtext1 sizeof(passwordtext1)/sizeof(PASSWORD)
osTimerDef		 (timer0_Object, callback);
osTimerDef		 (timer1_Object, callback);
osTimerId timerID0;
osTimerId timerID1;
uint32_t flag_time0;
uint32_t flag_time1;

void callback(void const *param){
	switch ((uint32_t) param){
		case 0:
			break;
		case 1:
			flag_time1++;
		if(flag_time1>=65564){flag_time1=0;}
			break;
	}
	GetState_Pin_BUTTON2(HIGH2LOW);
}

void Init_osTimer (void) {
	timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	timerID1 = osTimerCreate(osTimer(timer1_Object), osTimerPeriodic, (void *)1);	
	osTimerStart(timerID0, 10);	
	osTimerStart(timerID1, 5999);//1s	
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
//void Thread_Button (void const *argument) {
//  while (1) {
//	Wait_Pin_BUTTON(HIGH2LOW,10);
//	if(Button_MASK_main & (1<<1)){flag_button1 = 1;}
//	if(Button_MASK_main & (1<<2)){flag_button2 = 1;}
//	if(Button_MASK_main & (1<<3)){flag_button3 = 1;}
//	if(Button_MASK_main & (1<<4)){flag_button4 = 1;}
//	if(Button_MASK_main & (1<<6)){flag_button6 = 1;}
//	if(Button_MASK_main & (1<<7)){flag_button7 = 1;}
//	if(Button_MASK_main & (1<<8)){flag_button8 = 1;}
//	if(Button_MASK_main & (1<<9)){flag_button9 = 1;}
//	
//	if(Button_MASK_main & (1<<10)){flag_button10 = 1;}s
//	if(Button_MASK_main & (1<<11)){flag_button11 = 1;}
//	if(Button_MASK_main & (1<<16)){flag_button16 = 1;}
//	if(Button_MASK_main & (1<<18)){flag_button18 = 1;}
//	if(Button_MASK_main & (1<<17)){flag_button17 = 1;}
//	if(Button_MASK_main & (1<<20)){flag_button20 = 1;}
//	if(Button_MASK_main & (1<<21)){flag_button21 = 1;}
//	if(Button_MASK_main & (1<<22)){flag_button22 = 1;}
//	if(Button_MASK_main & (1<<24)){flag_button24 = 1;}
//	if(Button_MASK_main & (1<<25)){flag_button25 = 1;}
//	if(Button_MASK_main & (1<<26)){flag_button26 = 1;}
//	if(Button_MASK_main & (1<<27)){flag_button27 = 1;}
//	if(Button_MASK_main & (1<<28)){osDelay(5000);flag_button28 = 1;}
//}
//}

BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOD, 15 	,	0	},//key_red
{ GPIOD, 14 	,	1	},//key_white
{ GPIOD, 13 	,	2	},//key_green
{ GPIOD, 12 	,	3	},//yaokong
};
#endif
