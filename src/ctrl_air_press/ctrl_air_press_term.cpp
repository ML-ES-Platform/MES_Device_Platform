#include "ctrl_air_press_term.h"
#include "ctrl_air_press.h"
#include "dd_air_pump/dd_air_pump.h"
#include "Arduino.h"


void ctrl_air_press_report()
{
  if (ctrl_air_press_is_enabled())
  {
    Serial.print(F("CTRL_AIR_PRESS: Mode AUTO"));
  }
  else
  {
    Serial.print(F("CTRL_AIR_PRESS: Mode MANUAL"));
  }

  float press_current = ctrl_air_press_get_current_press();
  Serial.print(F(" | Cur: "));
  Serial.print(press_current,5);
  Serial.print(F(" Bar"));

  float press_setpoint = ctrl_air_press_get_setpoint();
  Serial.print(F(" | SP: "));
  Serial.print(press_setpoint);
  Serial.print(F(" Bar"));

  Serial.print(F(" | HIST [ "));
  Serial.print(press_setpoint + CTRL_AIR_PRESS_HISTERESIS);

  Serial.print(F(" .. "));
  Serial.print(press_setpoint - CTRL_AIR_PRESS_HISTERESIS);
  Serial.print(F(" Bar] "));

    Serial.print(F(" | OUT: "));
    if (ctrl_air_press_get_output() == CTRL_AIR_PRESS_OUT_ON)
    {
      Serial.print(F("ON"));
    }
    else if (ctrl_air_press_get_output() == CTRL_AIR_PRESS_OUT_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }

    Serial.println();

}

void ctrl_air_press_cmd_help()
{
  Serial.println(F("CTRL_AIR_PRESS: Commands:"));
  Serial.println(F(" b - Change mode AUTO/MANUAL"));
  Serial.println(F(" t - Setpoint UP / Air_press ON"));
  Serial.println(F(" g - Setpoint DOWN / Air_press OFF"));
}

void ctrl_air_press_term_cmd(char cmd)
{
  Serial.print(F("CTRL_AIR_PRESS: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      ctrl_air_press_cmd_help();
      break;

    case '`': // report
      ctrl_air_press_report();
      break;

    case 'b': //  manual or automat control
      if (ctrl_air_press_is_enabled())
      { // go to manual control
        Serial.println(F(" CTRL_AIR_PRESS:  Change mode to MANUAL"));
        ctrl_air_press_set_mode_manual();
      }
      else
      { // go to automat control
        Serial.println(F(" CTRL_AIR_PRESS:  Change mode to AUTO"));
        ctrl_air_press_set_mode_auto();
      }
      break;
    case 't': // UP
      if (ctrl_air_press_is_enabled())
      {
        ctrl_air_press_setpoint_up(0.1);
        Serial.print(F("CTRL_AIR_PRESS: Increase Setpoint:"));
        float sp = ctrl_air_press_get_setpoint();
        Serial.println(sp);
      }
      else
      {
       dd_air_pump_on(CTRL_AIR_PRESS_OP_D_TIME);
        Serial.println(F("CTRL_AIR_PRESS: Manual Air_press ON"));
      }
      break;
    case 'g': // Down
      if (ctrl_air_press_is_enabled())
      {
        ctrl_air_press_setpoint_dn(0.1);
        Serial.print(F("CTRL_AIR_PRESS: Decreasing Setpoint:"));
        float sp = ctrl_air_press_get_setpoint();
        Serial.println(sp);
      }
      else
      {
        dd_air_pump_off();
        Serial.println(F(" DD_AIR_PUMP: Air_press OFF"));
      }
      break;
    default:
      Serial.println(F("CTRL_AIR_PRESS: Unknown command"));
      ctrl_air_press_cmd_help();
      break;
  }
}