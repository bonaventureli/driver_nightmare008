#include "thread.h"
                                       
osThreadDef (Thread_start, osPriorityNormal, 1, 0); 
osThreadDef (Thread_task2, osPriorityNormal, 1, 0); 
osThreadDef (Thread_task3, osPriorityNormal, 1, 0); 
int Init_Thread_start (void) {
  osThreadCreate (osThread(Thread_start), NULL);
	osThreadCreate (osThread(Thread_task2), NULL);
	osThreadCreate (osThread(Thread_task3), NULL);
  return(0);
}

void Thread_start (void const *argument) {
  while (1) {

  }
}
void Thread_task2 (void const *argument) {
  while (1) {

  }
}
void Thread_task3 (void const *argument) {
  while (1) {

  }
}