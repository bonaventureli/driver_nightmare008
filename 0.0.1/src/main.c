/*-----------------------------------------------------------------------------
 * Name:    		main.c
 * Purpose: 		main 
 * Rev.:    		1.01
 * Author:  		LIFEI
 * LastUptime:	2016-12-9 10:35:17
 *-----------------------------------------------------------------------------*/
#ifndef _MAIN_C
#define _MAIN_C
#include "cmsis_os.h"
#include "app.h"
int main (void) {
osKernelInitialize ();                    // initialize CMSIS-RTOS
InitSTM32F103ZE();
osKernelStart ();                         // start thread execution 	
	while(1){
		LogicSTM32F103ZE();
}
}
#endif
