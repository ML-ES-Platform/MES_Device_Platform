#ifndef SRV_SYS_OS_H
#define SRV_SYS_OS_H

// Include any necessary libraries or headers
#include "ecu_config.h"

// Define any constants or macros



//=============================================================================
// time base definitions
//-----------------------------------------------------------------------------
#ifdef SYS_TICK
#define SYS_TICK (10.0)
#endif
#ifndef TIME_SEC
#define TIME_SEC (1000 )
#endif
#ifndef TIME_MIN
#define TIME_MIN (60 * TIME_SEC)
#endif
#ifndef TIME_HOUR
#define TIME_HOUR (60 * TIME_MIN)
#endif
#ifndef TIME_DAY
#define TIME_DAY (24 * TIMTIME_HOUR)   
#endif

//=============================================================================
// Task Scheduling definitions
//-----------------------------------------------------------------------------
#ifdef USE_APP
#ifndef APP_REC
#define APP_REC (10 / SYS_TICK)
#endif
#ifndef APP_OFFSET
#define APP_OFFSET (1 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_HUM
#ifndef CTRL_AIR_HUM_REC
#define CTRL_AIR_HUM_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_AIR_HUM_OFFSET
#define CTRL_AIR_HUM_OFFSET (2 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
#ifndef CTRL_AIR_PRESS_REC
#define CTRL_AIR_PRESS_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_AIR_PRESS_OFFSET
#define CTRL_AIR_PRESS_OFFSET (3 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_HEAT
#ifndef CTRL_AIR_TEMP_HEAT_REC
#define CTRL_AIR_TEMP_HEAT_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_AIR_TEMP_HEAT_OFFSET
#define CTRL_AIR_TEMP_HEAT_OFFSET (4 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_VENT
#ifndef CTRL_AIR_TEMP_VENT_REC
#define CTRL_AIR_TEMP_VENT_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_AIR_TEMP_VENT_OFFSET
#define CTRL_AIR_TEMP_VENT_OFFSET (5 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AMB_LIGHT
#ifndef CTRL_AMB_LIGHT_REC
#define CTRL_AMB_LIGHT_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_AMB_LIGHT_OFFSET
#define CTRL_AMB_LIGHT_OFFSET (6 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_CAN_STEER
#ifndef CTRL_CAN_STEER_REC
#define CTRL_CAN_STEER_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_CAN_STEER_OFFSET
#define CTRL_CAN_STEER_OFFSET (7 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
#ifndef CTRL_SERVO_ADC_DC_REC
#define CTRL_SERVO_ADC_DC_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_SERVO_ADC_DC_OFFSET
#define CTRL_SERVO_ADC_DC_OFFSET (8 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
#ifndef CTRL_SOIL_MOIST_REC
#define CTRL_SOIL_MOIST_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_SOIL_MOIST_OFFSET
#define CTRL_SOIL_MOIST_OFFSET (9 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
#ifndef CTRL_WHEEL_STEER_REC
#define CTRL_WHEEL_STEER_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_WHEEL_STEER_OFFSET
#define CTRL_WHEEL_STEER_OFFSET (10 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
#ifndef CTRL_WHEEL_TRACT_REC
#define CTRL_WHEEL_TRACT_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_WHEEL_TRACT_OFFSET
#define CTRL_WHEEL_TRACT_OFFSET (11 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
#ifndef DD_AIR_PUMP_REC
#define DD_AIR_PUMP_REC (10 / SYS_TICK)
#endif
#ifndef DD_AIR_PUMP_OFFSET
#define DD_AIR_PUMP_OFFSET (12 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
#ifndef DD_DC_MOTOR_REC
#define DD_DC_MOTOR_REC (10 / SYS_TICK)
#endif
#ifndef DD_DC_MOTOR_OFFSET
#define DD_DC_MOTOR_OFFSET (13 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
#ifndef DD_HEATER_REC
#define DD_HEATER_REC (10 / SYS_TICK)
#endif
#ifndef DD_HEATER_OFFSET
#define DD_HEATER_OFFSET (14 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
#ifndef DD_JOYSTICK_REC
#define DD_JOYSTICK_REC (10 / SYS_TICK)
#endif
#ifndef DD_JOYSTICK_OFFSET
#define DD_JOYSTICK_OFFSET (15 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
#ifndef DD_LIGHTS_REC
#define DD_LIGHTS_REC (10 / SYS_TICK)
#endif
#ifndef DD_LIGHTS_OFFSET
#define DD_LIGHTS_OFFSET (16 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
#ifndef DD_VALVE_REC
#define DD_VALVE_REC (10 / SYS_TICK)
#endif
#ifndef DD_VALVE_OFFSET
#define DD_VALVE_OFFSET (17 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
#ifndef DD_WATER_PUMP_REC
#define DD_WATER_PUMP_REC (10 / SYS_TICK)
#endif
#ifndef DD_WATER_PUMP_OFFSET
#define DD_WATER_PUMP_OFFSET (18 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
#ifndef DD_WINDOW_REC
#define DD_WINDOW_REC (10 / SYS_TICK)
#endif
#ifndef DD_WINDOW_OFFSET
#define DD_WINDOW_OFFSET (19 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
#ifndef ED_BH1750_REC
#define ED_BH1750_REC (10 / SYS_TICK)
#endif
#ifndef ED_BH1750_OFFSET
#define ED_BH1750_OFFSET (20 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
#ifndef ED_BMP_REC
#define ED_BMP_REC (10 / SYS_TICK)
#endif
#ifndef ED_BMP_OFFSET
#define ED_BMP_OFFSET (21 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
#ifndef ED_BUZZER_REC
#define ED_BUZZER_REC (10 / SYS_TICK)
#endif
#ifndef ED_BUZZER_OFFSET
#define ED_BUZZER_OFFSET (22 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
#ifndef ED_CAN_MCP_REC
#define ED_CAN_MCP_REC (10 / SYS_TICK)
#endif
#ifndef ED_CAN_MCP_OFFSET
#define ED_CAN_MCP_OFFSET (23 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
#ifndef ED_CONTACT_REC
#define ED_CONTACT_REC (10 / SYS_TICK)
#endif
#ifndef ED_CONTACT_OFFSET
#define ED_CONTACT_OFFSET (24 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
#ifndef ED_DC_ESC_REC
#define ED_DC_ESC_REC (10 / SYS_TICK)
#endif
#ifndef ED_DC_ESC_OFFSET
#define ED_DC_ESC_OFFSET (25 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
#ifndef ED_DHT_REC
#define ED_DHT_REC (10 / SYS_TICK)
#endif
#ifndef ED_DHT_OFFSET
#define ED_DHT_OFFSET (26 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
#ifndef ED_ENCODER_REC
#define ED_ENCODER_REC (10 / SYS_TICK)
#endif
#ifndef ED_ENCODER_OFFSET
#define ED_ENCODER_OFFSET (27 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
#ifndef ED_L298_REC
#define ED_L298_REC (10 / SYS_TICK)
#endif
#ifndef ED_L298_OFFSET
#define ED_L298_OFFSET (28 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
#ifndef ED_RELAY_REC
#define ED_RELAY_REC (10 / SYS_TICK)
#endif
#ifndef ED_RELAY_OFFSET
#define ED_RELAY_OFFSET (29 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
#ifndef ED_SERVO_REC
#define ED_SERVO_REC (10 / SYS_TICK)
#endif
#ifndef ED_SERVO_OFFSET
#define ED_SERVO_OFFSET (30 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
#ifndef ED_SNS_SOIL_MOIST_REC
#define ED_SNS_SOIL_MOIST_REC (10 / SYS_TICK)
#endif
#ifndef ED_SNS_SOIL_MOIST_OFFSET
#define ED_SNS_SOIL_MOIST_OFFSET (31 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
#ifndef SRV_COM_CAN_REC
#define SRV_COM_CAN_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_CAN_OFFSET
#define SRV_COM_CAN_OFFSET (32 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
#ifndef SRV_COM_LORA_REC
#define SRV_COM_LORA_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_LORA_OFFSET
#define SRV_COM_LORA_OFFSET (33 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
#ifndef SRV_COM_MODBUS_REC
#define SRV_COM_MODBUS_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_MODBUS_OFFSET
#define SRV_COM_MODBUS_OFFSET (34 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
#ifndef SRV_COM_MQTT_REC
#define SRV_COM_MQTT_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_MQTT_OFFSET
#define SRV_COM_MQTT_OFFSET (35 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
#ifndef SRV_CONTROL_REC
#define SRV_CONTROL_REC (10 / SYS_TICK)
#endif
#ifndef SRV_CONTROL_OFFSET
#define SRV_CONTROL_OFFSET (36 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
#ifndef SRV_HEARTBEAT_REC
#define SRV_HEARTBEAT_REC (10 / SYS_TICK)
#endif
#ifndef SRV_HEARTBEAT_OFFSET
#define SRV_HEARTBEAT_OFFSET (37 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
#ifndef SRV_SNS_AIR_HUM_REC
#define SRV_SNS_AIR_HUM_REC (10 / SYS_TICK)
#endif
#ifndef SRV_SNS_AIR_HUM_OFFSET
#define SRV_SNS_AIR_HUM_OFFSET (38 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
#ifndef SRV_SNS_AIR_PRESS_REC
#define SRV_SNS_AIR_PRESS_REC (10 / SYS_TICK)
#endif
#ifndef SRV_SNS_AIR_PRESS_OFFSET
#define SRV_SNS_AIR_PRESS_OFFSET (39 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
#ifndef SRV_SNS_AIR_TEMP_REC
#define SRV_SNS_AIR_TEMP_REC (10 / SYS_TICK)
#endif
#ifndef SRV_SNS_AIR_TEMP_OFFSET
#define SRV_SNS_AIR_TEMP_OFFSET (40 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
#ifndef SRV_SNS_AMB_LIGHT_REC
#define SRV_SNS_AMB_LIGHT_REC (10 / SYS_TICK)
#endif
#ifndef SRV_SNS_AMB_LIGHT_OFFSET
#define SRV_SNS_AMB_LIGHT_OFFSET (41 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
#ifndef SRV_SNS_SOIL_MOIST_REC
#define SRV_SNS_SOIL_MOIST_REC (10 / SYS_TICK)
#endif
#ifndef SRV_SNS_SOIL_MOIST_OFFSET
#define SRV_SNS_SOIL_MOIST_OFFSET (42 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
#ifndef SRV_UI_BT_REC
#define SRV_UI_BT_REC (10 / SYS_TICK)
#endif
#ifndef SRV_UI_BT_OFFSET
#define SRV_UI_BT_OFFSET (43 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
#ifndef SRV_UI_LCD_REC
#define SRV_UI_LCD_REC (10 / SYS_TICK)
#endif
#ifndef SRV_UI_LCD_OFFSET
#define SRV_UI_LCD_OFFSET (44 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#ifndef SRV_UI_SERIAL_REC
#define SRV_UI_SERIAL_REC (10 / SYS_TICK)
#endif
#ifndef SRV_UI_SERIAL_OFFSET
#define SRV_UI_SERIAL_OFFSET (45 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_TEST_MODULE
#ifndef TEST_MODULE_REC
#define TEST_MODULE_REC (10 / SYS_TICK)
#endif
#ifndef TEST_MODULE_OFFSET
#define TEST_MODULE_OFFSET (46 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------



// Declare any global variables or functions

#endif // SRV_SYS_OS_H
