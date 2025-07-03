#include "dd_joystick_mqtt.h"
#include "dd_joystick.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char dd_joystick_mqtt_subscribe_topic[] = DD_JOYSTICK_MQTT_SUBSCRIBE_TOPIC;
char dd_joystick_mqtt_publish_topic[] = DD_JOYSTICK_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to dd_joystick MQTT topic
void dd_joystick_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_DD_JOYSTICK

  Serial.println(F("DD_JOYSTICK_MQTT: dd_joystick_mqtt_subscribe"));

  if (mqttClient.subscribe(dd_joystick_mqtt_subscribe_topic))
  {
    Serial.print(F("DD_JOYSTICK_MQTT: Subscribed to: "));
    Serial.println(dd_joystick_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("DD_JOYSTICK_MQTT: Failed to subscribe to: "));
    Serial.println(dd_joystick_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish dd_joystick Data to MQTT
void dd_joystick_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_DD_JOYSTICK

  Serial.println(F("DD_JOYSTICK_MQTT: dd_joystick_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 115;
  doc_out["unit_name"] = "dd_joystick";
  doc_out["cur_hum"] = dd_joystick_get_current_hum();
  doc_out["set_point"] = dd_joystick_get_setpoint();
  doc_out["ctrl_mode"] = dd_joystick_get_mode();
  doc_out["ctrl_out"] = dd_joystick_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(dd_joystick_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// dd_joystick MQTT Callback
int dd_joystick_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_DD_JOYSTICK

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, dd_joystick_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("DD_JOYSTICK_MQTT: dd_joystick_mqtt_callback"));
    // Serial.print(F("DD_JOYSTICK_MQTT: Received message on topic: "));
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
      dd_joystick_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == DD_JOYSTICK_DISABLE)
      {
        dd_joystick_set_mode_manual();
      }
      else if (mode == DD_JOYSTICK_ENABLE)
      {
        dd_joystick_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == DD_JOYSTICK_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_DD_JOYSTICK_ID);
      }
      else if (out == DD_JOYSTICK_OUT_ON)
      {
        dd_valve_on(DD_VALVE_DD_JOYSTICK_ID, DD_JOYSTICK_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("DD_JOYSTICK_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

