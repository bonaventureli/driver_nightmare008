/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for jianyu_jiankong_room
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 ten minutes later
 start up:flog,warning light,six door
 if button in jianyu is pressed,open three door and light the led out of the jinyu
 if button out of jianyu is pressed,start up flog,warning.
 *-----------------------------------------------------------------------------*/
#include "app.h"
extern uint32_t flag_time1;
extern BUTTON_PIN_ID2 Pin_BUTTON[];
void func_baoluan(void);
void InitSTM32F103ZE(void){
Init_osTimer();
LED_Initialize();
Initialize_Pin_BUTTON(HIGH2LOW);
}

void LogicSTM32F103ZE(void){
	
	while(1){	if(Pin_BUTTON[2].Buttonflag>10){break;}}
	LED_On(6);
	/*1.After ten minutes open warning led, flog and six door.*/
	while(1){
		if((flag_time1>1800)||(Pin_BUTTON[3].Buttonflag>10)){//60*30
		flag_time1=0;
			break;
		}
	}
	LED_On(5);//six door
	LED_On(9);
	func_baoluan();
	/*2.If button in jianyu room pressed, open three door and the button out of jianyu is enabled.*/
	Wait_Pin_BUTTON_Done(1,HIGH2LOW,5,PRESS);
	LED_On(4);//open three door
	
	LED_On(8);//button out of jianyu is enable
	/*3.If button out of jianyu is pressed, warning led and flog.*/
	Wait_Pin_BUTTON_Done(0,HIGH2LOW,5,PRESS);
	func_baoluan();
	
	LED_Off(6);
	while(1){}
}
void func_baoluan(void){
	uint16_t i;
	LED_On2(1,2,3,-1);//warning led
	LED_On(0);//flog
	for(i=0;i<4;i++){
	osDelay(5999);
	}
	LED_Off(0);
	for(i=0;i<8;i++){
	osDelay(5999);
	}
	LED_Off2(1,2,3,-1);
}
