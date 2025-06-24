#ifndef ED_SNS_SOIL_MOIST_H_
#define ED_SNS_SOIL_MOIST_H_

#define ED_SNS_SOIL_MOIST_PIN 34   // ADC   // Analog pin connected to the sensor 

void ed_sns_soil_moist_setup();
void ed_sns_soil_moist_loop();

float ed_sns_soil_moist_get_value(void);

#endif