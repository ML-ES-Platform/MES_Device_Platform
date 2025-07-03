#ifndef SRV_CONTROL_MQTT_H_
#define SRV_CONTROL_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef SRV_CONTROL_MQTT_PUBLISH_TOPIC
#define SRV_CONTROL_MQTT_PUBLISH_TOPIC "MES_Device_Platform/srv_control"
#endif

#ifndef SRV_CONTROL_MQTT_SUBSCRIBE_TOPIC
#define SRV_CONTROL_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/srv_control/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void srv_control_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int srv_control_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void srv_control_mqtt_subscribe(PubSubClient &mqttClient);

#endif // SRV_CONTROL_MQTT_H

