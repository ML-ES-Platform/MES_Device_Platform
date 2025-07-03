#include "ctrl_amb_light_mqtt.h"
#include "ctrl_amb_light.h"
#include "dd_lights/dd_lights.h"
#include "Arduino.h"

char ctrl_amb_light_mqtt_subscribe_topic[] = CTRL_AMB_LIGHT_MQTT_SUBSCRIBE_TOPIC;
char ctrl_amb_light_mqtt_publish_topic[] = CTRL_AMB_LIGHT_MQTT_PUBLISH_TOPIC;

//----------------------------------------------------------
// Subscribe to ctrl_amb_light MQTT topic
void ctrl_amb_light_mqtt_subscribe(PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AMB_LIGHT

  Serial.println(F("CTRL_AMB_LIGHT_MQTT: ctrl_amb_light_mqtt_subscribe"));

  if (mqttClient.subscribe(ctrl_amb_light_mqtt_subscribe_topic))
  {
    Serial.print(F("CTRL_AMB_LIGHT_MQTT: Subscribed to: "));
    Serial.println(ctrl_amb_light_mqtt_subscribe_topic);
  }
  else
  {
    Serial.print(F("CTRL_AMB_LIGHT_MQTT: Failed to subscribe to: "));
    Serial.println(ctrl_amb_light_mqtt_subscribe_topic);
  }
#endif
}

//----------------------------------------------------------
// Publish ctrl_amb_light Data to MQTT
void ctrl_amb_light_mqtt_publish(DynamicJsonDocument &doc_out, PubSubClient &mqttClient)
{

#ifdef USE_CTRL_AMB_LIGHT

  Serial.println(F("CTRL_AMB_LIGHT_MQTT: ctrl_amb_light_mqtt_publish"));

  // JSON mapping
  doc_out.clear();
  doc_out["device_id"] = "gh_001";
  doc_out["unit_id"] = 111;
  doc_out["cur_hum"] = ctrl_amb_light_get_current_light();
  doc_out["set_point"] = ctrl_amb_light_get_setpoint();
  doc_out["ctrl_mode"] = ctrl_amb_light_get_mode();
  doc_out["ctrl_out"] = ctrl_amb_light_get_output();

  // Publishing data throgh MQTT
  char mqtt_message[128];
  serializeJson(doc_out, mqtt_message);
  mqttClient.publish(ctrl_amb_light_mqtt_publish_topic, mqtt_message, true);
#endif
}


// //----------------------------------------------------------
// // Publish Lights Control Data to MQTT
// void ctrl_amb_light_mqtt_publish(DynamicJsonDocument &doc, PubSubClient &mqttClient )
// {
// #ifdef USE_CTRL_AMB_LIGHT
//   float light_ctrl_cur_lum = ctrl_amb_light_get_current_light();
//   float light_ctrl_sp = ctrl_amb_light_get_setpoint();
//   int light_ctrl_mode = ctrl_amb_light_get_mode();
//   int light_out = ctrl_amb_light_get_output();
//   // JSON mapping
//   doc.clear();
//   doc["unit_id"] = 666;
//   doc["cur_lum"] = light_ctrl_cur_lum;
//   doc["set_point"] = light_ctrl_sp;
//   doc["ctrl_mode"] = light_ctrl_mode;
//   doc["ctrl_out"] = light_out;

//   // Publishing data throgh MQTT
//   char mqtt_message[128];
//   serializeJson(doc, mqtt_message);
//   mqttClient.publish("microlab/agro/green_house/light_ctrl", mqtt_message, true);
// #endif
// }



//----------------------------------------------------------
// ctrl_amb_light MQTT Callback
int ctrl_amb_light_mqtt_callback(DynamicJsonDocument &doc_in, char *topic, byte *payload, unsigned int length)
{
  int result = 0; // default return value

#ifdef USE_CTRL_AMB_LIGHT

  Serial.println();

  // check if the topic is the one we subscribed to
  if (strcmp(topic, ctrl_amb_light_mqtt_subscribe_topic) == 0)
  {
    result = 1; // set result to 1 if the topic matches

    // Serial.println(F("CTRL_AMB_LIGHT_MQTT: ctrl_amb_light_mqtt_callback"));
    // Serial.print(F("CTRL_AMB_LIGHT_MQTT: Received message on topic: "));
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
      ctrl_amb_light_set_setpoint(value_f);
    }
    else if (strcmp(cmd, "ctrl_mode") == 0)
    {
      int mode = value_f;
      if (mode == CTRL_AMB_LIGHT_DISABLE)
      {
        ctrl_amb_light_set_mode_manual();
      }
      else if (mode == CTRL_AMB_LIGHT_ENABLE)
      {
        ctrl_amb_light_set_mode_auto();
      }
    }
    else if (strcmp(cmd, "ctrl_out") == 0)
    {
      int out = value_f;
      if (out == CTRL_AMB_LIGHT_OUT_OFF)
      {
        dd_lights_off();
      }
      else if (out == CTRL_AMB_LIGHT_OUT_ON)
      {
        dd_lights_on(-1);
      }
    }
  }
  else
  {
    result = 0; // set result to 0 if the topic does not match
    // Serial.print(F("CTRL_AMB_LIGHT_MQTT: Received message on unknown topic: "));
    // Serial.println(topic);
  }
#endif
  return result; // return 1 if the topic matches, otherwise return 0
}

//----------------------------------------------------------
// // Ambient Light Control MQTT Callback
// void ctrl_amb_light_mqtt_callback(char *topic, byte *payload, unsigned int length)
// {
// #ifdef USE_CTRL_AMB_LIGHT

//   Serial.println();

//   Serial.println(F("SRV_COM_MQTT: ctrl_amb_light_mqtt_callback"));

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
//     ctrl_amb_light_set_setpoint(value_f);
//   }
//   else if (strcmp(cmd, "ctrl_mode") == 0)
//   {
//     int mode = value_f;
//     if (mode == CTRL_AMB_LIGHT_DISABLE)
//     {
//       ctrl_amb_light_set_mode_manual();
//     }
//     else if (mode == CTRL_AMB_LIGHT_ENABLE)
//     {
//       ctrl_amb_light_set_mode_auto();
//     }
//   }
//   else if (strcmp(cmd, "ctrl_out") == 0)
//   {
//     int out = value_f;
//     if (out == CTRL_AMB_LIGHT_OUT_OFF)
//     {
//       dd_lights_off();
//     }
//     else if (out == CTRL_AMB_LIGHT_OUT_ON)
//     {
//       dd_lights_on(-1);
//     }
//   }

// }