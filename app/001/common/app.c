/*-----------------------------------------------------------------------------
 * Name:    		RoomA_Logic1.c
 * Purpose: 		Logic for Nightmare room1
 * Rev.:    		2.00
 * Author:  		LIFEI
 * LastUptime:	2016-11-30 13:58:09
 *-----------------------------------------------------------------------------*/
#include "app.h"
#include "can_config.h"

extern int Init_Thread_Button (void);
typedef void (*func[])(void);
func pfunc = {
funcNULL,
funcNULL,
funcNULL,
func3,
func4,
func5,
func6,
func7,
func8,
func9,
func10,
funcNULL,
funcNULL,
funcNULL,
func14,
funcNULL,
funcNULL,
funcNULL,
func18,
funcNULL,
funcNULL,
funcNULL,
func22,
func23,
func24,
funcNULL,
funcNULL,
func27,
func28,
func29,
func30,
func31,
func32,
func33,
funcNULL,
func35,
func36,
func37,
funcNULL,
funcNULL,
func40
};
#define DEBUG 2

#if (DEBUG == 0)
#define BEGIN 2
#elif (DEBUG == 1)
#define BEGIN 12//4 9  11 12 15
//12 speaker
//13
//16
//18
//19
#else
#define BEGIN 10
#endif

#define RecordA_COUNT  sizeof(RoomARecordID)

extern uint8_t RxBuffer[];
extern uint8_t MusicOverBuffer[][10];
extern uint8_t TxBuffer[][10];


uint8_t n;
uint8_t m;
extern uint32_t Button_MASK_main;
extern uint32_t Turntable_Button_MASK_main;
extern uint32_t Temp_Button_MASK_main;
extern uint8_t flag_button8,\
flag_button9,\
flag_button7,\
flag_button10,\
flag_button16,\
flag_button21,\
flag_button22,\
flag_button23,\
flag_button6,\
flag_button3,\
flag_button27,\
flag_button1,\
flag_button2,\
flag_button4,\
flag_button26,\
flag_button24,\
flag_button20,\
flag_button25,\
flag_button28,\
flag_button12,\
flag_button18,\
flag_button17,\
flag_button11;
uint8_t RoomARecordID[]={
25,1,2,18,19,3,20,21,4,5,22,6,7,31,32,9,10,27,28,40,16,17,19,36,37
};

extern osThreadId can_thread_id;// thread id

void InitSTM32F103ZE(void){
//	Init_Thread_CAN();
//	Init_Thread_Button();
	RDM6300_Initialize(USART1);
	RDM6300_Initialize(USART2);
	RDM6300_Initialize(USART3);
	RDM6300_Initialize(UART4);
	RDM6300_Initialize(UART5);
	Initialize_Pin_BUTTON(HIGH2LOW);
	LED_Initialize();
	Turntable_Buttons_Initialize_high2low();
	MP230_Initialize(USART1);
	MP230_Initialize(USART2);
	MP230_Initialize(USART3);
	DB2204MA_Initialize(GPIOC,6,GPIOE,9);
}
/********************************
*@brif RoomALogic1 logic of room1-romm2
*@para BackgroundMusic USARTx:USART1 USART2 USART3 UART4 UART5  
			 Radio USARTy:USART1 USART2 USART3 UART4 UART5
*@return None
********************************/
void RoomALogic1(USART_TypeDef* USARTx,USART_TypeDef* USARTy,USART_TypeDef* USARTz,USART_TypeDef* USARTw){
	uint32_t n;
	n = 0;

	#if (DEBUG == 1)

	#endif
	
	#if (DEBUG == 2)
while(1){
LED_Flash2(5999,2,-1);//1s
}
	#endif
		LED_On2(2,6,11,16,22,19,-1);
		LED_Off(14);
#if (DEBUG == 0)
flag_button25=0;flag_button28=0;
while(1){if((flag_button25==1)||(flag_button28==1)){flag_button25=0;flag_button28=0;break;}}
osDelay(5000);
BackgroundMusic_Room1_Done(USART1,InstructionLength,25);
#endif

	for (n = 	BEGIN; n < RecordA_COUNT; n++) {
		osDelay(2000);
		Radio_Room1_Done(USARTx,InstructionLength,RoomARecordID[n]);
		pfunc[RoomARecordID[n]]();
	}	
}

uint8_t BackgroundMusic_Room1_Done(USART_TypeDef* USARTx,uint16_t TempBufferLength,\
												 uint8_t InstructionID){
	return SendOneInstructionB2(USARTx,TempBufferLength,InstructionID);
}
uint8_t Radio_Room1_Done(USART_TypeDef* USARTx,uint16_t TempBufferLength,\
												 uint8_t InstructionID){
return SendOneInstructionB2(USARTx,TempBufferLength,InstructionID);													 
}
												 
void funcNULL(void){}
void func3(void){
	LED_On(28);
	Wait_Pin_BUTTON_Done(0,HIGH2LOW,8,PRESS);//	WaitButtonDone2_high2low(0);
	LED_Off(28);
}
void func4(void){
	LED_On(21);
	Wait_Pin_BUTTON_Done(6,HIGH2LOW,8,PRESS);
	LED_Off(21);
	osDelay(1000);
	LED_On(21);
}
void func5(void){
	flag_button21 = 0;
	flag_button6= 0;
flag_button22= 0;
flag_button9= 0;
	LED_Off(37);
	while(1){
		LED_On(21);
		if(flag_button6 == 1){
		LED_On(21);
		osDelay(1000);
		LED_Off(21);
		osDelay(1000);
		LED_On(21);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,5);
		flag_button6 = 0;
		}
		if(flag_button22==1){
			LED_On(13);
		}
		if(((flag_button22==1)&&(flag_button9==1))||(flag_button28==1)){
		LED_On(13);
			flag_button21=0;
		while(1){if(flag_button21==1){break;}}//Wait_Pin_BUTTON_Done(21,HIGH2LOW,8,PRESS);
		LED_Off(19);
		flag_button22 = 0;
		flag_button28 = 0;
		flag_button9 = 0;
		break;
	}

}
}
void func6(void){
flag_button7 = 0;
flag_button10 = 0;
flag_button28 = 0;
	while(1){
		LED_On(25);
		if(flag_button7 == 1){
		LED_On(25);
		osDelay(1000);
		LED_Off(25);
			osDelay(1000);
			LED_On(25);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,6);
		flag_button7 = 0;
		}
		if((flag_button10 == 1)||(flag_button28 == 1)){
			LED_On(15);
			LED_Off(11);
			LED_Off(13);	
			flag_button10=0;
			break;
		}
	}
	
	osDelay(1000);
			JustSendOneInstruction(USART1,InstructionLength,23);
			osDelay(2000);
			func23();
}
void func7(void){
flag_button8=0;
flag_button16=0;
flag_button28=0;
	LED_Off(15);
	while(1){
		LED_On(35);
		if(flag_button8 == 1){
		LED_On(35);
		osDelay(1000);
		LED_Off(35);
		osDelay(1000);
		LED_On(35);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,7);
		flag_button8 = 0;
		}
		if((flag_button16 == 1)||(flag_button28 == 1)){
			flag_button28 = 0;
			flag_button16 = 0;
			break;
		}
	}
	LED_Off(35);
}
void func8(void){
	osDelay(100);
			BackgroundMusic_Room1_Done(USART1,InstructionLength,11);
			func11();
			BackgroundMusic_Room1_Done(USART1,InstructionLength,40);
			osDelay(100);
			func24();
			JustSendOneInstruction(USART1,InstructionLength,29);
			func29();
			func35();
}
void func9(void){
	osDelay(1000);
	LED_Off(16);
	flag_button18=0;flag_button28=0;
while(1){if((flag_button18==1)||(flag_button28==1)){flag_button18=0;flag_button28=0;break;}}
	LED_On(16);
flag_button17=0;
	while(1){if(flag_button17==1){break;}}//Wait_Pin_BUTTON_Done(17,HIGH2LOW,10,PRESS);
	flag_button18=0;flag_button28=0;
while(1){if((flag_button18==1)||(flag_button28==1)){flag_button18=0;flag_button28=0;break;}}
	osDelay(1000);
	LED_On(10);
	
JustSendOneInstruction(USART1,InstructionLength,33);
			osDelay(60000);
			func33();
}
void func10(void){
	LED_On(27);
	flag_button4=0;while(1){if(flag_button4==1){break;}}//Wait_Pin_BUTTON_Done(4,HIGH2LOW,8,PRESS);
	LED_Off(27);
	osDelay(1000);
	LED_On(27);
	osDelay(100);
}
void func11(void){
	flag_button1=0;
flag_button26=0;
flag_button28=0;
	while(1){
		LED_On(33);
		if(flag_button1 == 1){
		LED_On(33);
		osDelay(2000);
		LED_Off(33);
		osDelay(2000);
		LED_On(33);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,11);
		flag_button1 = 0;
		}
if((flag_button26 == 1)||(flag_button28 == 1)){
		break;
		}
	}
	LED_On(12);
	flag_button20=0;while(1){if(flag_button20==1){break;}}//Wait_Pin_BUTTON_Done(20,HIGH2LOW,8,PRESS);//WaitButtonDone2_high2low(20);
	LED_Off(16);
}
void func14(void){
LED_On(29);
flag_button3=0;while(1){if(flag_button3==1){break;}}//Wait_Pin_BUTTON_Done(3,HIGH2LOW,8,PRESS);//WaitButtonDone2_high2low(3);
LED_Off(29);	
}
void func18(void){
LED_On(32); 	
LED_On(26);
LED_DEL();
}
void func22(void){
/************************/
LED_On(0);
LED_On(4);
osDelay(13800);
/*opposite 138000*/
DB2204MA_Opposite (GPIOE,9);
DB2204MA_Start();
osDelay(13800);
/*stop 4400*/
DB2204MA_Stop();
osDelay(4400);
/*forward 13800*/
DB2204MA_Forward(GPIOE,9);
DB2204MA_Start();
//osDelay(13800);
osDelay(6900);
/*stop 4400*/
DB2204MA_Stop();
/*end********************/
//LED_Off(0);
LED_Off(4);	

osDelay(1000);
osDelay(1000);
BackgroundMusic_Room1_Done(USART1,InstructionLength,35);
LED_Off(21);	
LED_On(25);
flag_button7=0;while(1){if(flag_button7==1){break;}}//Wait_Pin_BUTTON_Done(7,HIGH2LOW,8,PRESS);
LED_Off(25);
osDelay(1000);
LED_On(25);
osDelay(100);
}
void func23(void){
LED_Off(25);
LED_On(35);
flag_button8=0;while(1){if(flag_button8==1){break;}}//Wait_Pin_BUTTON_Done(8,HIGH2LOW,8,PRESS);	
LED_Off(35);
osDelay(1000);
LED_On(35);
}
void func24(void){
LED_Off(33);
LED_On(29);
flag_button3=0;while(1){if(flag_button3==1){break;}}//Wait_Pin_BUTTON_Done(3,HIGH2LOW,8,PRESS);//WaitButtonDone2_high2low(3);
LED_Off(29);	
osDelay(2000);
LED_On(29);
}
void func27(void){
	flag_button4=0;
flag_button11=0;
flag_button28=0;
	while(1){
		LED_On(27);
		LED_On(37);
		if(flag_button4 == 1){
		LED_On(27);
		osDelay(1000);
		LED_Off(27);
			osDelay(1000);
			LED_On(27);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,27);
		flag_button4 = 0;
		}
		if((flag_button11 == 1)||(flag_button28 == 1)){
			break;
		}
	}
LED_Off(27);
LED_On(31);
flag_button2=0;while(1){if(flag_button2==1){break;}}//Wait_Pin_BUTTON_Done(2,HIGH2LOW,8,PRESS);//WaitButtonDone2_high2low(2);	
LED_Off(31);
	osDelay(1000);
	LED_On(31);

	
}
void func28(void){
	LED_On(7);
	LED_On(18);
	LED_Off(22);
	osDelay(5000);
	JustSendOneInstruction(USART3,InstructionLength,11);
	flag_button20 = 0;
flag_button2 = 0;
flag_button26 = 0;
flag_button28 = 0;
	while(1){
	LED_On(31);		
		if(flag_button2 == 1){
		LED_On(31);
		osDelay(1000);
		LED_Off(31);
		osDelay(1000);
		LED_On(31);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,28);
		flag_button2 = 0;
		}
		if((flag_button26 == 1)||(flag_button28 == 1)){//		if((flag_button24 == 1)&&(flag_button26 == 1)){
			LED_On(12);
		}
		if(((flag_button20 == 1)&&(flag_button26 == 1))||(flag_button28 == 1)){//		if((flag_button20 == 1)&&(flag_button24 == 1)&&(flag_button26 == 1)){
		LED_Off(31);
		LED_Off(16);
		flag_button20=0;
		flag_button26=0;
		flag_button28=0;
		break;
		}
		}
}
void func29(void){
	flag_button3 = 0;
	flag_button27 = 0;
	flag_button28 = 0;
		while(1){
		LED_On(29);
		if(flag_button3 == 1){
		LED_On(29);
		osDelay(1000);
		LED_Off(29);
		osDelay(1000);
		LED_On(29);
		BackgroundMusic_Room1_Done(USART1,InstructionLength,29);
		flag_button3 = 0;
		}
		if((flag_button27 == 1)||(flag_button28 == 1)){
			flag_button27=0;
			flag_button28=0;
			osDelay(100);
			break;
		}
		}
LED_Off(29);		
}
void func30(void){
flag_button9=0;while(1){if(flag_button9==1){break;}}//Wait_Pin_BUTTON_Done(9,HIGH2LOW,8,PRESS);
}
void func31(void){
	LED_DEL();
	LED_Off2(9,0,-1);
	LED_On2(32,19,26,-1);
	osDelay(5000);
	LED_On(17);
}
void func32(void){
LED_Off(16);
	osDelay(2000);
}
void func33(void){
LED_On(10);
LED_Off(2);
osDelay(45534);
LED_Off(10);
	osDelay(100);
}
void func35(void){
	LED_On2(0,4,17,-1);
	osDelay(5000);
	LED_Off2(0,4,17,-1);
	LED_DEL();
	
/************************/
	LED_On2(0,4,-1);
/*opposite 138000*/
DB2204MA_Opposite (GPIOE,9);
DB2204MA_Start();
//osDelay(13800);
	osDelay(6900);
/*stop 4400*/
DB2204MA_Stop();
osDelay(4400);
/*forward 13800*/
DB2204MA_Forward(GPIOE,9);
DB2204MA_Start();
osDelay(13800);
//osDelay(6900);
/*stop 4400*/
DB2204MA_Stop();
/*end********************/
LED_Off2(0,4,-1);
}
void func36(void){
	LED_DEL();
	LED_Off(6);
}

void func37(void){
	LED_On(5);
	Turntable2();		
	LED_On(14);	
	while(1){}
}
void func40(void){
	flag_button1=0;
flag_button3=0;

	while(1){
		LED_On(33);
		if(flag_button1 == 1){
			LED_On(33);
			osDelay(1000);
			LED_Off(33);
			osDelay(1000);
			LED_On(33);
			BackgroundMusic_Room1_Done(USART1,InstructionLength,8);	
			flag_button1 = 0;
			LED_On(29);
		}
		if(flag_button3 == 1){
			flag_button3 = 0;
			LED_Off(33);
			LED_On(29);
			osDelay(1000);
			LED_Off(29);
			osDelay(1000);
			LED_On(29);
			osDelay(100);
			break;
		}
		}
	
		osDelay(100);
				BackgroundMusic_Room1_Done(USART1,InstructionLength,29);
			  func29();
}
void Turntable(void){
/*08380108*/
		uint8_t i;
	for(i=0;i<8;i++){
		LED_Flash2(1000,27,28,29,30,-1);
	}

while(1)
{
	if(n == 0){
		Turntable_WaitButtonDone_high2low(0);//0
		n++;
		LED_On(27);
	}
	else if(n == 1){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<3)){//8
		n++;
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 2){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<2)){//3
		n++;
			LED_On(29);
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 3){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<3)){//8
		n++;
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 4){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<0)){//0
		n++;
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 5){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<1)){//1
		n++;
			LED_On(30);
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 6){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<0)){//0
		n++;
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	
	else if(n == 7){
		Turntable_WaitButton_high2low();
		if(Turntable_Button_MASK_main & (1<<3)){//8
		n++;
			LED_On(28);
		}
		else{
			LED_Off2(27,28,29,30,-1);
		n = 0;
		}
	}
	osDelay(5000);
}
}

void Turntable2(void){
	uint8_t n;
	uint8_t i;
		n = 0;
	for(i=0;i<8;i++){
		LED_Flash2(1000,20,1,8,3,-1);
	}

/*08380108*/
while(1)
{
	//LED_On(20);
	if(n == 0){
		Turntable_WaitButtonDone_high2low(0);//0
		n++;
		LED_On(20);
	}
	else if(n == 1){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<0)){//0
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//8
		m = 2;
		}
		if(m ==1){
		n = 1;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		m = 0;
		}
	}
	
	else if(n == 2){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//8
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<2)){//3
		m = 2;
		}
		if(m ==1){
		n = 2;
		}
		else if(m == 2){
		n++;
			LED_On(1);
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	
	else if(n == 3){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<2)){//3
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//8
		m = 2;
		}
		if(m ==1){
		n = 3;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	
	else if(n == 4){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//8
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<0)){//0
		m = 2;
		}
		if(m ==1){
		n = 4;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	
	else if(n == 5){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<0)){//0
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<1)){//1
		m = 2;
		}
		if(m ==1){
		n = 5;
		}
		else if(m == 2){
		n++;
		LED_On(8);
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	
	else if(n == 6){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<1)){//1
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;			
		if(Turntable_Button_MASK_main & (1<<0)){//0
		m = 2;
		}
		if(m ==1){
		n = 6;
		}
		else if(m == 2){
		n++;
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	
	else if(n == 7){
		m = 0;
		Turntable_WaitButton_high2low();
		Temp_Button_MASK_main = Turntable_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<0)){//1
		m = 1;
		}
		Turntable_Button_MASK_main = Temp_Button_MASK_main;
		if(Turntable_Button_MASK_main & (1<<3)){//8
		m = 2;
		}
		if(m ==1){
		n = 7;
		}
		else if(m == 2){
		n++;
		LED_On(3);
		break;
		}
		else{
			LED_Off2(20,1,8,3,-1);
		n = 0;
		}
	}
	osDelay(1000);
}
}

void LED_DEL(void){
	uint8_t i;
	LED_On2(34,30,9,-1);
	osDelay(9000);
	LED_Off(34);
	
	for(i=0;i<13;i++){
		LED_Flash2(500,9,-1);
	}	
	LED_Off(30);
}
void LED_DEL2(void){
	uint8_t i;
	
	LED_On(34);
	osDelay(2000);
	LED_Off(34);
	
	for(i = 0;i<10;i++){
	LED_Flash(9,1000);	
	}
	LED_Off(9);

	LED_On(30);
	osDelay(2000);
	LED_Off(30);
}
void LogicSTM32F103ZE(void){
	RoomALogic1(USART1,USART2,USART3,UART4);
}
