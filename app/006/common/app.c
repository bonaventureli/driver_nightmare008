/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
#ifndef _APP_C
#define _APP_C
#include "app.h"
extern BUTTON_PIN_ID2 Pin_BUTTON[];

void InitSTM32F103ZE(void){
Init_osTimer();
Init_Thread_CAN();
Initialize_Pin_BUTTON(HIGH2LOW);
MP230_Initialize(USART1);
	LED_Initialize();
}

void LogicSTM32F103ZE(void){

while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}
SendOneInstructionB2(USART1,10,0);//wo shi huangxiaohai
LED_On(1);//1-1
while(1){if(Pin_BUTTON[1].Buttonflag>100){break;}}//B1-1
SendOneInstructionB2(USART1,10,1);//R1-1

//CAN_Send STM_Chuanghu
/*
if chuanghu is ok
LED_On(0);//xilisuo
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_chaunghu is closed
*/
//CAN_Receive STM_Chuanghu is ok
while(1){if(Pin_BUTTON[2].Buttonflag>100){break;}}//B_taideng
LED_On(2);//taideng
SendOneInstructionB2(USART1,10,2);//R_lingsheng
//CAN_Send STM_shizhong
//CAN_Reveive STM_shizhong
LED_On(3);//1-2
while(1){if(Pin_BUTTON[3].Buttonflag>100){break;}}//B1-2
SendOneInstructionB2(USART1,10,3);//R1-2
while(1){if(Pin_BUTTON[4].Buttonflag>100){break;}}//B_Mofang
SendOneInstructionB2(USART1,10,3);//R_bolishuilei
LED_On(4);//1-3
//CAN_Send STM_Chuanghu
/*
LED_Off(0);//xilisuo
LED_Off(2);//yaoshi
*/
//CAN_Receive STM_Chuanghu is ok
//CAN_Receive STM_Men
/*
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_weishenmebujiuwo
LED_On(2);//Chongqi
SendOneInstructionB2(USART1,10,0);//R_kaimensheng
LED_Off(0);//Open the door
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_Somebody is in the door
LED_On(0);//Power the door
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_door is closed &&
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_Somebody is in the door
LED_On(1);//fangqi
SendOneInstructionB2(USART1,10,1);//R_jianjiao
LED_On(3);//Open the second door
SendOneInstructionB2(USART1,10,2);//R_jiaoshou,wo men cheng gong le.
LED_Off(2);//Chongqi
//CAN_Send STM_Penyan
//LED_On(0);//penyan
//LED_On(1);//baoshan
*/
//CAN_STM_Room2 Receive STM_Penyan is over
/*
SendOneInstructionB2(USART1,10,0);//R_nimenkan
LED_On(0);//2-1
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B2-1
SendOneInstructionB2(USART1,10,1);//R2-1
while(1){if(Pin_BUTTON[1].Buttonflag>100){break;}}//B_Mofang
LED_On(1);//2-2
while(1){if(Pin_BUTTON[2].Buttonflag>100){break;}}//B2-2
SendOneInstructionB2(USART1,10,2);//R2-2
*/
//CAN_STM_Chuanghu2 Receive STM_Room2
/*
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_Pintu
LED_On(0);//xilishuo
while(1){if(Pin_BUTTON[1].Buttonflag>100){break;}}//B_Chuanghu
SendOneInstructionB2(USART1,10,0);//R_xintiao
*/
//CAN_STM_Room1 Receive STM_Chuanghu2
/*
LED_On(4);//1-4
while(1){if(Pin_BUTTON[1].Buttonflag>100){break;}}//B1-4
SendOneInstructionB2(USART1,10,0);//R1-4
*/
//CAN_STM_Room2 Receive STM_Room1
/*
LED_On(3);//2-3
while(1){if(Pin_BUTTON[1].Buttonflag>100){break;}}//B2-3
SendOneInstructionB2(USART1,10,0);//R2-3
*/
//CAN_STM_xiaohai Receive STM_Room2
/*
while(1){if(Pin_BUTTON[0].Buttonflag>100){break;}}//B_xiaohai
SendOneInstructionB2(USART1,10,0);//R_jiaoshou,kanlai
*/
//CAN_STM_Room2 Receive STM_xiaohai
/*
LED_Off(6);//diaoshu
//zhuanpan
//gameover
*/
}
#endif 
