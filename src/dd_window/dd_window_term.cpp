#include "dd_window_term.h"
#include "dd_window.h"
#include "Arduino.h"

void dd_window_report()
{
  // Window Report

  int window_state = dd_window_get_state();
  Serial.print(F("DD_WINDOW: Windoe "));
  Serial.print(window_state);
  Serial.print(F(" - "));

  if (window_state == DD_WINDOW_STOP)
  {
    Serial.println(F(" STOP"));
  }
  else if (window_state == DD_WINDOW_CLOSE)
  {
    Serial.println(F(" CLOSE"));
  }
  else if (window_state == DD_WINDOW_OPEN)
  {
    Serial.println(F(" OPRN"));
  }
  else
  {
    Serial.println(F(" UNDEFINED"));
  }
}

void dd_window_cmd_help()
{
  Serial.println(F("DD_WINDOW: Commands:"));
  Serial.println(F(" z - Window STOP"));
  Serial.println(F(" q - Window OPEN"));
  Serial.println(F(" a - Window CLOSE"));
  Serial.println();
}

void dd_window_term_cmd(char cmd)
{
  Serial.print(F("DD_WINDOW: Received command: "));
  Serial.println(cmd);

  switch (cmd)
  {

  case '?': // help
    dd_window_cmd_help();
    break;

  case '`': // report
    dd_window_report();
    break;

  case 'z': //  manual or automat control
    dd_window_stop();
    Serial.println(F("DD_WINDOW: STOP Command"));
    break;

  case 'q': // UP
    dd_window_open(DD_WINDOW_OP_D_TIME);
    Serial.println(F("DD_WINDOW: Window opening"));
    break;

  case 'a': // Down
    dd_window_close(DD_WINDOW_OP_D_TIME);
    Serial.println(F("DD_WINDOW: Window closing"));
    break;

  default:
    Serial.println(F("DD_WINDOW: Unknown command"));
    dd_window_cmd_help();
    break;
  }
}
