#include "srv_sns_soil_moist.h"
#include "ed_sns_soil_moist/ed_sns_soil_moist.h"

float srv_sns_soil_moist_moisture = 0.0;
int srv_sns_soil_moist_moisture_error = 0;


float srv_sns_soil_moist_get_moisture(void)
{
return srv_sns_soil_moist_moisture;
}

int srv_sns_soil_moist_get_moisture_error(void)
{
return srv_sns_soil_moist_moisture_error;
}


void srv_sns_soil_moist_setup()
{

}

void srv_sns_soil_moist_loop()
{

}

