#include "dd_heater_mqtt.h"
#include "dd_heater.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char dd_heater_mqtt_subscribe_topic[] = DD_HEATER_MQTT_SUBSCRIBE_TOPIC;
char dd_heater_mqtt_publish_topic[] = DD_HEATER_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to dd_heater MQTT topic
void dd_heater_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_DD_HEATER

  Serial.println(F("DD_HEATER_MQTT: dd_heater_mqtt_subscribe"));

  if (mqttClient.subscribe(dd_heater_mqtt_subscribe_topic))
  {
    Serial.print(F("DD_HEATER_MQTT: Subscribed to: "));
    Serial.println(dd_heater_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("DD_HEATER_MQTT: Failed to subscribe to: "));
    Serial.println(dd_heater_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish dd_heater Data to MQTT
void dd_heater_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_DD_HEATER

  Serial.println(F("DD_HEATER_MQTT: dd_heater_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 114;
  doc_out["unit_name"] = "dd_heater";
  doc_out["cur_hum"] = dd_heater_get_current_hum();
  doc_out["set_point"] = dd_heater_get_setpoint();
  doc_out["ctrl_mode"] = dd_heater_get_mode();
  doc_out["ctrl_out"] = dd_heater_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(dd_heater_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// dd_heater MQTT Callback
int dd_heater_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_DD_HEATER

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, dd_heater_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("DD_HEATER_MQTT: dd_heater_mqtt_callback"));
    // Serial.print(F("DD_HEATER_MQTT: Received message on topic: "));
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
      dd_heater_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == DD_HEATER_DISABLE)
      {
        dd_heater_set_mode_manual();
      }
      else if (mode == DD_HEATER_ENABLE)
      {
        dd_heater_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == DD_HEATER_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_DD_HEATER_ID);
      }
      else if (out == DD_HEATER_OUT_ON)
      {
        dd_valve_on(DD_VALVE_DD_HEATER_ID, DD_HEATER_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("DD_HEATER_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

