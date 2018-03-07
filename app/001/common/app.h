#ifndef _APP_H
#define _APP_H
/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.h
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:24
 *-----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "MP230_Nightmare.h"
#include "Buttons_Nightmare.h"
#include "LED_Nightmare.h"
#include "GPIO_STM32F10x.h"
#include "db2204ma.h"
#include "rdm6300_nightmare.h"
#include "led5604.h"
uint8_t BackgroundMusic_Room1_Done(USART_TypeDef* USARTx,uint16_t TempBufferLength,\
												 uint8_t InstructionID);
uint8_t Radio_Room1_Done(USART_TypeDef* USARTx,uint16_t TempBufferLength,\
												 uint8_t InstructionID);
void Turntable(void);
void Turntable2(void);
void func0(void);
void func2(void);
void func3(void);
void func4(void);
void func5(void);
void func6(void);
void func7(void);
void func8(void);
void func9(void);
void func10(void);
void func11(void);
void func14(void);
void func18(void);
void func22(void);
void func23(void);
void func24(void);
void func27(void);
void func28(void);
void func29(void);
void func30(void);
void func31(void);
void func32(void);
void func33(void);
void func35(void);
void func36(void);
void func37(void);
void func40(void);
void funcNULL(void);
void LED_DEL(void);
void LED_DEL2(void);
void RoomALogic1(USART_TypeDef* USARTx,USART_TypeDef* USARTy,USART_TypeDef* USARTz,USART_TypeDef* USARTw);
void BackgroundMusic_Room1_Init(USART_TypeDef* USARTx);
void Radio_Room1_Init(USART_TypeDef* USARTx);
void SoundEffectA_Room1_Init(USART_TypeDef* USARTx);
int Init_Thread_tiaoguan (void);
void Thread_tiaoguan (void const *argument);
void InitSTM32F103ZE(void);
void LogicSTM32F103ZE(void);

#endif
