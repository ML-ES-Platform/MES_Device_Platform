#include "ctrl_lights_term.h"
#include "ctrl_lights.h"
#include "dd_lights/dd_lights.h"
#include "Arduino.h"

void ctrl_lights_report()
{
  if (ctrl_lights_is_enabled())
  {
    Serial.print(F("CTRL_LIGHTS: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_LIGHTS: Mode MANUAL"));
  }

  float lights_current = ctrl_lights_get_current_light();
  Serial.print(F(" | Cur: "));
  Serial.print(lights_current,5);
  Serial.print(F(" %"));

  float lights_setpoint = ctrl_lights_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(lights_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(lights_setpoint + CTRL_LIGHTS_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(lights_setpoint - CTRL_LIGHTS_HISTERESIS);
  Serial.print(F(" %] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_lights_get_output() == CTRL_LIGHTS_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_lights_get_output() == CTRL_LIGHTS_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}

void ctrl_lights_cmd_help()
{
  Serial.println(F("CTRL_LIGHTS: Commands:"));
  Serial.println(F(" n - Change mode AUTO/MANUAL"));
  Serial.println(F(" y - Setpoint UP / Lights ON")); 
  Serial.println(F(" h - Setpoint DOWN / Lights OFF"));
}

void ctrl_lights_term_cmd(char cmd)
{
  Serial.print(F("CTRL_LIGHTS: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      ctrl_lights_cmd_help();
      break;

    case '`': // report
      ctrl_lights_report();
      break;

    case 'n': // Change mode AUTO/MANUAL
      if (ctrl_lights_is_enabled())
      { // go to manual control
        Serial.println(F(" CTRL_LIGHTS:  Change mode to MANUAL"));
        ctrl_lights_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(F(" CTRL_LIGHTS:  Change mode to AUTO"));
        ctrl_lights_set_mode_auto();
      }
      break;

    case 'y': // Setpoint UP / Lights ON
      if (ctrl_lights_is_enabled())
      {
        ctrl_lights_setpoint_up(0.1);
        Serial.print(F("CTRL_LIGHTS: Increase Setpoint:"));
        int sp = ctrl_lights_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_lights_on(-1);
        Serial.println(F("CTRL_LIGHTS: Manual Lights ON"));
      }
      break;

    case 'h': // Setpoint DOWN / Lights OFF
      if (ctrl_lights_is_enabled())
      {
        ctrl_lights_setpoint_dn(0.1);
        Serial.print(F("CTRL_LIGHTS: Decreasing Setpoint:"));
        int sp = ctrl_lights_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_lights_off();
        Serial.println(F(" DD_LIGHTS: Lights OFF"));
      }
      break;

    default:
      Serial.print(F("CTRL_LIGHTS: Unknown command: "));
      ctrl_lights_cmd_help();
  }
}