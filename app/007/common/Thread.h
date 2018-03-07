#ifndef __THREAD_H
#define __THREAD_H
#include "cmsis_os.h" 
#include "buttons_nightmare.h"
int Init_Thread_start (void);
void Thread_start (void const *argument);
void Thread_task2 (void const *argument);
void Thread_task3 (void const *argument);
#endif
