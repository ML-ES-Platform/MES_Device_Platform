#include "test_module_mqtt.h"
#include "test_module.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char test_module_mqtt_subscribe_topic[] = TEST_MODULE_MQTT_SUBSCRIBE_TOPIC;
char test_module_mqtt_publish_topic[] = TEST_MODULE_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to test_module MQTT topic
void test_module_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_TEST_MODULE

  Serial.println(F("TEST_MODULE_MQTT: test_module_mqtt_subscribe"));

  if (mqttClient.subscribe(test_module_mqtt_subscribe_topic))
  {
    Serial.print(F("TEST_MODULE_MQTT: Subscribed to: "));
    Serial.println(test_module_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("TEST_MODULE_MQTT: Failed to subscribe to: "));
    Serial.println(test_module_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish test_module Data to MQTT
void test_module_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_TEST_MODULE

  Serial.println(F("TEST_MODULE_MQTT: test_module_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 146;
  doc_out["unit_name"] = "test_module";
  doc_out["cur_hum"] = test_module_get_current_hum();
  doc_out["set_point"] = test_module_get_setpoint();
  doc_out["ctrl_mode"] = test_module_get_mode();
  doc_out["ctrl_out"] = test_module_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(test_module_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// test_module MQTT Callback
int test_module_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_TEST_MODULE

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, test_module_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("TEST_MODULE_MQTT: test_module_mqtt_callback"));
    // Serial.print(F("TEST_MODULE_MQTT: Received message on topic: "));
    // Serial.println(topic);

    deserializeJson(doc_in, (const byte *)payload, length);

    char cmd[32];
    strlcpy(cmd, doc_in["cmd"] | "default", sizeof(cmd));

    Serial.print(F("Command:"));
    Serial.println(cmd);

    char value[32];
    strlcpy(value, doc_in["value"] | "default", sizeof(value));

    Serial.print(F("Value:"));
    Serial.println(value);

    float value_f = atof(value);
    Serial.print(F("Value_f:"));
    Serial.println(value_f);

    // subscribe message example
    // {
    //   "cmd":"set_point",
    //   "value":"17.3"
    // }

    if (strcmp(cmd, "set_point") == 0)
    {
      test_module_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == TEST_MODULE_DISABLE)
      {
        test_module_set_mode_manual();
      }
      else if (mode == TEST_MODULE_ENABLE)
      {
        test_module_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == TEST_MODULE_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_TEST_MODULE_ID);
      }
      else if (out == TEST_MODULE_OUT_ON)
      {
        dd_valve_on(DD_VALVE_TEST_MODULE_ID, TEST_MODULE_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("TEST_MODULE_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

