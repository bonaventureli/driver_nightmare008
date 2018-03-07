/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
#include "app.h"

uint8_t n;
uint8_t m;
T_flag flag;
extern BUTTON_PIN_ID2 Pin_BUTTON[];
extern uint32_t Turntable_Button_MASK_main;
extern uint32_t Temp_Button_MASK_main;

void pass11(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t e,uint8_t z);
void InitSTM32F103ZE(void){
  //Init_osTimer();
	Initialize_Pin_BUTTON(HIGH2LOW);
	MP230_Initialize(USART1);
	LED_Initialize();
	Init_Thread_start();
	SPIx_Init();
	SPIx_SetSpeed(3); 
}

void LogicSTM32F103ZE(void){
	uint8_t i;
 Wait_Pin_BUTTON_Done(10,HIGH2LOW,1,RELEASE);
	
	LED_On(6);//12 button led
	LED_On(3);
	osDelay(2000);
	Wait_Pin_BUTTON_Done(11,HIGH2LOW,100,PRESS);
	JustSendOneInstruction(USART1,10,1);
	osDelay(2000);
	Wait_Pin_BUTTON_Done3(12,13,HIGH2LOW,15,PRESS);
	LED_On(5);//xiaomen_left
	JustSendOneInstruction(USART1,10,6);//yinxiao
	osDelay(2000);
	pass11(0,1,2,3,4,1);
	JustSendOneInstruction(USART1,10,2);	
	osDelay(2000);
	LED_On(4);//xiaomen_right
	pass11(5,6,7,8,9,0);
	JustSendOneInstruction(USART1,10,3);
	osDelay(5999);
	
	JustSendOneInstruction(USART1,10,5);
	LED_On(7);//room2_door
  Wait_Pin_BUTTON_Done(14,HIGH2LOW,1,RELEASE);
	LED_On(0);
	
}

void pass11(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t e,uint8_t z){
	
//	uint8_t i;
		
flag.tiaoguan=0;
while(1)
{
		
if(flag.tiaoguan==1){break;}
	if(flag.err==0){
		if(Pin_BUTTON[15].Buttonflag>50){
			break;
		}
	if(n == 0){
		Wait_Pin_BUTTON_Done_pass(a,HIGH2LOW,100,PRESS);//0
		if(flag.tiaoguan==1){break;}
		else n++;
		if(Pin_BUTTON[15].Buttonflag>50){
			break;
		}
		if(z==1){
			LED_On(12);
		}
		else
			LED_On(10);
	}
	else if(n == 1){
		m = 0;
		Wait_Pin_BUTTON_pass(HIGH2LOW,100);
		if(flag.tiaoguan==1){break;}
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<a)){//0
		m = 1;
																						if(z==1){
																						LED_On(12);
																						}
																						else
																						LED_On(10);
	}
		
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<b)){//1
		m = 2;
																									if(z==1){
																						LED_On(11);
																						}
																						else
																						LED_On(13);
		}
		if(m ==1){
		n = 1;
		}
		else if(m == 2){
		n++;
		}
		else{
																						if(z==1){
																						LED_Off2(1,8,11,12,15,-1);//road1
																						}
																						else{
																						LED_Off2(2,9,10,13,14,-1);//road2
																						}
			flag.err=1;
			JustSendOneInstruction(USART1,10,4);
		n = 0;
		m = 0;
		}
	}

	else if(n == 2){
		m = 0;
		Wait_Pin_BUTTON_pass(HIGH2LOW,100);
		if(flag.tiaoguan==1){break;}
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<b)){//1
		m = 1;
																									if(z==1){
																						LED_On(11);
																						}
																						else
																						LED_On(13);
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<c)){//2
		m = 2;
																									if(z==1){
																						LED_On(15);
																						}
																						else
																						LED_On(14);
		}
		if(m ==1){
		n = 2;
		}
		else if(m == 2){
		n++;
		}
		else{
																						if(z==1){
																						LED_Off2(1,8,11,12,15,-1);//road1
																						}
																						else{
																						LED_Off2(2,9,10,13,14,-1);//road2
																						}
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 3){
		m = 0;
		Wait_Pin_BUTTON_pass(HIGH2LOW,100);
		if(flag.tiaoguan==1){break;}
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<c)){//2
		m = 1;
																									if(z==1){
																						LED_On(15);
																						}
																						else
																						LED_On(14);
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<d)){//3
		m = 2;
																									if(z==1){
																						LED_On(8);
																						}
																						else
																						LED_On(9);
		}
		if(m ==1){
		n = 3;
		}
		else if(m == 2){
		n++;
		}
		else{
																						if(z==1){
																						LED_Off2(1,8,11,12,15,-1);//road1
																						}
																						else{
																						LED_Off2(2,9,10,13,14,-1);//road2
																						}
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 4){
		m = 0;
		Wait_Pin_BUTTON_pass(HIGH2LOW,100);
		if(flag.tiaoguan==1){break;}
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<d)){//3
		m = 1;
																									if(z==1){
																						LED_On(8);
																						}
																						else
																						LED_On(9);
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<e)){//4
		m = 2;
																									if(z==1){
																						LED_On(1);
																						}
																						else
																						LED_On(2);
		}
		if(m ==1){
		n = 4;
		}
		else if(m == 2){
		n=0;
		flag.pass=1;
		break;
		}
		else{
																						if(z==1){
																						LED_Off2(1,8,11,12,15,-1);//road1
																						}
																						else{
																						LED_Off2(2,9,10,13,14,-1);//road2
																						}
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	osDelay(1000);
}
}
}

void pass12(void){
	
//	uint8_t i;
		

while(1)
{
	if(flag.err==0){
		
	if(n == 0){
		Wait_Pin_BUTTON_Done_pass(0,HIGH2LOW,100,PRESS);//Turntable_WaitButtonDone_high2low(0);//0
		n++;
		LED_On(20);
	}
	else if(n == 1){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);//Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<0)){//0
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<1)){//1
		m = 2;
		}
		if(m ==1){
		n = 1;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
			flag.err=1;
			JustSendOneInstruction(USART1,10,4);
		n = 0;
		m = 0;
		}
	}
	
	else if(n == 2){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<1)){//1
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<2)){//2
		m = 2;
		}
		if(m ==1){
		n = 2;
		}
		else if(m == 2){
		n++;
			LED_On(1);
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 3){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<2)){//2
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//3
		m = 2;
		}
		if(m ==1){
		n = 3;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 4){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//3
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<4)){//4
		m = 2;
		}
		if(m ==1){
		n = 4;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 5){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<4)){//4
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<5)){//5
		m = 2;
		}
		if(m ==1){
		n = 5;
		}
		else if(m == 2){
		n++;
		LED_On(8);
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 6){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<5)){//5
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;			
		if(Turntable_Button_MASK_main & (1<<6)){//6
		m = 2;
		}
		if(m ==1){
		n = 6;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	
	else if(n == 7){
		m = 0;
		Wait_Pin_BUTTON(HIGH2LOW,100);
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<6)){//6
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<7)){//7
		m = 2;
		}
		if(m ==1){
		n = 7;
		}
		else if(m == 2){
		n++;
		LED_On(3);
		flag.pass=1;
		break;
		}
		else{
			LED_Off2(20,1,8,3,-1);
			JustSendOneInstruction(USART1,10,4);
			flag.err=1;
		n = 0;
		}
	}
	osDelay(1000);
}
}
}
