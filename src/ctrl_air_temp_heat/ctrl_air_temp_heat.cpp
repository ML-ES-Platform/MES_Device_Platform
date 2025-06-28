#include "ctrl_air_temp_heat.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_heater/dd_heater.h"

#include "Arduino.h"

float ctrl_air_temp_heat_setpoint = 19.0;
int8_t ctrl_air_temp_heat_mode = CTRL_AIR_TEMP_HEAT_DISABLE;
int8_t ctrl_air_temp_heat_output = CTRL_AIR_TEMP_HEAT_OUT_OFF;

float ctrl_air_temp_heat_set_setpoint(float setpoint)
{
  ctrl_air_temp_heat_setpoint = setpoint;
  return ctrl_air_temp_heat_setpoint;
}

float ctrl_air_temp_heat_get_setpoint()
{
  return ctrl_air_temp_heat_setpoint;
}

float ctrl_air_temp_heat_setpoint_up(float d_val)
{
  float setpoint = ctrl_air_temp_heat_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_air_temp_heat_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_air_temp_heat_setpoint_dn(float d_val)
{
  float setpoint = ctrl_air_temp_heat_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_air_temp_heat_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_air_temp_heat_set_mode(int8_t mode)
{
  if (mode == CTRL_AIR_TEMP_HEAT_DISABLE)
  {
    ctrl_air_temp_heat_mode = CTRL_AIR_TEMP_HEAT_DISABLE;
  }
  else if (mode == CTRL_AIR_TEMP_HEAT_ENABLE)
  {
    ctrl_air_temp_heat_mode = CTRL_AIR_TEMP_HEAT_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_air_temp_heat_mode;
}
int8_t ctrl_air_temp_heat_get_mode()
{
  return ctrl_air_temp_heat_mode;
}
int8_t ctrl_air_temp_heat_set_mode_manual()
{
  return ctrl_air_temp_heat_set_mode(CTRL_AIR_TEMP_HEAT_DISABLE);
}
int8_t ctrl_air_temp_heat_set_mode_auto()
{
  return ctrl_air_temp_heat_set_mode(CTRL_AIR_TEMP_HEAT_ENABLE);
}
int8_t ctrl_air_temp_heat_is_enabled()
{
  return ctrl_air_temp_heat_mode == CTRL_AIR_TEMP_HEAT_ENABLE;
}
float ctrl_air_temp_heat_get_current_temp()
{
  return srv_sns_air_get_temperature();
}
int8_t ctrl_air_temp_heat_get_output()
{
  return ctrl_air_temp_heat_output;
}

void ctrl_air_temp_heat_setup()
{
  ctrl_air_temp_heat_setpoint = 19.0;
  ctrl_air_temp_heat_mode = CTRL_AIR_TEMP_HEAT_DISABLE;
}

void ctrl_air_temp_heat_loop()
{
  if (ctrl_air_temp_heat_mode == CTRL_AIR_TEMP_HEAT_ENABLE)
  {
    if (srv_sns_air_get_temperature_error() == 0)
    {
      float temp_current = srv_sns_air_get_temperature();
      int temp_off = ctrl_air_temp_heat_setpoint + CTRL_AIR_TEMP_HEAT_HISTERESIS;
      int temp_on = ctrl_air_temp_heat_setpoint - CTRL_AIR_TEMP_HEAT_HISTERESIS;

      // ON OFF Control cu Histereza
      if (temp_current > temp_off)
      {
        dd_heater_off();
      }
      else if (temp_current < temp_on)
      {
        dd_heater_on( CTRL_AIR_TEMP_HEAT_OP_D_TIME);
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      dd_heater_off();
    }
  }
  if(dd_heater_get_state() == DD_HEATER_ON)
  {
    ctrl_air_temp_heat_output = CTRL_AIR_TEMP_HEAT_OUT_ON;
  }
  else
  {
    ctrl_air_temp_heat_output = CTRL_AIR_TEMP_HEAT_OUT_OFF;
  } 
}
