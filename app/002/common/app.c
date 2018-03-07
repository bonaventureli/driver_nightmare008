/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for jianyu_zhiwenshibei
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 logic:
 wait button of zhiwen
 voice:zhiwen jie shuo shi bai,qi dong yu yin shi bei.
 yuyinshibei:wo shi a li shang dong ge pei er
 if yuyin is correct,open the door, else start the warning light.
 loop:
 if yaokong is pressed, open the door, else power the door.
 *-----------------------------------------------------------------------------*/
#include "app.h"
extern uint8_t flag_button1;
extern uint8_t flag_button2;
extern BUTTON_PIN_ID2 Pin_BUTTON[];
extern  int percent;
extern 	int decade;
extern 	int single;
extern uint8_t flag_voice;
void InitSTM32F103ZE(void){
	Init_osTimer();
	
	LED_Initialize();
	Initled5604_2();
	Initialize_Pin_BUTTON(HIGH2LOW);
	MP230_Initialize(USART1);
}

void LogicSTM32F103ZE(void){	
	LED_On(5);
	LED_On(3);
	LED_Off(4);
	while(1){	if(Pin_BUTTON[0].Buttonflag>3){break;}}
	
	
	SendOneInstructionB(USART1,10,1);
	LED_Off(5);
	LED_blink2();//wait button of voice be press in 3min
	
//	if(Pin_BUTTON[1].Buttonflag>3){
//	LED_Off(3);//open the door
//	osDelay(5999);
//	}
	if(flag_voice==1){
	LED_On(4);//start the warning led
	osDelay(5999);
	osDelay(5999);
	osDelay(5999);
	osDelay(5999);
	osDelay(5999);
	LED_Off(4);
	}
	else
	{
	LED_Off(3);//open the door
	osDelay(5999);
	}
	while(1){}
}
