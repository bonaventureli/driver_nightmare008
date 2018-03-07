/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.h
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:24
 *-----------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "buttons_nightmare.h"
#include "mp230_nightmare.h"
#include "led_nightmare.h"
#include "led5604.h"
#include "thread.h"
#include "spi.h"
typedef struct game_data{
	u8 err;
	u8 pass;
	u8 tiaoguan;
	u16 P;
	u16 C;
	u16 T;
	u8 pass_num[4];
	u8 musicdata;
	u8 bgm;
	u8 room1_pass;
	u8 room2_pass;
	u8 room3_pass;
	u8 room4_pass;
}T_flag; 
void InitSTM32F103ZE(void);
void LogicSTM32F103ZE(void);
