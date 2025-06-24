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



