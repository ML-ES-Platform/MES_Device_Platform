#include "ctrl_air_hum_term.h"
#include "ctrl_air_hum.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"

void ctrl_air_hum_report()
{
  if (ctrl_air_hum_is_enabled())
  {
    Serial.print(F("CTRL_AIR_HUM: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_AIR_HUM: Mode MANUAL"));
  }

  float hum_current = ctrl_air_hum_get_current_hum();
  Serial.print(F(" | Cur: "));
  Serial.print(hum_current, 5);
  Serial.print(F(" %"));

  float hum_setpoint = ctrl_air_hum_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(hum_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(hum_setpoint + CTRL_AIR_HUM_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(hum_setpoint - CTRL_AIR_HUM_HISTERESIS);
  Serial.print(F(" %] "));

  Serial.print(F(" | OUT: "));
  if (ctrl_air_hum_get_output() == CTRL_AIR_HUM_OUT_ON)
  {
    Serial.print(F("ON"));
  }
  else if (ctrl_air_hum_get_output() == CTRL_AIR_HUM_OUT_OFF)
  {
    Serial.print(F("OFF"));
  }
  else
  {
    Serial.print(F("UNKNOWN"));
  }

  Serial.println();
}

void ctrl_air_hum_cmd_help()
{
  Serial.println(F("CTRL_AIR_HUM: Commands:"));
  Serial.println(F(" c - Change mode AUTO/MANUAL"));
  Serial.println(F(" e - Setpoint UP / Humidifier ON"));
  Serial.println(F(" g - Setpoint DOWN / Humidifier OFF"));
}

void ctrl_air_hum_term_cmd(char cmd)
{
  Serial.print(F("CTRL_AIR_HUM: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
  case '?': // help
    ctrl_air_hum_cmd_help();
    break;

  case '`': // report
    ctrl_air_hum_report();
    break;

  case 'c': //  manual or automat control
    if (ctrl_air_hum_is_enabled())
    { // go to manual control
      Serial.println(F(" CTRL_AIR_HUM:  Change mode to MANUAL"));
      ctrl_air_hum_set_mode_manual();
    }
    else
    { // go to automat control
      Serial.println(F(" CTRL_AIR_HUM:  Change mode to AUTO"));
      ctrl_air_hum_set_mode_auto();
    }
    break;

  case 'e': // UP
    if (ctrl_air_hum_is_enabled())
    {
      ctrl_air_hum_setpoint_up(0.1);
      Serial.print(F("CTRL_AIR_HUM: Increase Setpoint:"));
      float sp = ctrl_air_hum_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      Serial.println(F("CTRL_AIR_HUM: Humidifier ON"));
      dd_valve_on(DD_VALVE_ID_1, CTRL_AIR_HUM_OP_D_TIME);
    }
    break;

  case 'g': // Down
    if (ctrl_air_hum_is_enabled())
    {
      ctrl_air_hum_setpoint_dn(0.1);
      Serial.print(F("CTRL_AIR_HUM: Decreasing Setpoint:"));
      float sp = ctrl_air_hum_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      Serial.println(F("CTRL_AIR_HUM: Humidifier OFF"));
      dd_valve_off(DD_VALVE_ID_1);
    }
    break;

  default:
    Serial.print(F("CTRL_AIR_HUM: Unknown command: "));
    ctrl_air_hum_cmd_help();
  }
}
