#ifndef ECU_CONFIG_H_
#define ECU_CONFIG_H_

#define SYS_TICK (10.0) // ms

#define TIME_mSEC 1
#define TIME_SEC (1000 * TIME_mSEC)
#define TIME_MIN (60 * TIME_SEC)
#define TIME_HOUR (60 * TIME_MIN)
#define TIME_DAY (24 * TIMTIME_HOURE_MIN)

//=============================================================================
// posible configurations for ECU

#define ECU_ALL 0

//------------------------------------------------
// Greeenhouse configuration
#define ECU_CTRL_GREEN_HOUSE  100
#define ECU_CTRL_AIR_TEMP_VENT    101
#define ECU_CTRL_AIR_TEMP_HEAT    102
#define ECU_CTRL_AIR_HUM      103
#define ECU_CTRL_SOIL_MOIST   104
#define ECU_CTRL_AIR_PRESS    105
#define ECU_CTRL_LIGHT        106




#define ECU_TST 7
//------------------------------------------------
// Vehicle ECU COnfiguration set
#define ECU_UI_LCD 8
#define ECU_UI_BLUETOOTH 9
#define ECU_STEERING 10
#define ECU_TRACTION 11
#define ECU_OMNIWHEEL 12
#define ECU_AGROBOT_ATV 13

#define ECU_STEER_HB 14


#define ECU_HEARTBEAT 999
#define ECU_CTRL_NONE 1000

#define ECU_STATUS_ON 1
#define ECU_STATUS_OFF 0






// #define ECU_CONFIG ECU_TST

// #define ECU_CONFIG ECU_UI_BLUETOOTH
// #define ECU_CONFIG ECU_UI_LCD
// #define ECU_CONFIG ECU_TRACTION
// #define ECU_CONFIG ECU_STEERING

// #define ECU_CONFIG ECU_OMNIWHEEL
// #define ECU_CONFIG ECU_AGROBOT_ATV


#define CAN_ID_BUZZER   0x111
#define CAN_ID_JOYSTICK 0x222
#define CAN_ID_UI_BT    0x055
#define CAN_ID_UI_BT_CHASSIS    0x077
// to implement a claim mechanism on can
// when many ecu reports the same message



//==============================================================================
// Select configuration for ECU HERE !!
#define ECU_CONFIG ECU_CTRL_GREEN_HOUSE  // <--- HERE
//==============================================================================

#if ECU_CONFIG == ECU_ALL

#define USE_SRV_UI_SERIAL

#elif ECU_CONFIG == ECU_CTRL_GREEN_HOUSE

#include "ecu_config_green_house_ctrl.h"

#elif ECU_CONFIG == ECU_CTRL_AIR_TEMP_VENT

#include "ecu_config_gh_ctrl_air_temp_vent.h"

#elif ECU_CONFIG == ECU_CTRL_AIR_TEMP_HEAT

#include "ecu_config_ctrl_air_temp_heat.h"

#elif ECU_CONFIG == ECU_CTRL_LIGHT

#include "ecu_config_gh_ctrl_amb_light.h"

#elif ECU_CONFIG == ECU_CTRL_AIR_PRESS

#include "ecu_config_gh_ctrl_air_press.h"

#elif ECU_CONFIG == ECU_CTRL_SOIL_MOIST

#include "ecu_config_gh_ctrl_soil_moist.h"

#elif ECU_CONFIG == ECU_CTRL_AIR_HUM

#include "ecu_config_gh_ctrl_air_hum.h"

#elif ECU_CONFIG == ECU_CTRL_NONE

#include "ecu_config_none.h"
#elif ECU_CONFIG == ECU_HEARTBEAT

#define USE_SRV_UI_SERIAL
#define SRV_UI_SERIAL_BAUDRATE 115200
#define USE_SRV_HEARTBEAT
#define USE_SRV_SYS_OS_SEQ
#define SRV_HEARTBEAT_LED_PIN LED_BUILTIN

#elif ECU_CONFIG == ECU_TST 

#define USE_SRV_UI_SERIAL 
#define USE_DC_MOTOR
#define USE_DD_JOYSTICK
#define USE_ED_BUZZER
#define USE_ED_CAN_MCP
#define USE_ED_ESC
#define USE_ED_ENCODER
#define USE_ED_L298
#define USE_SRV_COM_CAN
#define USE_SRV_CONTROL
#define USE_SRV_UI_BT
#define USE_SRV_UI_LCD
#define USE_CTRL_WHEEL_TRACT


#define TX_CAN_ID_NR_OF 4
#define TX_CAN_ID_LIST {CAN_ID_BUZZER, CAN_ID_JOYSTICK, CAN_ID_UI_BT, CAN_ID_UI_BT_CHASSIS}
#define RX_CAN_ID_NR_OF 5
#define RX_CAN_ID_LIST {CAN_ID_JOYSTICK, CAN_ID_BUZZER, CAN_ID_UI_BT, CAN_ID_UI_BT_CHASSIS, CAN_ID_STEER_HB}

#elif ECU_CONFIG == ECU_UI_LCD

#include "ecu_config_ui_lcd.h"

#elif ECU_CONFIG == ECU_UI_BLUETOOTH

#include "ecu_config_ui_bt.h"

#elif ECU_CONFIG == ECU_STEERING        

#include "ecu_config_steering.h"

#elif ECU_CONFIG == ECU_TRACTION        

#include "ecu_config_traction.h"

#elif ECU_CONFIG == ECU_OMNIWHEEL        

#include "ecu_config_omniwheel.h"

#elif ECU_CONFIG == ECU_AGROBOT_ATV

#include "ecu_config_agrobot.h"

#elif ECU_CONFIG == ECU_STEER_HB

#include "ecu_config_can_steer.h"

#endif



// BUZZER ECU CONFIG
#define ED_BUZZER_PIN A6

// CAN MCP ECU CONFIG
// #define CAN0_INT 2 // Set INT to pin 2
// #define CAN0_CS 10 // Set CS to pin 2




#endif