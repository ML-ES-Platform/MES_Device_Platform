#include "ctrl_air_press_mqtt.h"
#include "ctrl_air_press.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

char ctrl_air_press_mqtt_subscribe_topic[] = CTRL_AIR_PRESS_MQTT_SUBSCRIBE_TOPIC;
char ctrl_air_press_mqtt_publish_topic[] = CTRL_AIR_PRESS_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ctrl_air_press MQTT topic
void ctrl_air_press_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AIR_PRESS

  Serial.println(F("CTRL_AIR_PRESS_MQTT: ctrl_air_press_mqtt_subscribe"));

  if (mqttClient.subscribe(ctrl_air_press_mqtt_subscribe_topic))
  {
    Serial.print(F("CTRL_AIR_PRESS_MQTT: Subscribed to: "));
    Serial.println(ctrl_air_press_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("CTRL_AIR_PRESS_MQTT: Failed to subscribe to: "));
    Serial.println(ctrl_air_press_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ctrl_air_press Data to MQTT
void ctrl_air_press_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AIR_PRESS

  Serial.println(F("CTRL_AIR_PRESS_MQTT: ctrl_air_press_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 111;
  doc_out["cur_press"] = ctrl_air_press_get_current_press();
  doc_out["set_point"] = ctrl_air_press_get_setpoint();
  doc_out["ctrl_mode"] = ctrl_air_press_get_mode();
  doc_out["ctrl_out"] = ctrl_air_press_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ctrl_air_press_mqtt_publish_topic, mqtt_message, true);
#endif
}

// //----------------------------------------------------------
// // Publish Pressure Isolation Control Data to MQTT
// void ctrl_air_press_mqtt_publish(DynamicJsonDocument &doc, PubSubClient &mqttClient )
// {
// #ifdef USE_CTRL_AIR_PRESS
//   float air_press_ctrl_cur_press = ctrl_air_press_get_current_press();
//   float air_press_ctrl_sp = ctrl_air_press_get_setpoint();
//   int air_press_ctrl_mode = ctrl_air_press_get_mode();
//   int air_press_out = ctrl_air_press_get_output();
//   // JSON mapping
//   doc.clear();
//   doc["unit_id"] = 555;
//   doc["cur_press"] = air_press_ctrl_cur_press;
//   doc["set_point"] = air_press_ctrl_sp;
//   doc["ctrl_mode"] = air_press_ctrl_mode;
//   doc["ctrl_out"] = air_press_out;

//   // Publishing data throgh MQTT
//   char mqtt_message[128];
//   serializeJson(doc, mqtt_message);
//   mqttClient.publish("microlab/agro/green_house/air_press_ctrl", mqtt_message, true);
// #endif
// }


//----------------------------------------------------------
// ctrl_air_press MQTT Callback
int ctrl_air_press_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_CTRL_AIR_PRESS

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ctrl_air_press_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("CTRL_AIR_PRESS_MQTT: ctrl_air_press_mqtt_callback"));
    // Serial.print(F("CTRL_AIR_PRESS_MQTT: Received message on topic: "));
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
      ctrl_air_press_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == CTRL_AIR_PRESS_DISABLE)
      {
        ctrl_air_press_set_mode_manual();
      }
      else if (mode == CTRL_AIR_PRESS_ENABLE)
      {
        ctrl_air_press_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == CTRL_AIR_PRESS_OUT_OFF)
      {
        dd_valve_off(DD_VALVE_AIR_HUM_ID);
      }
      else if (out == CTRL_AIR_PRESS_OUT_ON)
      {
        dd_valve_on(DD_VALVE_AIR_HUM_ID, CTRL_AIR_PRESS_OP_D_TIME);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("CTRL_AIR_PRESS_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}


//----------------------------------------------------------
// // Air Pressure Control MQTT Callback
// void ctrl_air_press_mqtt_callback(char *topic, byte *payload, unsigned int length)
// {
// #ifdef USE_CTRL_AIR_PRESS

//   Serial.println();

//   Serial.println(F("SRV_COM_MQTT: ctrl_air_press_mqtt_callback"));

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
//     ctrl_air_press_set_setpoint(value_f);
//   }
//   else if (strcmp(cmd, "ctrl_mode") == 0)
//   {
//     int mode = value_f;
//     if (mode == CTRL_AIR_PRESS_DISABLE)
//     {
//       ctrl_air_press_set_mode_manual();
//     }
//     else if (mode == CTRL_AIR_PRESS_ENABLE)
//     {
//       ctrl_air_press_set_mode_auto();
//     }
//   }
//   else if (strcmp(cmd, "ctrl_out") == 0)
//   {
//     int out = value_f;
//     if (out == CTRL_AIR_PRESS_OUT_OFF)
//     {
//       dd_valve_off(DD_VALVE_AIR_HUM_ID);
//     }
//     else if (out == CTRL_AIR_PRESS_OUT_ON)
//     {
//       dd_valve_on(DD_VALVE_AIR_HUM_ID, CTRL_AIR_PRESS_OP_D_TIME);
//     }
//   }
// #endif
// }
