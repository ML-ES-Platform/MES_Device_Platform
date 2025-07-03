#include "Arduino.h"
#include "ecu_config.h"
#include "ecu_modules.h"
#include "srv_com_mqtt.h"

#ifndef ESP32
void srv_com_mqtt_setup() {}
void srv_com_mqtt_loop() {}
#else
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#endif
//=============================================================================
// Include MQTT capabilityes of the units
//-----------------------------------------------------------------------------
#ifdef USE_APP
#include "app/app_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_HUM
#include "ctrl_air_hum/ctrl_air_hum_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_PRESS
#include "ctrl_air_press/ctrl_air_press_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_HEAT
#include "ctrl_air_temp_heat/ctrl_air_temp_heat_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AIR_TEMP_VENT
#include "ctrl_air_temp_vent/ctrl_air_temp_vent_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_AMB_LIGHT
#include "ctrl_amb_light/ctrl_amb_light_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_CAN_STEER
#include "ctrl_can_steer/ctrl_can_steer_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SERVO_ADC_DC
#include "ctrl_servo_adc_dc/ctrl_servo_adc_dc_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moist/ctrl_soil_moist_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_STEER
#include "ctrl_wheel_steer/ctrl_wheel_steer_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_CTRL_WHEEL_TRACT
#include "ctrl_wheel_tract/ctrl_wheel_tract_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_AIR_PUMP
#include "dd_air_pump/dd_air_pump_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_DC_MOTOR
#include "dd_dc_motor/dd_dc_motor_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_HEATER
#include "dd_heater/dd_heater_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_JOYSTICK
#include "dd_joystick/dd_joystick_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_LIGHTS
#include "dd_lights/dd_lights_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_VALVE
#include "dd_valve/dd_valve_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WATER_PUMP
#include "dd_water_pump/dd_water_pump_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_DD_WINDOW
#include "dd_window/dd_window_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BH1750
#include "ed_bh1750/ed_bh1750_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BMP
#include "ed_bmp/ed_bmp_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_BUZZER
#include "ed_buzzer/ed_buzzer_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CAN_MCP
#include "ed_can_mcp/ed_can_mcp_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_CONTACT
#include "ed_contact/ed_contact_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DC_ESC
#include "ed_dc_esc/ed_dc_esc_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_DHT
#include "ed_dht/ed_dht_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_ENCODER
#include "ed_encoder/ed_encoder_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_L298
#include "ed_l298/ed_l298_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_RELAY
#include "ed_relay/ed_relay_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SERVO
#include "ed_servo/ed_servo_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_ED_SNS_SOIL_MOIST
#include "ed_sns_soil_moist/ed_sns_soil_moist_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_CAN
#include "srv_com_can/srv_com_can_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_LORA
#include "srv_com_lora/srv_com_lora_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_COM_MODBUS
#include "srv_com_modbus/srv_com_modbus_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_CONTROL
#include "srv_control/srv_control_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_HEARTBEAT
#include "srv_heartbeat/srv_heartbeat_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_HUM
#include "srv_sns_air_hum/srv_sns_air_hum_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_PRESS
#include "srv_sns_air_press/srv_sns_air_press_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AIR_TEMP
#include "srv_sns_air_temp/srv_sns_air_temp_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_AMB_LIGHT
#include "srv_sns_amb_light/srv_sns_amb_light_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_SNS_SOIL_MOIST
#include "srv_sns_soil_moist/srv_sns_soil_moist_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_BT
#include "srv_ui_bt/srv_ui_bt_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_LCD
#include "srv_ui_lcd/srv_ui_lcd_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_SRV_UI_SERIAL
#include "srv_ui_serial/srv_ui_serial_mqtt.h"
#endif
//-----------------------------------------------------------------------------
#ifdef USE_TEST_MODULE
#include "test_module/test_module_mqtt.h"
#endif
//-----------------------------------------------------------------------------

//=============================================================================
// Function declarations
//-----------------------------------------------------------------------------
void srv_com_mqtt_connectToWiFi();
void callback(char *topic, byte *payload, unsigned int length);
void publishMessage(int data);
void setupMQTT();
void reconnect();

//=============================================================================
// WiFi and MQTT configuration
//-----------------------------------------------------------------------------
#include "iot_crt.h"

// WiFi access point
#define WIFI_AP_NAME "Galaxy Fold4DBB3"
// WiFi password
#define WIFI_PASSWORD "the8time"
// #define WIFI_PASSWORD       "A3KBuSpq"

// const char *SSID = WIFI_AP_NAME;
// const char *PWD = "the8time";
const char SSID[] = "FabLab-FREE";
const char PWD[] = "";
// MQTT Broker
DynamicJsonDocument doc_out(1024);
DynamicJsonDocument doc_in(1024);
WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);
// char mqttServer[] = "9b7b323ee67e46d18f9317162c8e8841.s1.eu.hivemq.cloud";
char mqttServer[] = "d5e3702cf49544dc93dafafff5bfa7e1.s1.eu.hivemq.cloud";
// char mqtt_username[] = "sergiu.doncila";
char mqtt_username[] = "hivemq.webclient.1744459053013";
// char mqtt_password[] = "QWEasd!@#123";
char mqtt_password[] = "OT9.57Iu0USfg!x&C,im";
int mqttPort = 8883;
long last_time = 0;
char data[10];

//=============================================================================
// Function definitions
//-----------------------------------------------------------------------------
void srv_com_mqtt_connectToWiFi()
{
  Serial.print(F("Connecting to WiFi "));
  WiFi.begin(SSID, PWD);
  Serial.print(F("SSID: "));
  Serial.println(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(F("Connected to WiFi"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
}

void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(callback);
}

//=============================================================================
// MQTT callback function 
// This function is called when a message is received on a subscribed topic)
//-----------------------------------------------------------------------------
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println(F("MQTT Callback "));
  Serial.print(F("Topic:"));
  Serial.println(topic);

  Serial.println(F("Message:"));
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();


#ifdef USE_APP
  app_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
  ctrl_air_temp_heat_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
  ctrl_air_temp_vent_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_AMB_LIGHT
  ctrl_amb_light_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_CAN_STEER
  ctrl_can_steer_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
  ctrl_servo_adc_dc_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_WHEEL_STEER
  ctrl_wheel_steer_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_CTRL_WHEEL_TRACT
  ctrl_wheel_tract_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_AIR_PUMP
  dd_air_pump_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_DC_MOTOR
  dd_dc_motor_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_HEATER
  dd_heater_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_JOYSTICK
  dd_joystick_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_VALVE
  dd_valve_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_WATER_PUMP
  dd_water_pump_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_DD_WINDOW
  dd_window_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_BH1750
  ed_bh1750_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_BMP
  ed_bmp_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_BUZZER
  ed_buzzer_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_CAN_MCP
  ed_can_mcp_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_CONTACT
  ed_contact_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_DC_ESC
  ed_dc_esc_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_DHT
  ed_dht_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_ENCODER
  ed_encoder_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_L298
  ed_l298_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_RELAY
  ed_relay_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_SERVO
  ed_servo_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
  ed_sns_soil_moist_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_COM_CAN
  srv_com_can_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_COM_LORA
  srv_com_lora_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_COM_MODBUS
  srv_com_modbus_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_CONTROL
  srv_control_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_HEARTBEAT
  srv_heartbeat_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  srv_sns_air_hum_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
  srv_sns_air_press_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
  srv_sns_amb_light_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
  srv_sns_soil_moist_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_UI_BT
  srv_ui_bt_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_UI_LCD
  srv_ui_lcd_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_mqtt_callback(doc_in, topic, payload, length);
#endif
#ifdef USE_TEST_MODULE
  test_module_mqtt_callback(doc_in, topic, payload, length);
#endif

}
//============================================================================= 
// MQTT reconnect function 
/ This function attempts to reconnect to the MQTT broker if the connection is lost 
//-----------------------------------------------------------------------------
void reconnect()
{
  Serial.println(F("Connecting to MQTT Broker..."));
  while (!mqttClient.connected())
  {
    Serial.print(F("Actual state: "));
    Serial.println(mqttClient.state());
    Serial.println(F("Reconnecting to MQTT Broker.."));
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str(), mqtt_username, mqtt_password))
    {
      Serial.println(F("Connected to MQTT broker.----------------------------------"));
#ifdef USE_APP
      app_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_AIR_HUM
      ctrl_air_hum_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_AIR_PRESS
      ctrl_air_press_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
      ctrl_air_temp_heat_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
      ctrl_air_temp_vent_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_AMB_LIGHT
      ctrl_amb_light_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_CAN_STEER
      ctrl_can_steer_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
      ctrl_servo_adc_dc_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_SOIL_MOIST
      ctrl_soil_moist_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_WHEEL_STEER
      ctrl_wheel_steer_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_CTRL_WHEEL_TRACT
      ctrl_wheel_tract_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_AIR_PUMP
      dd_air_pump_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_DC_MOTOR
      dd_dc_motor_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_HEATER
      dd_heater_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_JOYSTICK
      dd_joystick_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_LIGHTS
      dd_lights_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_VALVE
      dd_valve_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_WATER_PUMP
      dd_water_pump_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_DD_WINDOW
      dd_window_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_BH1750
      ed_bh1750_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_BMP
      ed_bmp_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_BUZZER
      ed_buzzer_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_CAN_MCP
      ed_can_mcp_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_CONTACT
      ed_contact_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_DC_ESC
      ed_dc_esc_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_DHT
      ed_dht_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_ENCODER
      ed_encoder_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_L298
      ed_l298_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_RELAY
      ed_relay_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_SERVO
      ed_servo_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
      ed_sns_soil_moist_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_COM_CAN
      srv_com_can_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_COM_LORA
      srv_com_lora_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_COM_MODBUS
      srv_com_modbus_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_CONTROL
      srv_control_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_HEARTBEAT
      srv_heartbeat_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_HUM
      srv_sns_air_hum_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
      srv_sns_air_press_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
      srv_sns_air_temp_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
      srv_sns_amb_light_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
      srv_sns_soil_moist_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_UI_BT
      srv_ui_bt_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_UI_LCD
      srv_ui_lcd_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_SRV_UI_SERIAL
      srv_ui_serial_mqtt_subscribe(mqttClient);
#endif
#ifdef USE_TEST_MODULE
      test_module_mqtt_subscribe(mqttClient);
#endif
//======================================================================
// MQTT setup function
//----------------------------------------------------------------------
void srv_com_mqtt_setup()
{
  // put your setup code here, to run once:
  delay(1000);
  srv_com_mqtt_connectToWiFi();
  wifiClient.setInsecure();
  setupMQTT();

}

#ifdef USE_APP
app_setup();
#endif
#ifdef USE_CTRL_AIR_HUM
ctrl_air_hum_setup();
#endif
#ifdef USE_CTRL_AIR_PRESS
ctrl_air_press_setup();
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
ctrl_air_temp_heat_setup();
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
ctrl_air_temp_vent_setup();
#endif
#ifdef USE_CTRL_AMB_LIGHT
ctrl_amb_light_setup();
#endif
#ifdef USE_CTRL_CAN_STEER
ctrl_can_steer_setup();
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
ctrl_servo_adc_dc_setup();
#endif
#ifdef USE_CTRL_SOIL_MOIST
ctrl_soil_moist_setup();
#endif
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
#ifdef USE_DD_WATER_PUMP
dd_water_pump_setup();
#endif
#ifdef USE_DD_WINDOW
dd_window_setup();
#endif
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
#ifdef USE_SRV_COM_CAN
srv_com_can_setup();
#endif
#ifdef USE_SRV_COM_LORA
srv_com_lora_setup();
#endif
#ifdef USE_SRV_COM_MODBUS
srv_com_modbus_setup();
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
#endif
#ifdef USE_SRV_UI_SERIAL
srv_ui_serial_setup();
#endif
#ifdef USE_TEST_MODULE
test_module_setup();
#endif
}

//=============================================================================
// MQTT loop function
//-----------------------------------------------------------------------------
void srv_com_mqtt_loop()
{
  // put your main code here, to run repeatedly:
  if (!mqttClient.connected())
    reconnect();
  mqttClient.loop();
#ifdef USE_APP
  app_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_AIR_HUM
  ctrl_air_hum_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_AIR_PRESS
  ctrl_air_press_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_AIR_TEMP_HEAT
  ctrl_air_temp_heat_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_AIR_TEMP_VENT
  ctrl_air_temp_vent_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_AMB_LIGHT
  ctrl_amb_light_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_CAN_STEER
  ctrl_can_steer_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_SERVO_ADC_DC
  ctrl_servo_adc_dc_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_WHEEL_STEER
  ctrl_wheel_steer_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_CTRL_WHEEL_TRACT
  ctrl_wheel_tract_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_AIR_PUMP
  dd_air_pump_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_DC_MOTOR
  dd_dc_motor_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_HEATER
  dd_heater_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_JOYSTICK
  dd_joystick_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_LIGHTS
  dd_lights_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_VALVE
  dd_valve_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_WATER_PUMP
  dd_water_pump_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_DD_WINDOW
  dd_window_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_BH1750
  ed_bh1750_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_BMP
  ed_bmp_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_BUZZER
  ed_buzzer_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_CAN_MCP
  ed_can_mcp_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_CONTACT
  ed_contact_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_DC_ESC
  ed_dc_esc_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_DHT
  ed_dht_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_ENCODER
  ed_encoder_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_L298
  ed_l298_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_RELAY
  ed_relay_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_SERVO
  ed_servo_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_ED_SNS_SOIL_MOIST
  ed_sns_soil_moist_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_COM_CAN
  srv_com_can_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_COM_LORA
  srv_com_lora_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_COM_MODBUS
  srv_com_modbus_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_CONTROL
  srv_control_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_HEARTBEAT
  srv_heartbeat_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_HUM
  srv_sns_air_hum_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_PRESS
  srv_sns_air_press_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_SNS_AIR_TEMP
  srv_sns_air_temp_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_SNS_AMB_LIGHT
  srv_sns_amb_light_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_SNS_SOIL_MOIST
  srv_sns_soil_moist_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_UI_BT
  srv_ui_bt_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_UI_LCD
  srv_ui_lcd_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_SRV_UI_SERIAL
  srv_ui_serial_mqtt_publish(doc_out, mqttClient);
#endif
#ifdef USE_TEST_MODULE
  test_module_mqtt_publish(doc_out, mqttClient);
#endif

}
