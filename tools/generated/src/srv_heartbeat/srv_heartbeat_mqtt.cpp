#include "srv_heartbeat_mqtt.h"
#include "srv_heartbeat.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char srv_heartbeat_mqtt_subscribe_topic[] = SRV_HEARTBEAT_MQTT_SUBSCRIBE_TOPIC;
char srv_heartbeat_mqtt_publish_topic[] = SRV_HEARTBEAT_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to srv_heartbeat MQTT topic
void srv_heartbeat_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_SRV_HEARTBEAT

  Serial.println(F("SRV_HEARTBEAT_MQTT: srv_heartbeat_mqtt_subscribe"));

  if (mqttClient.subscribe(srv_heartbeat_mqtt_subscribe_topic))
  {
    Serial.print(F("SRV_HEARTBEAT_MQTT: Subscribed to: "));
    Serial.println(srv_heartbeat_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("SRV_HEARTBEAT_MQTT: Failed to subscribe to: "));
    Serial.println(srv_heartbeat_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish srv_heartbeat Data to MQTT
void srv_heartbeat_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_SRV_HEARTBEAT

  Serial.println(F("SRV_HEARTBEAT_MQTT: srv_heartbeat_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 137;
  doc_out["unit_name"] = "srv_heartbeat";
  doc_out["cur_hum"] = srv_heartbeat_get_current_hum();
  doc_out["set_point"] = srv_heartbeat_get_setpoint();
  doc_out["ctrl_mode"] = srv_heartbeat_get_mode();
  doc_out["ctrl_out"] = srv_heartbeat_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(srv_heartbeat_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// srv_heartbeat MQTT Callback
int srv_heartbeat_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_SRV_HEARTBEAT

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, srv_heartbeat_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("SRV_HEARTBEAT_MQTT: srv_heartbeat_mqtt_callback"));
    // Serial.print(F("SRV_HEARTBEAT_MQTT: Received message on topic: "));
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
      srv_heartbeat_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == SRV_HEARTBEAT_DISABLE)
      {
        srv_heartbeat_set_mode_manual();
      }
      else if (mode == SRV_HEARTBEAT_ENABLE)
      {
        srv_heartbeat_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == SRV_HEARTBEAT_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_SRV_HEARTBEAT_ID);
      }
      else if (out == SRV_HEARTBEAT_OUT_ON)
      {
        dd_valve_on(DD_VALVE_SRV_HEARTBEAT_ID, SRV_HEARTBEAT_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("SRV_HEARTBEAT_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

