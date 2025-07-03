#ifndef CTRL_WHEEL_TRACT_MQTT_H_
#define CTRL_WHEEL_TRACT_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef CTRL_WHEEL_TRACT_MQTT_PUBLISH_TOPIC
#define CTRL_WHEEL_TRACT_MQTT_PUBLISH_TOPIC "MES_Device_Platform/ctrl_wheel_tract"
#endif

#ifndef CTRL_WHEEL_TRACT_MQTT_SUBSCRIBE_TOPIC
#define CTRL_WHEEL_TRACT_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/ctrl_wheel_tract/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void ctrl_wheel_tract_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int ctrl_wheel_tract_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void ctrl_wheel_tract_mqtt_subscribe(PubSubClient &mqttClient);

#endif // CTRL_WHEEL_TRACT_MQTT_H

