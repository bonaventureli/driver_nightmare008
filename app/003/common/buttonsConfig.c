#ifdef STM32F103ZE_BUTTON

void Thread_Button (void const *argument) {
  while (1) {
	Wait_Pin_BUTTON(HIGH2LOW,10);
	if(Button_MASK_main & (1<<1)){flag_button1 = 1;}
	if(Button_MASK_main & (1<<2)){flag_button2 = 1;}
	if(Button_MASK_main & (1<<3)){flag_button3 = 1;}
	if(Button_MASK_main & (1<<4)){flag_button4 = 1;}
	if(Button_MASK_main & (1<<6)){flag_button6 = 1;}
	if(Button_MASK_main & (1<<7)){flag_button7 = 1;}
	if(Button_MASK_main & (1<<8)){flag_button8 = 1;}
	if(Button_MASK_main & (1<<9)){flag_button9 = 1;}
	
	if(Button_MASK_main & (1<<10)){flag_button10 = 1;}
	if(Button_MASK_main & (1<<11)){flag_button11 = 1;}
	if(Button_MASK_main & (1<<16)){flag_button16 = 1;}
	if(Button_MASK_main & (1<<18)){flag_button18 = 1;}
	if(Button_MASK_main & (1<<17)){flag_button17 = 1;}
	if(Button_MASK_main & (1<<20)){flag_button20 = 1;}
	if(Button_MASK_main & (1<<21)){flag_button21 = 1;}
	if(Button_MASK_main & (1<<22)){flag_button22 = 1;}
	if(Button_MASK_main & (1<<24)){flag_button24 = 1;}
	if(Button_MASK_main & (1<<25)){flag_button25 = 1;}
	if(Button_MASK_main & (1<<26)){flag_button26 = 1;}
	if(Button_MASK_main & (1<<27)){flag_button27 = 1;}
	if(Button_MASK_main & (1<<28)){osDelay(5000);flag_button28 = 1;}
}
}

BUTTON_PIN_ID2 Pin_BUTTON[] = {
{ GPIOD, 15 	,	0	},
{ GPIOE, 15 	,	1	},
{ GPIOE, 14 	,	2	},//button yaokong
};
#endif
