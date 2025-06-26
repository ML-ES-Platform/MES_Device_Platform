#include "dd_heater_term.h"
#include "dd_heater.h"
#include "Arduino.h"

void dd_heater_report()
{
  // Heater Report

  int heater_state = dd_heater_get_state();
  Serial.print(F("DD_HEATER: Heater "));
  Serial.print(heater_state);
  Serial.print(F(" - "));

  if (heater_state == DD_HEATER_OFF)
  {
    Serial.println(F(" STOP"));
  }
  else if (heater_state == DD_HEATER_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}

void dd_heater_cmd_help()
{
  Serial.println(F("DD_HEATER: Commands:"));
  Serial.println(F(" x - Heater ON/OFF"));
  Serial.println(F(" w - Heater ON"));
  Serial.println(F(" s - Heater OFF"));
  Serial.println();
}

void dd_heater_term_cmd(char cmd)
{
  Serial.print(F("DD_HEATER: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
  case '?': // help
    dd_heater_cmd_help();
    break;
    
  case '`': // report
    dd_heater_report();
    break;

  case 'x': //  stop
    dd_heater_off();
    Serial.println(F("DD_HEATER: STOP Command"));
    break;

  case 'w': // UP
    dd_heater_on(DD_HEATER_OP_D_TIME);
    Serial.println(F("DD_HEATER: Heater ON"));
    break;

  case 's': // Down
    dd_heater_off();
    Serial.println(F("DD_HEATER: Heater OFF"));
    break;

  default:
    Serial.println(F("DD_HEATER: Unknown command"));
    dd_heater_cmd_help();
    break;
  }
}
