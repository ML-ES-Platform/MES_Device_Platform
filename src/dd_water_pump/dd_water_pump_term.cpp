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
