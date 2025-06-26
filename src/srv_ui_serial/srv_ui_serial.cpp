#include "Arduino.h"

#include "srv_ui_serial.h"

#include "ecu_config.h"
#include "ecu_modules.h"

#ifndef SRV_UI_SERIAL_BAUDRATE
#define SRV_UI_SERIAL_BAUDRATE 115200
#endif
//-----------------------------------------------
// include Control components reports
#ifdef USE_CTRL_TEMP_HEAT
#include "ctrl_temp_heat/ctrl_temp_heat_term.h"
#endif
#ifdef USE_CTRL_TEMP_VENT
#include "ctrl_temp_vent/ctrl_temp_vent_term.h"
#endif
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_hum/ctrl_air_hum_term.h"
#endif
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moist/ctrl_soil_moist_term.h"
#endif
#ifdef USE_CTRL_AIR_PRESS
#include "ctrl_air_press/ctrl_air_press_term.h"
#endif
#ifdef USE_CTRL_LIGHTS
#include "ctrl_lights/ctrl_lights_term.h"
#endif

//-----------------------------------------------
// include Sensor components reports
#ifdef USE_SRV_SNS_AIR_PRESS
#include "srv_sns_air_press/srv_sns_air_press_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp_term.h"
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist_term.h"
#endif
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum_term.h"
#endif
#ifdef USE_SRV_SNS_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light_term.h"
#endif

//-----------------------------------------------
// include Actuator components reports
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window_term.h"
#endif
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater_term.h"
#endif
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve_term.h"
#endif
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump_term.h"
#endif
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights_term.h"
#endif

//-----------------------------------------------
// include ECU report components
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht_term.h"
#endif
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp_term.h"
#endif
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750_term.h"
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
#include "ed_sns_soil_moist/ed_sns_soil_moist_term.h"
#endif
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay_term.h"
#endif

void srv_ui_serial_setup()
{
      Serial.begin(SRV_UI_SERIAL_BAUDRATE);
      Serial.println(F("SRV_SERIAL: Device System started"));
}

void srv_ui_serial_in_green_house(char cmd)
{

#if defined USE_CTRL_TEMP_VENT
      ctrl_temp_vent_term_cmd(cmd);
#elif defined USE_DD_WINDOW
      dd_window_term_cmd(cmd);
#elif defined USE_ED_RELAY // 1,2
      ed_relay_term_cmd(cmd);
#endif

#if defined USE_CTRL_TEMP_HEAT
      ctrl_temp_heat_term_cmd(cmd);
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

#if defined USE_CTRL_LIGHTS
      ctrl_lights_term_cmd(cmd);
#elif defined USE_DD_LIGHTS
      dd_lights_term_cmd(cmd);
#elif defined USE_ED_RELAY // 7
      ed_relay_term_cmd(cmd);
#endif
}

void srv_ui_serial_in_can_steer(char cmd)
{
}

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

void srv_ui_serial_out_loop()
{
      Serial.println(F("=============== MLP: System Report =============== "));

//-----------------------------------------------
//  Report Control components state
#ifdef USE_CTRL_TEMP_VENT
      ctrl_temp_vent_report();
#endif
#ifdef USE_CTRL_TEMP_HEAT
      ctrl_temp_heat_report();
#endif
#ifdef USE_CTRL_AIR_HUM
      ctrl_air_hum_report();
#endif
#ifdef USE_CTRL_SOIL_MOIST
      ctrl_soil_moist_report();
#endif
#ifdef USE_CTRL_AIR_PRESS
      ctrl_air_press_report();
#endif
#ifdef USE_CTRL_LIGHTS
      ctrl_lights_report();
#endif

//-----------------------------------------------
//  Report Sensor components state
#ifdef USE_SRV_SNS_AIR_TEMP
      srv_sns_air_temp_report();
#endif
#ifdef USE_SRV_SNS_AIR_HUM
      srv_sns_air_hum_report();
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
      srv_sns_soil_moist_report();
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
      srv_sns_air_press_report();
#endif
#ifdef USE_SRV_SNS_LIGHT
      srv_sns_light_report();
#endif

// initialize services
#ifdef USE_SRV_COM_CAN
      dd_can_matrix_report();
// dd_can_signal_setup();
#endif
//-----------------------------------------------
//  Report Actuator components state
#ifdef USE_DD_WINDOW
      dd_window_report();
#endif
#ifdef USE_DD_HEATER
      dd_heater_report();
#endif
#ifdef USE_DD_VALVE
      dd_valve_report();
#endif
#ifdef USE_DD_AIR_PUMP
      dd_air_pump_report();
#endif
#ifdef USE_DD_LIGHTS
      dd_lights_report();
#endif

//-----------------------------------------------
//  Report ECU components state
#ifdef USE_ED_DHT
      ed_dht_report();
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
      ed_sns_soil_moist_report();
#endif
#ifdef USE_ED_BMP
      ed_bmp_report();
#endif
#ifdef USE_ED_BH1750
      ed_bh1750_report();
#endif

#ifdef USE_ED_RELAY
      ed_relay_report();
#endif

      Serial.println();
}
