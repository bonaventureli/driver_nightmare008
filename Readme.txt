0.03 
button_nightmare.c add 
uint8_t fun_password_single(PASSWORD *tmp);
uint8_t fun_password_loop(PASSWORD *tmp);
void app_password(void);
void GetState_Pin_BUTTON2 (ButtonState bState) ;
void Init_osTimer (void);

rdm6300_nightmare.h  add
uint8_t app_card(void);

1.After ten minutes open flash led, flog and six door.
2.If button in jianyu room pressed, open three door and the button out of jianyu is enabled.
3.If button out of jianyu is pressed, flash led and flog.

1.add an yaokong button which can directly control the room of bangongshi.

1.add an yaokong button which can jump the step of stolen the box on the desk.

1.add one micontrol beside the tuigan.

rt_CMSIS.c
856 osStatus svcDelay (uint32_t millisec) {
rt_dly_wait(rt_ms2tick(millisec));
}
427 static uint16_t rt_ms2tick (uint32_t millisec) {
if (millisec > 4000000U) { return 0xFFFEU; }          // Max ticks supported
tick = ((1000U * millisec) + os_clockrate - 1U)  / os_clockrate;
if (tick > 0xFFFEU) { return 0xFFFEU; }
}
0.834162s
10000
11988

rt_time.c 
63 void rt_dly_wait (U16 delay_time) {
rt_block (delay_time, WAIT_DLY);
}

rt_Task.c
137 void rt_block (U16 timeout, U8 block_state) {
rt_put_dly (os_tsk.run, timeout);
}

rt_Lisht.c
170 void rt_put_dly (P_TCB p_task, U16 delay) {
p->delta_time = (U16)(idelay - delta);
}

RTX_Config.h
60 extern U32 const os_clockrate;
RTX_Conf_CM.c
128 #define OS_TICK        1000

osDelay(5999);//1s