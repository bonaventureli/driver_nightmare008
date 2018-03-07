/*-----------------------------------------------------------------------------
 * Name:    		Buttons_Nightmare.h
 * Purpose: 		Buttons interface header file
 * Rev.:    		3.01
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 11:00:21
 *-----------------------------------------------------------------------------*/
#ifndef __BUTTONS_NIGHTMARE_H
#define __BUTTONS_NIGHTMARE_H
#include <stdint.h> 
#include "GPIO_STM32F10x.h"
#include "cmsis_os.h"
/*Private typedef ***************************************/

typedef struct _BUTTON_PIN_ID {
  GPIO_TypeDef *port;
  uint8_t       num;
	uint8_t       mask;
} BUTTON_PIN_ID;

typedef struct _BUTTON_PIN_ID2 {
  GPIO_TypeDef *port;
  uint8_t       num;
	uint8_t       mask;
	uint8_t      Buttonflag;
} BUTTON_PIN_ID2;

typedef enum {HIGH2LOW = 0, LOW2HIGH = !HIGH2LOW} ButtonState;
typedef enum { RELEASE = 0, PRESS = !RELEASE} ButtonStatus;

int32_t Turntable_Buttons_Initialize_high2low(void);
uint32_t Turntable_Buttons_GetState_high2low(void);
uint8_t Turntable_WaitButtonDone_high2low(uint32_t BUTTONx);
void Turntable_WaitButton_high2low(void);
uint32_t Password_Buttons_GetState_high2low (void) ;
int32_t Password_Buttons_Initialize_high2low (void) ;
void Password_WaitButton_high2low(void);
void func_tiaoguan2(uint8_t a,uint8_t b,uint32_t count);
uint32_t Password_Buttons_GetState (ButtonState bState,uint32_t count);
void Password_WaitButton(ButtonState bState,uint32_t count);
void Initialize_Pin_BUTTON (ButtonState bState);
uint32_t GetState_Pin_BUTTON (uint32_t val,ButtonState bState,uint32_t count);
uint32_t Wait_Pin_BUTTON_Done(uint32_t BUTTONx,ButtonState bState,uint32_t count,uint8_t pressState);
void Wait_Pin_BUTTON(ButtonState bState,uint32_t count);
void Thread_Button (void const *argument);
int Init_Thread_Button (void);
#endif /* __BUTTONS_NIGHTMARE_H */
