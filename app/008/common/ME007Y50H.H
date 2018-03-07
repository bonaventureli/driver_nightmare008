/*MP230_Nightmare.h*/

#ifndef _MP230_H_
#define _MP230_H_

#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include "cmsis_os.h"

#define InstructionSize   (countof(TxBuffer))			//Size of one instruction
#define InstructionLength   (sizeof(*(TxBuffer)))		//Length of one instruction

/*
uint8_t TxBuffer[][10] = {
{0x7E,0x10,0x06,0x0f,0x00,0x01,0x01,0xFF,0xD9,0xEF},
{0x7E,0x10,0x06,0x0f,0x00,0x01,0x02,0xFF,0xD8,0xEF}
}
Instruction Length is 10
Instruction Size is 2
Instruction ID is 0,1
*/
//int32_t MP230_Initialize (void);
int32_t MP230_Initialize (USART_TypeDef* USARTx);
uint8_t* SendOneInstruction(USART_TypeDef* USARTx,\
	uint8_t TempTxBuffer[][10],\
	uint8_t TempRxBuffer[10],\
	uint16_t TempTxxCounter,\
	uint16_t TempBufferLength);
void SendOneInstructionA( USART_TypeDef* USARTx,\
													uint16_t TempBufferLength,\
													uint8_t InstructionID);
uint8_t SendOneInstructionB( USART_TypeDef* USARTx,\
														 uint16_t TempBufferLength,\
														 uint8_t InstructionID);
uint8_t SendOneInstructionB2(USART_TypeDef* USARTx,\
												 uint16_t TempBufferLength,\
												 uint8_t InstructionID);
void JustSendOneInstruction(USART_TypeDef* USARTx,\
												 uint16_t TempBufferLength,\
												 uint8_t InstructionID);
uint8_t SendInstruction(USART_TypeDef* USARTx,\
												 uint8_t InstructionID);
uint8_t SendOneInstructionB_music(USART_TypeDef* USARTx,\
												 uint16_t TempBufferLength,\
												 uint8_t InstructionID);
#endif
