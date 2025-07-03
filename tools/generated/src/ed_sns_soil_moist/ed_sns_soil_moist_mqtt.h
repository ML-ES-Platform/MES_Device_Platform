#ifndef ED_SNS_SOIL_MOIST_MQTT_H_
#define ED_SNS_SOIL_MOIST_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef ED_SNS_SOIL_MOIST_MQTT_PUBLISH_TOPIC
#define ED_SNS_SOIL_MOIST_MQTT_PUBLISH_TOPIC "MES_Device_Platform/ed_sns_soil_moist"
#endif

#ifndef ED_SNS_SOIL_MOIST_MQTT_SUBSCRIBE_TOPIC
#define ED_SNS_SOIL_MOIST_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/ed_sns_soil_moist/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void ed_sns_soil_moist_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int ed_sns_soil_moist_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void ed_sns_soil_moist_mqtt_subscribe(PubSubClient &mqttClient);

#endif // ED_SNS_SOIL_MOIST_MQTT_H

