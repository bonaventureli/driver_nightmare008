/*-----------------------------------------------------------------------------
 * Name:    Common.c
 * Purpose: Common use
 * Rev.:    1.00
 *----------------------------------------------------------------------------*/
/* Copyright (c) 2016/5/16 LIFEI
   ---------------------------------------------------------------------------*/
#ifndef _COMMON_C
#define _COMMON_C
#include "Common.h"
typedef struct _USART_PIN_ID {
  GPIO_TypeDef *port;
  uint8_t       num;
} USART_PIN_ID;
/************************************
const
************************************/
const USART_PIN_ID Pin_USART_Tx[] = {
  { GPIOA, 9 },	//USART1_TX
  { GPIOA, 2 },	//USART2_TX
	{ GPIOB, 10 },//USART3_TX
	{ GPIOC, 10 },//UART4_TX
	{ GPIOC, 12 } //UART5_TX
};

const USART_PIN_ID Pin_USART_Rx[] = {
  { GPIOA, 10 },//USART1_RX
  { GPIOA, 3 },	//USART2_RX
	{ GPIOB, 11 },//USART3_RX
	{ GPIOC, 11 },//UART4_RX
	{ GPIOD, 2 }  //UART5_RX
};

#define USART_COUNT_Tx (sizeof(Pin_USART_Tx)/sizeof(GPIO_PIN_ID))
#define USART_COUNT_Rx (sizeof(Pin_USART_Rx)/sizeof(GPIO_PIN_ID))
/**
   * @brief  Compares two buffers.
   * @param  pBuffer1, pBuffer2: buffers to be compared.
   * @param  BufferLength: buffer's length
   * @retval PASSED: pBuffer1 identical to pBuffer2
   *         FAILED: pBuffer1 differs from pBuffer2
   */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength){
 while(BufferLength--){
	 if(*pBuffer1 != *pBuffer2){
		 return FAILED;
	 }
	 pBuffer1++;
	 pBuffer2++;
 }
 return PASSED;  
}
/********************************
*@brif Initialize the USARTx
*@para USARTx: USART1 USART2 USART3 UART4 UART5
*@return 0 
********************************/
int32_t USARTx_Initialize (USART_TypeDef* USARTx) {
	uint32_t n;
	USART_InitTypeDef USART_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);

	for (n = 0; n < USART_COUNT_Tx; n++) {
	GPIO_PortClock   (Pin_USART_Tx[n].port, true);
	GPIO_PinConfigure(Pin_USART_Tx[n].port, Pin_USART_Tx[n].num,
										GPIO_AF_PUSHPULL, 
										GPIO_MODE_OUT50MHZ);
	GPIO_PortClock   (Pin_USART_Rx[n].port, true);
	GPIO_PinConfigure(Pin_USART_Rx[n].port, Pin_USART_Rx[n].num,
										GPIO_IN_FLOATING, 
										GPIO_MODE_INPUT);			
  }
	
	/*Universal synchronous asynchronous receiver transmitter USART------------*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx,&USART_InitStructure);
	USART_Cmd(USARTx,ENABLE);
  return 0;
}
#endif
