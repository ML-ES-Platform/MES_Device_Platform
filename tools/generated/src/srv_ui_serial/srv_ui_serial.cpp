#include "Arduino.h"
#include "ecu_config.h"
#include "ecu_modules.h"
#include "srv_com_mqtt.h"

#ifndef SRV_UI_SERIAL_BAUDRATE
#define SRV_UI_SERIAL_BAUDRATE 115200
#endif

//-----------------------------------------------
// include Control components reports
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_hum/ctrl_air_hum_term.h"
#endif
#ifdef USE_CTRL_AIR_PRESS
#include "ctrl_air_press/ctrl_air_press_term.h"
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
#include "ctrl_air_temp_heat/ctrl_air_temp_heat_term.h"
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
#include "ctrl_air_temp_vent/ctrl_air_temp_vent_term.h"
#endif
#ifdef USE_CTRL_AMB_LIGHT
#include "ctrl_amb_light/ctrl_amb_light_term.h"
#endif
#ifdef USE_CTRL_CAN_STEER
#include "ctrl_can_steer/ctrl_can_steer_term.h"
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
#include "ctrl_servo_adc_dc/ctrl_servo_adc_dc_term.h"
#endif
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moist/ctrl_soil_moist_term.h"
#endif
#ifdef USE_CTRL_WHEEL_STEER
#include "ctrl_wheel_steer/ctrl_wheel_steer_term.h"
#endif
#ifdef USE_CTRL_WHEEL_TRACT
#include "ctrl_wheel_tract/ctrl_wheel_tract_term.h"
#endif

//-----------------------------------------------
// include Sensor components reports
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
#include "srv_sns_air_press/srv_sns_air_press_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp_term.h"
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light_term.h"
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist_term.h"
#endif

//-----------------------------------------------
// include device drivers components reports
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump_term.h"
#endif
#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor_term.h"
#endif
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater_term.h"
#endif
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick_term.h"
#endif
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights_term.h"
#endif
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve_term.h"
#endif
#ifdef USE_DD_WATER_PUMP
#include "dd_water_pump/dd_water_pump_term.h"
#endif
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window_term.h"
#endif

//-----------------------------------------------
// include ECU components reports
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750_term.h"
#endif
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp_term.h"
#endif
#ifdef USE_ED_BUZZER
#include "ed_buzzer/ed_buzzer_term.h"
#endif
#ifdef USE_ED_CAN_MCP
#include "ed_can_mcp/ed_can_mcp_term.h"
#endif
#ifdef USE_ED_CONTACT
#include "ed_contact/ed_contact_term.h"
#endif
#ifdef USE_ED_DC_ESC
#include "ed_dc_esc/ed_dc_esc_term.h"
#endif
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht_term.h"
#endif
#ifdef USE_ED_ENCODER
#include "ed_encoder/ed_encoder_term.h"
#endif
#ifdef USE_ED_L298
#include "ed_l298/ed_l298_term.h"
#endif
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay_term.h"
#endif
#ifdef USE_ED_SERVO
#include "ed_servo/ed_servo_term.h"
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
#include "ed_sns_soil_moist/ed_sns_soil_moist_term.h"
#endif

//-----------------------------------------------
// setup serial service
void srv_ui_serial_setup()
{
      Serial.begin(SRV_UI_SERIAL_BAUDRATE);
      Serial.println(F("SRV_SERIAL: Device System started"));
}

//-----------------------------------------------
// process command for green house
void srv_ui_serial_in_green_house(char cmd)
{
#if defined USE_CTRL_AIR_TEMP_VENT
      ctrl_air_temp_vent_term_cmd(cmd);
#elif defined USE_DD_WINDOW
      dd_window_term_cmd(cmd);
#elif defined USE_ED_RELAY // 1,2
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_AIR_TEMP_HEAT
      ctrl_air_temp_heat_term_cmd(cmd);
#elif defined USE_DD_HEATER
      dd_heater_term_cmd(cmd);
#elif defined USE_ED_RELAY // 3
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_AIR_HUM
      ctrl_air_hum_term_cmd(cmd);
#elif defined USE_DD_VALVE
      dd_valve_term_cmd(cmd);
#elif defined USE_ED_RELAY // 4
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_SOIL_MOIST
      ctrl_soil_moist_term_cmd(cmd);
#elif defined USE_DD_VALVE
      dd_valve_term_cmd(cmd);
#elif defined USE_ED_RELAY // 5
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_AIR_PRESS
      ctrl_air_press_term_cmd(cmd);
#elif defined USE_DD_AIR_PUMP
      dd_air_pump_term_cmd(cmd);
#elif defined USE_ED_RELAY // 6
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_AMB_LIGHT
      ctrl_amb_light_term_cmd(cmd);
#elif defined USE_DD_LIGHTS
      dd_lights_term_cmd(cmd);
#elif defined USE_ED_RELAY // 7
      ed_relay_term_cmd(cmd);
#endif
}

//-----------------------------------------------
// process command for CAN bus
void srv_ui_serial_in_can_steer(char cmd)
{
      // TODO: Implement CAN steering command processing
}

//-----------------------------------------------
// process command for serial input
void srv_ui_serial_in_loop()
{
      if (Serial.available())
      {
            char cmd = Serial.read();
            Serial.print(F("SRV_UI_SERIAL: Recived command: "));
            Serial.println(cmd);
            // Process command for green house
            srv_ui_serial_in_green_house(cmd);
      }
}

//-----------------------------------------------
// report system state
void srv_ui_serial_out_loop()
{
      Serial.println(F("=============== MLP: System Report =============== "));
//-----------------------------------------------
//  Report Control components state
#ifdef USE_CTRL_AIR_HUM
      ctrl_air_hum_report();
#endif
#ifdef USE_CTRL_AIR_PRESS
      ctrl_air_press_report();
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
      ctrl_air_temp_heat_report();
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
      ctrl_air_temp_vent_report();
#endif
#ifdef USE_CTRL_AMB_LIGHT
      ctrl_amb_light_report();
#endif
#ifdef USE_CTRL_CAN_STEER
      ctrl_can_steer_report();
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
      ctrl_servo_adc_dc_report();
#endif
#ifdef USE_CTRL_SOIL_MOIST
      ctrl_soil_moist_report();
#endif
#ifdef USE_CTRL_WHEEL_STEER
      ctrl_wheel_steer_report();
#endif
#ifdef USE_CTRL_WHEEL_TRACT
      ctrl_wheel_tract_report();
#endif

//-----------------------------------------------
//  Report Sensor components state
#ifdef USE_SRV_SNS_AIR_HUM
      srv_sns_air_hum_report();
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
      srv_sns_air_press_report();
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
      srv_sns_air_temp_report();
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
      srv_sns_amb_light_report();
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
      srv_sns_soil_moist_report();
#endif

//-----------------------------------------------
//  Report Can Matrix messages state
#ifdef USE_SRV_COM_CAN
      dd_can_matrix_report();
#endif

//-----------------------------------------------
//  Report Device Drivers components
#ifdef USE_DD_AIR_PUMP
      dd_air_pump_report();
#endif
#ifdef USE_DD_DC_MOTOR
      dd_dc_motor_report();
#endif
#ifdef USE_DD_HEATER
      dd_heater_report();
#endif
#ifdef USE_DD_JOYSTICK
      dd_joystick_report();
#endif
#ifdef USE_DD_LIGHTS
      dd_lights_report();
#endif
#ifdef USE_DD_VALVE
      dd_valve_report();
#endif
#ifdef USE_DD_WATER_PUMP
      dd_water_pump_report();
#endif
#ifdef USE_DD_WINDOW
      dd_window_report();
#endif

//-----------------------------------------------
//  Report ECU components state
#ifdef USE_ED_BH1750
      ed_bh1750_report();
#endif
#ifdef USE_ED_BMP
      ed_bmp_report();
#endif
#ifdef USE_ED_BUZZER
      ed_buzzer_report();
#endif
#ifdef USE_ED_CAN_MCP
      ed_can_mcp_report();
#endif
#ifdef USE_ED_CONTACT
      ed_contact_report();
#endif
#ifdef USE_ED_DC_ESC
      ed_dc_esc_report();
#endif
#ifdef USE_ED_DHT
      ed_dht_report();
#endif
#ifdef USE_ED_ENCODER
      ed_encoder_report();
#endif
#ifdef USE_ED_L298
      ed_l298_report();
#endif
#ifdef USE_ED_RELAY
      ed_relay_report();
#endif
#ifdef USE_ED_SERVO
      ed_servo_report();
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
      ed_sns_soil_moist_report();
#endif

}

