#include "ctrl_temp_vent_term.h"
#include "ctrl_temp_vent.h"
#include "dd_window/dd_window.h"
#include "Arduino.h"

void ctrl_temp_vent_report()
{
  if (ctrl_temp_vent_get_mode() == CTRL_TEMP_VENT_ENABLE)
  {
    Serial.print(F("CTRL_TEMP_VENT: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_TEMP_VENT: Mode MANUAL"));
  }

  float temp_current = ctrl_temp_vent_get_current_temp();
  Serial.print(F(" | Cur: "));
  Serial.print(temp_current, 5);
  Serial.print(F(" °C"));

  float temp_setpoint = ctrl_temp_vent_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(temp_setpoint);
  Serial.print(F(" °C"));

  Serial.print(F(" | HIST [ "));
  Serial.print(temp_setpoint + CTRL_TEMP_VENT_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(temp_setpoint - CTRL_TEMP_VENT_HISTERESIS);
  Serial.print(F(" °C] "));

  Serial.print(F(" | OUT: "));
  if (ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_OPEN)
  {
    Serial.print(F("OPEN"));
  }
  else if (ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_CLOSE)
  {
    Serial.print(F("CLOSE"));
  }
  else if (ctrl_temp_vent_get_output() == CTRL_TEMP_VENT_OUT_STOP)
  {
    Serial.print(F("STOP"));
  }
  else
  {
    Serial.print(F("UNKNOWN"));
  }
  Serial.println();
}

void ctrl_temp_vent_cmd_help()
{
  Serial.println(F("CTRL_TEMP_VENT: Commands:"));
  Serial.println(F(" z - Change mode AUTO/MANUAL"));
  Serial.println(F(" q - Setpoint UP / Window OPEN"));
  Serial.println(F(" a - Setpoint DOWN / Window CLOSE"));
  Serial.println();
}

void ctrl_temp_vent_term_cmd(char cmd)
{

  Serial.print(F("CTRL_TEMP_VENT: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
  case '?': // help
    ctrl_temp_vent_cmd_help();
    break;

  case '`': // report
    ctrl_temp_vent_report();
    break;

  case 'z': // Change mode AUTO/MANUAL
    if (ctrl_temp_vent_is_enabled())
    { // go to manual control
      Serial.println(F(" CTRL_TEMP_VENT:  Change mode to MANUAL"));
      ctrl_temp_vent_set_mode_manual();
    }
    else
    { // go to automat control
      Serial.println(F(" CTRL_TEMP_VENT:  Change mode to AUTO"));
      ctrl_temp_vent_set_mode_auto();
    }
    break;

  case 'q': // Setpoint UP / Window OPEN
    if (ctrl_temp_vent_is_enabled())
    {
      ctrl_temp_vent_setpoint_up(0.1);
      Serial.print(F("CTRL_TEMP_VENT: Increase Setpoint:"));
      int sp = ctrl_temp_vent_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      dd_window_open(CTRL_TEMP_VENT_OP_D_TIME);
      Serial.println(F("CTRL_TEMP_VENT: Manual Window opening"));
    }
    break;

  case 'a': // Setpoint DOWN / Window CLOSE
    if (ctrl_temp_vent_is_enabled())
    {
      ctrl_temp_vent_setpoint_dn(0.1);
      Serial.print(F("CTRL_TEMP_VENT: Decreasing Setpoint:"));
      int sp = ctrl_temp_vent_get_setpoint();
      Serial.println(sp);
    }
    else
    {
      dd_window_close(CTRL_TEMP_VENT_OP_D_TIME);
      Serial.println(F(" DD_WINDOW: Window Closing"));
    }
    break;

  default:
    Serial.println(F("CTRL_TEMP_VENT: Unknown command"));
    ctrl_temp_vent_cmd_help();
    break;
  }
}
