/*-----------------------------------------------------------------------------
 * Name:    RDM6300_Nightmare.c
 * Purpose: RDM6300 Nightmare reader Card
 * "www.ewoodpecker.cn" ETZ-MP230
 * Rev.:    1.03
 add
 uint8_t app_card(void);
 *----------------------------------------------------------------------------*/
 /* Copyright (c) 2017-1-2 11:19:34 LIFEI
   ---------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include <cmsis_os.h>
#include "common.h"
#define NCd   (countof(CardID))			//number of Card
#define NCID   (sizeof(*(CardID)))		//number of CardID

void arrayshiftB(uint8_t x[],uint8_t a[],uint8_t bl[],uint8_t br[],uint8_t BufferLength,uint8_t shiftbit);
void ReceiveOneInstruction(USART_TypeDef* USARTx,uint16_t TempBufferLength,uint8_t TempRxBuffer[]);
uint8_t CheckAllCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t pBuffer[][14]);
uint8_t CheckOneCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t* pBuffer);

uint8_t* RDM6300_ReadCardID(USART_TypeDef* USARTx,uint16_t BufferLength,uint16_t tempNumCard);
int32_t RDM6300_Initialize (USART_TypeDef* USARTx);
uint8_t app_card(void);
