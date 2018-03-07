/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for baoxianxiang_jianyu
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 voice:loop password_ok
 012

 0-2+0+1
 
 012 wrong ,empty loop
 02 correct,password_ok
 
 21 wrong ,empty loop
 201 correct,password_ok
 
 first:if(02) password_ok
 
 second:if(01){ 
 password_ok
 break;
 }

 else:loop
 password[]={
 02,01
 }
 
 if(memcmp(rx_data,password,8)==0){
 while(1){
 if((02)&&(flag02==0)){
 SendOneInstructionB2(USART1,10,0);
 flag02=1;
 }
 else if((01)&&(flag02==1)){
 SendOneInstructionB2(USART1,10,0);
 LED_Off(0);//Open the box.
 }
 else{
 SendOneInstructionB2(USART1,10,1);
 }
 }
 }
 
 logic2
 button1 is pressed .voice1 osDelay(5999)
 if button1 is pressed, flag++.else flag=0;
 button2 is pressed .voice1 osDelay(5999)
 if button2 is pressed, flag++.else flag=0;
 button3 is pressed .voice1 osDelay(5999)
 if button2 is pressed, flag++.else flag=0;
 else 
 voice2
 if(flag>=3) open the box
 *-----------------------------------------------------------------------------*/
#include "app.h"
extern BUTTON_PIN_ID2 Pin_BUTTON[];
extern uint8_t flag_time0;
extern uint8_t flag_time1;
uint32_t f_button1;
uint32_t f_button2;
uint32_t f_button3;
uint32_t b_voice1;
uint32_t b_voice2;
uint32_t b_voice3;
void InitSTM32F103ZE(void){
Init_osTimer();
MP230_Initialize(USART1);
Initialize_Pin_BUTTON(HIGH2LOW);	
	LED_Initialize();
	LED_On(0);
}

void LogicSTM32F103ZE(void){
//app_password();
	
	if(Pin_BUTTON[2].Buttonflag>3){
		b_voice3=0;
		b_voice1++;
		if(b_voice1==1){
		SendOneInstructionB2(USART1,10,2);
			osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		}
//		else{
//		JustSendOneInstruction(USART1,10,1);
//		osDelay(10);
//		}
		if(b_voice3>65530){b_voice3=2;}
		f_button1=1;
		
	}
	else if(Pin_BUTTON[1].Buttonflag>3){
		b_voice1=0;
		b_voice2++;
		if(b_voice2==1){
		SendOneInstructionB2(USART1,10,2);
			osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		}
//		else{
//		JustSendOneInstruction(USART1,10,1);
//		osDelay(10);
//		}
		if(b_voice3>65530){b_voice3=2;}
		
		if(f_button1==1){
			f_button2=1;
		}
		else{
			f_button1=0;
			f_button2=0;
			f_button3=0;
		}
	}
	else if(Pin_BUTTON[0].Buttonflag>3){
		b_voice2=0;
		b_voice3++;
		if(b_voice3==1){
		SendOneInstructionB2(USART1,10,2);
			osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		osDelay(5999);
		}
//		else{
//		JustSendOneInstruction(USART1,10,1);
//		osDelay(10);
//		}
		if(b_voice3>65530){b_voice3=2;}
		
		if(f_button2==1){
			f_button3=1;
			LED_Off(0);
		}
			else{
			f_button1=0;
			f_button2=0;
			f_button3=0;
		}
	}
	
	else if(flag_time0==1){
	JustSendOneInstruction(USART1,10,1);
		flag_time0=0;
	}
	if(flag_time1==1){
	GetState_Pin_BUTTON2(HIGH2LOW);
		flag_time1=0;
	}
		//while(1){if(app_card()==1){break;}}

}
