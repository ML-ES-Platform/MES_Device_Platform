#include "ed_bmp_mqtt.h"
#include "ed_bmp.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char ed_bmp_mqtt_subscribe_topic[] = ED_BMP_MQTT_SUBSCRIBE_TOPIC;
char ed_bmp_mqtt_publish_topic[] = ED_BMP_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ed_bmp MQTT topic
void ed_bmp_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_ED_BMP

  Serial.println(F("ED_BMP_MQTT: ed_bmp_mqtt_subscribe"));

  if (mqttClient.subscribe(ed_bmp_mqtt_subscribe_topic))
  {
    Serial.print(F("ED_BMP_MQTT: Subscribed to: "));
    Serial.println(ed_bmp_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("ED_BMP_MQTT: Failed to subscribe to: "));
    Serial.println(ed_bmp_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ed_bmp Data to MQTT
void ed_bmp_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_ED_BMP

  Serial.println(F("ED_BMP_MQTT: ed_bmp_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 111;
  doc_out["cur_hum"] = ed_bmp_get_current_hum();
  doc_out["set_point"] = ed_bmp_get_setpoint();
  doc_out["ctrl_mode"] = ed_bmp_get_mode();
  doc_out["ctrl_out"] = ed_bmp_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ed_bmp_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// ed_bmp MQTT Callback
int ed_bmp_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_ED_BMP

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ed_bmp_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("ED_BMP_MQTT: ed_bmp_mqtt_callback"));
    // Serial.print(F("ED_BMP_MQTT: Received message on topic: "));
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
      ed_bmp_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == ED_BMP_DISABLE)
      {
        ed_bmp_set_mode_manual();
      }
      else if (mode == ED_BMP_ENABLE)
      {
        ed_bmp_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == ED_BMP_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_ED_BMP_ID);
      }
      else if (out == ED_BMP_OUT_ON)
      {
        dd_valve_on(DD_VALVE_ED_BMP_ID, ED_BMP_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("ED_BMP_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

