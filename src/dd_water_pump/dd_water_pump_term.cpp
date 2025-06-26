#include "dd_water_pump_term.h"
#include "dd_water_pump.h"
#include "Arduino.h"


void dd_water_pump_report()
{
  // Air Pump Report

  int water_pump_state = dd_water_pump_get_state();
  Serial.print(F("DD_WATER_PUMP: Water Pump "));
  Serial.print(water_pump_state);
  Serial.print(F(" - "));

  if (water_pump_state == DD_WATER_PUMP_OFF)
  {
    Serial.println(F(" OFF"));
  }
  else if (water_pump_state == DD_WATER_PUMP_ON)
  {
    Serial.println(F(" ON"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}

void dd_water_pump_cmd_help()
{
  Serial.println(F("DD_WATER_PUMP: Commands:"));
  Serial.println(F(" r - Water Pump ON"));
  Serial.println(F(" f - Water Pump OFF"));
  Serial.println();
}

void dd_water_pump_term_cmd(char cmd)
{
  Serial.print(F("DD_WATER_PUMP: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    case '?': // help
      dd_water_pump_cmd_help();
      break;

    case '`': // report
      dd_water_pump_report();
      break;

    case 'r': // UP
      dd_water_pump_on(DD_WATER_PUMP_OP_D_TIME);
      Serial.println(F("DD_WATER_PUMP: Water Pump ON"));
      break;

    case 'f': // Down
      dd_water_pump_off();
      Serial.println(F("DD_WATER_PUMP: Water Pump OFF"));
      break;

    default:
      Serial.print(F("DD_WATER_PUMP: Unknown command: "));
      dd_water_pump_cmd_help();
  }
}


