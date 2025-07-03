#include "ctrl_air_temp_vent_mqtt.h"
#include "ctrl_air_temp_vent.h"
#include "dd_window/dd_window.h"
#include "Arduino.h"

char ctrl_air_temp_vent_mqtt_subscribe_topic[] = CTRL_AIR_TEMP_VENT_MQTT_SUBSCRIBE_TOPIC;
char ctrl_air_temp_vent_mqtt_publish_topic[] = CTRL_AIR_TEMP_VENT_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ctrl_air_temp_vent MQTT topic
void ctrl_air_temp_vent_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AIR_TEMP_VENT

  Serial.println(F("CTRL_AIR_TEMP_VENT_MQTT: ctrl_air_temp_vent_mqtt_subscribe"));

  if (mqttClient.subscribe(ctrl_air_temp_vent_mqtt_subscribe_topic))
  {
    Serial.print(F("CTRL_AIR_TEMP_VENT_MQTT: Subscribed to: "));
    Serial.println(ctrl_air_temp_vent_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("CTRL_AIR_TEMP_VENT_MQTT: Failed to subscribe to: "));
    Serial.println(ctrl_air_temp_vent_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ctrl_air_temp_vent Data to MQTT
void ctrl_air_temp_vent_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AIR_TEMP_VENT

  Serial.println(F("CTRL_AIR_TEMP_VENT_MQTT: ctrl_air_temp_vent_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 105;
  doc_out["unit_name"] = "ctrl_air_temp_vent";
  doc_out["cur_temp"] = ctrl_air_temp_vent_get_current_temp();
  doc_out["set_point"] = ctrl_air_temp_vent_get_setpoint();
  doc_out["ctrl_mode"] = ctrl_air_temp_vent_get_mode();
  doc_out["ctrl_out"] = ctrl_air_temp_vent_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[256];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ctrl_air_temp_vent_mqtt_publish_topic, mqtt_message, true);
#endif
}


//----------------------------------------------------------
// // Publish Temperature Control by Ventilation Data to MQTT
// void ctrl_air_temp_vent_mqtt_publish(DynamicJsonDocument &doc, PubSubClient &mqttClient )
// {
// #ifdef USE_CTRL_AIR_TEMP_VENT
//   float temp_ctrl_cur_temp = ctrl_air_temp_vent_get_current_temp();
//   float temp_ctrl_sp = ctrl_air_temp_vent_get_setpoint();
//   int temp_ctrl_mode = ctrl_air_temp_vent_get_mode();
//   int temp_out = ctrl_air_temp_vent_get_output();
//   // JSON mapping
//   doc.clear();
//   doc["unit_id"] = 111;
//   doc["cur_temp"] = temp_ctrl_cur_temp;
//   doc["set_point"] = temp_ctrl_sp;
//   doc["ctrl_mode"] = temp_ctrl_mode;
//   doc["ctrl_out"] = temp_out;

//   // Publishing data throgh MQTT
//   char mqtt_message[128];
//   serializeJson(doc, mqtt_message);
//   mqttClient.publish("microlab/agro/green_house/temp_vent_ctrl", mqtt_message, true);
// #endif
// }




//----------------------------------------------------------
// ctrl_air_temp_vent MQTT Callback
int ctrl_air_temp_vent_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_CTRL_AIR_TEMP_VENT

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ctrl_air_temp_vent_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("CTRL_AIR_TEMP_VENT_MQTT: ctrl_air_temp_vent_mqtt_callback"));
    // Serial.print(F("CTRL_AIR_TEMP_VENT_MQTT: Received message on topic: "));
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
    // "cmd":"set_point",
    // "value":"17.3"
    // }

    if (strcmp(cmd, "set_point") == 0)
    {
      ctrl_air_temp_vent_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == CTRL_AIR_TEMP_VENT_DISABLE)
      {
        ctrl_air_temp_vent_set_mode_manual();
      }
      else if (mode == CTRL_AIR_TEMP_VENT_ENABLE)
      {
        ctrl_air_temp_vent_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == CTRL_AIR_TEMP_VENT_OUT_OPEN)
      {
        dd_window_open(CTRL_AIR_TEMP_HEAT_OP_D_TIME);
      }
      else if (out == CTRL_AIR_TEMP_VENT_OUT_CLOSE)
      {
        dd_window_close(CTRL_AIR_TEMP_HEAT_OP_D_TIME);
      }
      else if (out == CTRL_AIR_TEMP_VENT_OUT_STOP)
      {
        dd_window_stop();
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("CTRL_AIR_TEMP_VENT_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

//----------------------------------------------------------
// // Temperature Control by Ventilation MQTT Callback
// void ctrl_air_temp_vent_mqtt_callback(char *topic, byte *payload, unsigned int length)
// {
// #ifdef USE_CTRL_AIR_TEMP_VENT

//   Serial.println();

//   Serial.println(F("SRV_COM_MQTT: ctrl_air_temp_vent_mqtt_callback"));

//   deserializeJson(doc_in, (const byte *)payload, length);

//   char cmd[32];
//   strlcpy(cmd, doc_in["cmd"] | "default", sizeof(cmd));

//   Serial.print(F("Command:"));
//   Serial.println(cmd);

//   char value[32];
//   strlcpy(value, doc_in["value"] | "default", sizeof(value));

//   Serial.print(F("Value:"));
//   Serial.println(value);

//   float value_f = atof(value);
//   Serial.print(F("Value_f:"));
//   Serial.println(value_f);

//   // subscribe message example
//   // {
//   // "cmd":"set_point",
//   // "value":"17.3"
//   // }

//   if (strcmp(cmd, "set_point") == 0)
//   {
//     ctrl_air_temp_vent_set_setpoint(value_f);
//   }
//   else if (strcmp(cmd, "ctrl_mode") == 0)
//   {
//     int mode = value_f;
//     if (mode == CTRL_AIR_TEMP_VENT_DISABLE)
//     {
//       ctrl_air_temp_vent_set_mode_manual();
//     }
//     else if (mode == CTRL_AIR_TEMP_VENT_ENABLE)
//     {
//       ctrl_air_temp_vent_set_mode_auto();
//     }
//   }
//   else if (strcmp(cmd, "ctrl_out") == 0)
//   {
//     int out = value_f;
//     if (out == CTRL_AIR_TEMP_VENT_OUT_OPEN)
//     {
//       dd_window_open(CTRL_AIR_TEMP_HEAT_OP_D_TIME);
//     }
//     else if (out == CTRL_AIR_TEMP_VENT_OUT_CLOSE)
//     {
//       dd_window_close(CTRL_AIR_TEMP_HEAT_OP_D_TIME);
//     }
//     else if (out == CTRL_AIR_TEMP_VENT_OUT_STOP)
//     {
//       dd_window_stop();
//     }
//   }
// #endif
// }
