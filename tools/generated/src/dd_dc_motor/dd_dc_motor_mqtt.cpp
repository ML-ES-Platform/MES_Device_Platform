#include "dd_dc_motor_mqtt.h"
#include "dd_dc_motor.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char dd_dc_motor_mqtt_subscribe_topic[] = DD_DC_MOTOR_MQTT_SUBSCRIBE_TOPIC;
char dd_dc_motor_mqtt_publish_topic[] = DD_DC_MOTOR_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to dd_dc_motor MQTT topic
void dd_dc_motor_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_DD_DC_MOTOR

  Serial.println(F("DD_DC_MOTOR_MQTT: dd_dc_motor_mqtt_subscribe"));

  if (mqttClient.subscribe(dd_dc_motor_mqtt_subscribe_topic))
  {
    Serial.print(F("DD_DC_MOTOR_MQTT: Subscribed to: "));
    Serial.println(dd_dc_motor_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("DD_DC_MOTOR_MQTT: Failed to subscribe to: "));
    Serial.println(dd_dc_motor_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish dd_dc_motor Data to MQTT
void dd_dc_motor_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_DD_DC_MOTOR

  Serial.println(F("DD_DC_MOTOR_MQTT: dd_dc_motor_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 113;
  doc_out["unit_name"] = "dd_dc_motor";
  doc_out["cur_hum"] = dd_dc_motor_get_current_hum();
  doc_out["set_point"] = dd_dc_motor_get_setpoint();
  doc_out["ctrl_mode"] = dd_dc_motor_get_mode();
  doc_out["ctrl_out"] = dd_dc_motor_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(dd_dc_motor_mqtt_publish_topic, mqtt_message, true);
#endif
}

//----------------------------------------------------------
// dd_dc_motor MQTT Callback
int dd_dc_motor_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_DD_DC_MOTOR

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, dd_dc_motor_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("DD_DC_MOTOR_MQTT: dd_dc_motor_mqtt_callback"));
    // Serial.print(F("DD_DC_MOTOR_MQTT: Received message on topic: "));
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
      dd_dc_motor_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == DD_DC_MOTOR_DISABLE)
      {
        dd_dc_motor_set_mode_manual();
      }
      else if (mode == DD_DC_MOTOR_ENABLE)
      {
        dd_dc_motor_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == DD_DC_MOTOR_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_DD_DC_MOTOR_ID);
      }
      else if (out == DD_DC_MOTOR_OUT_ON)
      {
        dd_valve_on(DD_VALVE_DD_DC_MOTOR_ID, DD_DC_MOTOR_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("DD_DC_MOTOR_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

