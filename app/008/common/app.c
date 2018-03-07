/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
#include "app.h"
//#include <stdio.h>
#include "cmsis_os.h"
#include "buttons_nightmare.h"
extern BUTTON_PIN_ID2 Pin_BUTTON[];
extern uint8_t RxBuffer[7];
uint16_t buffer,buffer1;
uint16_t Buffer[10],Buffer1[10],aveBuffer,aveBuffer1;
int16_t i,j,m,str[4],str_ad[4];
 unsigned char  fseg[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
 unsigned char  segbit[]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
 unsigned char  disbuf[4]={0,0,0,0};
 unsigned char  LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -   .
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf,0x7F,
};
struct bu{
bool bBUTTON;	
bool bBUTTON0;
bool bBUTTON1;
bool bBUTTON2;
bool bBUTTON3;
bool bBUTTON4;
bool bBUTTON5;
bool bBUTTON6;
bool bBUTTON7;
bool bBUTTON8;
bool bBUTTON9;
bool bBUTTON10;
bool bBUTTON11;
bool bBUTTON12;
} sB;
enum age{
	NO,
	MAN_AG_25=1,
	MAN_AG_25_29,
	MAN_AG_30_39,
	MAN_AG_40_59,
	WAMAN_AG_25,
	WAMAN_AG_25_44,
	WAMAN_AG_45_49,
	WAMAN_AG_50_54,
	WAMAN_AG_55_59,
};
char cAG;
enum result{
	LOW=1,
	NOMAL,
	HIGH,
};
char cRESULT;
#define SCLKON GPIO_SetBits(GPIOC,GPIO_Pin_0)//SHCP shift register clock input
#define SCLKOFF GPIO_ResetBits(GPIOC,GPIO_Pin_0)
#define RCLKON GPIO_SetBits(GPIOC,GPIO_Pin_1)//STCP storage register clock input
#define RCLKOFF GPIO_ResetBits(GPIOC,GPIO_Pin_1)
#define DIOON GPIO_SetBits(GPIOC,GPIO_Pin_2)
#define DIOOFF GPIO_ResetBits(GPIOC,GPIO_Pin_2)//DS serial data input

#define SCLKON1 GPIO_SetBits(GPIOE,GPIO_Pin_13)//SHCP shift register clock input
#define SCLKOFF1 GPIO_ResetBits(GPIOE,GPIO_Pin_13)
#define RCLKON1 GPIO_SetBits(GPIOE,GPIO_Pin_14)//STCP storage register clock input
#define RCLKOFF1 GPIO_ResetBits(GPIOE,GPIO_Pin_14)
#define DIOON1 GPIO_SetBits(GPIOE,GPIO_Pin_15)
#define DIOOFF1 GPIO_ResetBits(GPIOE,GPIO_Pin_15)//DS serial data input

#define SCLKON2 GPIO_SetBits(GPIOC,GPIO_Pin_3)//SHCP shift register clock input
#define SCLKOFF2 GPIO_ResetBits(GPIOC,GPIO_Pin_3)
#define RCLKON2 GPIO_SetBits(GPIOC,GPIO_Pin_4)//STCP storage register clock input
#define RCLKOFF2 GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define DIOON2 GPIO_SetBits(GPIOC,GPIO_Pin_5)
#define DIOOFF2 GPIO_ResetBits(GPIOC,GPIO_Pin_5)//DS serial data input

#define uchar unsigned char
bool f_shengao;
uchar LED[4];	
uchar LED1[4];	
uchar LED2[4];

unsigned char  LED_0F[];		

void LED_OUT(uchar X);	
void LED_OUT1(uchar X);	
void LED_OUT2(uchar X);	

void LED4_Display (void);		
void LED4_Display1 (void);
void LED4_Display2 (void);
void Thread (void const *argument);                             // thread function
osThreadId tid_Thread;                                          // thread id
osThreadDef (Thread, osPriorityNormal, 1, 0);                   // thread object
int Init_Thread (void);

void Thread1 (void const *argument);                             // thread function
osThreadId tid_Thread1;                                          // thread id
osThreadDef (Thread1, osPriorityNormal, 1, 0);                   // thread object
int Init_Thread1 (void);
int Init_Thread2 (void);

void Thread2 (void const *argument);                             // thread function
osThreadId tid_Thread2;                                          // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object
int Init_Thread1 (void);
/*----- Periodic Timer Example -----*/
static void Timer2_Callback (void const *arg);                  // prototype for timer callback function

static osTimerId id2;                                           // timer id
static uint32_t  exec2;                                         // argument for the timer call back function
static osTimerDef (Timer2, Timer2_Callback);
void Init_Timers (void);

 #define ADC1_DR_Address    ((uint32_t)0x4001244C)
  ADC_InitTypeDef ADC_InitStructure;
 DMA_InitTypeDef DMA_InitStructure;
 __IO uint16_t ADCConvertedValue;
 
 /* Private function prototypes -----------------------------------------------*/
 void RCC_Configuration(void);
 void GPIO_Configuration(void);
 void shengao(void);
 void tizhong(void);
void InitSTM32F103ZE(void){

	LED_Initialize();
	Initialize_Pin_BUTTON(HIGH2LOW);
	MP230_Initialize(USART1);
	MP230_Initialize(USART2);
	Init_Thread();
	Init_Thread1();
	Init_Thread2();
	Init_Timers();
	//Init_osTimer();
	/* System clocks configuration ---------------------------------------------*/
   RCC_Configuration();
   /* GPIO configuration ------------------------------------------------------*/
   GPIO_Configuration();
 
   /* DMA1 channel1 configuration ----------------------------------------------*/
   DMA_DeInit(DMA1_Channel1);
   DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
   DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCConvertedValue;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
   DMA_InitStructure.DMA_BufferSize = 1;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
   DMA_Init(DMA1_Channel1, &DMA_InitStructure);
   
   /* Enable DMA1 channel1 */
   DMA_Cmd(DMA1_Channel1, ENABLE);
   
   /* ADC1 configuration ------------------------------------------------------*/
   ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
   ADC_InitStructure.ADC_ScanConvMode = ENABLE;
   ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
   ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
   ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStructure.ADC_NbrOfChannel = 1;
   ADC_Init(ADC1, &ADC_InitStructure);
 
   /* ADC1 regular channel14 configuration */ 
   ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);
 
   /* Enable ADC1 DMA */
   ADC_DMACmd(ADC1, ENABLE);
   
   /* Enable ADC1 */
   ADC_Cmd(ADC1, ENABLE);
 
   /* Enable ADC1 reset calibration register */   
   ADC_ResetCalibration(ADC1);
   /* Check the end of ADC1 reset calibration register */
   while(ADC_GetResetCalibrationStatus(ADC1));
 
   /* Start ADC1 calibration */
   ADC_StartCalibration(ADC1);
   /* Check the end of ADC1 calibration */
   while(ADC_GetCalibrationStatus(ADC1));
      
   /* Start ADC1 Software Conversion */ 
   ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	 
	LED[0]=15;
	LED[1]=15;
	LED[2]=15;
	LED[3]=15;
	
	LED1[0]=15;
	LED1[1]=15;
	LED1[2]=15;
	LED1[3]=15;
	
	LED2[0]=15;
	LED2[1]=15;
	LED2[2]=15;
	LED2[3]=15;
}





void LogicSTM32F103ZE(void){
	GetState_Pin_BUTTON2(HIGH2LOW);
	if(Pin_BUTTON[0].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON0=true;cAG=MAN_AG_25;}
	if(Pin_BUTTON[1].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON1=true;cAG=MAN_AG_25_29;}
	if(Pin_BUTTON[2].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON2=true;cAG=MAN_AG_30_39;}
	if(Pin_BUTTON[3].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON3=true;cAG=MAN_AG_40_59;}
	
	if(Pin_BUTTON[4].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON4=true;}
	if(Pin_BUTTON[5].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON5=true;}
	if(Pin_BUTTON[6].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON6=true;}
	if(Pin_BUTTON[7].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON7=true;}
	
	if(Pin_BUTTON[8].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON8=true; cAG=WAMAN_AG_25;}
	if(Pin_BUTTON[9].Buttonflag>10){sB.bBUTTON=true;sB.bBUTTON9=true; cAG=WAMAN_AG_25_44;}
if(Pin_BUTTON[10].Buttonflag >10){sB.bBUTTON=true;sB.bBUTTON10=true;cAG=WAMAN_AG_45_49;}
if(Pin_BUTTON[11].Buttonflag >10){sB.bBUTTON=true;sB.bBUTTON11=true;cAG=WAMAN_AG_50_54;}
if(Pin_BUTTON[12].Buttonflag >10){sB.bBUTTON=true;sB.bBUTTON12=true;cAG=WAMAN_AG_55_59;}

osThreadYield ();				
}
void LED4_Display (void)
{
	unsigned char  *led_table;          
	uchar i;

	led_table = LED_0F + LED[0];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLKOFF;
	RCLKON;

	led_table = LED_0F + LED[1];
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLKOFF;
	RCLKON;

	led_table = LED_0F + LED[2];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLKOFF;
	RCLKON;

	led_table = LED_0F + LED[3];
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLKOFF;
	RCLKON;
	

	LED_OUT(0xFF);			
	LED_OUT(0xFF);		

	RCLKOFF;
	RCLKON;
}

void LED4_Display1 (void)
{
	unsigned char  *led_table;          
	uchar i;

	led_table = LED_0F + LED1[0];
	i = *led_table;

	LED_OUT1(i);			
	LED_OUT1(0x01);		

	RCLKOFF1;
	RCLKON1;

	led_table = LED_0F + LED1[1];
	i = *led_table;

	LED_OUT1(i);		
	LED_OUT1(0x02);		

	RCLKOFF1;
	RCLKON1;

	led_table = LED_0F + LED1[2];
	i = *led_table;

	LED_OUT1(i);			
	LED_OUT1(0x04);	

	RCLKOFF1;
	RCLKON1;

	led_table = LED_0F + LED1[3];
	i = *led_table;

	LED_OUT1(i);			
	LED_OUT1(0x08);		

	RCLKOFF1;
	RCLKON1;
	

	LED_OUT1(0xFF);			
	LED_OUT1(0xFF);		

	RCLKOFF1;
	RCLKON1;
}
void LED4_Display2 (void)
{
	unsigned char  *led_table;          
	uchar i;

	led_table = LED_0F + LED2[0];
	i = *led_table;

	LED_OUT2(i);			
	LED_OUT2(0x01);		

	RCLKOFF2;
	RCLKON2;

	led_table = LED_0F + LED2[1];
	i = *led_table;

	LED_OUT2(i);		
	LED_OUT2(0x02);		

	RCLKOFF2;
	RCLKON2;

	led_table = LED_0F + LED2[2];
	i = *led_table;

	LED_OUT2(i);			
	LED_OUT2(0x04);	

	RCLKOFF2;
	RCLKON2;

	led_table = LED_0F + LED2[3];
	i = *led_table;

	LED_OUT2(i);			
	LED_OUT2(0x08);		

	RCLKOFF2;
	RCLKON2;
	

	LED_OUT2(0xFF);			
	LED_OUT2(0xFF);		

	RCLKOFF2;
	RCLKON2;
}

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIOON; else DIOOFF;
		X<<=1;
		SCLKOFF;
		SCLKON;
	}
}
void LED_OUT1(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIOON1; else DIOOFF1;
		X<<=1;
		SCLKOFF1;
		SCLKON1;
	}
}
void LED_OUT2(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIOON2; else DIOOFF2;
		X<<=1;
		SCLKOFF2;
		SCLKON2;
	}
}


int Init_Thread (void) {

  tid_Thread = osThreadCreate (osThread(Thread), NULL);
  if (!tid_Thread) return(-1);
  
  return(0);
}
int Init_Thread1 (void) {

  tid_Thread1 = osThreadCreate (osThread(Thread1), NULL);
  if (!tid_Thread1) return(-1);
  
  return(0);
}
int Init_Thread2 (void) {

  tid_Thread2 = osThreadCreate (osThread(Thread2), NULL);
  if (!tid_Thread2) return(-1);
  
  return(0);
}
void Thread2 (void const *argument) {

  while (1) {
	//LED4_Display2 ();
		if(sB.bBUTTON0==true){
			SendOneInstructionB_music(USART1,10,1);	sB.bBUTTON0=false;
			LED_On2(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1);		
			LED_On2(15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,-1);
		}

		if(sB.bBUTTON1==true){SendOneInstructionB_music(USART1,10,2);sB.bBUTTON1=false;}
		if(sB.bBUTTON2==true){SendOneInstructionB_music(USART1,10,3);sB.bBUTTON2=false;}
		if(sB.bBUTTON3==true){SendOneInstructionB_music(USART1,10,4);sB.bBUTTON3=false;}
		if(sB.bBUTTON4==true){SendOneInstructionB_music(USART1,10,5);sB.bBUTTON4=false;}
		if(sB.bBUTTON5==true){SendOneInstructionB_music(USART1,10,6);sB.bBUTTON5=false;}
		if(sB.bBUTTON6==true){SendOneInstructionB_music(USART1,10,7);sB.bBUTTON6=false;}
		if(sB.bBUTTON7==true){SendOneInstructionB_music(USART1,10,8);sB.bBUTTON7=false;}
		if(sB.bBUTTON8==true){SendOneInstructionB_music(USART1,10,9);sB.bBUTTON8=false;}
		if(sB.bBUTTON9==true){SendOneInstructionB_music(USART1,10,10);sB.bBUTTON9=false;}
		if(sB.bBUTTON10==true){SendOneInstructionB_music(USART1,10,11);sB.bBUTTON10=false;}
		if(sB.bBUTTON11==true){SendOneInstructionB_music(USART1,10,12);sB.bBUTTON11=false;}
		if(sB.bBUTTON12==true){sB.bBUTTON12=false;}

		osThreadYield ();
  }
}
void Thread1 (void const *argument) {

  while (1) {
	LED4_Display1 ();
		//osThreadYield ();
  }
}
void Thread (void const *argument) {

  while (1) {
		LED4_Display ();
		//osThreadYield ();
  }
}

void shengao(void){
	int i;
	aveBuffer=0;
	
	for(i=10;i>=0;i--){
		Buffer[i]=0;
		SendInstruction(USART2,0);
		Buffer[i]=RxBuffer[4];
		Buffer[i]<<=8;
		Buffer[i]|=RxBuffer[5];
		aveBuffer+=Buffer[i];
	}
	aveBuffer=aveBuffer/10;
		j=0;
	aveBuffer=3000-aveBuffer;//3m
	while(aveBuffer){
		str[j]=aveBuffer%10;
		aveBuffer/=10;
		j++;
	}

	for(i=3;i>=0;i--){
		LED[i]=str[i];
	}
	for(i=3;i>=0;i--){
		str[i]=0;
	}
	f_shengao=false;
}
void tizhong(void){
	int i;
	j=0;
	aveBuffer1=0;
	
	for(i=10;i>=0;i--){
		Buffer1[i]=0;
	}
	
	buffer1=0;
	buffer1=(ADCConvertedValue)*65/2200;
	while(buffer1){
	str_ad[j]=buffer1%10;
	buffer1/=10;
	j++;
	}
	
	for(i=3;i>=0;i--){
		LED1[i]=str_ad[i];
	}
	for(i=3;i>=0;i--){
		str_ad[i]=0;
	}
}
// Periodic Timer Example
static void Timer2_Callback (void const *arg) {

	if(ADCConvertedValue>1000&&sB.bBUTTON==true){//MAX=4096
		sB.bBUTTON=false;
		
  if(f_shengao==false){
	shengao();
	}
  tizhong();
	}
	else
	{
	LED[0]=15;
	LED[1]=15;
	LED[2]=15;
	LED[3]=15;
	
	LED1[0]=15;
	LED1[1]=15;
	LED1[2]=15;
	LED1[3]=15;
	f_shengao=false;
	}
  switch (cAG){
			case MAN_AG_25:
					if(aveBuffer>=1600&&aveBuffer<1610){if(buffer1<47){cRESULT=LOW;}else if(buffer1>=47&&buffer1<=64){cRESULT=NOMAL;}else if(buffer1>64){cRESULT=HIGH;}}
					if(aveBuffer>=1610&&aveBuffer<1620){if(buffer1<47){cRESULT=LOW;}else if(buffer1>=47&&buffer1<=64){cRESULT=NOMAL;}else if(buffer1>64){cRESULT=HIGH;}}
					if(aveBuffer>=1620&&aveBuffer<1630){if(buffer1<47){cRESULT=LOW;}else if(buffer1>=47&&buffer1<=64){cRESULT=NOMAL;}else if(buffer1>64){cRESULT=HIGH;}}
					if(aveBuffer>=1630&&aveBuffer<1640){if(buffer1<47){cRESULT=LOW;}else if(buffer1>=47&&buffer1<=64){cRESULT=NOMAL;}else if(buffer1>64){cRESULT=HIGH;}}
					if(aveBuffer>=1640&&aveBuffer<1650){if(buffer1<47){cRESULT=LOW;}else if(buffer1>=47&&buffer1<=64){cRESULT=NOMAL;}else if(buffer1>64){cRESULT=HIGH;}}
				break;
			case MAN_AG_25_29:
				break;
			case MAN_AG_30_39:
				break;
			case MAN_AG_40_59:
				break;
			
			case WAMAN_AG_25:
				break;
			case WAMAN_AG_25_44:
				break;
			case WAMAN_AG_45_49:
				break;
			case WAMAN_AG_50_54:
				break;
			case WAMAN_AG_55_59:
				break;
			default:
				break;
		}
}


// Example: Create and Start timers
void Init_Timers (void) {
  osStatus status;                                              // function return status
 
  // Create periodic timer
  exec2 = 2;
  id2 = osTimerCreate (osTimer(Timer2), osTimerPeriodic, &exec2);
  if (id2 != NULL) {    // Periodic timer created
    // start timer with periodic 1000ms interval
    status = osTimerStart (id2, 20000);   //20000         
    if (status != osOK) {
      // Timer could not be started
    }
  }
}

/**
   * @brief  Configures the different system clocks.
   * @param  None
   * @retval None
   */
 void RCC_Configuration(void)
 {
 #if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)
   /* ADCCLK = PCLK2/2 */
   RCC_ADCCLKConfig(RCC_PCLK2_Div2); 
 #else
   /* ADCCLK = PCLK2/4 */
   RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
 #endif
   /* Enable peripheral clocks ------------------------------------------------*/
   /* Enable DMA1 clock */
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
 
   /* Enable ADC1 and GPIOC clock */
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE);
 }
 
 /**
   * @brief  Configures the different GPIO ports.
   * @param  None
   * @retval None
   */
 void GPIO_Configuration(void)
 {
   GPIO_InitTypeDef GPIO_InitStructure;
 
   /* Configure PC.04 (ADC Channel14) as analog input -------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
 }
