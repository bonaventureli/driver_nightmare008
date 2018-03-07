/*-----------------------------------------------------------------------------
 * Name:    DB2204MA.c
 * Purpose: DB2204MA is the motor driver
 * Rev.:    1.00
 *----------------------------------------------------------------------------*/
/* Copyright (c) 2016/5/16 LIFEI
   ---------------------------------------------------------------------------*/

/*DB2204MA.c*/
#include "db2204ma.h"

/************************************
*@brif Initialize the DB2204MA
*@para GPIOt:
*@return NONE
*************************************/
void DB2204MA_Initialize(GPIO_TypeDef *GPIOt,uint32_t numt,\
	GPIO_TypeDef *GPIOx,uint32_t num){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	GPIO_PortClock   (GPIOt, true);
	GPIO_PinConfigure(GPIOt, numt,
                      GPIO_AF_PUSHPULL,
                      GPIO_MODE_OUT50MHZ);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); 
	
	DB2204MA_InitDirection(GPIOx,num);
	DB2204MA_Forward(GPIOx,num);
	
	InitPWM(TIM3,24000000,240,5000);
	//InitPWM(TIM3,24000000,2400,500);
}
void DB2204MA_Start(void){
	TIM_Cmd(TIM3, ENABLE);
}
void DB2204MA_Stop(void){
	TIM_Cmd(TIM3, DISABLE);
}
/************************************
*@brif Initialize the DB2204MA Direction
*@para GPIOx:
					num:
*@return NONE
*************************************/
void DB2204MA_InitDirection(GPIO_TypeDef *GPIOx,uint32_t num){
	  GPIO_PortClock   (GPIOx, true);
		GPIO_PinWrite    (GPIOx, num, 0);
		GPIO_PinConfigure(GPIOx, num,
											GPIO_OUT_PUSH_PULL, 
											GPIO_MODE_OUT50MHZ);
}
/************************************
*@brif Set the DB2204MA Forward
*@para GPIOx:
					num:
*@return 0
*************************************/
int32_t DB2204MA_Forward (GPIO_TypeDef *GPIOx,uint32_t num) {
  GPIO_PinWrite(GPIOx, num, 1);
  return 0;
}
/************************************
*@brif Set the DB2204MA Opposite
*@para GPIOx:
					num:
*@return 0
*************************************/
int32_t DB2204MA_Opposite (GPIO_TypeDef *GPIOx,uint32_t num) {
  GPIO_PinWrite(GPIOx, num, 0);
  return 0;
}
/************************************
*@brif Set the DB2204MA Opposite
*@para TIMx:where x can be 1 to 17 to select the TIM peripheral.
			 TIM_CounterClock:24000000 24MHz
			 TIM_Frequency:36000 36KHz;  TIMx Frequency = TIMx counter clock/(ARR + 1)
			 TIM_CCRx: 0<TIM_CCRx<(TIM_CounterClock/TIM_Frequency-1)
*@return None
*************************************/
void InitPWM(TIM_TypeDef* TIMx,uint32_t TIM_CounterClock,uint32_t TIM_Frequency,uint32_t TIM_CCRx)
{
	uint16_t PrescalerValue;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	/* -----------------------------------------------------------------------
	The TIMxCLK frequency is set to SystemCoreClock (Hz)
	Prescaler = (TIMxCLK / TIMx counter clock) - 1
	TIMx Channel1 duty cycle = (TIM_CCRx/ TIMx_ARR)* 100 = 50%
	----------------------------------------------------------------------- */
	PrescalerValue = (uint16_t) (SystemCoreClock / TIM_CounterClock) - 1;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(TIM_CounterClock/TIM_Frequency)-1;/* Set the Autoreload value ARR */
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = TIM_CCRx;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	TIM_OC1Init(TIMx, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIMx, ENABLE);
	//TIM_Cmd(TIMx, ENABLE);	
}
