/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.h
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:24
 *-----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led_nightmare.h"
#include "led5604.h"
#include "buttons_nightmare.h"
#include "mp230_nightmare.h"
extern uint8_t flag_button0;
void InitSTM32F103ZE(void);
void LogicSTM32F103ZE(void);
