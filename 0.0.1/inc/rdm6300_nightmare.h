/*RDM6300_Nightmare.h*/
#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include <cmsis_os.h>
#include "common.h"
#define NumCard   (countof(CardID))			//number of Card
#define NumCardID   (sizeof(*(CardID)))		//number of CardID

void arrayshiftB(uint8_t x[],uint8_t a[],uint8_t bl[],uint8_t br[],uint8_t BufferLength,uint8_t shiftbit);
void ReceiveOneInstruction(USART_TypeDef* USARTx,uint16_t TempBufferLength,uint8_t TempRxBuffer[]);
uint8_t CheckAllCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t pBuffer[][14]);
uint8_t CheckOneCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t* pBuffer);

uint8_t* RDM6300_ReadCardID(USART_TypeDef* USARTx,uint16_t BufferLength,uint16_t tempNumCard);
int32_t RDM6300_Initialize (USART_TypeDef* USARTx);

