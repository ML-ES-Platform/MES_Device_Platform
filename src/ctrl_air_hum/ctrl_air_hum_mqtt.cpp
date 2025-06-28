// #include "ctrl_air_hum_term.h"
// #include "ctrl_air_hum.h"
// #include "dd_valve/dd_valve.h"
// #include "Arduino.h"


// //----------------------------------------------------------
// // Publish Air Humidity Control Data to MQTT
// void ctrl_air_hum_mqtt_publish()
// {
// #ifdef USE_CTRL_AIR_HUM
//   float air_hum_ctrl_cur_hum = ctrl_air_hum_get_current_hum();
//   float air_hum_ctrl_sp = ctrl_air_hum_get_setpoint();
//   int air_hum_ctrl_mode = ctrl_air_hum_get_mode();
//   int air_hum_out = ctrl_air_hum_get_output();
//   // JSON mapping
//   doc.clear();
//   doc["sensor_id"] = 333;
//   doc["cur_hum"] = air_hum_ctrl_cur_hum;
//   doc["set_point"] = air_hum_ctrl_sp;
//   doc["ctrl_mode"] = air_hum_ctrl_mode;
//   doc["ctrl_out"] = air_hum_out;

//   // Publishing data throgh MQTT
//   char mqtt_message[128];
//   serializeJson(doc, mqtt_message);
//   mqttClient.publish("microlab/agro/green_house/air_hum_ctrl", mqtt_message, true);
// #endif
// }

// //----------------------------------------------------------
// // Air Humidity Control MQTT Callback
// void ctrl_air_hum_mqtt_callback(char *topic, byte *payload, unsigned int length)
// {
//   #ifdef USE_CTRL_AIR_HUM

//   Serial.println();

//   Serial.println(F("SRV_COM_MQTT: ctrl_air_hum_mqtt_callback"));

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
//     ctrl_air_hum_set_setpoint(value_f);
//   }
//   else if (strcmp(cmd, "ctrl_mode") == 0)
//   {
//     int mode = value_f;
//     if (mode == CTRL_AIR_HUM_DISABLE)
//     {
//       ctrl_air_hum_set_mode_manual();
//     }
//     else if (mode == CTRL_AIR_HUM_ENABLE)
//     {
//       ctrl_air_hum_set_mode_auto();
//     }
//   }
//   else if (strcmp(cmd, "ctrl_out") == 0)
//   {
//     int out = value_f;
//     if (out == CTRL_AIR_HUM_OUT_OFF)
//     {
//       dd_valve_off();
//     }
//     else if (out == CTRL_AIR_HUM_OUT_ON)
//     {
//       dd_valve_on(CTRL_AIR_HUM_OP_D_TIME);
//     }
//   }
//   #endif
// }
