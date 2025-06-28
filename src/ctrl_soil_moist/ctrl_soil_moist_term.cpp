#include "ctrl_soil_moist_term.h"
#include "ctrl_soil_moist.h"
#include "dd_valve/dd_valve.h"
#include "Arduino.h"


void ctrl_soil_moist_report()
{
  if (ctrl_soil_moist_is_enabled())
  {
    Serial.print(F("CTRL_SOIL_MOIST: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_SOIL_MOIST: Mode MANUAL"));
  }

  float moist_current = ctrl_soil_moist_get_current_moist();
  Serial.print(F(" | Cur: "));
  Serial.print(moist_current,5);
  Serial.print(F(" %"));

  float moist_setpoint = ctrl_soil_moist_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(moist_setpoint);
  Serial.print(F(" %"));

  Serial.print(F(" | HIST [ "));
  Serial.print(moist_setpoint + CTRL_SOIL_MOIST_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(moist_setpoint - CTRL_SOIL_MOIST_HISTERESIS);
  Serial.print(F(" %] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_soil_moist_get_output() == CTRL_SOIL_MOIST_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_soil_moist_get_output() == CTRL_SOIL_MOIST_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}

void ctrl_soil_moist_cmd_help()
{
  Serial.println(F("CTRL_SOIL_MOIST: Commands:"));
  Serial.println(F(" v - Change mode AUTO/MANUAL"));
  Serial.println(F(" r - Setpoint UP / Valve ON"));
  Serial.println(F(" f - Setpoint DOWN / Valve OFF"));
}

void ctrl_soil_moist_term_cmd(char cmd)
{
  Serial.print(F("CTRL_SOIL_MOIST: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      ctrl_soil_moist_cmd_help();
      break;

    case '`': // report
      ctrl_soil_moist_report();
      break;

    case 'v': //  manual or automat control
      if (ctrl_soil_moist_is_enabled())
      { // go to manual control
        Serial.println(F(" CTRL_SOIL_MOIST:  Change mode to MANUAL"));
        ctrl_soil_moist_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(F(" CTRL_SOIL_MOIST:  Change mode to AUTO"));
        ctrl_soil_moist_set_mode_auto();
      }
      break;

    case 'r': // UP
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_setpoint_up(0.1);
        Serial.print(F("CTRL_SOIL_MOIST: Increase Threshold:"));
        float threshold = ctrl_soil_moist_get_setpoint();
        Serial.println(threshold);
      }
      else
      {
        dd_valve_on(DD_VALVE_SOIL_MOIST_ID,CTRL_SOIL_MOIST_OP_D_TIME);
        Serial.println(F("CTRL_SOIL_MOIST: Valve opening"));
      }
      break;

    case 'f': // Down
      if (ctrl_soil_moist_is_enabled())
      {
        ctrl_soil_moist_setpoint_dn(0.1);
        Serial.print(F("CTRL_SOIL_MOIST: Decreasing Threshold:"));
        float threshold = ctrl_soil_moist_get_setpoint();
        Serial.println(threshold);
      }
      else
      {
        dd_valve_off(DD_VALVE_SOIL_MOIST_ID);
        Serial.println(F(" DD_VALVE: Valve Closing"));
      }
      break;

    default:
      Serial.print(F("CTRL_SOIL_MOIST: Unknown command: "));
      ctrl_soil_moist_cmd_help();
  }
}



