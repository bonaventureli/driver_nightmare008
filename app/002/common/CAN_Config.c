#include "can_config.h"

#define CAN_STM32_rx_EXTENDED_ID 0x11111111U
#define CAN_STM32_tx_EXTENDED_ID 0x12222222U

// CAN Interface configuration -------------------------------------------------

#define  CAN_CONTROLLER         1       // CAN Controller number
#define  CAN_LOOPBACK           0       // 0 = no loopback, 1 = external loopback
#define  CAN_BITRATE_NOMINAL    125000  // Nominal bitrate (125 kbit/s)

//------------------------------------------------------------------------------

#define _CAN_Driver_(n)         Driver_CAN##n
#define  CAN_Driver_(n)        _CAN_Driver_(n)
extern   ARM_DRIVER_CAN         CAN_Driver_(CAN_CONTROLLER);
#define  ptrCAN               (&CAN_Driver_(CAN_CONTROLLER))

uint32_t                        rx_obj_idx;
uint8_t                         rx_data[8];
uint8_t                         rx_data2;
ARM_CAN_MSG_INFO                rx_msg_info;
uint32_t                        tx_obj_idx;
uint8_t                         tx_data[8];
uint8_t                         tx_data2;
ARM_CAN_MSG_INFO                tx_msg_info;

uint8_t RxBuffer1;
osThreadDef(CAN_Thread, osPriorityNormal, 1U, NULL);
osThreadId can_thread_id;

void Init_Thread_CAN(void){
if (CAN_Initialize () == false) { 
Error_Handler (); 
}
  can_thread_id = osThreadCreate (osThread(CAN_Thread), NULL);	
}

bool CAN_Initialize (void) {
	
  ARM_CAN_CAPABILITIES     can_cap;
  ARM_CAN_OBJ_CAPABILITIES can_obj_cap;
  int32_t                  status;
  uint32_t                 i, num_objects, clock;

  can_cap = ptrCAN->GetCapabilities ();                                         // Get CAN driver capabilities
  num_objects = can_cap.num_objects;                                            // Number of receive/transmit objects

  status = ptrCAN->Initialize    (CAN_SignalUnitEvent, CAN_SignalObjectEvent);  if (status != ARM_DRIVER_OK) { return false; }
  status = ptrCAN->PowerControl  (ARM_POWER_FULL); if (status != ARM_DRIVER_OK) { return false; }
  status = ptrCAN->SetMode       (ARM_CAN_MODE_INITIALIZATION); if (status != ARM_DRIVER_OK) { return false; }
 
  clock = ptrCAN->GetClock();                                                   // Get CAN bas clock
  if ((clock % (8U*CAN_BITRATE_NOMINAL)) == 0U) {                               // If CAN base clock is divisible by 8 * nominal bitrate without remainder
    status = ptrCAN->SetBitrate    (ARM_CAN_BITRATE_NOMINAL,                    // Set nominal bitrate
                                    CAN_BITRATE_NOMINAL,                        // Set nominal bitrate to configured constant value
                                    ARM_CAN_BIT_PROP_SEG  (5U) |                // Set propagation segment to 5 time quanta
                                    ARM_CAN_BIT_PHASE_SEG1(1U) |                // Set phase segment 1 to 1 time quantum (sample point at 87.5% of bit time)
                                    ARM_CAN_BIT_PHASE_SEG2(1U) |                // Set phase segment 2 to 1 time quantum (total bit is 8 time quanta long)
                                    ARM_CAN_BIT_SJW       (1U));                // Resynchronization jump width is same as phase segment 2
  } else if ((clock % (10U*CAN_BITRATE_NOMINAL)) == 0U) {                       // If CAN base clock is divisible by 10 * nominal bitrate without remainder
    status = ptrCAN->SetBitrate    (ARM_CAN_BITRATE_NOMINAL,                    // Set nominal bitrate
                                    CAN_BITRATE_NOMINAL,                        // Set nominal bitrate to configured constant value
                                    ARM_CAN_BIT_PROP_SEG  (7U) |                // Set propagation segment to 7 time quanta
                                    ARM_CAN_BIT_PHASE_SEG1(1U) |                // Set phase segment 1 to 1 time quantum (sample point at 90% of bit time)
                                    ARM_CAN_BIT_PHASE_SEG2(1U) |                // Set phase segment 2 to 1 time quantum (total bit is 10 time quanta long)
                                    ARM_CAN_BIT_SJW       (1U));                // Resynchronization jump width is same as phase segment 2
  } else if ((clock % (12U*CAN_BITRATE_NOMINAL)) == 0U) {                       // If CAN base clock is divisible by 12 * nominal bitrate without remainder
    status = ptrCAN->SetBitrate    (ARM_CAN_BITRATE_NOMINAL,                    // Set nominal bitrate
                                    CAN_BITRATE_NOMINAL,                        // Set nominal bitrate to configured constant value
                                    ARM_CAN_BIT_PROP_SEG  (7U) |                // Set propagation segment to 7 time quanta
                                    ARM_CAN_BIT_PHASE_SEG1(2U) |                // Set phase segment 1 to 2 time quantum (sample point at 83.3% of bit time)
                                    ARM_CAN_BIT_PHASE_SEG2(2U) |                // Set phase segment 2 to 2 time quantum (total bit is 12 time quanta long)
                                    ARM_CAN_BIT_SJW       (2U));                // Resynchronization jump width is same as phase segment 2
  } else {
    return false;
  }
  if (status != ARM_DRIVER_OK) { return false; }

  rx_obj_idx = 0xFFFFFFFFU;
  tx_obj_idx = 0xFFFFFFFFU;
  for (i = 0U; i < num_objects; i++) {                                          // Find first available object for receive and transmit
    can_obj_cap = ptrCAN->ObjectGetCapabilities (i);                            // Get object capabilities
    if      ((rx_obj_idx == 0xFFFFFFFFU) && (can_obj_cap.rx == 1U)) { rx_obj_idx = i;        }
    else if ((tx_obj_idx == 0xFFFFFFFFU) && (can_obj_cap.tx == 1U)) { tx_obj_idx = i; break; }
  }
  if ((rx_obj_idx == 0xFFFFFFFFU) || (tx_obj_idx == 0xFFFFFFFFU)) { return false; }
	
	status = ptrCAN->ObjectSetFilter(rx_obj_idx, ARM_CAN_FILTER_ID_EXACT_ADD, ARM_CAN_EXTENDED_ID(CAN_STM32_rx_EXTENDED_ID), 0U);
  if (status != ARM_DRIVER_OK) { return false; }
	
  status = ptrCAN->ObjectConfigure(tx_obj_idx, ARM_CAN_OBJ_TX);                 // Configure transmit object
  if (status != ARM_DRIVER_OK) { return false; }

  status = ptrCAN->ObjectConfigure(rx_obj_idx, ARM_CAN_OBJ_RX);                 // Configure receive object
  if (status != ARM_DRIVER_OK) { return false; }

#if (CAN_LOOPBACK == 1)
  if (can_cap.external_loopback != 1U) { return false; }
  status = ptrCAN->SetMode (ARM_CAN_MODE_LOOPBACK_EXTERNAL);                    // Activate loopback external mode
  if (status != ARM_DRIVER_OK) { return false; }
#else
  status = ptrCAN->SetMode (ARM_CAN_MODE_NORMAL);                               // Activate normal operation mode
  if (status != ARM_DRIVER_OK) { return false; }
#endif

  return true;

}

void CAN_SignalObjectEvent (uint32_t obj_idx, uint32_t event) {

  if (event == ARM_CAN_EVENT_RECEIVE) {         // If receive event
    if (obj_idx == rx_obj_idx) {                // If receive object event
      ptrCAN->MessageRead(rx_obj_idx, &rx_msg_info, rx_data, 8U);
    }
  }
  if (event == ARM_CAN_EVENT_SEND_COMPLETE) {   // If send completed event
    if (obj_idx == tx_obj_idx) {                // If transmit object event
    }
  }
}
void CAN_SignalUnitEvent (uint32_t event) {

  switch (event) {
    case ARM_CAN_EVENT_UNIT_ACTIVE:
      break;
    case ARM_CAN_EVENT_UNIT_WARNING:
      break;
    case ARM_CAN_EVENT_UNIT_PASSIVE:
      break;
    case ARM_CAN_EVENT_UNIT_BUS_OFF:
      break;
  }
}
void CAN_Thread (void const *arg) {
  uint32_t i;
  memset(&tx_msg_info, 0U, sizeof(ARM_CAN_MSG_INFO));   // Clear message info structure
	tx_msg_info.id = ARM_CAN_EXTENDED_ID(CAN_STM32_tx_EXTENDED_ID);

  i = 0xFFU;	
  while (1) {
    i = (i + 1U) & 0xFFU;
    memset (tx_data, i, 8U);                            // Fill transmit buffer
    // Send data message
    ptrCAN->MessageSend(tx_obj_idx, &tx_msg_info, tx_data, 8U);
    osDelay(1000U);
  }
}	
static void Error_Handler (void) {
  while (1);
}
