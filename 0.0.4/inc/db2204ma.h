/*DB2204MA.h*/
#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
void DB2204MA_InitDirection(GPIO_TypeDef *GPIOx,uint32_t num);
int32_t DB2204MA_Forward (GPIO_TypeDef *GPIOx,uint32_t num);
int32_t DB2204MA_Opposite (GPIO_TypeDef *GPIOx,uint32_t num);
void InitPWM(TIM_TypeDef* TIMx,uint32_t TIM_CounterClock,uint32_t TIM_Frequency,uint32_t TIM_CCRx);
void DB2204MA_Initialize(GPIO_TypeDef *GPIOt,uint32_t numt,\
	GPIO_TypeDef *GPIOx,uint32_t num);
void DB2204MA_Start(void);
void DB2204MA_Stop(void);
