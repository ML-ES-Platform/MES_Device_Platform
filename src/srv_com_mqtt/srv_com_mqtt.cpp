#include <Arduino.h>

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
#ifdef USE_CTRL_SOIL_MOIST
#include "ctrl_soil_moist/ctrl_soil_moist_mqtt.h"
#endif


























// https://github.com/knolleary/pubsubclient/issues/284


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



void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.println("---------------------------XXXXXXXXXXXXXXXXXXXXX----------------------------------------------------------------------");
  Serial.println(F("MQTT Callback "));
  Serial.print(F("Topic:"));
  Serial.println(topic);
  Serial.print(F("Message:"));
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }

  Serial.println();

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
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_mqtt_callback(doc_in, topic, payload, length);
#endif

  Serial.println();
}

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

// subscribe to topic
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
#ifdef USE_CTRL_SOIL_MOIST
      ctrl_soil_moist_mqtt_subscribe(mqttClient);
#endif

    }
  }
}

//==========================================================
// MQTT Callbacks
//==========================================================

// 

void srv_com_mqtt_setup()
{
  // put your setup code here, to run once:
  delay(1000);
  srv_com_mqtt_connectToWiFi();
  wifiClient.setInsecure();
  setupMQTT();
}


void srv_com_mqtt_loop()
{
  // put your main code here, to run repeatedly:

  if (!mqttClient.connected())
    reconnect();

  mqttClient.loop();

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
#ifdef USE_CTRL_SOIL_MOIST
  ctrl_soil_moist_mqtt_publish(doc_out, mqttClient);
#endif


}






// 


