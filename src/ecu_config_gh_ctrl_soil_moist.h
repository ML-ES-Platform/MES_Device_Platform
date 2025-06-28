#ifndef ECU_CONFIG_GH_CTRL_SOIL_MOIST_H_
#define ECU_CONFIG_GH_CTRL_SOIL_MOIST_H_

#define USE_CTRL_SOIL_MOIST
// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_HEARTBEAT
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_SRV_SNS_SOIL_MOIST

#define USE_DD_VALVE
#define USE_ED_RELAY
#define USE_ED_SNS_SOIL_MOIST


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
#define ED_SNS_SOIL_MOIST_REC (500 * TIME_mSEC)
#define ED_SNS_SOIL_MOIST_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_SOIL_MOIST_REC (200 * TIME_mSEC)
#define SRV_SNS_SOIL_MOIST_OFFSET (2.8 * TIME_SEC)

#define CTRL_SOIL_MOIST_REC (200 * TIME_mSEC)
#define CTRL_SOIL_MOIST_OFFSET (3.0 * TIME_SEC)

#define DD_VALVE_REC (200 * TIME_mSEC)
#define DD_VALVE_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_mSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_SOIL_MOIST_OP_D_TIME (4 * TIME_SEC)
#define CTRL_SOIL_MOIST_HISTERESIS (0.5)
#define CTRL_SOIL_MOIST_CUR_DEFAULT (10.0) 
#define CTRL_SOIL_MOIST_SP_DEFAULT (60.0)


#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN

#define ED_RELAY_4_PIN 33


#endif