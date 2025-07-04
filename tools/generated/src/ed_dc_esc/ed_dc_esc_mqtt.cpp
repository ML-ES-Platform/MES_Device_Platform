#include "ed_dc_esc_mqtt.h"
#include "ed_dc_esc.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char ed_dc_esc_mqtt_subscribe_topic[] = ED_DC_ESC_MQTT_SUBSCRIBE_TOPIC;
char ed_dc_esc_mqtt_publish_topic[] = ED_DC_ESC_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ed_dc_esc MQTT topic
void ed_dc_esc_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_ED_DC_ESC

  Serial.println(F("ED_DC_ESC_MQTT: ed_dc_esc_mqtt_subscribe"));

  if (mqttClient.subscribe(ed_dc_esc_mqtt_subscribe_topic))
  {
    Serial.print(F("ED_DC_ESC_MQTT: Subscribed to: "));
    Serial.println(ed_dc_esc_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("ED_DC_ESC_MQTT: Failed to subscribe to: "));
    Serial.println(ed_dc_esc_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ed_dc_esc Data to MQTT
void ed_dc_esc_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_ED_DC_ESC

  Serial.println(F("ED_DC_ESC_MQTT: ed_dc_esc_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 125;
  doc_out["unit_name"] = "ed_dc_esc";
  doc_out["cur_hum"] = ed_dc_esc_get_current_hum();
  doc_out["set_point"] = ed_dc_esc_get_setpoint();
  doc_out["ctrl_mode"] = ed_dc_esc_get_mode();
  doc_out["ctrl_out"] = ed_dc_esc_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ed_dc_esc_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// ed_dc_esc MQTT Callback
int ed_dc_esc_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_ED_DC_ESC

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ed_dc_esc_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("ED_DC_ESC_MQTT: ed_dc_esc_mqtt_callback"));
    // Serial.print(F("ED_DC_ESC_MQTT: Received message on topic: "));
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
      ed_dc_esc_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == ED_DC_ESC_DISABLE)
      {
        ed_dc_esc_set_mode_manual();
      }
      else if (mode == ED_DC_ESC_ENABLE)
      {
        ed_dc_esc_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == ED_DC_ESC_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_ED_DC_ESC_ID);
      }
      else if (out == ED_DC_ESC_OUT_ON)
      {
        dd_valve_on(DD_VALVE_ED_DC_ESC_ID, ED_DC_ESC_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("ED_DC_ESC_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

