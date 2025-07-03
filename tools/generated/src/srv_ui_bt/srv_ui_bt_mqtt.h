#ifndef SRV_UI_BT_MQTT_H_
#define SRV_UI_BT_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef SRV_UI_BT_MQTT_PUBLISH_TOPIC
#define SRV_UI_BT_MQTT_PUBLISH_TOPIC "MES_Device_Platform/srv_ui_bt"
#endif

#ifndef SRV_UI_BT_MQTT_SUBSCRIBE_TOPIC
#define SRV_UI_BT_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/srv_ui_bt/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void srv_ui_bt_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int srv_ui_bt_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void srv_ui_bt_mqtt_subscribe(PubSubClient &mqttClient);

#endif // SRV_UI_BT_MQTT_H

