#include "ed_relay_term.h"
#include "ed_relay.h"
#include "Arduino.h"

void ed_relay_report()
{
  // Relay Report
  Serial.print(F("ED_RELAY: Relay "));
  for (size_t relay_it = 0; relay_it < ED_RELAY_NR_OF; relay_it++)
  {
    /* code */
    int relay_state = ed_relay_getState(relay_it);
    int relay_pin = ed_relay_get_pin(relay_it);
    Serial.print(F(" ["));
    Serial.print(relay_it);
    Serial.print(F(":"));
    Serial.print(relay_pin);
    Serial.print(F("]-"));
    if (relay_state == ED_RELAY_ON)
    {
      Serial.print(F("ON"));
    }
    else if (relay_state == ED_RELAY_OFF)
    {
      Serial.print(F("OFF"));
    }
    else
    {
      Serial.print(F("UNKNOWN"));
    }
  }
  Serial.println();
}

void ed_relay_term_cmd(char cmd)
{
  Serial.print(F("ED_RELAY: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {
    // Window control
    case 'z': // stop
      Serial.println(F("DD_RELAY: STOP Command"));
      ed_relay_off(ED_RELAY_ID_1);
      ed_relay_off(ED_RELAY_ID_2);
      break;

    case 'q': // UP
      ed_relay_on(ED_RELAY_ID_1);
      ed_relay_off(ED_RELAY_ID_2);
      Serial.println(F("DD_WINDOW: Window opening"));
      break;

    case 'a': // Down
      ed_relay_off(ED_RELAY_ID_1);
      ed_relay_on(ED_RELAY_ID_2);
      Serial.println(F("ED_RELAY: Window Closing"));
      break;

    // Heater control
    case 'x': // manual or automat control
      Serial.println(F("DD_RELAY: STOP Command"));
      // toggle heater
      if(ed_relay_getState(ED_RELAY_ID_3) == ED_RELAY_ON)
      {
        ed_relay_off(ED_RELAY_ID_3);
        Serial.println(F("ED_RELAY: Toggle Heater OFF"));
      }
      else
      {
        ed_relay_on(ED_RELAY_ID_3);
        Serial.println(F("ED_RELAY: Toggle Heater ON"));
      }
      break;

    case 'w': // UP
      ed_relay_on(ED_RELAY_ID_3);
      Serial.println(F("ED_RELAY: Heater ON"));
      break;

    case 's': // Down
      ed_relay_off(ED_RELAY_ID_3);
      Serial.println(F("ED_RELAY: Heater OFF"));
      break;

    // humidityfier control
    case 'c': // manual or automat control
      Serial.println(F("DD_RELAY: STOP Command"));
      // toggle humidityfier
      if(ed_relay_getState(ED_RELAY_ID_3) == ED_RELAY_ON)
      {
        ed_relay_off(ED_RELAY_ID_3);
        Serial.println(F("ED_RELAY: Toggle Humidityfier OFF"));
      }
      else
      {
        ed_relay_on(ED_RELAY_ID_3);
        Serial.println(F("ED_RELAY: Toggle Humidityfier ON"));
      }

      break;

    case 'e': // UP
      ed_relay_on(ED_RELAY_ID_4);
      Serial.println(F("DD_VALVE: Valve opening"));
      break;

    case 'd': // Down
      ed_relay_off(ED_RELAY_ID_4);
      Serial.println(F("ED_RELAY: Valve Closing"));
      // moisture control
    case 'v': // manual or automat control
      Serial.println(F("DD_RELAY: STOP Command"));
      ed_relay_off(ED_RELAY_ID_5);
      break;

    case 'r': // UP
      ed_relay_on(ED_RELAY_ID_5);
      Serial.println(F("DD_VALVE: Valve opening"));
      break;

    case 'f': // Down
      ed_relay_off(ED_RELAY_ID_5);
      Serial.println(F("ED_RELAY: Valve Closing"));
      break;

    // air pressure control
    case 'b': // manual or automat control
      Serial.println(F("DD_RELAY: STOP Command"));
      ed_relay_off(ED_RELAY_ID_6);
      break;

    case 't': // UP
      ed_relay_on(ED_RELAY_ID_6);
      Serial.println(F("DD_RELAY: Air_pump ON"));
      break;

    case 'g': // Down
      ed_relay_off(ED_RELAY_ID_6);
      Serial.println(F("ED_RELAY: Air_press OFF"));
      break;

    // lights control
    case 'n': // manual or automat control
      Serial.println(F("DD_RELAY: STOP Command"));
      ed_relay_off(ED_RELAY_ID_7);
      break;

    case 'y': // UP
      ed_relay_on(ED_RELAY_ID_7);
      Serial.println(F("DD_LIGHTS: Lights ON"));
      break;

    case 'h': // Down
      ed_relay_off(ED_RELAY_ID_7);
      Serial.println(F("ED_RELAY: Lights OFF"));
      break;

    default:
      break;
  }
}
