#include "srv_sys_os_seq.h"
#include "ecu_modules.h"

#include "Arduino.h"
void srv_sys_os_seq_setup_isr();


//=============================================================================
// Task Scheduling definitions
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_HUM
int ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
int ctrl_air_press_rec_cnt = CTRL_AIR_PRESS_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_LIGHTS
int ctrl_lights_rec_cnt = CTRL_LIGHTS_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
int ctrl_servo_adc_dc_rec_cnt = CTRL_SERVO_ADC_DC_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
int ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_HEAT
int ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_TEMP_VENT
int ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
int ctrl_wheel_steer_rec_cnt = CTRL_WHEEL_STEER_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
int ctrl_wheel_tract_rec_cnt = CTRL_WHEEL_TRACT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
int dd_air_pump_rec_cnt = DD_AIR_PUMP_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
int dd_dc_motor_rec_cnt = DD_DC_MOTOR_REC + 5;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
int dd_heater_rec_cnt = DD_HEATER_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
int dd_joystick_rec_cnt = DD_JOYSTICK_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
int dd_lights_rec_cnt = DD_LIGHTS_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
int dd_valve_rec_cnt = DD_VALVE_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
int dd_water_pump_rec_cnt = DD_WATER_PUMP_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
int dd_window_rec_cnt = DD_WINDOW_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
int ed_bh1750_rec_cnt = ED_BH1750_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
int ed_bmp_rec_cnt = ED_BMP_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
int ed_buzzer_rec_cnt = ED_BUZZER_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
int ed_can_mcp_rec_cnt = ED_CAN_MCP_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
int ed_contact_rec_cnt = ED_CONTACT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
int ed_dc_esc_rec_cnt = ED_DC_ESC_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
int ed_dht_rec_cnt = ED_DHT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
int ed_encoder_rec_cnt = ED_ENCODER_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
int ed_l298_rec_cnt = ED_L298_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
int ed_relay_rec_cnt = ED_RELAY_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
int ed_servo_rec_cnt = ED_SERVO_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
int ed_sns_soil_moist_rec_cnt = ED_SNS_SOIL_MOIST_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
int srv_com_can_send_rec_cnt = SRV_COM_CAN_SEND_OFFSET;
#endif
#ifdef USE_SRV_COM_CAN
int srv_com_can_recv_rec_cnt = SRV_COM_CAN_RECV_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
int srv_com_lora_rec_cnt = SRV_COM_LORA_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
int srv_com_modbus_rec_cnt = SRV_COM_MODBUS_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MQTT
int srv_com_mqtt_rec_cnt = SRV_COM_MQTT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
int srv_control_rec_cnt = SRV_CONTROL_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
int srv_heartbeat_rec_cnt = SRV_HEARTBEAT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
int srv_sns_air_hum_rec_cnt = SRV_SNS_AIR_HUM_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
int srv_sns_air_press_rec_cnt = SRV_SNS_AIR_PRESS_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
int srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
int srv_sns_amb_light_rec_cnt = SRV_SNS_AMB_LIGHT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
int srv_sns_soil_moist_rec_cnt = SRV_SNS_SOIL_MOIST_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
int srv_ui_bt_rec_cnt = SRV_UI_BT_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
int srv_ui_lcd_rec_cnt = SRV_UI_LCD_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
int srv_ui_serial_in_rec_cnt = SRV_UI_SERIAL_IN_OFFSET;
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
int srv_ui_serial_out_rec_cnt = SRV_UI_SERIAL_OUT_OFFSET;
#endif
//-----------------------------------------------------------------------------
 
void srv_sys_os_seq_setup()
{

#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_setup();
#endif


// initialize control components
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_setup();
#endif
#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_setup();
#endif
#ifdef USE_CTRL_LIGHTS
  ctrl_lights_setup();
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
  ctrl_servo_adc_dc_setup();
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_setup();

#endif
#ifdef USE_CTRL_TEMP_HEAT
  ctrl_temp_heat_setup();
#endif
#ifdef USE_CTRL_TEMP_VENT
  ctrl_temp_vent_setup();
#endif

  // initialize device drivers
#ifdef USE_CTRL_WHEEL_STEER
  ctrl_wheel_steer_setup();
#endif
#ifdef USE_CTRL_WHEEL_TRACT
  ctrl_wheel_tract_setup();
#endif
#ifdef USE_DD_AIR_PUMP
  dd_air_pump_setup();
#endif
#ifdef USE_DD_DC_MOTOR
  dd_dc_motor_setup();
#endif
#ifdef USE_DD_HEATER
  dd_heater_setup();
#endif
#ifdef USE_DD_JOYSTICK
  dd_joystick_setup();
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_setup();
#endif
#ifdef USE_DD_VALVE
  dd_valve_setup();
#endif
#ifdef USE_DD_WINDOW
  dd_window_setup();
#endif

  // Initialize electronic devices
#ifdef USE_ED_BH1750
  ed_bh1750_setup();
#endif
#ifdef USE_ED_BMP
  ed_bmp_setup();
#endif
#ifdef USE_ED_BUZZER
  ed_buzzer_setup();
#endif
#ifdef USE_ED_CAN_MCP
  ed_can_mcp_setup();
#endif
#ifdef USE_ED_CONTACT
  ed_contact_setup();
#endif
#ifdef USE_ED_DC_ESC
  ed_dc_esc_setup();
#endif
#ifdef USE_ED_DHT
  ed_dht_setup();
#endif
#ifdef USE_ED_ENCODER
  ed_encoder_setup();
#endif
#ifdef USE_ED_L298
  ed_l298_setup();
#endif
#ifdef USE_ED_RELAY
  ed_relay_setup();
#endif
#ifdef USE_ED_SERVO
  ed_servo_setup();
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
  ed_sns_soil_moist_setup();
#endif

// initialize services
#ifdef USE_SRV_COM_CAN
  dd_can_matrix_setup();
// dd_can_signal_setup();
#endif
#ifdef USE_SRV_COM_LORA
  srv_com_lora_setup();
#endif
#ifdef USE_SRV_COM_MODBUS
  srv_com_modbus_setup();
#endif
#ifdef USE_SRV_COM_MQTT
  srv_com_mqtt_setup();
#endif
#ifdef USE_SRV_CONTROL
  srv_control_setup();
#endif
#ifdef USE_SRV_HEARTBEAT
  srv_heartbeat_setup();
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  srv_sns_air_hum_setup();
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
  srv_sns_air_press_setup();
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_setup();
  srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_OFFSET;
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
  srv_sns_amb_light_setup();
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
  srv_sns_soil_moist_setup();
#endif
#ifdef USE_SRV_UI_BT
  srv_ui_bt_setup();
#endif
#ifdef USE_SRV_UI_LCD
  srv_ui_lcd_setup();
  srv_ui_lcd_rec_cnt = SRV_UI_LCD_OFFSET;
#endif

 srv_sys_os_seq_setup_isr();

}

void srv_sys_os_seq_scheduler()
{
#ifdef USE_CTRL_AIR_HUM
  // Task for air humidity control
  if (--ctrl_air_hum_rec_cnt <= 0)
  {
    ctrl_air_hum_loop();
    ctrl_air_hum_rec_cnt = CTRL_AIR_HUM_REC;
  }
#endif
#ifdef USE_CTRL_AIR_PRESS
  // Task for pressure control with isolation
  if (--ctrl_air_press_rec_cnt <= 0)
  {
    ctrl_air_press_loop();
    ctrl_air_press_rec_cnt = CTRL_AIR_PRESS_REC;
  }
#endif
#ifdef USE_CTRL_LIGHTS
  // Task for light control
  if (--ctrl_lights_rec_cnt <= 0)
  {
    ctrl_lights_loop();
    ctrl_lights_rec_cnt = CTRL_LIGHTS_REC;
  }
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
  if (--ctrl_servo_adc_dc_rec_cnt <= 0)
  {
    ctrl_servo_adc_dc_loop();
    ctrl_servo_adc_dc_rec_cnt = CTRL_SERVO_ADC_DC_REC;
  }
#endif
#ifdef USE_CTRL_SOIL_MOIST
  // Task for soil moisture control
  if (--ctrl_soil_moist_rec_cnt <= 0)
  {
    ctrl_soil_moist_loop();
    ctrl_soil_moist_rec_cnt = CTRL_SOIL_MOIST_REC;
  }
#endif
#ifdef USE_CTRL_TEMP_HEAT
  // Task for temperature control with heater
  if (--ctrl_temp_heat_rec_cnt <= 0)
  {
    ctrl_temp_heat_loop();
    ctrl_temp_heat_rec_cnt = CTRL_TEMP_HEAT_REC;
  }
#endif
#ifdef USE_CTRL_TEMP_VENT
  // Task for temperature control with ventilation
  if (--ctrl_temp_vent_rec_cnt <= 0)
  {
    ctrl_temp_vent_loop();
    ctrl_temp_vent_rec_cnt = CTRL_TEMP_VENT_REC;
  }
#endif
#ifdef USE_CTRL_WHEEL_STEER
  if (--ctrl_wheel_steer_rec_cnt <= 0)
  {
    ctrl_wheel_steer_loop();
    ctrl_wheel_steer_rec_cnt = CTRL_WHEEL_STEER_REC;
  }
#endif
#ifdef USE_CTRL_WHEEL_TRACT
  if (--ctrl_wheel_tract_rec_cnt <= 0)
  {
    ctrl_wheel_tract_loop();
    ctrl_wheel_tract_rec_cnt = CTRL_WHEEL_TRACT_REC;
  }
#endif
#ifdef USE_DD_AIR_PUMP
  if (--dd_air_pump_rec_cnt <= 0)
  {
    dd_air_pump_loop();
    dd_air_pump_rec_cnt = DD_AIR_PUMP_REC;
  }
#endif
#ifdef USE_DD_DC_MOTOR
  if (--dd_dc_motor_rec_cnt <= 0)
  {
    dd_dc_motor_loop();
    dd_dc_motor_rec_cnt = DD_DC_MOTOR_REC;
  }
#endif
#ifdef USE_DD_HEATER
  // Task for managing the heater
  if (--dd_heater_rec_cnt <= 0)
  {
    dd_heater_loop();
    dd_heater_rec_cnt = DD_HEATER_REC;
  }
#endif
#ifdef USE_DD_JOYSTICK
  if (--dd_joystick_rec_cnt <= 0)
  {
    dd_joystick_loop();
    dd_joystick_rec_cnt = DD_JOYSTICK_REC;
  }
#endif
#ifdef USE_DD_LIGHTS
  // Task for managing the lights
  if (--dd_lights_rec_cnt <= 0)
  {
    dd_lights_loop();
    dd_lights_rec_cnt = DD_LIGHTS_REC;
  }
#endif
#ifdef USE_DD_VALVE
  // Task for managing the valve
  if (--dd_valve_rec_cnt <= 0)
  {
    dd_valve_loop();
    dd_valve_rec_cnt = DD_VALVE_REC;
  }
#endif
#ifdef USE_DD_WINDOW
  // Task for managing the windows
  if (--dd_window_rec_cnt <= 0)
  {
    dd_window_loop();
    dd_window_rec_cnt = DD_WINDOW_REC;
  }
#endif
#ifdef USE_ED_BH1750
  if (--ed_bh1750_rec_cnt <= 0)
  {
    ed_bh1750_loop();
    ed_bh1750_rec_cnt = ED_BH1750_REC;
  }
#endif
#ifdef USE_ED_BMP
  // Task for collecting data from the BMP sensor
  if (--ed_bmp_rec_cnt <= 0)
  {
    ed_bmp_loop();
    ed_bmp_rec_cnt = ED_BMP_REC;
  }
#endif
#ifdef USE_ED_BUZZER
  if (--ed_buzzer_rec_cnt <= 0)
  {
    ed_buzzer_loop();
    ed_buzzer_rec_cnt = ED_BUZZER_REC;
  }
#endif

#ifdef USE_ED_CONTACT
  if (--ed_contact_rec_cnt <= 0)
  {
    ed_contact_loop();
    ed_contact_rec_cnt = ED_CONTACT_REC;
  }
#endif
#ifdef USE_ED_DC_ESC
  if (--ed_dc_esc_rec_cnt <= 0)
  {
    ed_dc_esc_loop();
    ed_dc_esc_rec_cnt = ED_DC_ESC_REC;
  }
#endif
#ifdef USE_ED_DHT
  // Task for collecting data from the DHT11 sensor
  if (--ed_dht_rec_cnt <= 0)
  {
    ed_dht_loop();
    ed_dht_rec_cnt = ED_DHT_REC;
  }
#endif
#ifdef USE_ED_ENCODER
  if (--ed_encoder_rec_cnt <= 0)
  {
    ed_encoder_loop();
    ed_encoder_rec_cnt = ED_ENCODER_REC;
  }
#endif
#ifdef USE_ED_L298
  if (--ed_l298_rec_cnt <= 0)
  {
    ed_l298_loop();
    ed_l298_rec_cnt = ED_L298_REC;
  }
#endif
#ifdef USE_ED_RELAY
  // Task for managing the relay
  if (--ed_relay_rec_cnt <= 0)
  {
    ed_relay_loop();
    ed_relay_rec_cnt = ED_RELAY_REC;
  }
#endif
#ifdef USE_ED_SERVO
  if (--ed_servo_rec_cnt <= 0)
  {
    ed_servo_loop();
    ed_servo_rec_cnt = ED_SERVO_REC;
  }
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
  // Task for collecting data from the soil moisture sensor
  if (--ed_sns_soil_moist_rec_cnt <= 0)
  {
    ed_sns_soil_moist_loop();
    ed_sns_soil_moist_rec_cnt = ED_SNS_SOIL_MOIST_REC;
  }
#endif
#ifdef USE_SRV_COM_CAN
  if (--srv_com_can_send_rec_cnt <= 0)
  { // send data per 100ms
    ed_can_mcp_send_loop();
    srv_com_can_send_rec_cnt = SRV_COM_CAN_SEND_REC;
  }
#endif

#ifdef USE_SRV_COM_CAN
  if (--srv_com_can_recv_rec_cnt <= 0)
  {
    ed_can_mcp_recv_loop();
    dd_can_signal_loop();
    srv_com_can_recv_rec_cnt = SRV_COM_CAN_RECV_REC;
  }
#endif
#ifdef USE_ED_CAN_MCP
  if (--ed_can_mcp_rec_cnt <= 0)
  {
    // ed_can_mcp_loop();
    ed_can_mcp_rec_cnt = ED_CAN_MCP_REC;
  }
#endif
#ifdef USE_SRV_COM_LORA
  if (--srv_com_lora_rec_cnt <= 0)
  {
    srv_com_lora_loop();
    srv_com_lora_rec_cnt = SRV_COM_LORA_REC;
  }
#endif
#ifdef USE_SRV_COM_MODBUS
  if (--srv_com_modbus_rec_cnt <= 0)
  {
    srv_com_modbus_loop();
    srv_com_modbus_rec_cnt = SRV_COM_MODBUS_REC;
  }
#endif
#ifdef USE_SRV_COM_MQTT
  // Task for handling MQTT communication
  if (--srv_com_mqtt_rec_cnt <= 0)
  {
    srv_com_mqtt_loop();
    srv_com_mqtt_rec_cnt = SRV_COM_MQTT_REC;
  }
#endif
#ifdef USE_SRV_CONTROL
  if (--srv_control_rec_cnt <= 0)
  {
    srv_control_loop();
    srv_control_rec_cnt = SRV_CONTROL_REC;
  }
#endif
#ifdef USE_SRV_HEARTBEAT
  // Task for periodic reporting of signals in serial terminal
  if (--srv_heartbeat_rec_cnt <= 0)
  {
    srv_heartbeat_loop();
    srv_heartbeat_rec_cnt = SRV_HEARTBEAT_REC;
  }
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  // Task for collecting data from the air humidity sensor
  if (--srv_sns_air_hum_rec_cnt <= 0)
  {
    srv_sns_air_hum_loop();
    srv_sns_air_hum_rec_cnt = SRV_SNS_AIR_HUM_REC;
  }
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
  if (--srv_sns_air_press_rec_cnt <= 0)
  {
    srv_sns_air_press_loop();
    srv_sns_air_press_rec_cnt = SRV_SNS_AIR_PRESS_REC;
  }
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  // Task for collecting data from the air temperature sensor
  if (--srv_sns_air_temp_rec_cnt <= 0)
  {
    srv_sns_air_temp_loop();
    srv_sns_air_temp_rec_cnt = SRV_SNS_AIR_TEMP_REC;
  }
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
  if (--srv_sns_amb_light_rec_cnt <= 0)
  {
    srv_sns_amb_light_loop();
    srv_sns_amb_light_rec_cnt = SRV_SNS_AMB_LIGHT_REC;
  }
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
  if (--srv_sns_soil_moist_rec_cnt <= 0)
  {
    srv_sns_soil_moist_loop();
    srv_sns_soil_moist_rec_cnt = SRV_SNS_SOIL_MOIST_REC;
  }
#endif
#ifdef USE_SRV_UI_BT
  if (--srv_ui_bt_rec_cnt <= 0)
  {
    srv_ui_bt_loop();
    srv_ui_bt_rec_cnt = SRV_UI_BT_REC;
  }
#endif
#ifdef USE_SRV_UI_LCD
  if (--srv_ui_lcd_rec_cnt <= 0)
  {
    srv_ui_lcd_loop();
    srv_ui_lcd_rec_cnt = SRV_UI_LCD_REC;
  }
#endif
#ifdef USE_SRV_UI_SERIAL
  // Task for periodic reporting of signals in serial terminal
  if (--srv_ui_serial_out_rec_cnt <= 0)
  {
    srv_ui_serial_out_loop();
    srv_ui_serial_out_rec_cnt = SRV_UI_SERIAL_OUT_REC;
  }
#endif
#ifdef USE_SRV_UI_SERIAL
  // Task for reading commands from the serial terminal
  if (--srv_ui_serial_in_rec_cnt <= 0)
  {
    srv_ui_serial_in_loop();
    srv_ui_serial_in_rec_cnt = SRV_UI_SERIAL_IN_REC;
  }
#endif
}

#ifdef ESP32

// #define LED 21
hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR srv_sys_os_seq_scheduler_isr()
{
  // digitalWrite(LED, !digitalRead(LED));
  srv_sys_os_seq_scheduler();
  //   Serial.println(F("OS"));
}

void srv_sys_os_seq_setup_isr()
{
  // pinMode(LED, OUTPUT);
  Timer0_Cfg = timerBegin(0, 80, true);
  timerAttachInterrupt(Timer0_Cfg, &srv_sys_os_seq_scheduler_isr, true);
  timerAlarmWrite(Timer0_Cfg, SYS_TICK, true);
  timerAlarmEnable(Timer0_Cfg);
}

#else

#include <TimerOne.h>
// Interrupt service routine that will be called every 1ms
void srv_sys_os_seq_scheduler_isr()
{
  srv_sys_os_seq_scheduler();
}

void srv_sys_os_seq_setup_isr()
{
  // Initialize Timer1 to trigger an interrupt every 1ms
  Timer1.initialize(1000);
  Timer1.attachInterrupt(srv_sys_os_seq_scheduler_isr);
}
#endif
