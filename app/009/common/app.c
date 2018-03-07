/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
 
#include "app.h"
//#include "led_nightmare.h"

 /**
   ******************************************************************************
   * @file    ADC/RegSimul_DualMode/main.c 
   * @author  MCD Application Team
   * @version V3.5.0
   * @date    08-April-2011
   * @brief   Main program body
   ******************************************************************************
   * @attention
   *
   * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
   * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
   * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
   * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
   * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
   * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
   *
   * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
   ******************************************************************************
   */ 
 
 /* Includes ------------------------------------------------------------------*/
 #include "stm32f10x.h"
#include "common.h"
#include "mp230_nightmare.h"
void InitSTM32F103ZE(void){
//LED_Initialize();
USARTx_Initialize(USART1);
}

void LogicSTM32F103ZE(void){
//LED_On2(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1);
SendOneInstructionB(USART1,10,1);
	SendOneInstructionB(USART1,10,2);
	SendOneInstructionB(USART1,10,3);
	SendOneInstructionB(USART1,10,4);
	SendOneInstructionB(USART1,10,5);
	SendOneInstructionB(USART1,10,6);
	SendOneInstructionB(USART1,10,7);
	SendOneInstructionB(USART1,10,7);
	SendOneInstructionB(USART1,10,8);
	SendOneInstructionB(USART1,10,9);
	SendOneInstructionB(USART1,10,10);
	SendOneInstructionB(USART1,10,11);
	SendOneInstructionB(USART1,10,12);
	SendOneInstructionB(USART1,10,13);
osDelay(5000);
osDelay(5000);
}


 
 /******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
