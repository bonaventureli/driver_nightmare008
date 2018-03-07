/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for jianyu_bangongshi_room
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 logic:
 wait button:
 if button1 release ,start the warning light.
 if button2 press ,empty.
 turn on the key light,and wait the button.
 if button pressed.open chouti.
 if card id correct.turn right the tuigan.
 *-----------------------------------------------------------------------------*/
#include "app.h"
extern uint8_t CardRxBufferUSARTOne[14];
extern uint8_t CardID[][14];
extern uint32_t Button_MASK_main;
osThreadDef(card_thread,osPriorityNormal,1,0);
osTimerDef		 (timer0_Object, callback);

void InitSTM32F103ZE(void){
Initialize_Pin_BUTTON(HIGH2LOW);
//Init_Thread_Button();
LED_Initialize();
RDM6300_Initialize(USART1);
//Init_osTimer();
//Init_cardthread();
}

void LogicSTM32F103ZE(void){
	uint16_t i;
	uint32_t button;

	LED_On(2);
	//Wait_Pin_BUTTON_Done(1,HIGH2LOW,10,PRESS);
	while(1){
	Wait_Pin_BUTTON( HIGH2LOW, 10);
	if(((Button_MASK_main>>1)&(0x01))==1){
		goto laber2;
	}
	if(((Button_MASK_main>>2)&(0x01))==1){
		LED_Off(2);
		goto laber1;
	}
}
		/*add an yaokong button which can jump the step of stolen the box on the desk.*/
	laber1: Wait_Pin_BUTTON_Done2(0,2,HIGH2LOW,1,RELEASE);
	
	LED_On(3);//start the warning led.
	for(i=0;i<6;i++){
	osDelay(5999);
	}
	LED_Off(3);
	
	for(i=0;i<60;i++){
	osDelay(5999);//1s
	}
	LED_On(2);
	Wait_Pin_BUTTON_Done(1,HIGH2LOW,10,PRESS);
	
laber2: LED_On(1);
	while(1){
		if(CheckOneCard(USART1,14,CardRxBufferUSARTOne,CardID[0])==1){
			break;
		}
		if(CheckOneCard(USART1,14,CardRxBufferUSARTOne,CardID[1])==1){
			break;
		}
	}
	LED_On(0);
	while(1){}
}
int Init_cardthread(void){
	osThreadCreate(osThread(card_thread),NULL);
	return 0;
}
void callback(void const *param){
	GPIOE->ODR ^= 0x1;	
}

void Init_osTimer (void) {
	osTimerId timerID0 = osTimerCreate(osTimer(timer0_Object), osTimerPeriodic, (void *)0);	
	osTimerStart(timerID0, 60000);	
}
void card_thread(void const *argument){
	while(1){
			if(CheckOneCard(USART1,14,CardRxBufferUSARTOne,CardID[0])==1){
	LED_Flash2(2000,0,1,2,3,-1);
 }
	}
}
