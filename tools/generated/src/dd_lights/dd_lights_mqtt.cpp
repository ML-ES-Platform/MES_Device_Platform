#include "dd_lights_mqtt.h"
#include "dd_lights.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char dd_lights_mqtt_subscribe_topic[] = DD_LIGHTS_MQTT_SUBSCRIBE_TOPIC;
char dd_lights_mqtt_publish_topic[] = DD_LIGHTS_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to dd_lights MQTT topic
void dd_lights_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_DD_LIGHTS

  Serial.println(F("DD_LIGHTS_MQTT: dd_lights_mqtt_subscribe"));

  if (mqttClient.subscribe(dd_lights_mqtt_subscribe_topic))
  {
    Serial.print(F("DD_LIGHTS_MQTT: Subscribed to: "));
    Serial.println(dd_lights_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("DD_LIGHTS_MQTT: Failed to subscribe to: "));
    Serial.println(dd_lights_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish dd_lights Data to MQTT
void dd_lights_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_DD_LIGHTS

  Serial.println(F("DD_LIGHTS_MQTT: dd_lights_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 111;
  doc_out["cur_hum"] = dd_lights_get_current_hum();
  doc_out["set_point"] = dd_lights_get_setpoint();
  doc_out["ctrl_mode"] = dd_lights_get_mode();
  doc_out["ctrl_out"] = dd_lights_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(dd_lights_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// dd_lights MQTT Callback
int dd_lights_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_DD_LIGHTS

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, dd_lights_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("DD_LIGHTS_MQTT: dd_lights_mqtt_callback"));
    // Serial.print(F("DD_LIGHTS_MQTT: Received message on topic: "));
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
      dd_lights_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == DD_LIGHTS_DISABLE)
      {
        dd_lights_set_mode_manual();
      }
      else if (mode == DD_LIGHTS_ENABLE)
      {
        dd_lights_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == DD_LIGHTS_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_DD_LIGHTS_ID);
      }
      else if (out == DD_LIGHTS_OUT_ON)
      {
        dd_valve_on(DD_VALVE_DD_LIGHTS_ID, DD_LIGHTS_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("DD_LIGHTS_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

