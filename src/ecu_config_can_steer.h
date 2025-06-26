#ifndef ECU_CONFIG_CAN_STEER_H_
#define ECU_CONFIG_CAN_STEER_H_


#define USE_SRV_SYS_OS_SEQ
#define SYS_TICK (10.0)

// #define USE_CTRL_WHEEL_TRACT
#define USE_CTRL_CAN_STEER

#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_CAN
// #define USE_SRV_UI_LCD
// #define USE_SRV_UI_BT
// #define USE_SRV_CONTROL

// #define USE_DD_DC_MOTOR
// #define USE_ED_ENCODER
// #define USE_DD_JOYSTICK

// #define USE_ED_BUZZER
#define USE_ED_CAN_MCP
// #define USE_ED_ESC
// #define USE_ED_L298








// CAN MCP ECU CONFIG
#define CAN0_INT 2 // Set INT to pin 2
#define CAN0_CS 10 // Set CS to pin 2

#define CAN_ID_EXTENDED 0x80000000

#define CAN_ID_STEER_HB (0x07000001)
#define CAN_ID_STEER_SEND (0x06000001)
#define CAN_ID_STEER_RECV (0x05800001)




#define TX_CAN_ID_NR_OF 1
#define TX_CAN_ID_LIST {CAN_ID_STEER_SEND}
#define RX_CAN_ID_NR_OF 2
#define RX_CAN_ID_LIST {CAN_ID_STEER_HB, CAN_ID_STEER_RECV}

#endif
