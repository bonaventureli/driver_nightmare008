/*LED5604.c*/
#include "led5604.h"

#define LOADON GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define LOADOFF GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define CLKON GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define CLKOFF GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define SDKON GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define SDKOFF GPIO_ResetBits(GPIOD,GPIO_Pin_13)
extern uint8_t flag_button1;
void Initled5604(void){
	LOADOFF;
	SPI5064(0x00);
	SPI5064(0x00);
	SPI5064(0x00);
	LOADON;
}

void Initled5604_2(void){
	LOADOFF;
	SPI5064_2(0x00);
	SPI5064_2(0x00);
	SPI5064_2(0x00);
	LOADON;
}
void LED_blink(void){
	int percent;
	int decade;
	int single;
	int npercent=1;
	int ndecade=8;
	int nsingle=0;
//	unsigned char  Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,  //С�����
//	0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
		unsigned char  Tab[] = {0xFA,0x30,0xD9,0x79,0x33,0x6B,0xEB,0x38,0xFB,0x7B};//0 1 2 3 4 5 6 7 8 9 A B C D F �������
	//for(;;){
for(percent=npercent;(percent>=0&&(flag_button1==0));percent--){
for(decade=ndecade;(decade>=0&&(flag_button1==0));decade--){
for(single=nsingle;(single>=0&&(flag_button1==0));single--){
	LOADOFF;
	SPI5064(Tab[single]);
	SPI5064(Tab[decade]);
	SPI5064(Tab[percent]);
	LOADON;
	if(flag_button1==1){
	SPI5064(0x00);
	SPI5064(0x00);
	SPI5064(0x00);
	break;
	}
	
	delay_ms(250);
	if(single==0){nsingle=9;}
	if(decade==0){ndecade=9;}
	if(percent==0){
//	npercent=9;
		break;
	}
	}
if(flag_button1==1){break;}
}
if(flag_button1==1){break;}
}
//if(flag_button1==1){break;}
//}
}

void SPI5064(unsigned char out_data)
{
    unsigned char i,temp;
    for(i=0;i<8;i++)
    {
        CLKOFF;
        delay_ms(2);
        temp=out_data&0x80;
        if(temp==0x80)
        SDKON;
        else SDKOFF;    
        delay_ms(30);
        out_data=out_data<<1;
				CLKON;
        delay_ms(2);
    }
}
void SPI5064_2(unsigned char out_data)
{
    unsigned char i,temp;
    for(i=0;i<8;i++)
    {
        CLKOFF;
        osDelay(2);
        temp=out_data&0x80;
        if(temp==0x80)
        SDKON;
        else SDKOFF;    
        osDelay(30);
        out_data=out_data<<1;
				CLKON;
        osDelay(2);
    }
}
void LED_blink2(void){
	int percent;
	int decade;
	int single;
	int npercent=1;
	int ndecade=8;
	int nsingle=0;
//	unsigned char  Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,  //С�����
//	0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};
		unsigned char  Tab[] = {0xFA,0x30,0xD9,0x79,0x33,0x6B,0xEB,0x38,0xFB,0x7B};//0 1 2 3 4 5 6 7 8 9 A B C D F �������
for(percent=npercent;(percent>=0&&(flag_button1==0));percent--){
for(decade=ndecade;(decade>=0&&(flag_button1==0));decade--){
for(single=nsingle;(single>=0&&(flag_button1==0));single--){
	LOADOFF;
	SPI5064_2(Tab[single]);
	SPI5064_2(Tab[decade]);
	SPI5064_2(Tab[percent]);
	LOADON;
	osDelay(5000);
	if((single==0)&&(decade==0)&&(percent==0)){
	break;
	}
	if(single==0){nsingle=9;}
	if(decade==0){ndecade=9;}
	if(percent==0){npercent=9;}
	}
}
}
	LOADOFF;
	SPI5064_2(0x00);
	SPI5064_2(0x00);
	SPI5064_2(0x00);
	LOADON;
}
