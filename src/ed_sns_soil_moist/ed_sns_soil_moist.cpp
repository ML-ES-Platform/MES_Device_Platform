#include <Arduino.h>

#include "ed_sns_soil_moist.h"


float ed_sns_soil_moisture = 0;

float ed_sns_soil_moist_get_value(void)
{
  return ed_sns_soil_moisture;
}


void ed_sns_soil_moist_setup()
{
  
}

void ed_sns_soil_moist_loop()
{
  int moisture = analogRead(ED_SNS_SOIL_MOIST_PIN); // read the analog value from sensor
  ed_sns_soil_moisture = moisture;

  // Serial.print(F("Moisture: "));
  // Serial.println(moisture);

}
