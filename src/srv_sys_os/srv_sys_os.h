#ifndef SRV_SYS_OS_H
#define SRV_SYS_OS_H

// Include any necessary libraries or headers
#include "ecu_config.h"

// Define any constants or macros



//=============================================================================
// time base definitions
//-----------------------------------------------------------------------------
#ifndef SYS_TICK
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
#ifdef USE_CTRL_AIR_HUM
#ifndef CTRL_AIR_HUM_REC
#define CTRL_AIR_HUM_REC (60000 )
#endif
#ifndef CTRL_AIR_HUM_OFFSET
#define CTRL_AIR_HUM_OFFSET (CTRL_AIR_HUM_REC + 6)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
#ifndef CTRL_AIR_PRESS_REC
#define CTRL_AIR_PRESS_REC (100 )
#endif
#ifndef CTRL_AIR_PRESS_OFFSET
#define CTRL_AIR_PRESS_OFFSET (CTRL_AIR_PRESS_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AMB_LIGHT
#ifndef CTRL_AMB_LIGHT_REC
#define CTRL_AMB_LIGHT_REC (10000 )
#endif
#ifndef CTRL_AMB_LIGHT_OFFSET
#define CTRL_AMB_LIGHT_OFFSET (CTRL_AMB_LIGHT_REC + 4)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
#ifndef CTRL_SERVO_ADC_DC_REC
#define CTRL_SERVO_ADC_DC_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_SERVO_ADC_DC_OFFSET
#define CTRL_SERVO_ADC_DC_OFFSET (4 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
#ifndef CTRL_SOIL_MOIST_REC
#define CTRL_SOIL_MOIST_REC (60 * TIME_SEC)
#endif
#ifndef CTRL_SOIL_MOIST_OFFSET
#define CTRL_SOIL_MOIST_OFFSET (1 * TIME_SEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_HEAT
#ifndef CTRL_AIR_TEMP_HEAT_REC
#define CTRL_AIR_TEMP_HEAT_REC (10000 )
#endif
#ifndef CTRL_AIR_TEMP_HEAT_OFFSET
#define CTRL_AIR_TEMP_HEAT_OFFSET (CTRL_AIR_TEMP_HEAT_REC + 3)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_VENT
#ifndef CTRL_AIR_TEMP_VENT_REC
#define CTRL_AIR_TEMP_VENT_REC (60 * TIME_SEC)
#endif
#ifndef CTRL_AIR_TEMP_VENT_OFFSET
#define CTRL_AIR_TEMP_VENT_OFFSET (61 * TIME_SEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_CAN_STEER
#ifndef CTRL_CAN_STEER_REC
#define CTRL_CAN_STEER_REC ((5 * TIME_SEC) / SYS_TICK)
#endif
#ifndef CTRL_CAN_STEER_OFFSET
#define CTRL_CAN_STEER_OFFSET (CTRL_CAN_STEER_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
#ifndef CTRL_WHEEL_STEER_REC
#define CTRL_WHEEL_STEER_REC (10 / SYS_TICK)
#endif
#ifndef CTRL_WHEEL_STEER_OFFSET
#define CTRL_WHEEL_STEER_OFFSET (CTRL_WHEEL_STEER_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
#ifndef CTRL_WHEEL_TRACT_REC
#define CTRL_WHEEL_TRACT_REC (1000 / SYS_TICK)
#endif
#ifndef CTRL_WHEEL_TRACT_OFFSET
#define CTRL_WHEEL_TRACT_OFFSET (CTRL_WHEEL_TRACT_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
#ifndef DD_AIR_PUMP_REC
#define DD_AIR_PUMP_REC (200 * TIME_mSEC)
#endif
#ifndef DD_AIR_PUMP_OFFSET
#define DD_AIR_PUMP_OFFSET (3.1 * TIME_SEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
#ifndef DD_DC_MOTOR_REC
#define DD_DC_MOTOR_REC (10 / SYS_TICK)
#endif
#ifndef DD_DC_MOTOR_OFFSET
#define DD_DC_MOTOR_OFFSET (DD_DC_MOTOR_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
#ifndef DD_HEATER_REC
#define DD_HEATER_REC (100 )
#endif
#ifndef DD_HEATER_OFFSET
#define DD_HEATER_OFFSET 11
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
#ifndef DD_JOYSTICK_REC
#define DD_JOYSTICK_REC (10 / SYS_TICK)
#endif
#ifndef DD_JOYSTICK_OFFSET
#define DD_JOYSTICK_OFFSET (DD_JOYSTICK_REC + 3)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
#ifndef DD_LIGHTS_REC
#define DD_LIGHTS_REC (100 )
#endif
#ifndef DD_LIGHTS_OFFSET
#define DD_LIGHTS_OFFSET 12
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
#ifndef DD_VALVE_REC
#define DD_VALVE_REC (100 )
#endif
#ifndef DD_VALVE_OFFSET
#define DD_VALVE_OFFSET 13
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
#ifndef DD_WATER_PUMP_REC
#define DD_WATER_PUMP_REC (10 / SYS_TICK)
#endif
#ifndef DD_WATER_PUMP_OFFSET
#define DD_WATER_PUMP_OFFSET (16 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
#ifndef DD_WINDOW_REC
#define DD_WINDOW_REC (100 )
#endif
#ifndef DD_WINDOW_OFFSET
#define DD_WINDOW_OFFSET 14
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
#ifndef ED_BH1750_REC
#define ED_BH1750_REC (500 * TIME_mSEC)
#endif
#ifndef ED_BH1750_OFFSET
#define ED_BH1750_OFFSET (2.8 * TIME_SEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
#ifndef ED_BMP_REC
#define ED_BMP_REC (100 )
#endif
#ifndef ED_BMP_OFFSET
#define ED_BMP_OFFSET 1
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
#ifndef ED_BUZZER_REC
#define ED_BUZZER_REC (10 / SYS_TICK)
#endif
#ifndef ED_BUZZER_OFFSET
#define ED_BUZZER_OFFSET (ED_BUZZER_REC + 4)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
#ifndef ED_CAN_MCP_REC
#define ED_CAN_MCP_REC (10 / SYS_TICK)
#endif
#ifndef ED_CAN_MCP_OFFSET
#define ED_CAN_MCP_OFFSET (20 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
#ifndef ED_CONTACT_REC
#define ED_CONTACT_REC (100 )
#endif
#ifndef ED_CONTACT_OFFSET
#define ED_CONTACT_OFFSET 1
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
#ifndef ED_DC_ESC_REC
#define ED_DC_ESC_REC (10 / SYS_TICK)
#endif
#ifndef ED_DC_ESC_OFFSET
#define ED_DC_ESC_OFFSET (22 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
#ifndef ED_DHT_REC
#define ED_DHT_REC (100 )
#endif
#ifndef ED_DHT_OFFSET
#define ED_DHT_OFFSET 2
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
#ifndef ED_ENCODER_REC
#define ED_ENCODER_REC (1 / SYS_TICK)
#endif
#ifndef ED_ENCODER_OFFSET
#define ED_ENCODER_OFFSET (ED_ENCODER_REC + 4)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
#ifndef ED_L298_REC
#define ED_L298_REC (100 / SYS_TICK)
#endif
#ifndef ED_L298_OFFSET
#define ED_L298_OFFSET (ED_L298_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
#ifndef ED_RELAY_REC
#define ED_RELAY_REC (100 )
#endif
#ifndef ED_RELAY_OFFSET
#define ED_RELAY_OFFSET 5
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
#ifndef ED_SERVO_REC
#define ED_SERVO_REC (10 / SYS_TICK)
#endif
#ifndef ED_SERVO_OFFSET
#define ED_SERVO_OFFSET (27 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
#ifndef ED_SNS_SOIL_MOIST_REC
#define ED_SNS_SOIL_MOIST_REC (100 )
#endif
#ifndef ED_SNS_SOIL_MOIST_OFFSET
#define ED_SNS_SOIL_MOIST_OFFSET 3
#endif
#endif
//=============================================================================
// Service task definitions
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
#ifndef SRV_COM_CAN_SEND_REC
#define SRV_COM_CAN_SEND_REC (50 / SYS_TICK)
#endif
#ifndef SRV_COM_CAN_SEND_OFFSET 
#define SRV_COM_CAN_SEND_OFFSET (SRV_COM_CAN_SEND_REC + 1)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
#ifndef SRV_COM_CAN_RECV_REC
#define SRV_COM_CAN_RECV_REC (1 / SYS_TICK)
#endif
#ifndef SRV_COM_CAN_RECV_OFFSET
#define SRV_COM_CAN_RECV_OFFSET (SRV_COM_CAN_RECV_REC + 2)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
#ifndef SRV_COM_LORA_REC
#define SRV_COM_LORA_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_LORA_OFFSET
#define SRV_COM_LORA_OFFSET (30 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
#ifndef SRV_COM_MODBUS_REC
#define SRV_COM_MODBUS_REC (10 / SYS_TICK)
#endif
#ifndef SRV_COM_MODBUS_OFFSET
#define SRV_COM_MODBUS_OFFSET (31 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
#ifndef SRV_COM_MQTT_REC
#define SRV_COM_MQTT_REC (1 * TIME_SEC)
#endif
#ifndef SRV_COM_MQTT_OFFSET
#define SRV_COM_MQTT_OFFSET (5 * TIME_SEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
#ifndef SRV_CONTROL_REC
#define SRV_CONTROL_REC (500 / SYS_TICK)
#endif
#ifndef SRV_CONTROL_OFFSET
#define SRV_CONTROL_OFFSET (SRV_CONTROL_REC + 5)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
#ifndef SRV_HEARTBEAT_REC
#define SRV_HEARTBEAT_REC (500 * TIME_mSEC )
#endif
#ifndef SRV_HEARTBEAT_OFFSET
#define SRV_HEARTBEAT_OFFSET (10* TIME_mSEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
#ifndef SRV_SNS_AIR_HUM_REC
#define SRV_SNS_AIR_HUM_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_HUM_OFFSET
#define SRV_SNS_AIR_HUM_OFFSET 50
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
#ifndef SRV_SNS_AIR_PRESS_REC
#define SRV_SNS_AIR_PRESS_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_PRESS_OFFSET
#define SRV_SNS_AIR_PRESS_OFFSET (36 / SYS_TICK)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
#ifndef SRV_SNS_AIR_TEMP_REC
#define SRV_SNS_AIR_TEMP_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AIR_TEMP_OFFSET
#define SRV_SNS_AIR_TEMP_OFFSET 60
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
#ifndef SRV_SNS_AMB_LIGHT_REC
#define SRV_SNS_AMB_LIGHT_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_AMB_LIGHT_OFFSET
#define SRV_SNS_AMB_LIGHT_OFFSET (70)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
#ifndef SRV_SNS_SOIL_MOIST_REC
#define SRV_SNS_SOIL_MOIST_REC (TIME_SEC / 10)
#endif
#ifndef SRV_SNS_SOIL_MOIST_OFFSET
#define SRV_SNS_SOIL_MOIST_OFFSET (80)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
#ifndef SRV_UI_BT_REC
#define SRV_UI_BT_REC (25 / SYS_TICK)
#endif
#ifndef SRV_UI_BT_OFFSET
#define SRV_UI_BT_OFFSET (SRV_UI_BT_REC + 3)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
#ifndef SRV_UI_LCD_REC
#define SRV_UI_LCD_REC (50 / SYS_TICK)
#endif
#ifndef SRV_UI_LCD_OFFSET
#define SRV_UI_LCD_OFFSET (SRV_UI_LCD_REC + 3)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#ifndef SRV_UI_SERIAL_IN_REC
#define SRV_UI_SERIAL_IN_REC (1 * TIME_mSEC)
#endif
#ifndef SRV_UI_SERIAL_IN_OFFSET
#define SRV_UI_SERIAL_IN_OFFSET (4 * TIME_mSEC)
#endif
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#ifndef SRV_UI_SERIAL_OUT_REC
#define SRV_UI_SERIAL_OUT_REC (3 * TIME_SEC )
#endif
#ifndef SRV_UI_SERIAL_OUT_OFFSET
#define SRV_UI_SERIAL_OUT_OFFSET (5 * TIME_mSEC)
#endif
#endif
//-----------------------------------------------------------------------------



// Declare any global variables or functions

#endif // SRV_SYS_OS_H
