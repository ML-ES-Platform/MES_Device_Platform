#include "ctrl_air_temp_vent.h"
#include "srv_sns_air_temp/srv_sns_air_temp.h"
#include "dd_window/dd_window.h"



float ctrl_air_temp_vent_setpoint = CTRL_AIR_TEMP_VENT_SP_DEFAULT;
int8_t ctrl_air_temp_vent_mode = CTRL_AIR_TEMP_VENT_DISABLE;
int8_t ctrl_air_temp_vent_output = DD_WINDOW_UNKNOWN;


float ctrl_air_temp_vent_set_setpoint(float setpoint)
{
  ctrl_air_temp_vent_setpoint = setpoint;
  return ctrl_air_temp_vent_setpoint;
}

float ctrl_air_temp_vent_get_setpoint()
{
  return ctrl_air_temp_vent_setpoint;
}

float ctrl_air_temp_vent_setpoint_up(float d_val)
{
  float setpoint = ctrl_air_temp_vent_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_air_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_air_temp_vent_setpoint_dn(float d_val)
{
  float setpoint = ctrl_air_temp_vent_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_air_temp_vent_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_air_temp_vent_set_mode(int8_t mode)
{
  if (mode == CTRL_AIR_TEMP_VENT_DISABLE)
  {
    ctrl_air_temp_vent_mode = CTRL_AIR_TEMP_VENT_DISABLE;
  }
  else if (mode == CTRL_AIR_TEMP_VENT_ENABLE)
  {
    ctrl_air_temp_vent_mode = CTRL_AIR_TEMP_VENT_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_air_temp_vent_mode;
}

int8_t ctrl_air_temp_vent_get_mode()
{
  return ctrl_air_temp_vent_mode;
}
int8_t ctrl_air_temp_vent_set_mode_manual()
{
  return ctrl_air_temp_vent_set_mode(CTRL_AIR_TEMP_VENT_DISABLE);
}
int8_t ctrl_air_temp_vent_set_mode_auto()
{
  return ctrl_air_temp_vent_set_mode(CTRL_AIR_TEMP_VENT_ENABLE);
}
int8_t ctrl_air_temp_vent_is_enabled()
{
  return ctrl_air_temp_vent_mode == CTRL_AIR_TEMP_VENT_ENABLE;
}
float ctrl_air_temp_vent_get_current_temp()
{
  return srv_sns_air_get_temperature();
}
int8_t ctrl_air_temp_vent_get_output()
{
  return ctrl_air_temp_vent_output;
}

void ctrl_air_temp_vent_setup()
{
  ctrl_air_temp_vent_setpoint = CTRL_AIR_TEMP_VENT_SP_DEFAULT;
  ctrl_air_temp_vent_mode = CTRL_AIR_TEMP_VENT_DISABLE;
}

void ctrl_air_temp_vent_loop()
{
  if (ctrl_air_temp_vent_mode == CTRL_AIR_TEMP_VENT_ENABLE)
  {
    if (srv_sns_air_get_temperature_error() == 0)
    {
      float temp_current = srv_sns_air_get_temperature();
      float temp_open = ctrl_air_temp_vent_setpoint + CTRL_AIR_TEMP_VENT_HISTERESIS;
      float temp_close = ctrl_air_temp_vent_setpoint - CTRL_AIR_TEMP_VENT_HISTERESIS;

      // OPEN/CLOSE Control cu Histereza
      if (temp_current > temp_open)
      {
        dd_window_open(CTRL_AIR_TEMP_VENT_OP_D_TIME);
      }
      else if (temp_current < temp_close)
      {
        dd_window_close(CTRL_AIR_TEMP_VENT_OP_D_TIME);
      }
      else
      {
        dd_window_stop();
      }
    }
    else
    {
      dd_window_stop();
    }
  }

  int dd_window_state = dd_window_get_state();
  if(dd_window_state == DD_WINDOW_OPEN)
  {
    ctrl_air_temp_vent_output = CTRL_AIR_TEMP_VENT_OUT_OPEN;
  }
  else if(dd_window_state == DD_WINDOW_CLOSE)
  {
    ctrl_air_temp_vent_output = CTRL_AIR_TEMP_VENT_OUT_CLOSE;
  }
  else if(dd_window_state == DD_WINDOW_STOP)
  {
    ctrl_air_temp_vent_output = CTRL_AIR_TEMP_VENT_OUT_STOP;
  }
  else if(dd_window_state == DD_WINDOW_UNKNOWN)
  {
    ctrl_air_temp_vent_output = CTRL_AIR_TEMP_VENT_OUT_UNKNOWN;
  }

}
