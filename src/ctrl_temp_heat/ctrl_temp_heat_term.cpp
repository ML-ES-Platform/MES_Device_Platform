#include "ctrl_temp_heat_term.h"
#include "ctrl_temp_heat.h"
#include "dd_heater/dd_heater.h"
#include "Arduino.h"

void ctrl_temp_heat_report()
{
  if (ctrl_temp_heat_get_mode() == CTRL_TEMP_HEAT_ENABLE)
  {
    Serial.print(F("CTRL_TEMP_HEAT: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_TEMP_HEAT: Mode MANUAL"));
  }

  float temp_current = ctrl_temp_heat_get_current_temp();
  Serial.print(F(" | Cur: "));
  Serial.print(temp_current, 5);
  Serial.print(F(" °C"));

  float temp_setpoint = ctrl_temp_heat_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F(" °C"));

  Serial.print(F(" | HIST [ "));
  Serial.print(temp_setpoint + CTRL_TEMP_HEAT_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(temp_setpoint - CTRL_TEMP_HEAT_HISTERESIS);
  Serial.print(F(" °C] "));

  Serial.print(F(" | OUT: "));
  if (ctrl_temp_heat_get_output() == CTRL_TEMP_HEAT_OUT_ON)
  {
    Serial.print(F("ON"));
  }
  else if (ctrl_temp_heat_get_output() == CTRL_TEMP_HEAT_OUT_OFF)
  {
    Serial.print(F("OFF"));
  }
  else
  {
    Serial.print(F("UNKNOWN"));
  }

  Serial.println();
}

void ctrl_temp_heat_cmd_help()
{
  Serial.println(F("CTRL_TEMP_HEAT: Commands:"));
  Serial.println(F(" x - Change mode AUTO/MANUAL"));
  Serial.println(F(" w - Setpoint UP / Heater ON"));
  Serial.println(F(" s - Setpoint DOWN / Heater OFF"));
}

void ctrl_temp_heat_term_cmd(char cmd)
{

  Serial.print(F("CTRL_TEMP_HEAT: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
  case '?': // Help
    ctrl_temp_heat_cmd_help();
    break;

  case '`': // Report
    ctrl_temp_heat_report();
    break;

  case 'x': // Change mode AUTO/MANUAL
    if (ctrl_temp_heat_is_enabled())
    {
      Serial.println(F(" CTRL_TEMP_HEAT:  Change mode to MANUAL"));
      ctrl_temp_heat_set_mode_manual();
    }
    else
    {
      Serial.println(F(" CTRL_TEMP_HEAT:  Change mode to AUTO"));
      ctrl_temp_heat_set_mode_auto();
    }
    break;

  case 'w': // Setpoint UP / Heater ON
    if (ctrl_temp_heat_is_enabled())
    {
      ctrl_temp_heat_setpoint_up(0.1);
      Serial.print(F("CTRL_TEMP_HEAT: Increase Setpoint:"));
      float sp = ctrl_temp_heat_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      dd_heater_on(CTRL_TEMP_HEAT_OP_D_TIME);
      Serial.println(F("CTRL_TEMP_HEAT: Manual Heater ON"));
    }
    break;

  case 's': // Setpoint DOWN / Heater OFF
    if (ctrl_temp_heat_is_enabled())
    {
      ctrl_temp_heat_setpoint_dn(0.1);
      Serial.print(F("CTRL_TEMP_HEAT: Decreasing Setpoint:"));
      float sp = ctrl_temp_heat_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      dd_heater_off();
      Serial.println(F(" DD_HEATER: Heater OFF"));
    }
    break;

  default:
    Serial.println(F("CTRL_TEMP_HEAT: Unknown command"));
    ctrl_temp_heat_cmd_help();
    break;
  }
}