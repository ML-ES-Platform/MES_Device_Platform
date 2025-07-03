#ifndef DD_AIR_PUMP_MQTT_H_
#define DD_AIR_PUMP_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef DD_AIR_PUMP_MQTT_PUBLISH_TOPIC
#define DD_AIR_PUMP_MQTT_PUBLISH_TOPIC "MES_Device_Platform/dd_air_pump"
#endif

#ifndef DD_AIR_PUMP_MQTT_SUBSCRIBE_TOPIC
#define DD_AIR_PUMP_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/dd_air_pump/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void dd_air_pump_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int dd_air_pump_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void dd_air_pump_mqtt_subscribe(PubSubClient &mqttClient);

#endif // DD_AIR_PUMP_MQTT_H

