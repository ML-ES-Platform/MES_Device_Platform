#ifndef ECU_CONFIG_GH_CTRL_AIR_PRESS_H_
#define ECU_CONFIG_GH_CTRL_AIR_PRESS_H_

//==================  Control units ============================================
#define USE_CTRL_AIR_PRESS
// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_HEARTBEAT
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_SRV_SNS_AIR_PRESS
#define USE_DD_AIR_PUMP
#define USE_ED_BMP
#define USE_ED_RELAY


//-------------------------------------------------------------------------
// configure task recurrence and offset for services
#define SRV_UI_SERIAL_IN_REC (1 * TIME_mSEC)
#define SRV_UI_SERIAL_IN_OFFSET (4 * TIME_mSEC)

#define SRV_UI_SERIAL_OUT_REC (5.0 * TIME_SEC)
#define SRV_UI_SERIAL_OUT_OFFSET (5 * TIME_mSEC)

#define SRV_COM_MQTT_REC (10.0 * TIME_SEC)
#define SRV_COM_MQTT_OFFSET (5.0 * TIME_SEC)

//-------------------------------------------------------------------------
// configure task recurrence and offset
#define ED_BMP_REC (500 * TIME_mSEC)
#define ED_BMP_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_PRESS_REC (200 * TIME_mSEC)
#define SRV_SNS_AIR_PRESS_OFFSET (2.8 * TIME_SEC)

#define CTRL_AIR_PRESS_REC (200 * TIME_mSEC)
#define CTRL_AIR_PRESS_OFFSET (3.0 * TIME_SEC)

#define DD_AIR_PUMP_REC (200 * TIME_mSEC)
#define DD_AIR_PUMP_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_mSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AIR_PRESS_OP_D_TIME (1.0 * TIME_SEC)
#define CTRL_AIR_PRESS_HISTERESIS (0.05)
#define CTRL_AIR_PRESS_CUR_DEFAULT (1.0)
#define CTRL_AIR_PRESS_SP_DEFAULT (1.0)


#define DD_AIR_PUMP_OP_D_TIME (1.0 * TIME_SEC)

#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN

#define ED_RELAY_6_PIN 33


#endif