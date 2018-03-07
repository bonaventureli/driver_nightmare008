#include "stm32f10x.h"
#include <stdbool.h>
#include "cmsis_os.h"
#include <string.h>
#include "Driver_CAN.h"
void CAN_SignalUnitEvent (uint32_t event);
void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event);
void CAN_Thread (void const *arg);
bool CAN_Initialize (void);
void Init_Thread_CAN(void);
static void Error_Handler (void);
