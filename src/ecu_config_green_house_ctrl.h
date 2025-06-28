#ifndef ECU_CONFIG_CTRL_GREEN_HOUSE_H_
#define ECU_CONFIG_CTRL_GREEN_HOUSE_H_

//==================  Control units ============================================
#define USE_CTRL_AIR_HUM
#define USE_CTRL_AIR_PRESS
#define USE_CTRL_AMB_LIGHT
#define USE_CTRL_SOIL_MOIST
#define USE_CTRL_AIR_TEMP_HEAT
#define USE_CTRL_AIR_TEMP_VENT



//================== Services components =======================================
// #define USE_SRV_SYS_OS_SEQ
#define USE_SRV_SYS_OS_FREERTOS
#define USE_SRV_HEARTBEAT
#define USE_SRV_UI_SERIAL
#define USE_SRV_COM_MQTT

//------------------- Sensor services components -------------------------------
#define USE_SRV_SNS_AIR_HUM
#define USE_SRV_SNS_AIR_PRESS
#define USE_SRV_SNS_AMB_LIGHT
#define USE_SRV_SNS_AIR_TEMP
#define USE_SRV_SNS_SOIL_MOIST


//================== Device Drivers components =================================
#define USE_DD_AIR_PUMP
#define USE_DD_HEATER
#define USE_DD_LIGHTS
#define USE_DD_VALVE
#define USE_DD_WINDOW

//================== ECU Drivers components ============================
#define USE_ED_BMP
#define USE_ED_BH1750

#define USE_ED_DHT
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

#define SRV_HEARTBEAT_REC (0.5 * TIME_SEC)
#define SRV_HEARTBEAT_OFFSET (5 * TIME_mSEC)

//-------------------------------------------------------------------------
// configure task recurrence and offset
#define ED_BH1750_REC (500 * TIME_mSEC)
#define ED_BH1750_OFFSET (2.8 * TIME_SEC)

#define ED_BMP_REC (500 * TIME_mSEC)
#define ED_BMP_OFFSET (2.8 * TIME_SEC)

#define ED_DHT_REC (500 * TIME_mSEC)
#define ED_DHT_OFFSET (2.8 * TIME_SEC)

#define ED_SNS_SOIL_MOIST_REC (500 * TIME_mSEC)
#define ED_SNS_SOIL_MOIST_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_HUM_REC (200 * TIME_mSEC)
#define SRV_SNS_AIR_HUM_OFFSET (2.8 * TIME_SEC)

#define SRV_SNS_AIR_PRESS_REC (200 * TIME_mSEC)
#define SRV_SNS_AIR_PRESS_OFFSET (2.8 * TIME_SEC)


#define SRV_SNS_AIR_TEMP_REC (200 * TIME_mSEC)
#define SRV_SNS_AIR_TEMP_OFFSET (2.8 * TIME_SEC)


#define SRV_SNS_SOIL_MOIST_REC (200 * TIME_mSEC)
#define SRV_SNS_SOIL_MOIST_OFFSET (2.8 * TIME_SEC)


#define CTRL_AIR_HUM_REC (200 * TIME_mSEC)
#define CTRL_AIR_HUM_OFFSET (3.0 * TIME_SEC)

#define CTRL_AIR_PRESS_REC (200 * TIME_mSEC)
#define CTRL_AIR_PRESS_OFFSET (3.0 * TIME_SEC)

#define CTRL_AMB_LIGHT_REC (200 * TIME_mSEC)
#define CTRL_AMB_LIGHT_OFFSET (3.0 * TIME_SEC)

#define CTRL_SOIL_MOIST_REC (200 * TIME_mSEC)
#define CTRL_SOIL_MOIST_OFFSET (3.0 * TIME_SEC)

#define CTRL_AIR_TEMP_HEAT_REC (200 * TIME_mSEC)
#define CTRL_AIR_TEMP_HEAT_OFFSET (3.0 * TIME_SEC)

#define CTRL_AIR_TEMP_VENT_REC (200 * TIME_mSEC)
#define CTRL_AIR_TEMP_VENT_OFFSET (3.0 * TIME_SEC)

#define SRV_SNS_AMB_LIGHT_REC (200 * TIME_mSEC)
#define SRV_SNS_AMB_LIGHT_OFFSET (2.8 * TIME_SEC)



#define DD_AIR_PUMP_REC (200 * TIME_mSEC)
#define DD_AIR_PUMP_OFFSET (3.1 * TIME_SEC)

#define DD_HEATER_REC (200 * TIME_mSEC)
#define DD_HEATER_OFFSET (3.1 * TIME_SEC)

#define DD_LIGHTS_REC (200 * TIME_mSEC)
#define DD_LIGHTS_OFFSET (3.1 * TIME_SEC)

#define DD_VALVE_REC (200 * TIME_mSEC)
#define DD_VALVE_OFFSET (3.1 * TIME_SEC)

#define DD_WINDOW_REC (200 * TIME_mSEC)
#define DD_WINDOW_OFFSET (3.1 * TIME_SEC)

#define ED_RELAY_REC (200 * TIME_mSEC)
#define ED_RELAY_OFFSET (3.2 * TIME_SEC)

//-------------------------------------------------------------------------


#define CTRL_AIR_HUM_OP_D_TIME (4 * TIME_SEC)
#define CTRL_AIR_HUM_HISTERESIS (0.5)
#define CTRL_AIR_HUM_CUR_DEFAULT (10.0) 
#define CTRL_AIR_HUM_SP_DEFAULT (60.0)

#define CTRL_AIR_PRESS_OP_D_TIME (1.0 * TIME_SEC)
#define CTRL_AIR_PRESS_HISTERESIS (0.05)
#define CTRL_AIR_PRESS_CUR_DEFAULT (1.0)
#define CTRL_AIR_PRESS_SP_DEFAULT (1.0)


#define CTRL_AMB_LIGHT_OP_D_TIME (5.0 * TIME_SEC)
#define CTRL_AMB_LIGHT_HISTERESIS (5.0)
#define CTRL_AMB_LIGHT_CUR_DEFAULT (10.0)
#define CTRL_AMB_LIGHT_SP_DEFAULT (60.0)

#define CTRL_SOIL_MOIST_OP_D_TIME (4 * TIME_SEC)
#define CTRL_SOIL_MOIST_HISTERESIS (0.5)
#define CTRL_SOIL_MOIST_CUR_DEFAULT (10.0) 
#define CTRL_SOIL_MOIST_SP_DEFAULT (60.0)

#define CTRL_AIR_TEMP_HEAT_OP_D_TIME (1.0 * TIME_SEC)
#define CTRL_AIR_TEMP_HEAT_HISTERESIS (0.5)
#define CTRL_AIR_TEMP_HEAT_CUR_DEFAULT (10.0)
#define CTRL_AIR_TEMP_HEAT_SP_DEFAULT (19.0)


#define CTRL_AIR_TEMP_VENT_OP_D_TIME (3 * TIME_SEC)
#define CTRL_AIR_TEMP_VENT_HISTERESIS (0.5)
#define CTRL_AIR_TEMP_VENT_CUR_DEFAULT (10.0) 
#define CTRL_AIR_TEMP_VENT_SP_DEFAULT (19.0)


#define ED_DHT_PIN 4 // Digital pin connected to the DHT sensor

#define DD_AIR_PUMP_OP_D_TIME (1.0 * TIME_SEC)
#define DD_LIGHTS_OP_D_TIME (5.0 * TIME_SEC)
#define DD_VALVE_OP_D_TIME (4 * TIME_SEC)
#define DD_WIN_OP_D_TIME (4 * TIME_SEC)


#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN

#define CTRL_AIR_HUM_RELAY_ID ED_RELAY_HUMIDIFY_ID

#define ED_RELAY_1_PIN 32
#define ED_RELAY_2_PIN 33
#define ED_RELAY_3_PIN 33
#define ED_RELAY_4_PIN 33
#define ED_RELAY_5_PIN 33
#define ED_RELAY_6_PIN 33
#define ED_RELAY_7_PIN 33 


#endif