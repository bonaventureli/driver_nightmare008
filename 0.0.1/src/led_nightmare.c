/*-----------------------------------------------------------------------------
 * Name:    		LED_Nightmare.c
 * Purpose: 		LED Nightmare for Nightmare for room1-room2-room3
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-29 10:14:48
 *-----------------------------------------------------------------------------*/
#ifndef __LED_NIGHTMARE_C
#define __LED_NIGHTMARE_C

#include "led_nightmare.h"
#define STM32F103ZE_LED
#include "ledconfig.c"


/*Private define ***************************************/
#define LED_COUNT (sizeof(Pin_LED)/sizeof(GPIO_PIN_ID))
uint8_t LED_FLASH=0x01;

/*************************************
  @brief       Initialize LEDs
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_Initialize (void) {
		uint32_t n;

		/* Configure pins: Push-pull Output Mode (50 MHz) with Pull-down resistors */
		for (n = 0; n < LED_COUNT; n++) {
		GPIO_PortClock   (Pin_LED[n].port, true);
		GPIO_PinWrite    (Pin_LED[n].port, Pin_LED[n].num, 0);
		GPIO_PinConfigure(Pin_LED[n].port, Pin_LED[n].num,
											GPIO_OUT_PUSH_PULL, 
											GPIO_MODE_OUT2MHZ);
  }

  return 0;
}

/*************************************
  @brief       De-initialize LEDs
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_Uninitialize (void) {
  uint32_t n;

  /* Configure pins: Input mode, without Pull-up/down resistors */
		for (n = 0; n < LED_COUNT; n++) {
		GPIO_PinConfigure(Pin_LED[n].port, Pin_LED[n].num,
                      GPIO_IN_FLOATING,
                      GPIO_MODE_INPUT);
  }
  return 0;
}

/*************************************
  @brief       Turn on requested LED
  @param[in]   num  LED number
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_On (uint32_t num) {
  GPIO_PinWrite(Pin_LED[num].port, Pin_LED[num].num, 1);
  return 0;
}
int32_t LED_On2 (int32_t num,...) {
	int32_t i;
	va_list ap;
	va_start(ap,num);
	for(i=num;i!=-1;i=va_arg(ap,int32_t)){
		GPIO_PinWrite(Pin_LED[i].port, Pin_LED[i].num, 1);
	}
	va_end(ap);
  return 0;
}
/*************************************
  @brief       Flash  LED
  @param[in]   num  LED number
							 n : timer delay
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_Flash (uint32_t num,uint32_t n) {
  GPIO_PinWrite(Pin_LED[num].port, Pin_LED[num].num, LED_FLASH);
	LED_FLASH =(~LED_FLASH)&0x01;
	osDelay(n);
  return 0;
}
int32_t LED_Flash2 (uint32_t n,int32_t num,...) {
	int32_t i;
	va_list ap;
	va_start(ap,num);
	for(i=num;i!=-1;i=va_arg(ap,uint32_t)){
		GPIO_PinWrite(Pin_LED[i].port, Pin_LED[i].num, LED_FLASH);
	}
	va_end(ap);
	LED_FLASH =(~LED_FLASH)&0x01;
	osDelay(n);
  return 0;
}
/*************************************
  @brief       Turn off requested LED
  @param[in]   num  LED number
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_Off (uint32_t num) {
  GPIO_PinWrite(Pin_LED[num].port, Pin_LED[num].num, 0);
  return 0;
}
int32_t LED_Off2 (int32_t num,...) {
	int32_t i;
	va_list ap;
	va_start(ap,num);
	for(i=num;i!=-1;i=va_arg(ap,int32_t)){
		GPIO_PinWrite(Pin_LED[i].port, Pin_LED[i].num, 0);
	}
	va_end(ap);
  return 0;
}
/*************************************
  @brief       Write value to LEDs
  @param[in]   val  value to be displayed on LEDs
  @returns
     0: function succeeded
    -1: function failed
************************************/
int32_t LED_SetOut (uint32_t val) {
  uint32_t n;
  for (n = 0; n < LED_COUNT; n++) {
    if (val & (1<<n)) {
      LED_On (n);
    } 
		else {
      LED_Off(n);
    }
  }
  return 0;
}

/***********************************
  @brief       Get number of LEDs
  @return      Number of available LEDs
************************************/
uint32_t LED_GetCount (void) {
  return LED_COUNT;
}
#endif
