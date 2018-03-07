/*Common.h*/
#ifndef _COMMON_H
#define  _COMMON_H
#include "stm32f10x.h"
//#include "MP230_Nightmare.h"
//#include "Buttons_Nightmare.h"
//#include "LED_Nightmare.h"
//#include "RDM6300_Nightmare.h"
//#include "DB2204MA.h"
//#include "app.h"
//#include "GPIO_STM32F10x.h"
//#include "MP230_Nightmare.h"
//#include "cmsis_os.h"
#include "GPIO_STM32F10x.h"

#define countof(a)   (sizeof(a) / sizeof(*(a)))
typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
int32_t USARTx_Initialize (USART_TypeDef* USARTx);
#endif
