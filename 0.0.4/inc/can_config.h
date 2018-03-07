#ifndef _CAN_CONFIG_H
#define _CAN_CONFIG_H
#include "stm32f10x.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include <string.h>
#include "Driver_CAN.h"

typedef enum _INSTRUCT{
	INSTRUCT0,
	INSTRUCT1,
	INSTRUCT2,
	INSTRUCT3,
	INSTRUCT4,
}INSTRUCT;
typedef enum _STM{
	penyan=1,
	chuanghu,
	shizhong,
	men,
}STM;

typedef enum _CAN_STATE{
ctxover,
crxover,
ctx_instruct,
crx_instruct,
}CAN_STATE;

typedef struct _CANTYPE{
uint8_t *crx_instruct[8];
uint8_t *ctx_instruct[8];
uint8_t *ctx_state[8];
uint8_t *crx_state[8];
uint8_t fcrx_instruct;
uint8_t fctx_instruct;
uint8_t fcrx_state;
uint8_t fctx_state;
}CANTYPE;

void CAN_SignalUnitEvent (uint32_t event);
void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event);
void CAN_Thread (void const *arg);
bool CAN_Initialize (void);
void Init_Thread_CAN(void);
static void Error_Handler (void);
#endif
