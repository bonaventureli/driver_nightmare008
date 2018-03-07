#ifndef __THREAD_C
#define __THREAD_C
#include "thread.h"
#include <math.h>
#include "spi.h"
#include "app.h"
#define PA(a,b) if(b) GPIO_SetBits(GPIOA,1<<a); else GPIO_ResetBits(GPIOA,1<<a); 
#define PB(a,b) if(b) GPIO_SetBits(GPIOB,1<<a); else GPIO_ResetBits(GPIOB,1<<a); 
#define PC(a,b) if(b) GPIO_SetBits(GPIOC,1<<a); else GPIO_ResetBits(GPIOC,1<<a); 
#define PD(a,b) if(b) GPIO_SetBits(GPIOD,1<<a); else GPIO_ResetBits(GPIOD,1<<a); 
#define PE(a,b) if(b) GPIO_SetBits(GPIOE,1<<a); else GPIO_ResetBits(GPIOE,1<<a); 
#define PF(a,b) if(b) GPIO_SetBits(GPIOF,1<<a); else GPIO_ResetBits(GPIOF,1<<a); 
#define PG(a,b) if(b) GPIO_SetBits(GPIOG,1<<a); else GPIO_ResetBits(GPIOG,1<<a); 
extern uint8_t n;
extern T_flag flag;
extern BUTTON_PIN_ID2 Pin_BUTTON[];
extern int32_t ButtonID,sum,Tsum,couter,flag_err,flag_ok; 
uint16_t INFO=6000;
const unsigned char  Tab[] = {0xc0,0xcf,0xa4,0xb0,0x99,0x92,0x82, 0xf8,0x80,
															0x90, 0x88,0x83,0xc6,0xa1,0x86,0x8e,0xff,0x7f};

osThreadDef (Thread_start, osPriorityNormal, 1, 0); 
osThreadDef (Thread_task2, osPriorityNormal, 1, 0); 
osThreadDef (Thread_task3, osPriorityNormal, 1, 0); 
int Init_Thread_start (void) {
//  osThreadCreate (osThread(Thread_start), NULL);
	osThreadCreate (osThread(Thread_task2), NULL);
	osThreadCreate (osThread(Thread_task3), NULL);
		PA(5,0);
	PA(6,1);
	PA(7,0);
  return(0);
}

void Thread_start (void const *argument) {
  while (1) {

  }
}
void Thread_task2 (void const *argument) {
SPIx_ReadWriteByte(0xff);
SPIx_ReadWriteByte(0xff);
SPIx_ReadWriteByte(0xff);
SPIx_ReadWriteByte(0xff);	
	while(1)	{
		if(flag.err==1){
			/* PA5 SCK_clk, PA7 MOSI_sdi    还一个接PA4*/
			SPIx_ReadWriteByte(Tab[INFO%10]);
			SPIx_ReadWriteByte(Tab[INFO/10%10]&0x7f);
			SPIx_ReadWriteByte(Tab[INFO/100%10]);
			SPIx_ReadWriteByte(Tab[INFO/1000]);
			PA(4,1);
			osDelay(400);//OSTimeDlyHMSM(0,0,0,3,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
			PA(4,0);
		  osDelay(400);//OSTimeDlyHMSM(0,0,1,3,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
			if(INFO==0){
			flag.err=0;
			INFO=6000;
				n = 0;
		}
		INFO=INFO-100;

		}

	}
}
void Thread_task3 (void const *argument) {
  while (1) {
		GetState_Pin_BUTTON2 (HIGH2LOW);
		if(Pin_BUTTON[15].Buttonflag>50){
			flag.tiaoguan=1;
		}
  }
}
#endif
