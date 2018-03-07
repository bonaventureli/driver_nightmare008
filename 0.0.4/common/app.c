/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
#include "app.h"
extern BUTTON_PIN_ID2 Pin_BUTTON[];
void InitSTM32F103ZE(void){
Init_osTimer();
}

void LogicSTM32F103ZE(void){
app_password();
	if(Pin_BUTTON[0].Buttonflag>100){}
		while(1){if(app_card()==1){break;}}
}


