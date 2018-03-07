/*-----------------------------------------------------------------------------
 * Name:    		Buttons_Nightmare.h
 * Purpose: 		Buttons interface header file
 * Rev.:    		3.03
 * Author:  		LIFEI
 * LastUptime:	2016-12-29 17:23:51
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
	uint32_t       mask;
	uint32_t      Buttonflag;
} BUTTON_PIN_ID2;

typedef struct _PASSWORD{
uint8_t password;
uint8_t mask;
uint8_t flag;	
} PASSWORD;

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
uint32_t Wait_Pin_BUTTON_Done2(uint32_t BUTTONx,uint32_t BUTTONy,ButtonState bState,uint32_t count,uint8_t pressState);
uint8_t fun_password_single(PASSWORD *tmp);
uint8_t fun_password_loop(PASSWORD *tmp);
void app_password(void);
void callback(void const *param);
void GetState_Pin_BUTTON2 (ButtonState bState);
void Init_osTimer (void);
#endif /* __BUTTONS_NIGHTMARE_H */