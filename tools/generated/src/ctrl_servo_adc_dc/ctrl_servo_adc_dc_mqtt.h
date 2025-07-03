#ifndef CTRL_SERVO_ADC_DC_MQTT_H_
#define CTRL_SERVO_ADC_DC_MQTT_H_

#include "ecu_config.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#ifndef CTRL_SERVO_ADC_DC_MQTT_PUBLISH_TOPIC
#define CTRL_SERVO_ADC_DC_MQTT_PUBLISH_TOPIC "MES_Device_Platform/ctrl_servo_adc_dc"
#endif

#ifndef CTRL_SERVO_ADC_DC_MQTT_SUBSCRIBE_TOPIC
#define CTRL_SERVO_ADC_DC_MQTT_SUBSCRIBE_TOPIC "MES_Device_Platform/ctrl_servo_adc_dc/set"
#endif

// Include any necessary libraries here

// Define any constants or macros here

// Declare any function prototypes here

void ctrl_servo_adc_dc_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient);
int ctrl_servo_adc_dc_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length);
void ctrl_servo_adc_dc_mqtt_subscribe(PubSubClient &mqttClient);

#endif // CTRL_SERVO_ADC_DC_MQTT_H

