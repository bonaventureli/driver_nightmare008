/*-----------------------------------------------------------------------------
 * Name:    		Buttons_Nightmare.c
 * Purpose: 		Buttons interface for Nightmare room1-room2-room3
 * Rev.:    		3.03
 * Author:  		LIFEI
 * LastUptime:	2016-12-29 17:23:32
 
 v3.02
 Add uint32_t Wait_Pin_BUTTON_Done2(uint32_t BUTTONx,uint32_t BUTTONy,ButtonState bState,uint32_t count,uint8_t pressState);
 Change void Wait_Pin_BUTTON(ButtonState bState,uint32_t count);
 *-----------------------------------------------------------------------------*/
/*Includes***************************************/
#ifndef _BUTTONS_C
#define _BUTTONS_C
#include "Buttons_Nightmare.h"
#include "app.h"
/*Private define ***************************************/
#define BUTTON_COUNT (sizeof(Pin_BUTTON0)/sizeof(GPIO_PIN_ID))
	#define BUTTON_COUNT_pass (sizeof(Pin_BUTTON_pass)/sizeof(GPIO_PIN_ID))
#define Turntable_BUTTON_COUNT_high2low (sizeof(Turntable_Pin_BUTTON_high2low)/sizeof(GPIO_PIN_ID))
#define Password_BUTTON_COUNT_high2low (sizeof(Password_Pin_BUTTON_high2low)/sizeof(GPIO_PIN_ID))
#define Password_BUTTON_COUNT (sizeof(Password_Pin_BUTTON)/sizeof(GPIO_PIN_ID))
uint8_t 
flag_button0,\
flag_button8,\
flag_button9,\
flag_button7,\
flag_button10,\
flag_button16,\
flag_button21,\
flag_button22,\
flag_button23,\
flag_button6,\
flag_button3,\
flag_button27,\
flag_button1,\
flag_button2,\
flag_button4,\
flag_button26,\
flag_button24,\
flag_button20,\
flag_button25,\
flag_button28,\
flag_button12,\
flag_button18,\
flag_button17,\
flag_button11;
uint32_t Button_MASK_main;
uint32_t Turntable_Button_MASK_main;
uint32_t Temp_Button_MASK_main;
uint32_t Password_Button_MASK_main;
uint32_t tempPassword;

#define STM32F103ZE_BUTTON
#include "ButtonsConfig.c"
const BUTTON_PIN_ID Turntable_Pin_BUTTON_high2low[] = {
{ GPIOE, 0 	,	0	},	//BUTTON0
{ GPIOE, 1 	,	1	},	//BUTTON1
{ GPIOE, 2 	,	2	},	//BUTTON2
{ GPIOE, 3 	,	3	},	//BUTTON3
{ GPIOE, 4 	,	4	},	//BUTTON4
{ GPIOE, 5 	,	5	},	//BUTTON5
{ GPIOE, 6 	,	6	},	//BUTTON6
{ GPIOE, 7 	,	7	},	//BUTTON7
};

const BUTTON_PIN_ID Password_Pin_BUTTON_high2low[] = {
{ GPIOE,9,	0	},
{ GPIOE,10,	1	},
{ GPIOE,11,	2	},
{ GPIOE,12,	3	},
{ GPIOE,13,	4	},
{ GPIOE,6,	5	},
{ GPIOE,15,	6	},
{ GPIOE,14,	7	},
};
const BUTTON_PIN_ID Password_Pin_BUTTON[] = {
{ GPIOE,9,	0	},
{ GPIOE,10,	1	},
{ GPIOE,11,	2	},
{ GPIOE,12,	3	},
{ GPIOE,13,	4	},
{ GPIOE,6,	5	},
{ GPIOE,15,	6	},
{ GPIOE,14,	7	},
};
BUTTON_PIN_ID2 Password_Pin_BUTTON2[] = {
{ GPIOE,9,	0	},
{ GPIOE,10,	1	},
{ GPIOE,11,	2	},
{ GPIOE,12,	3	},
{ GPIOE,13,	4	},
{ GPIOE,6,	5	},
{ GPIOE,15,	6	},
{ GPIOE,14,	7	},
};

//extern T_flag flag;
/****************************************
  @brief       Initialize buttons
  @returns
     0: function succeeded
    -1: function failed
****************************************/
int32_t Turntable_Buttons_Initialize_high2low (void) {
  uint32_t n;
	for (n = 0; n < Turntable_BUTTON_COUNT_high2low; n++) {
	GPIO_PortClock   (Turntable_Pin_BUTTON_high2low[n].port, true);
	GPIO_PinConfigure(Turntable_Pin_BUTTON_high2low[n].port, Turntable_Pin_BUTTON_high2low[n].num,
										GPIO_IN_PULL_UP, 
										GPIO_MODE_INPUT);/*high2low*/
  }

  return 0;
}

int32_t Password_Buttons_Initialize_high2low (void) {
  uint32_t n;
	for (n = 0; n < Password_BUTTON_COUNT_high2low; n++) {
	GPIO_PortClock   (Password_Pin_BUTTON_high2low[n].port, true);
	GPIO_PinConfigure(Password_Pin_BUTTON_high2low[n].port, Password_Pin_BUTTON_high2low[n].num,
										GPIO_IN_PULL_UP, 
										GPIO_MODE_INPUT);/*high2low*/
  }

  return 0;
}
void func_tiaoguan2(uint8_t a,uint8_t b,uint32_t count){
	uint8_t flag_a,flag_b;
	while(1){
	Wait_Pin_BUTTON(HIGH2LOW,count);
	Temp_Button_MASK_main = Button_MASK_main;
	if(Button_MASK_main & (1<<a)){
	flag_a = 1;
	}
	Button_MASK_main = Temp_Button_MASK_main;
	if(Button_MASK_main & (1<<b)){
	flag_b = 1;
	}
	if((flag_a == 1)||(flag_b == 1)){
	flag_a = 0;
	flag_b = 0;
	break;
	}
	}
}
/****************************************
  @brief       Get buttons state
  @returns     Turntable_Buttons state
****************************************/
uint32_t Turntable_Buttons_GetState_high2low (void) {
  uint32_t val = 0;
	uint32_t n;
  /* check the low to high pins */
	for (n = 0; n < Turntable_BUTTON_COUNT_high2low; n++) {
		if (GPIO_PinRead(Turntable_Pin_BUTTON_high2low[n].port, Turntable_Pin_BUTTON_high2low[n].num) == 0){
			val |= (1<<Turntable_Pin_BUTTON_high2low[n].mask);/*high2low*/
		}
	}
  return (val);
}

uint32_t Password_Buttons_GetState_high2low (void) {
  uint32_t val = 0;
	uint32_t n;
  /* check the low to high pins */
	for (n = 0; n < Password_BUTTON_COUNT_high2low; n++) {
		if (GPIO_PinRead(Password_Pin_BUTTON_high2low[n].port, Password_Pin_BUTTON_high2low[n].num) == 0){
			val |= (1<<Password_Pin_BUTTON_high2low[n].mask);/*high2low*/
		}
	}
  return (val);
}
uint32_t Password_Buttons_GetState (ButtonState bState,uint32_t count) {	
	uint32_t n;
	uint32_t val;
	val = 0;
	if(bState == LOW2HIGH){
		/* check the low to high pins */
		for (n = 0; n < Password_BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Password_Pin_BUTTON2[n].port, Password_Pin_BUTTON2[n].num) == 1){
				Password_Pin_BUTTON2[n].Buttonflag++;
			}
			else{
				Password_Pin_BUTTON2[n].Buttonflag=0;
			}
			if(Password_Pin_BUTTON2[n].Buttonflag>=count){
			Password_Pin_BUTTON2[n].Buttonflag=0;
			val |= (1<<Password_Pin_BUTTON2[n].mask);/*low2high*/
		}
		}
	}
	else if(bState == HIGH2LOW){
		 /* check the high TO low pins */
		for (n = 0; n < Password_BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Password_Pin_BUTTON2[n].port, Password_Pin_BUTTON2[n].num) == 0){
				Password_Pin_BUTTON2[n].Buttonflag++;
			}
			else{
				Password_Pin_BUTTON2[n].Buttonflag=0;
			}
			if(Password_Pin_BUTTON2[n].Buttonflag>=count){
			Password_Pin_BUTTON2[n].Buttonflag=0;
			val |= (1<<Password_Pin_BUTTON2[n].mask);/*high2low*/
		}
		}
	}
  return (val);
}
/*****************************************
*@brif check the BUTTONx
*@para BUTTONx: 0 1 2 3 
*@return 0
*****************************************/
uint8_t Turntable_WaitButtonDone_high2low(uint32_t BUTTONx)
{
	uint32_t Button_MASK;
	while(1){
		Button_MASK = Turntable_Buttons_GetState_high2low();
		osDelay(160);
		if(Button_MASK & (1<<BUTTONx)){
		break;
		}
	}
	return 0;
}
void Wait_Pin_BUTTON(ButtonState bState,uint32_t count)
{	
	/*wait button*/	
	Button_MASK_main = 0;
	Turntable_Button_MASK_main=0;
	while(1){
		Button_MASK_main = GetState_Pin_BUTTON(Button_MASK_main,bState,count);
		Turntable_Button_MASK_main=Button_MASK_main;
		//osDelay(100);
		if(Button_MASK_main){
			Turntable_Button_MASK_main=Button_MASK_main;
			break;
		}
	}
}
void Wait_Pin_BUTTON_pass(ButtonState bState,uint32_t count)
{	
	/*wait button*/	
	Button_MASK_main = 0;
	Turntable_Button_MASK_main=0;
	while(1){
//		if(Pin_BUTTON[15].Buttonflag>50){
//			break;
//		}
		Button_MASK_main = GetState_Pin_BUTTON_pass(Button_MASK_main,bState,count);
		Turntable_Button_MASK_main=Button_MASK_main;
		//osDelay(100);
		if(Button_MASK_main){
			Turntable_Button_MASK_main=Button_MASK_main;
			break;
		}
	}
}
uint32_t Wait_Pin_BUTTON_Done2(uint32_t BUTTONx,uint32_t BUTTONy,ButtonState bState,uint32_t count,uint8_t pressState){
	uint32_t Button_MASK;
	Button_MASK = 0;
	while(1){
		Button_MASK = GetState_Pin_BUTTON(Button_MASK,bState,count);
		//osDelay(100);
		if(pressState==PRESS){
			if(Button_MASK & (1<<BUTTONx)){
		return 1;
		}
			if(Button_MASK & (1<<BUTTONy)){
		return 2;
		}
		}
		else if(pressState==RELEASE){
			if((~Button_MASK) & (1<<BUTTONx)){
		return 1;
		}
			if((~Button_MASK) & (1<<BUTTONy)){
		return 2;
		}
		}
	}
}
void Wait_Pin_BUTTON_Done3(uint32_t BUTTONx,uint32_t BUTTONy,ButtonState bState,uint32_t count,uint8_t pressState){
	uint32_t Button_MASK;
	Button_MASK = 0;
	while(1){
//		if(Pin_BUTTON[15].Buttonflag>50){
//			break;
//		}
		Button_MASK = GetState_Pin_BUTTON(Button_MASK,bState,count);
			if((Button_MASK & (1<<BUTTONx))&&(Button_MASK & (1<<BUTTONy))){
		break;
		}
	}
}
/*****************************************
*@brif wait one Turntable_BUTTON
*@para None
*@return None
*****************************************/
void Turntable_WaitButton_high2low(void)
{	
	/*wait button*/	
	Turntable_Button_MASK_main = 0;
	while(1){
		Turntable_Button_MASK_main = Turntable_Buttons_GetState_high2low();
		osDelay(100);
		if(Turntable_Button_MASK_main){
			break;
		}
	}
}

void Password_WaitButton_high2low(void)
{	
	/*wait button*/	
	Password_Button_MASK_main = 0;
	while(1){
		Password_Button_MASK_main = Password_Buttons_GetState_high2low();
		osDelay(100);
		if(Password_Button_MASK_main){
			break;
		}
	}
}
void Password_Wait_Pin_BUTTON(ButtonState bState,uint32_t count)
{	
	/*wait button*/	
	Password_Button_MASK_main = 0;
	while(1){
		Password_Button_MASK_main = Password_Buttons_GetState(bState,count);
		osDelay(100);
		if(Password_Button_MASK_main){
			break;
		}
	}
}
void GetState_Pin_BUTTON2 (ButtonState bState) {
	uint32_t n;
	if(bState == LOW2HIGH){
		/* check the low to high pins */
		for (n = 0; n < BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Pin_BUTTON[n].port, Pin_BUTTON[n].num) == 1){
				Pin_BUTTON[n].Buttonflag++;
				if(Pin_BUTTON[n].Buttonflag>65530){
					Pin_BUTTON[n].Buttonflag=65530;
				}
			}
			else{
				Pin_BUTTON[n].Buttonflag=0;
			}
		}
	}
	else if(bState == HIGH2LOW){
		 /* check the high TO low pins */
		for (n = 0; n < BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Pin_BUTTON[n].port, Pin_BUTTON[n].num) == 0){
				Pin_BUTTON[n].Buttonflag++;
				if(Pin_BUTTON[n].Buttonflag>65530){
					Pin_BUTTON[n].Buttonflag=65530;
				}
			}
			else{
				Pin_BUTTON[n].Buttonflag=0;
			}
		}
	}
}

uint32_t GetState_Pin_BUTTON (uint32_t val,ButtonState bState,uint32_t count) {
	uint32_t n;
	val = 0;
	if(bState == LOW2HIGH){
		/* check the low to high pins */
		for (n = 0; n < BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Pin_BUTTON[n].port, Pin_BUTTON[n].num) == 1){
				Pin_BUTTON[n].Buttonflag++;
			}
			else{
				Pin_BUTTON[n].Buttonflag=0;
			}
			if(Pin_BUTTON[n].Buttonflag>=count){
			Pin_BUTTON[n].Buttonflag=0;
			val |= (1<<Pin_BUTTON[n].mask);/*low2high*/
		}
		}
	}
	else if(bState == HIGH2LOW){
		 /* check the high TO low pins */
		for (n = 0; n < BUTTON_COUNT; n++) {
			if (GPIO_PinRead(Pin_BUTTON[n].port, Pin_BUTTON[n].num) == 0){
				Pin_BUTTON[n].Buttonflag++;
			}
			else{
				Pin_BUTTON[n].Buttonflag=0;
			}
			if(Pin_BUTTON[n].Buttonflag>=count){
			Pin_BUTTON[n].Buttonflag=0;
			val |= (1<<Pin_BUTTON[n].mask);/*high2low*/
		}
		}
	}
  return (val);
}
uint32_t GetState_Pin_BUTTON_pass (uint32_t val,ButtonState bState,uint32_t count) {
	uint32_t n;
	val = 0;
	if(bState == LOW2HIGH){
		/* check the low to high pins */
		for (n = 0; n < BUTTON_COUNT_pass; n++) {
			if (GPIO_PinRead(Pin_BUTTON_pass2[n].port, Pin_BUTTON_pass2[n].num) == 1){
				Pin_BUTTON_pass2[n].Buttonflag++;
			}
			else{
				Pin_BUTTON_pass2[n].Buttonflag=0;
			}
			if(Pin_BUTTON_pass2[n].Buttonflag>=count){
			Pin_BUTTON_pass2[n].Buttonflag=0;
			val |= (1<<Pin_BUTTON_pass2[n].mask);/*low2high*/
		}
		}
	}
	else if(bState == HIGH2LOW){
		 /* check the high TO low pins */
		for (n = 0; n < BUTTON_COUNT_pass; n++) {
			if (GPIO_PinRead(Pin_BUTTON_pass2[n].port, Pin_BUTTON_pass2[n].num) == 0){
				Pin_BUTTON_pass2[n].Buttonflag++;
			}
			else{
				Pin_BUTTON_pass2[n].Buttonflag=0;
			}
			if(Pin_BUTTON_pass2[n].Buttonflag>=count){
			Pin_BUTTON_pass2[n].Buttonflag=0;
			val |= (1<<Pin_BUTTON_pass2[n].mask);/*high2low*/
		}
		}
	}
  return (val);
}
uint32_t Wait_Pin_BUTTON_Done(uint32_t BUTTONx,ButtonState bState,uint32_t count,uint8_t pressState){
	uint32_t Button_MASK;
	Button_MASK = 0;
	while(1){
//		if(Pin_BUTTON[15].Buttonflag>50){
////			flag.tiaoguan=1;
//			break;
//		}
		Button_MASK = GetState_Pin_BUTTON(Button_MASK,bState,count);
		//osDelay(100);
		if(pressState==PRESS){
			if(Button_MASK & (1<<BUTTONx)){
		return 1;
//				if(flag.tiaoguan==1){return 0;}
		}
		}
		else if(pressState==RELEASE){
			if((~Button_MASK) & (1<<BUTTONx)){
		return 1;
		}
		}
	}
}
uint32_t Wait_Pin_BUTTON_Done_pass(uint32_t BUTTONx,ButtonState bState,uint32_t count,uint8_t pressState){
	uint32_t Button_MASK;
	Button_MASK = 0;
	while(1){
//		if(Pin_BUTTON_pass2[15].Buttonflag>10){
//			flag.tiaoguan=1;
//			break;
//		}
		Button_MASK = GetState_Pin_BUTTON_pass(Button_MASK,bState,count);
		//osDelay(100);
		if(pressState==PRESS){
			if(Button_MASK & (1<<BUTTONx)){
		return 1;
		}
//			if(flag.tiaoguan==1){return 0;}
		}
		else if(pressState==RELEASE){
			if((~Button_MASK) & (1<<BUTTONx)){
		return 1;
		}
		}
	}
}
void Initialize_Pin_BUTTON (ButtonState bState) {
  uint32_t n;
	if(bState == LOW2HIGH){
	for (n = 0; n < BUTTON_COUNT; n++) {
	GPIO_PortClock   (Pin_BUTTON[n].port, true);
	GPIO_PinConfigure(Pin_BUTTON[n].port, Pin_BUTTON[n].num,
										GPIO_IN_PULL_DOWN, 
										GPIO_MODE_INPUT);/*low2high*/
  }	
	}
	else if(bState == HIGH2LOW){
	for (n = 0; n < BUTTON_COUNT; n++) {
	GPIO_PortClock   (Pin_BUTTON[n].port, true);
	GPIO_PinConfigure(Pin_BUTTON[n].port, Pin_BUTTON[n].num,
										GPIO_IN_PULL_UP, 
										GPIO_MODE_INPUT);/*high2low*/
  }
	}
}

uint8_t fun_password_single(PASSWORD *tmp){
	uint8_t n;
	osTimerStop(timerID0);
	for(n=0;n<password_numtext1;n++){
		Wait_Pin_BUTTON(HIGH2LOW,5);	
		if((((Button_MASK_main)>>(tmp[n].password))&0x01)==1){
			tmp[n].flag=1;//password right
		}
		else{
			return n;
		}
	}
	osTimerStart(timerID0, 1000);
	 return 100;
}
uint8_t fun_password_loop(PASSWORD *tmp){
	uint8_t n;
	uint32_t Temp_Button;
	osTimerStop(timerID0);
	for(n=0;n<password_numtext1;n++){
		Wait_Pin_BUTTON(HIGH2LOW,5);	
		Temp_Button=Button_MASK_main;
		if((((Button_MASK_main)>>(tmp[n].password))&0x01)==1){
			tmp[n].flag=1;//password right
		}
		Button_MASK_main=Temp_Button;
		if((((Button_MASK_main)>>(tmp[n-1].password))&0x01)==1){
			n--;
	 }
		else{
			return n;
		}
	}
	osTimerStart(timerID0, 1000);
	 return 100;
}
#endif
