#include "ed_bh1750_mqtt.h"
#include "ed_bh1750.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char ed_bh1750_mqtt_subscribe_topic[] = ED_BH1750_MQTT_SUBSCRIBE_TOPIC;
char ed_bh1750_mqtt_publish_topic[] = ED_BH1750_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ed_bh1750 MQTT topic
void ed_bh1750_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_ED_BH1750

  Serial.println(F("ED_BH1750_MQTT: ed_bh1750_mqtt_subscribe"));

  if (mqttClient.subscribe(ed_bh1750_mqtt_subscribe_topic))
  {
    Serial.print(F("ED_BH1750_MQTT: Subscribed to: "));
    Serial.println(ed_bh1750_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("ED_BH1750_MQTT: Failed to subscribe to: "));
    Serial.println(ed_bh1750_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ed_bh1750 Data to MQTT
void ed_bh1750_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_ED_BH1750

  Serial.println(F("ED_BH1750_MQTT: ed_bh1750_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 120;
  doc_out["unit_name"] = "ed_bh1750";
  doc_out["cur_hum"] = ed_bh1750_get_current_hum();
  doc_out["set_point"] = ed_bh1750_get_setpoint();
  doc_out["ctrl_mode"] = ed_bh1750_get_mode();
  doc_out["ctrl_out"] = ed_bh1750_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ed_bh1750_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// ed_bh1750 MQTT Callback
int ed_bh1750_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_ED_BH1750

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ed_bh1750_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("ED_BH1750_MQTT: ed_bh1750_mqtt_callback"));
    // Serial.print(F("ED_BH1750_MQTT: Received message on topic: "));
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
      ed_bh1750_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == ED_BH1750_DISABLE)
      {
        ed_bh1750_set_mode_manual();
      }
      else if (mode == ED_BH1750_ENABLE)
      {
        ed_bh1750_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == ED_BH1750_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_ED_BH1750_ID);
      }
      else if (out == ED_BH1750_OUT_ON)
      {
        dd_valve_on(DD_VALVE_ED_BH1750_ID, ED_BH1750_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("ED_BH1750_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

