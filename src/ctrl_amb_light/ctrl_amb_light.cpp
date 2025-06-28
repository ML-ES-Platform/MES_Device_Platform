#include "ctrl_amb_light.h"
#include "srv_sns_amb_light/srv_sns_amb_light.h"
#include "dd_lights/dd_lights.h"



float ctrl_amb_light_setpoint = CTRL_AMB_LIGHT_SP_DEFAULT;
int8_t ctrl_amb_light_mode = CTRL_AMB_LIGHT_DISABLE;
int8_t ctrl_amb_light_output = CTRL_AMB_LIGHT_OUT_OFF;

float ctrl_amb_light_set_setpoint(float setpoint)
{
  ctrl_amb_light_setpoint = setpoint;
  return ctrl_amb_light_setpoint;
}

float ctrl_amb_light_get_setpoint()
{
  return ctrl_amb_light_setpoint;
}

float ctrl_amb_light_setpoint_up(float d_val)
{
  float setpoint = ctrl_amb_light_get_setpoint();
  setpoint += d_val;
  setpoint = ctrl_amb_light_set_setpoint(setpoint);
  return setpoint;
}

float ctrl_amb_light_setpoint_dn(float d_val)
{
  float setpoint = ctrl_amb_light_get_setpoint();
  setpoint -= d_val;
  setpoint = ctrl_amb_light_set_setpoint(setpoint);
  return setpoint;
}

int8_t ctrl_amb_light_set_mode(int8_t mode)
{
  if (mode == CTRL_AMB_LIGHT_DISABLE)
  {
    ctrl_amb_light_mode = CTRL_AMB_LIGHT_DISABLE;
  }
  else if (mode == CTRL_AMB_LIGHT_ENABLE)
  {
    ctrl_amb_light_mode = CTRL_AMB_LIGHT_ENABLE;
  }
  else
  {
    return -1;
  }
  return ctrl_amb_light_mode;
}
int8_t ctrl_amb_light_get_mode()
{
  return ctrl_amb_light_mode;
}
int8_t ctrl_amb_light_set_mode_manual()
{
  return ctrl_amb_light_set_mode(CTRL_AMB_LIGHT_DISABLE);
}
int8_t ctrl_amb_light_set_mode_auto()
{
  return ctrl_amb_light_set_mode(CTRL_AMB_LIGHT_ENABLE);
}
int8_t ctrl_amb_light_is_enabled()
{
  return ctrl_amb_light_mode == CTRL_AMB_LIGHT_ENABLE;
}
float ctrl_amb_light_get_current_light()
{
  return srv_sns_amb_get_luminozity();
}
int8_t ctrl_amb_light_get_output()
{
  return ctrl_amb_light_output;
}

void ctrl_amb_light_setup()
{
  ctrl_amb_light_setpoint = CTRL_AMB_LIGHT_SP_DEFAULT;
  ctrl_amb_light_mode = CTRL_AMB_LIGHT_DISABLE;
}

void ctrl_amb_light_loop()
{

  if (ctrl_amb_light_mode == CTRL_AMB_LIGHT_ENABLE)
  {
    if (srv_sns_amb_get_luminozity_error() == 0)
    {

      float light_current = ctrl_amb_light_get_current_light();

      int light_off = ctrl_amb_light_setpoint + CTRL_AMB_LIGHT_HISTERESIS;
      int light_on = ctrl_amb_light_setpoint - CTRL_AMB_LIGHT_HISTERESIS;

      // ON OFF Control cu Histereza
      if (light_current > light_off)
      {
        dd_lights_off();
      }
      else if (light_current < light_on)
      {
        dd_lights_on(CTRL_AMB_LIGHT_OP_D_TIME);
      }
      else
      {
        // do nothing
      }
    }
    else
    {
      dd_lights_off();
    }
  }
  if (dd_lights_get_state() == DD_LIGHTS_ON)
  {
    ctrl_amb_light_output = CTRL_AMB_LIGHT_OUT_ON;
  }
  else
  {
    ctrl_amb_light_output = CTRL_AMB_LIGHT_OUT_OFF;
  }
}
