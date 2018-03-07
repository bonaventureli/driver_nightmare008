/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.h
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:24
 config:0.0.2
 buttons_nightmare.c
 led_nightmare.c
 rdm6300_nightmare.c
 common.c
 main.c
 *-----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "buttons_nightmare.h"
#include "led_nightmare.h"
#include "rdm6300_nightmare.h"
#include "cmsis_os.h"
void InitSTM32F103ZE(void);
void LogicSTM32F103ZE(void);
void Init_osTimer (void);
void callback(void const *param);
void card_thread(void const *argument);
int Init_cardthread(void);
