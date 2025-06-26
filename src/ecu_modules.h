#ifndef ECU_MODULES_H
#define ECU_MODULES_H

// Include any necessary libraries or headers here

#include "ecu_config.h"

//=============================================================================
// Control Modules
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_hum/ctrl_air_hum.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
#include "ctrl_air_press/ctrl_air_press.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_LIGHTS
#include "ctrl_lights/ctrl_lights.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
#include "ctrl_servo_adc_dc/ctrl_servo_adc_dc.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moist/ctrl_soil_moist.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_HEAT
#include "ctrl_temp_heat/ctrl_temp_heat.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_VENT
#include "ctrl_temp_vent/ctrl_temp_vent.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_CAN_STEER
#include "ctrl_can_steer/ctrl_can_steer.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
#include "ctrl_wheel_steer/ctrl_wheel_steer.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
#include "ctrl_wheel_tract/ctrl_wheel_tract.h"
#endif
//=============================================================================
// Device Abstraction components
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
#include "dd_water_pump/dd_water_pump.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window.h"
#endif
//=============================================================================
// ECU Abstraction components
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
#include "ed_buzzer/ed_buzzer.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
#include "ed_can_mcp/ed_can_mcp.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
#include "ed_contact/ed_contact.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
#include "ed_dc_esc/ed_dc_esc.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
#include "ed_encoder/ed_encoder.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
#include "ed_l298/ed_l298.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
#include "ed_servo/ed_servo.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
#include "ed_sns_soil_moist/ed_sns_soil_moist.h"
#endif
//=============================================================================
// Platform Services
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
#include "srv_com_can/srv_com_can_signal.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
#include "srv_com_lora/srv_com_lora.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
#include "srv_com_modbus/srv_com_modbus.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
#include "srv_com_mqtt/srv_com_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
#include "srv_control/srv_control.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
#include "srv_heartbeat/srv_heartbeat.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
#include "srv_sns_air_press/srv_sns_air_press.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist.h"
#endif

//-----------------------------------------------------------------------------
#ifdef USE_SRV_SYS_OS_SEQ
#include "srv_sys_os/srv_sys_os_seq.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SYS_OS_FREERTOS
#include "srv_sys_os/srv_sys_os_freertos.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
#include "srv_ui_bt/srv_ui_bt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
#include "srv_ui_lcd/srv_ui_lcd.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#include "srv_ui_serial/srv_ui_serial.h"
#endif
//-----------------------------------------------------------------------------



// Declare any global variables or functions

#endif // ECU_MODULES_H
