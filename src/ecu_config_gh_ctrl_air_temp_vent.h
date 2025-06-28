#ifndef ECU_CONFIG_GH_CTRL_AIR_TEMP_VENT_H_
#define ECU_CONFIG_GH_CTRL_AIR_TEMP_VENT_H_

#define USE_CTRL_AIR_TEMP_VENT
// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_HEARTBEAT
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
#define USE_SRV_SNS_AIR_TEMP
#define USE_DD_WINDOW
#define USE_ED_DHT
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
#define ED_DHT_REC (500 * TIME_mSEC)
#define ED_DHT_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_TEMP_REC (200 * TIME_mSEC)
#define SRV_SNS_AIR_TEMP_OFFSET (2.8 * TIME_SEC)

#define CTRL_AIR_TEMP_VENT_REC (200 * TIME_mSEC)
#define CTRL_AIR_TEMP_VENT_OFFSET (3.0 * TIME_SEC)

#define DD_WINDOW_REC (200 * TIME_mSEC)
#define DD_WINDOW_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_mSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AIR_TEMP_VENT_OP_D_TIME (3 * TIME_SEC)
#define CTRL_AIR_TEMP_VENT_HISTERESIS (0.5)
#define CTRL_AIR_TEMP_VENT_CUR_DEFAULT (10.0) 
#define CTRL_AIR_TEMP_VENT_SP_DEFAULT (19.0)


#define ED_DHT_PIN 4 // Digital pin connected to the DHT sensor
#define DD_WIN_OP_D_TIME (4 * TIME_SEC)
#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN


#define ED_RELAY_1_PIN 32
#define ED_RELAY_2_PIN 33


#endif