/*-----------------------------------------------------------------------------
 * Name:    RDM6300_Nightmare.c
 * Purpose: RDM6300 Nightmare reader Card
 * "www.ewoodpecker.cn" ETZ-MP230
 * Rev.:    1.02
 *----------------------------------------------------------------------------*/
 /* Copyright (c) 2016-12-9 09:59:27 LIFEI
   ---------------------------------------------------------------------------*/
#include "RDM6300_Nightmare.h"
#define STM32F103ZE_CARD
#include "card_config.c"
/***************************************
variable
****************************************/
uint8_t CardRxBuffer[NumCardID];
uint8_t CardRxBufferUSARTOne[NumCardID];
uint8_t CardRxBufferUSARTTwo[NumCardID];
uint8_t CardRxBufferUSARTThree[NumCardID];
uint8_t CardRxBufferUSARTFour[NumCardID];
uint8_t CardRxBufferUSARTFive[NumCardID];

int32_t USARTx_Initialize (USART_TypeDef* USARTx);
uint32_t timeout_C6,timeout_C7;
extern uint8_t flag_password;
extern osThreadId tid_Thread1;                                          // thread id
uint8_t Cardflag[NumCard];

/***************************************
*@brif Initialize the RDM6300
*@para none
*@return 0
****************************************/
int32_t RDM6300_Initialize (USART_TypeDef* USARTx) {
	USARTx_Initialize (USARTx);
return 0;
}
/*
|           x             |
|------|-----------|------|
|   a  |    bl     |  br  |
x[]={1,2,3,4,5,6,7,8,9,10};
shiftbit=3;

a[]={1,2,3};
bl[]={4,5,6,7};
br[]={8,9,s10};
frist:br bl a
x[]={8,9,10,4,5,6,7,1,2,3};
second:bl br a
x[]={4,5,6,7,8,9,10,1,2,3};
*/
void arrayshiftB(uint8_t x[],uint8_t a[],uint8_t bl[],uint8_t br[],uint8_t BufferLength,uint8_t shiftbit){
//	uint8_t x[]={0x02,0x34,0x30,0x30,0x30,0x34,0x44,0x35,0x36,0x35,0x37,0x30,0x43,0x03};
//	uint8_t a[3];
//	uint8_t bl[8];
//	uint8_t br[3];
	uint8_t n;
//	uint8_t BufferLength=14;
//	uint8_t shiftbit=3;
	uint8_t shift2bit=shiftbit*2;
	for(n=0;n<shiftbit;n++){
		a[n]=x[n];
	}
	
	for(n=shiftbit;n<(BufferLength-shiftbit);n++){
		bl[n-shiftbit]=x[n];
	}
	
	for(n=(BufferLength-shiftbit);n<BufferLength;n++){
		br[n-(BufferLength-shiftbit)]=x[n];
	}
	//////////////////////frist////////////////////////
	for(n=0;n<shiftbit;n++){
		x[n]=br[n];
	}
	for(n=(BufferLength-shiftbit);n<BufferLength;n++){
		x[n]=a[n-(BufferLength-shiftbit)];
	}
	//////////////////////second////////////////////////
	for(n=0;n<(BufferLength-shift2bit);n++){
		x[n]=bl[n];
	}
	for(n=(BufferLength-shift2bit);n<(BufferLength-shiftbit);n++){
		x[n]=br[n-(BufferLength-shift2bit)];
	}
}
void ReceiveOneInstruction(USART_TypeDef* USARTx,uint16_t TempBufferLength,uint8_t TempRxBuffer[]){
	uint8_t TempCounter;
  uint32_t i;
  i=0;
	/*wait the return values from the Music modern*/
	TempCounter = 0;
	while(TempCounter < TempBufferLength){
	/* Loop until the USARTx Receive Data Register is not empty */
	while((USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)&&(i!=0xFFFF)){
		i++;
	}
	i=0;
	/* Store the received byte in RxBuffer */
	TempRxBuffer[TempCounter++] = (USART_ReceiveData(USARTx) & 0x7F);
	}
}
uint8_t CheckOneCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t* pBuffer){
	uint8_t a[1];
	uint8_t bl[12];
	uint8_t br[1];
	uint8_t shiftbit=1;
	uint8_t n;
	
	ReceiveOneInstruction(USARTx,BufferLength,TempRxBuffer);
	for(n=0;n<BufferLength;n++){
		if((Buffercmp(pBuffer, TempRxBuffer, BufferLength))== PASSED){
		return 1;
		}
		else{
			arrayshiftB(pBuffer,a,bl,br,BufferLength,shiftbit);	
		}
	}
return 0;
}
uint8_t CheckAllCard(USART_TypeDef* USARTx,uint8_t BufferLength,uint8_t TempRxBuffer[],uint8_t pBuffer[][14]){
	uint8_t Card;
	uint8_t a[1];
	uint8_t bl[12];
	uint8_t br[1];
	uint8_t shiftbit=1;
	uint8_t n;
	ReceiveOneInstruction(USARTx,BufferLength,TempRxBuffer);
	for(Card=0;Card<NumCard;Card++){
		for(n=0;n<BufferLength;n++){
			if((Buffercmp(pBuffer [Card], TempRxBuffer, BufferLength))== PASSED){
			Cardflag[Card] = 1;	
			return Card;
			}
			else{
				Cardflag[Card] = 0;	
				arrayshiftB(pBuffer [Card],a,bl,br,BufferLength,shiftbit);	
			}
		}
	}
	return 100;
}
