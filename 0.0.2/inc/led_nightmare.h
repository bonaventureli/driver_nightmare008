/*-----------------------------------------------------------------------------
 * Name:    		LED_Nightmare.h
 * Purpose: 		LED Nightmare for Nightmare for room1-room2
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-29 10:15:07
 *-----------------------------------------------------------------------------*/
#ifndef __LED_NIGHTMARE_H
#define __LED_NIGHTMARE_H

#include <stdint.h>
#include <stdarg.h>
#include "GPIO_STM32F10x.h"
#include "cmsis_os.h"

int32_t  LED_Initialize   (void);
int32_t  LED_Uninitialize (void);
int32_t  LED_On           (uint32_t num);
int32_t  LED_Off          (uint32_t num);
int32_t  LED_SetOut       (uint32_t val);
uint32_t LED_GetCount     (void);
int32_t LED_Flash (uint32_t num,uint32_t n);
int32_t LED_Flash2 (uint32_t n,int32_t num,...);
int32_t LED_On2 (int32_t num,...);
int32_t LED_Off2 (int32_t num,...);
#endif /* __LED_NIGHTMARE_H */
