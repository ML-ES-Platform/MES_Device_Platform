#ifndef ECU_CONFIG_GH_CTRL_AMB_LIGHT_H_
#define ECU_CONFIG_GH_CTRL_AMB_LIGHT_H_

//==================  Control units ============================================
#define USE_CTRL_AMB_LIGHT
//================== Services components =======================================
// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_HEARTBEAT
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT
//------------------- Sensor services components -------------------------------
#define USE_SRV_SNS_AMB_LIGHT
#define USE_DD_LIGHTS

#define USE_ED_BH1750
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
#define ED_BH1750_REC (500 * TIME_mSEC)
#define ED_BH1750_OFFSET (2.8 * TIME_SEC)
#define CTRL_AMB_LIGHT_REC (200 * TIME_mSEC)
#define CTRL_AMB_LIGHT_OFFSET (3.0 * TIME_SEC)

#define SRV_SNS_AMB_LIGHT_REC (200 * TIME_mSEC)
#define SRV_SNS_AMB_LIGHT_OFFSET (2.8 * TIME_SEC)


#define DD_LIGHTS_REC (200 * TIME_mSEC)
#define DD_LIGHTS_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_mSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AMB_LIGHT_OP_D_TIME (5.0 * TIME_SEC)
#define CTRL_AMB_LIGHT_HISTERESIS (5.0)
#define CTRL_AMB_LIGHT_CUR_DEFAULT (10.0)
#define CTRL_AMB_LIGHT_SP_DEFAULT (60.0)


#define DD_LIGHTS_OP_D_TIME (5.0 * TIME_SEC)

#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN

#define ED_RELAY_8_PIN 33 


#endif