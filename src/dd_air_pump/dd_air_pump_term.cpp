#include "dd_air_pump_term.h"
#include "dd_air_pump.h"
#include "Arduino.h"


void dd_air_pump_report()
{
  // Air Pump Report

  int air_pump_state = dd_air_pump_get_state();
  Serial.print(F("DD_AIR_PUMP: Air Pump "));
  Serial.print(air_pump_state);
  Serial.print(F(" - "));

  if (air_pump_state == DD_AIR_PUMP_OFF)
  {
    Serial.println(F(" OFF"));
  }
  else if (air_pump_state == DD_AIR_PUMP_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}
void dd_air_pump_cmd_help()
{
  Serial.println(F("DD_AIR_PUMP: Commands:"));
  Serial.println(F(" t - Air Pump ON"));
  Serial.println(F(" g - Air Pump OFF"));
  Serial.println(F(" b - Air Pump STOP"));
  Serial.println();
}

void dd_air_pump_term_cmd(char cmd)
{
  Serial.print(F("DD_AIR_PUMP: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      dd_air_pump_cmd_help();
      break;

    case '`': // report
      dd_air_pump_report();
      break;

    case 'b': //  manual or automat control
      dd_air_pump_off();
      Serial.println(F("DD_AIR_PUMP: STOP Command"));
      break;

    case 't': // UP
      dd_air_pump_on(DD_AIR_PUMP_OP_D_TIME);
      Serial.println(F("DD_AIR_PUMP: Air Pump ON"));
      break;

    case 'g': // Down
      dd_air_pump_off();
      Serial.println(F("DD_AIR_PUMP: Air Pump OFF"));
      break;

    default:
      Serial.println(F("DD_AIR_PUMP: Unknown command"));
      dd_air_pump_cmd_help();
      break;
  }
}
