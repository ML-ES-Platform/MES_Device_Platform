#ifndef CTRL_SOIL_MOIST_MQTT_H_
#define CTRL_SOIL_MOIST_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef CTRL_SOIL_MOIST_MQTT_PUBLISH_TOPIC
#define CTRL_SOIL_MOIST_MQTT_PUBLISH_TOPIC "MES_Device_Platform/ctrl_soil_moist"
#endif

#ifndef CTRL_SOIL_MOIST_MQTT_SUBSCRIBE_TOPIC
#define CTRL_SOIL_MOIST_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/ctrl_soil_moist/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void ctrl_soil_moist_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int ctrl_soil_moist_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void ctrl_soil_moist_mqtt_subscribe(PubSubClient &mqttClient);

#endif // CTRL_SOIL_MOIST_MQTT_H

