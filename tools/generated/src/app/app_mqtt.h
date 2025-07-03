#ifndef APP_MQTT_H_
#define APP_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef APP_MQTT_PUBLISH_TOPIC
#define APP_MQTT_PUBLISH_TOPIC "MES_Device_Platform/app"
#endif

#ifndef APP_MQTT_SUBSCRIBE_TOPIC
#define APP_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/app/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void app_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int app_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void app_mqtt_subscribe(PubSubClient &mqttClient);

#endif // APP_MQTT_H

