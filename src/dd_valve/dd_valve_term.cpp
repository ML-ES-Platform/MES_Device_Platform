#include "dd_valve_term.h"
#include "dd_valve.h"
#include "Arduino.h"

void dd_valve_report(){
  Serial.print(F("DD_VALVE: Valve "));
  for (size_t valve_it = 0; valve_it < DD_VALVE_NR_OF; valve_it++)
  {
    int valve_state = dd_valve_get_state(valve_it);
    Serial.print(F(" ["));
    Serial.print(valve_it);
    Serial.print(F("]-"));
    if (valve_state == DD_VALVE_OPEN)
    {
      Serial.print(F("OPEN"));
    }
    else if (valve_state == DD_VALVE_CLOSE)
    {
      Serial.print(F("CLOSE"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }
  }

}


void dd_valve_cmd_help()
{
  Serial.println(F("DD_VALVE: Commands:"));
  Serial.println(F(" r - Valve OPEN"));
  Serial.println(F(" f - Valve CLOSE"));
  Serial.println();
}

void dd_valve_term_cmd(char cmd)
{

  Serial.print(F("DD_VALVE: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {

  case '?': // help
    dd_valve_cmd_help();
    break;

  case '`': // report
    dd_valve_report();
    break;

  case 'r': // UP
    dd_valve_on( DD_VALVE_AIR_HUM_ID, DD_VALVE_OP_D_TIME);
    Serial.println(F("DD_VALVE: Valve opening"));
    break;
  case 'f': // Down
    dd_valve_off(DD_VALVE_AIR_HUM_ID);
    Serial.println(F("DD_VALVE: Valve closing"));
    break;
  default:
    Serial.println(F("DD_VALVE: Unknown command"));
    dd_valve_cmd_help();
    break;
  }
}
