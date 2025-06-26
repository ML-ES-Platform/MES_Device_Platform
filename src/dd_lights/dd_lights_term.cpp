#include "dd_lights_term.h"
#include "dd_lights.h"
#include "Arduino.h"


void dd_lights_report()
{
  // Lights Report

  int lights_state = dd_lights_get_state();
  Serial.print(F("DD_LIGHTS: Lights "));
  Serial.print(lights_state);
  Serial.print(F(" - "));

  if (lights_state == DD_LIGHTS_OFF)
  {
    Serial.println(F(" OFF"));
  }
  else if (lights_state == DD_LIGHTS_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}

void dd_lights_cmd_help()
{
  Serial.println(F("DD_LIGHTS: Commands:"));
  Serial.println(F(" n - Lights Tohgle"));
  Serial.println(F(" y - Lights ON"));
  Serial.println(F(" h - Lights OFF"));
}

void dd_lights_term_cmd(char cmd)
{
  Serial.print(F("DD_LIGHTS: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      dd_lights_cmd_help();
      break;

    case '`': // report
      dd_lights_report();
      break;

    case 'n': // Toggle
      if (dd_lights_get_state() == DD_LIGHTS_ON)
      {
        dd_lights_off();
        Serial.println(F("DD_LIGHTS: Lights OFF"));
      }
      else
      {
        dd_lights_on(-1);
        Serial.println(F("DD_LIGHTS: Lights ON"));
      }
      break;
    case 'y': // UP
      dd_lights_on(-1);
      Serial.println(F("DD_LIGHTS: Lights ON"));
      break;
    case 'h': // Down
      dd_lights_off();
      Serial.println(F("DD_LIGHTS: Lights OFF"));
      break;
    default:
      Serial.print(F("DD_LIGHTS: Unknown command: "));
      dd_lights_cmd_help();
      break;
  }
}
