/*
Name:card_config.c
Rev:v1.01
LastUptime:2017-1-2 11:19:11
*/
#include "rdm6300_nightmare.h"
#ifdef STM32F103ZE_CARD
#include <stdint.h>
typedef struct _USART_FLAG{
	uint8_t flag1;
	uint8_t flag2;
	uint8_t flag3;
	uint8_t flag4;
	uint8_t flag5;
} USART_FLAG;
USART_FLAG UF;
#define CHECK_NUM 3
uint8_t CardID[][14] = {
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x38 ,0x31 ,0x41 ,0x39 ,0x37 ,0x32 ,0x03},//0
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x32 ,0x36 ,0x41 ,0x44 ,0x44 ,0x31 ,0x03},//1
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x38 ,0x31 ,0x41 ,0x37 ,0x37 ,0x43 ,0x03},//2
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x38 ,0x31 ,0x42 ,0x32 ,0x36 ,0x39 ,0x03},//3
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x38 ,0x31 ,0x41 ,0x38 ,0x37 ,0x33 ,0x03},//4
{0x02 ,0x37 ,0x36 ,0x30 ,0x30 ,0x32 ,0x43 ,0x38 ,0x31 ,0x42 ,0x34 ,0x36 ,0x46 ,0x03},//5
};

uint8_t BufOne[NCID];
uint8_t BufTwo[NCID];
uint8_t BufThree[NCID];
uint8_t BufFour[NCID];
uint8_t BufFive[NCID];
uint8_t app_card(void){
	if((CheckOneCard(USART1,14,BufOne,CardID[3])==1)){
	UF.flag1++;
	}
	else{
	UF.flag1=0;
	}
	if((CheckOneCard(USART2,14,BufTwo,CardID[5])==1)){
	UF.flag2++;
	}
	else{
	UF.flag2=0;
	}
	if((CheckOneCard(USART3,14,BufThree,CardID[0])==1)){
	UF.flag3++;
	}
	else{
	UF.flag3=0;
	}
	if((CheckOneCard(UART4,14,BufFour,CardID[1])==1)){
	UF.flag4++;
	}
	else{
	UF.flag4=0;
	}
	if((CheckOneCard(UART5,14,BufFive,CardID[2])==1)){
	UF.flag5++;
	}
	else{
	UF.flag5=0;
	}
	
	if((UF.flag1 >= CHECK_NUM)&&(UF.flag2 >= CHECK_NUM)&&\
		(UF.flag3 >= CHECK_NUM)&&(UF.flag4 >= CHECK_NUM)&&\
	(UF.flag5 >= CHECK_NUM)){
	UF.flag1 = 0;
	UF.flag2 = 0;
	UF.flag3 = 0;
	UF.flag4 = 0;
	UF.flag5 = 0;
	return 1;
	}
	else
	return 0;
}
#endif
