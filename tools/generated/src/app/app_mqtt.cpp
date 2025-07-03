#include "app_mqtt.h"
#include "app.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char app_mqtt_subscribe_topic[] = APP_MQTT_SUBSCRIBE_TOPIC;
char app_mqtt_publish_topic[] = APP_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to app MQTT topic
void app_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_APP

  Serial.println(F("APP_MQTT: app_mqtt_subscribe"));

  if (mqttClient.subscribe(app_mqtt_subscribe_topic))
  {
    Serial.print(F("APP_MQTT: Subscribed to: "));
    Serial.println(app_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("APP_MQTT: Failed to subscribe to: "));
    Serial.println(app_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish app Data to MQTT
void app_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_APP

  Serial.println(F("APP_MQTT: app_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 101;
  doc_out["unit_name"] = "app";
  doc_out["cur_hum"] = app_get_current_hum();
  doc_out["set_point"] = app_get_setpoint();
  doc_out["ctrl_mode"] = app_get_mode();
  doc_out["ctrl_out"] = app_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(app_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// app MQTT Callback
int app_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_APP

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, app_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("APP_MQTT: app_mqtt_callback"));
    // Serial.print(F("APP_MQTT: Received message on topic: "));
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
      app_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == APP_DISABLE)
      {
        app_set_mode_manual();
      }
      else if (mode == APP_ENABLE)
      {
        app_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == APP_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_APP_ID);
      }
      else if (out == APP_OUT_ON)
      {
        dd_valve_on(DD_VALVE_APP_ID, APP_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("APP_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

