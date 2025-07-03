#include "dd_window_mqtt.h"
#include "dd_window.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char dd_window_mqtt_subscribe_topic[] = DD_WINDOW_MQTT_SUBSCRIBE_TOPIC;
char dd_window_mqtt_publish_topic[] = DD_WINDOW_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to dd_window MQTT topic
void dd_window_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_DD_WINDOW

  Serial.println(F("DD_WINDOW_MQTT: dd_window_mqtt_subscribe"));

  if (mqttClient.subscribe(dd_window_mqtt_subscribe_topic))
  {
    Serial.print(F("DD_WINDOW_MQTT: Subscribed to: "));
    Serial.println(dd_window_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("DD_WINDOW_MQTT: Failed to subscribe to: "));
    Serial.println(dd_window_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish dd_window Data to MQTT
void dd_window_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_DD_WINDOW

  Serial.println(F("DD_WINDOW_MQTT: dd_window_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 119;
  doc_out["unit_name"] = "dd_window";
  doc_out["cur_hum"] = dd_window_get_current_hum();
  doc_out["set_point"] = dd_window_get_setpoint();
  doc_out["ctrl_mode"] = dd_window_get_mode();
  doc_out["ctrl_out"] = dd_window_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(dd_window_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// dd_window MQTT Callback
int dd_window_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_DD_WINDOW

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, dd_window_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("DD_WINDOW_MQTT: dd_window_mqtt_callback"));
    // Serial.print(F("DD_WINDOW_MQTT: Received message on topic: "));
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
      dd_window_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == DD_WINDOW_DISABLE)
      {
        dd_window_set_mode_manual();
      }
      else if (mode == DD_WINDOW_ENABLE)
      {
        dd_window_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == DD_WINDOW_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_DD_WINDOW_ID);
      }
      else if (out == DD_WINDOW_OUT_ON)
      {
        dd_valve_on(DD_VALVE_DD_WINDOW_ID, DD_WINDOW_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("DD_WINDOW_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

